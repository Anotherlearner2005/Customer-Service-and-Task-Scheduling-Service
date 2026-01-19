#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

// Enums for Priority and Status
enum Priority { Low, Medium, High };
enum Status { Pending, InProgress, Completed };

// Utility function to convert enum to string
std::string priorityToString(Priority p) {
    switch (p) {
        case Low: return "Low";
        case Medium: return "Medium";
        case High: return "High";
        default: return "Unknown";
    }
}

std::string statusToString(Status s) {
    switch (s) {
        case Pending: return "Pending";
        case InProgress: return "In Progress";
        case Completed: return "Completed";
        default: return "Unknown";
    }
}

// Base Class: User
class User {
private:
    int userId;
    std::string name;

public:
    User(int id, const std::string& n) : userId(id), name(n) {}
    int getUserId() const { return userId; }
    std::string getName() const { return name; }
};

// Derived Class: Customer
class Customer : public User {
private:
    std::string contactInfo;

public:
    Customer(int id, const std::string& n, const std::string& contact)
        : User(id, n), contactInfo(contact) {}
    std::string getContactInfo() const { return contactInfo; }
};

// Derived Class: ServiceAgent
class ServiceAgent : public User {
private:
    std::string specialization;
    bool isAvailable;

public:
    ServiceAgent(int id, const std::string& n, const std::string& spec)
        : User(id, n), specialization(spec), isAvailable(true) {}
    std::string getSpecialization() const { return specialization; }
    bool getIsAvailable() const { return isAvailable; }
    void setIsAvailable(bool avail) { isAvailable = avail; }
    void assignTask(int taskId) {
        // Logic to assign task, but since task is separate, just update availability
        setIsAvailable(false);
        std::cout << "Task " << taskId << " assigned to agent " << getName() << std::endl;
    }
};

// Class: ServiceRequest
class ServiceRequest {
private:
    int requestId;
    std::string description;
    Priority priority;
    int customerId;

public:
    ServiceRequest(int id, const std::string& desc, Priority p, int custId)
        : requestId(id), description(desc), priority(p), customerId(custId) {}
    int getRequestId() const { return requestId; }
    std::string getDescription() const { return description; }
    Priority getPriority() const { return priority; }
    int getCustomerId() const { return customerId; }
};

// Class: Task
class Task {
private:
    int taskId;
    std::string description;
    Priority priority;
    Status status;
    int assignedAgentId;

public:
    Task(int id, const std::string& desc, Priority p)
        : taskId(id), description(desc), priority(p), status(Pending), assignedAgentId(-1) {}
    int getTaskId() const { return taskId; }
    std::string getDescription() const { return description; }
    Priority getPriority() const { return priority; }
    Status getStatus() const { return status; }
    int getAssignedAgentId() const { return assignedAgentId; }
    void setStatus(Status s) { status = s; }
    void setAssignedAgentId(int id) { assignedAgentId = id; }
};

// Abstract Class: Scheduler
class Scheduler {
public:
    virtual void scheduleTask(std::vector<Task>& tasks, std::vector<ServiceAgent>& agents) = 0;
    virtual ~Scheduler() {}
};

