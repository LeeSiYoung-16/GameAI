#ifndef DEFENSE_GIVER_H
#define DEFENSE_GIVER_H
#pragma warning (disable:4786)


#include "Triggers/Trigger_Respawning.h"
#include "Triggers/TriggerRegion.h"
#include <iosfwd>
#include "../Raven_Bot.h"



class Trigger_DefenseGiver : public Trigger_Respawning<Raven_Bot>
{
private:

  //the amount of health an entity receives when it runs over this trigger
  int   m_iDefenseGiven;
  
public:

  Trigger_DefenseGiver(std::ifstream& datafile);

  //if triggered, the bot's health will be incremented
  void Try(Raven_Bot* pBot);
  
  //draws a box with a red cross at the trigger's location
  void Render();

  void Read (std::ifstream& is);
};



#endif