#ifndef TASKSMANAGER_H
#define TASKSMANAGER_H

//true 1 or false 0, to allow critical mission if process mutex is not locked
#define ALLOW_CRITICAL 1
#define DENY_CRITICAL 0

/// This is the Tasks Manager class
///
/// This class Controls the whole board processes, by (xcreate tasks, pause tasks, resume tasks, queue tasks with alternative mutex)
/// @param ALLOW_CRITICAL Preprocess defined boolean always stands for 1
/// @param DENY_CRITICAL Preprocess defined boolean always stands for 0

class TasksManager_class
{
    public:    
        void TasksManager_init();
        void TasksManager_Create_Tasks();
        void TasksManager_Suspend_Tasks();
        void TasksManager_Resume_Tasks();
    private:
    
};


#endif // TASKSMANAGER_H