// Derived Class: FCFSScheduler
class FCFSScheduler : public Scheduler {
public:
    void scheduleTask(std::vector<Task>& tasks, std::vector<ServiceAgent>& agents) override {
        // First Come First Serve: Assign tasks in the order they appear
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

// Derived Class: PriorityScheduler
class PriorityScheduler : public Scheduler {
public:
    void scheduleTask(std::vector<Task>& tasks, std::vector<ServiceAgent>& agents) override {
        // Sort tasks by priority (High first)
        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.getPriority() > b.getPriority();
        });
        // Then assign like FCFS
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

// Global counters for IDs
static int customerIdCounter = 1;
static int agentIdCounter = 1;
static int requestIdCounter = 1;
static int taskIdCounter = 1;

// Function to clear console (Windows specific)
void clearConsole() {
    system("cls");
}

// Function to display menu
void displayMenu() {
    std::cout << "\n=== Customer Service and Task Scheduling System ===\n";
    std::cout << "1. Add Customer\n";
    std::cout << "2. Add Service Agent\n";
    std::cout << "3. Create Service Request\n";
    std::cout << "4. Schedule Tasks\n";
    std::cout << "5. Update Task Status\n";
    std::cout << "6. Display All Tasks\n";
    std::cout << "7. Display Pending Tasks\n";
    std::cout << "8. Display Completed Tasks\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
}

// Function to add customer
void addCustomer(std::vector<Customer>& customers) {
    std::string name, contact;
    std::cout << "Enter customer name: ";
    std::getline(std::cin, name);
    std::cout << "Enter contact info: ";
    std::getline(std::cin, contact);
    customers.emplace_back(customerIdCounter++, name, contact);
    std::cout << "Customer added successfully!\n";
}

// Function to add service agent
void addServiceAgent(std::vector<ServiceAgent>& agents) {
    std::string name, spec;
    std::cout << "Enter agent name: ";
    std::getline(std::cin, name);
    std::cout << "Enter specialization: ";
    std::getline(std::cin, spec);
    agents.emplace_back(agentIdCounter++, name, spec);
    std::cout << "Service agent added successfully!\n";
}

// Function to create service request
void createServiceRequest(std::vector<Customer>& customers, std::vector<ServiceRequest>& requests, std::vector<Task>& tasks) {
    if (customers.empty()) {
        std::cout << "No customers available. Add a customer first.\n";
        return;
    }
    std::cout << "Select customer:\n";
    for (size_t i = 0; i < customers.size(); ++i) {
        std::cout << i + 1 << ". " << customers[i].getName() << std::endl;
    }
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choice < 1 || choice > static_cast<int>(customers.size())) {
        std::cout << "Invalid choice.\n";
        return;
    }
    int custId = customers[choice - 1].getUserId();
    std::string desc;
    std::cout << "Enter request description: ";
    std::getline(std::cin, desc);
    std::cout << "Enter priority (0-Low, 1-Medium, 2-High): ";
    int p;
    std::cin >> p;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Priority pri = static_cast<Priority>(p);
    requests.emplace_back(requestIdCounter++, desc, pri, custId);
    tasks.emplace_back(taskIdCounter++, desc, pri);
    std::cout << "Service request and task created successfully!\n";
}

// Function to schedule tasks
void scheduleTasks(std::vector<Task>& tasks, std::vector<ServiceAgent>& agents) {
    if (tasks.empty()) {
        std::cout << "No tasks to schedule.\n";
        return;
    }
    std::cout << "Select scheduler:\n";
    std::cout << "1. FCFS Scheduler\n";
    std::cout << "2. Priority Scheduler\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Scheduler* scheduler = nullptr;
    if (choice == 1) {
        scheduler = new FCFSScheduler();
    } else if (choice == 2) {
        scheduler = new PriorityScheduler();
    } else {
        std::cout << "Invalid choice.\n";
        return;
    }
    scheduler->scheduleTask(tasks, agents);
    delete scheduler;
    std::cout << "Tasks scheduled successfully!\n";
}

// Function to update task status
void updateTaskStatus(std::vector<Task>& tasks, std::vector<ServiceAgent>& agents) {
    if (tasks.empty()) {
        std::cout << "No tasks available.\n";
        return;
    }
    std::cout << "Select task to update:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". Task " << tasks[i].getTaskId() << " - " << statusToString(tasks[i].getStatus()) << std::endl;
    }
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choice < 1 || choice > static_cast<int>(tasks.size())) {
        std::cout << "Invalid choice.\n";
        return;
    }
    Task& task = tasks[choice - 1];
    std::cout << "Current status: " << statusToString(task.getStatus()) << std::endl;
    std::cout << "Enter new status (1-In Progress, 2-Completed): ";
    int s;
    std::cin >> s;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Status newStatus = static_cast<Status>(s);
    task.setStatus(newStatus);
    if (newStatus == Completed) {
        // Find agent and set available
        for (auto& agent : agents) {
            if (agent.getUserId() == task.getAssignedAgentId()) {
                agent.setIsAvailable(true);
                break;
            }
        }
    }
    std::cout << "Task status updated!\n";
}

// Function to display tasks
void displayTasks(const std::vector<Task>& tasks, Status filter = Pending) {
    bool all = (filter == Pending); // If filter is Pending, show all
    for (const auto& task : tasks) {
        if (all || task.getStatus() == filter) {
            std::cout << "Task ID: " << task.getTaskId() << "\n";
            std::cout << "Description: " << task.getDescription() << "\n";
            std::cout << "Priority: " << priorityToString(task.getPriority()) << "\n";
            std::cout << "Status: " << statusToString(task.getStatus()) << "\n";
            std::cout << "Assigned Agent ID: " << (task.getAssignedAgentId() == -1 ? "None" : std::to_string(task.getAssignedAgentId())) << "\n";
            std::cout << "------------------------\n";
        }
    }
}

int main() {
    std::vector<Customer> customers;
    std::vector<ServiceAgent> agents;
    std::vector<ServiceRequest> requests;
    std::vector<Task> tasks;

    int choice;
    do {
        clearConsole();
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
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
                std::cout << "\nAll Tasks:\n";
                displayTasks(tasks, Pending); // Show all by passing Pending as dummy
                break;
            case 7:
                std::cout << "\nPending Tasks:\n";
                displayTasks(tasks, Pending);
                break;
            case 8:
                std::cout << "\nCompleted Tasks:\n";
                displayTasks(tasks, Completed);
                break;
            case 9:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
        if (choice != 9) {
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    } while (choice != 9);

    return 0;
}