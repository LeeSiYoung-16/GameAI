#ifndef GOAL_DEFENSE_H
#define GOAL_DEFENSE_H
#pragma warning (disable:4786)

#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"
#include "../Raven_Bot.h"
#include "triggers/trigger.h"


//helper function to change an item type enumeration into a goal type
int ItemTypeToGoalType(int gt);


class Goal_Defense : public Goal_Composite<Raven_Bot>
{
private:
  Trigger<Raven_Bot>*     m_pGiverTrigger;

  //true if a path to the item has been formulated
  bool                    m_bFollowingPath;

  //returns true if the bot sees that the item it is heading for has been
  //picked up by an opponent
  bool hasItemBeenStolen()const;

public:

    Goal_Defense(Raven_Bot* pBot):Goal_Composite<Raven_Bot>(pBot, goal_get_defense),
                                m_pGiverTrigger(0),
                                m_bFollowingPath(false)
  {}


  void Activate();

  int  Process();

  bool HandleMessage(const Telegram& msg);

  void Terminate(){m_iStatus = completed;}
};






#endif
