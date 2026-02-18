#include<bits/stdc++.h>
using namespace std;

enum Priority { Low, Medium, High };
enum Status { Pending, InProgress, Completed };

string priorityToString(Priority p) {
    switch (p) {
        case Low: return "Low";
        case Medium: return "Medium";
        case High: return "High";
        default: return "Unknown";
    }
}

string statusToString(Status s) {
    switch (s) {
        case Pending: return "Pending";
        case InProgress: return "In Progress";
        case Completed: return "Completed";
        default: return "Unknown";
    }
}

class User {
private:
    int userId;
    string name;

public:
    User(int id, const string& n) : userId(id), name(n) {}
    int getUserId() const { return userId; }
    string getName() const { return name; }
};

class Customer : public User {
private:
    string contactInfo;

public:
    Customer(int id, const string& n, const string& contact)
        : User(id, n), contactInfo(contact) {}
    string getContactInfo() const { return contactInfo; }
};

class ServiceAgent : public User {
private:
    string specialization;
    bool isAvailable;

public:
    ServiceAgent(int id, const string& n, const string& spec)
        : User(id, n), specialization(spec), isAvailable(true) {}
    string getSpecialization() const { return specialization; }
    bool getIsAvailable() const { return isAvailable; }
    void setIsAvailable(bool avail) { isAvailable = avail; }
    void assignTask(int taskId) {
        // Logic to assign task, but since task is separate, just update availability
        setIsAvailable(false);
        cout << "Task " << taskId << " assigned to agent " << getName() << endl;
    }
};

class ServiceRequest {
private:
    int requestId;
    string description;
    Priority priority;
    int customerId;

public:
    ServiceRequest(int id, const string& desc, Priority p, int custId)
        : requestId(id), description(desc), priority(p), customerId(custId) {}
    int getRequestId() const { return requestId; }
    string getDescription() const { return description; }
    Priority getPriority() const { return priority; }
    int getCustomerId() const { return customerId; }
};

class Task {
private:
    int taskId;
    string description;
    Priority priority;
    Status status;
    int assignedAgentId;

public:
    Task(int id, const string& desc, Priority p)
        : taskId(id), description(desc), priority(p), status(Pending), assignedAgentId(-1) {}
    int getTaskId() const { return taskId; }
    string getDescription() const { return description; }
    Priority getPriority() const { return priority; }
    Status getStatus() const { return status; }
    int getAssignedAgentId() const { return assignedAgentId; }
    void setStatus(Status s) { status = s; }
    void setAssignedAgentId(int id) { assignedAgentId = id; }
};

class Scheduler {
public:
    virtual void scheduleTask(vector<Task>& tasks, vector<ServiceAgent>& agents) = 0;
    virtual ~Scheduler() {}
};

class FCFSScheduler : public Scheduler {
public:
    void scheduleTask(vector<Task>& tasks, vector<ServiceAgent>& agents) override {
        for (auto& task : tasks) {
            if (task.getStatus() == Pending) {
                for (auto& agent : agents) {
                    if (agent.getIsAvailable()) {
                        task.setAssignedAgentId(agent.getUserId());
                        task.setStatus(InProgress);
                        agent.assignTask(task.getTaskId());
                        break;
                    }
                }
            }
        }
    }
};

class PriorityScheduler : public Scheduler {
public:
    void scheduleTask(vector<Task>& tasks, vector<ServiceAgent>& agents) override {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.getPriority() > b.getPriority();
        });
        for (auto& task : tasks) {
            if (task.getStatus() == Pending) {
                for (auto& agent : agents) {
                    if (agent.getIsAvailable()) {
                        task.setAssignedAgentId(agent.getUserId());
                        task.setStatus(InProgress);
                        agent.assignTask(task.getTaskId());
                        break;
                    }
                }
            }
        }
    }
};

static int customerIdCounter = 1;
static int agentIdCounter = 1;
static int requestIdCounter = 1;
static int taskIdCounter = 1;

void clearConsole() {
    system("cls");
}

void displayMenu() {
    cout << "\n=== Customer Service and Task Scheduling System ===\n";
    cout << "1. Add Customer\t        ";
    cout << "2. Add Service Agent\t   ";
    cout << "3. Create Service Request\t   ";
    cout << "4. Schedule Tasks\n";
    cout << "5. Update Task Status\t";
    cout << "6. Display All Tasks\t   ";
    cout << "7. Display Pending Tasks\t   ";
    cout << "8. Display Completed Tasks\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

void addCustomer(vector<Customer>& customers) {
    string name, contact;
    cout << "Enter customer name: ";
    getline(cin, name);
    cout << "Enter contact info: ";
    getline(cin, contact);
    customers.emplace_back(customerIdCounter++, name, contact);
    cout << "Customer added successfully!\n";
}

void addServiceAgent(vector<ServiceAgent>& agents) {
    string name, spec;
    cout << "Enter agent name: ";
    getline(cin, name);
    cout << "Enter specialization: ";
    getline(cin, spec);
    agents.emplace_back(agentIdCounter++, name, spec);
    cout << "Service agent added successfully!\n";
}

void createServiceRequest(vector<Customer>& customers, vector<ServiceRequest>& requests, vector<Task>& tasks) {
    if (customers.empty()) {
        cout << "No customers available. Add a customer first.\n";
        return;
    }
    cout << "Select customer:\n";
    for (size_t i = 0; i < customers.size(); ++i) {
        cout << i + 1 << ". " << customers[i].getName() << endl;
    }
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choice < 1 || choice > static_cast<int>(customers.size())) {
        cout << "Invalid choice.\n";
        return;
    }
    int custId = customers[choice - 1].getUserId();
    string desc;
    cout << "Enter request description: ";
    getline(cin, desc);
    cout << "Enter priority (0-Low, 1-Medium, 2-High): ";
    int p;
    cin >> p;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Priority pri = static_cast<Priority>(p);
    requests.emplace_back(requestIdCounter++, desc, pri, custId);
    tasks.emplace_back(taskIdCounter++, desc, pri);
    cout << "Service request and task created successfully!\n";
}

