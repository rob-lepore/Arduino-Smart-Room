#include "Scheduler.h"

volatile bool ready = false;
void step()
{
    ready = true;
}

void Scheduler::init(int basePeriod)
{
    this->basePeriod = basePeriod;
    // tick every basePeriod milliseconds
    unsigned long period = basePeriod * 1000UL;
    Timer1.initialize(period);
    Timer1.attachInterrupt(step);
    nTasks = 0;
}

bool Scheduler::addTask(Task *task)
{
    if (nTasks < MAX_TASKS - 1)
    {
        taskList[nTasks] = task;
        nTasks++;
        return true;
    }
    else
    {
        return false;
    }
}

void Scheduler::schedule()
{
    while(!ready){}
    ready = false;
    
    for (int i = 0; i < nTasks; i++)
    {
        if (taskList[i]->updateAndCheckTime(basePeriod))
        {
            taskList[i]->tick();
        }
    }
    

}