# Customer-Service-and-Task-Scheduling-Service

## Project Description

The **Customer Service and Task Scheduling System** is a console-based C++ application designed to manage customer service requests and automate task scheduling for service agents. Built using Object-Oriented Programming (OOP) principles, this system simulates a real-world customer service workflow where customer requests are converted into tasks, prioritized, and assigned to available agents based on scheduling algorithms.

The application demonstrates key OOP concepts including encapsulation, inheritance, polymorphism, and abstraction, making it an excellent example for educational purposes, college practicals, viva preparations, and resume projects.

## Features

### Core Functionality
- **User Management**: Add and manage customers and service agents with unique IDs and attributes.
- **Service Request Creation**: Customers can submit service requests with descriptions and priority levels (Low, Medium, High).
- **Automatic Task Generation**: Each service request automatically creates a corresponding task.
- **Task Scheduling**: Two scheduling algorithms available:
  - **First Come First Serve (FCFS)**: Tasks are assigned in the order they are created.
  - **Priority Scheduling**: High-priority tasks are scheduled before lower-priority ones.
- **Agent Assignment**: Tasks are automatically assigned to available service agents.
- **Task Status Management**: Update task status from Pending to In Progress to Completed.
- **Agent Availability Tracking**: Agents' availability is updated when tasks are assigned or completed.
- **Task Reporting**: Display all tasks, pending tasks, or completed tasks with detailed information.

### OOP Concepts Demonstrated
- **Encapsulation**: Private data members with public getter/setter methods.
- **Inheritance**: User base class inherited by Customer and ServiceAgent.
- **Polymorphism**: Runtime polymorphism through virtual functions in the Scheduler abstract class.
- **Abstraction**: Abstract Scheduler class with pure virtual functions, hiding implementation details.

### Technical Features
- **Menu-Driven Interface**: User-friendly console menu for all operations.
- **Data Storage**: Uses STL vectors for in-memory storage (no external databases required).
- **Input Validation**: Basic validation for menu choices and data entry.
- **Clear Console Output**: Formatted output with separators for readability.
- **Modular Code Structure**: Well-organized classes and functions with comments.
- **C++11+ Standards**: Utilizes modern C++ features like enums, auto, and lambda functions.

## How It Works

### Workflow Overview
1. **Setup Phase**: Add customers and service agents to the system.
2. **Request Creation**: Select a customer and create a service request with description and priority.
3. **Task Generation**: The system automatically creates a task from the service request.
4. **Scheduling**: Choose a scheduling algorithm (FCFS or Priority) to assign pending tasks to available agents.
5. **Task Management**: Update task statuses as work progresses.
6. **Reporting**: View tasks by status for monitoring and analysis.

### Class Hierarchy
- **User** (Base Class)
  - Attributes: userId, name
  - Methods: Constructor, getters
- **Customer** (Inherits User)
  - Additional Attributes: contactInfo
  - Methods: Constructor, getter, createServiceRequest()
- **ServiceAgent** (Inherits User)
  - Additional Attributes: specialization, isAvailable
  - Methods: Constructor, getters/setters, assignTask(), updateAvailability()
- **ServiceRequest**
  - Attributes: requestId, description, priority, customerId
- **Task**
  - Attributes: taskId, description, priority, status, assignedAgentId
- **Scheduler** (Abstract Class)
  - Pure Virtual Method: scheduleTask()
- **FCFSScheduler** (Inherits Scheduler)
  - Implements FCFS scheduling logic
- **PriorityScheduler** (Inherits Scheduler)
  - Implements priority-based scheduling with sorting

### Scheduling Algorithms
- **FCFS Scheduler**: Processes tasks in the order they were created, assigning to the first available agent.
- **Priority Scheduler**: Sorts tasks by priority (High > Medium > Low) before assignment, ensuring urgent tasks are handled first.

## Requirements

- **Operating System**: Windows, Linux, or macOS
- **Compiler**: C++11 or later compatible compiler (e.g., g++, clang++, MSVC)
- **Libraries**: Standard C++ libraries (included with compiler)

## Installation and Compilation

1. **Clone or Download**: Place the <ins>customerServiceAndTaskScheduling.cpp</ins> file in your desired directory.

3. **Compile**:
  - **Using g++** (Linux/macOS):
> g++ -std=c++11 [customerServiceAndTaskScheduling.cpp](http://_vscodecontentref_/1) -o customerServiceSystem
  - **Using MSVC** (Windows):
> cl /std:c++11 [customerServiceAndTaskScheduling.cpp](http://_vscodecontentref_/2)

3. **Run**:
  - **Linux/macOS**: ./customerServiceSystem
  - **Windows**: customerServiceSystem.exe

## Usage

### Main Menu Options
1. **Add Customer**: Enter customer name and contact information.
2. **Add Service Agent**: Enter agent name and specialization.
3. **Create Service Request**: Select a customer, enter request description, and choose priority level.
4. **Schedule Tasks**: Choose between FCFS or Priority scheduling to assign pending tasks to available agents.
5. **Update Task Status**: Select a task and change its status (In Progress or Completed).
6. **Display All Tasks**: View all tasks with their details.
7. **Display Pending Tasks**: View only tasks with "Pending" status.
8. **Display Completed Tasks**: View only tasks with "Completed" status.
9. **Exit**: Close the application.

### Example Workflow
1. Add a customer named "Shan Singh" with contact "shansingh@gmail.com".
2. Add a service agent named "Harsh Kasaudhan" specialized in "Technical Support".
3. Create a service request for Shan with description "Computer not starting" and High priority.
4. Schedule tasks using Priority Scheduler.
5. Update the task status to Completed once resolved.

## Code Structure
The application is contained in a single C++ file with the following components:

- **Enums**: **Priority** and **Status** for type safety.
- **Class Definitions**: All OOP classes as specified.
- **Global Variables**: ID counters for automatic ID generation.
- **Utility Functions**: Console clearing, menu display, and string conversions.
- **Main Functions**: CRUD operations for customers, agents, requests, and tasks.
- **Main Loop**: Menu-driven interface with input handling.

<!-- ## Limitations and Future Enhancements
- **Data Persistence**: Currently uses in-memory storage; data is lost on exit.
- **Agent Matching**: No specialization-based task assignment.
- **Concurrency**: Single-threaded; no simultaneous task processing.
- **GUI**: Console-based; could be enhanced with a graphical interface.
- **Database Integration**: Could be extended to use file I/O or databases for persistence.

## Educational Value
This project serves as a comprehensive example of OOP principles in C++ and demonstrates practical application of data structures (vectors), algorithms (sorting), and software design patterns. It's suitable for:

- Computer Science students learning OOP
- Interview preparation for C++ developer roles
- Portfolio projects showcasing coding skills

## License
This project is open-source and available under the MIT License. Feel free to use, modify, and distribute. --!>