void scheduleTasks(vector<Task>& tasks, vector<ServiceAgent>& agents) {
    if (tasks.empty()) {
        cout << "No tasks to schedule.\n";
        return;
    }
    cout << "Select scheduler:\n";
    cout << "1. FCFS Scheduler\n";
    cout << "2. Priority Scheduler\n";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Scheduler* scheduler = nullptr;
    if (choice == 1) {
        scheduler = new FCFSScheduler();
    } else if (choice == 2) {
        scheduler = new PriorityScheduler();
    } else {
        cout << "Invalid choice.\n";
        return;
    }
    scheduler->scheduleTask(tasks, agents);
    delete scheduler;
    cout << "Tasks scheduled successfully!\n";
}

void updateTaskStatus(vector<Task>& tasks, vector<ServiceAgent>& agents) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }
    cout << "Select task to update:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". Task " << tasks[i].getTaskId() << " - " << statusToString(tasks[i].getStatus()) << endl;
    }
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choice < 1 || choice > static_cast<int>(tasks.size())) {
        cout << "Invalid choice.\n";
        return;
    }
    Task& task = tasks[choice - 1];
    cout << "Current status: " << statusToString(task.getStatus()) << endl;
    cout << "Enter new status (1-In Progress, 2-Completed): ";
    int s;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Status newStatus = static_cast<Status>(s);
    task.setStatus(newStatus);
    if (newStatus == Completed) {
        for (auto& agent : agents) {
            if (agent.getUserId() == task.getAssignedAgentId()) {
                agent.setIsAvailable(true);
                break;
            }
        }
    }
    cout << "Task status updated!\n";
}

void displayTasks(const vector<Task>& tasks, Status filter = InProgress) {
    bool showAll = (filter == InProgress); 
    bool found = false;

    const int widthId = 8;
    const int widthDesc = 32;
    const int widthPri = 10;
    const int widthStatus = 15;
    const int widthAgent = 12;
    int totalWidth = widthId + widthDesc + widthPri + widthStatus + widthAgent;

    cout << left << setw(widthId) << "TaskID" << setw(widthDesc) << "Description" << setw(widthPri) << "Priority" << setw(widthStatus) << "Status" << setw(widthAgent) << "AgentID" << endl;
    cout << string(totalWidth, '-') << endl;
    for (const auto& task : tasks) {
        if (showAll || task.getStatus() == filter) {
            found = true;
            string agent = (task.getAssignedAgentId() == -1 ? "None" : to_string(task.getAssignedAgentId()));
            string desc = task.getDescription();
            if (static_cast<int>(desc.length()) > widthDesc - 2) desc = desc.substr(0, widthDesc - 5) + "...";
            cout << setw(widthId) << task.getTaskId()
                 << setw(widthDesc) << desc
                 << setw(widthPri) << priorityToString(task.getPriority())
                 << setw(widthStatus) << statusToString(task.getStatus())
                 << setw(widthAgent) << agent << endl;
            cout << string(totalWidth, '-') << endl;
        }
    }
    if(!found){
        cout << "No such task available!"<< endl;
        cout << string(totalWidth, '-') << endl;
    }
}

int main() {
    vector<Customer> customers;
    vector<ServiceAgent> agents;
    vector<ServiceRequest> requests;
    vector<Task> tasks;

    int choice;
    do {
        clearConsole();
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        switch (choice) {
            case 1:
                addCustomer(customers);
                break;
            case 2:
                addServiceAgent(agents);
                break;
            case 3:
                createServiceRequest(customers, requests, tasks);
                break;
            case 4:
                scheduleTasks(tasks, agents);
                break;
            case 5:
                updateTaskStatus(tasks, agents);
                break;
            case 6:
                cout << "\nAll Tasks:\n";
                displayTasks(tasks); 
                break;
            case 7:
                cout << "\nPending Tasks:\n";
                displayTasks(tasks, Pending);
                break;
            case 8:
                cout << "\nCompleted Tasks:\n";
                displayTasks(tasks, Completed);
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
        if (choice != 9) {
            cout << "Press Enter to continue...";
            cin.get();
        }
    } while (choice != 9);

    return 0;
}