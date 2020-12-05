#include "Trigger_DefenseGiver.h"
#include "misc/Cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include <fstream>
#include "../lua/Raven_Scriptor.h"
#include "../constants.h"
#include "../Raven_ObjectEnumerations.h"


///////////////////////////////////////////////////////////////////////////////
Trigger_DefenseGiver::Trigger_DefenseGiver(std::ifstream& datafile):
      
Trigger_Respawning<Raven_Bot>(GetValueFromStream<int>(datafile))
{
  Read(datafile);
}


void Trigger_DefenseGiver::Try(Raven_Bot* pBot)
{
  if (isActive() && isTouchingTrigger(pBot->Pos(), pBot->BRadius()))
  {
    pBot->IncreaseDefense();

    Deactivate();
  } 
}


void Trigger_DefenseGiver::Render()
{
  if (isActive())
  {
      const int sz = 5;
      gdi->BluePen();
      gdi->Circle(Pos().x, Pos().y, sz + 2);
      gdi->Circle(Pos().x, Pos().y, sz);
  }
}


void Trigger_DefenseGiver::Read(std::ifstream& in)
{
  double x, y, r;
  int GraphNodeIndex;
  
  in >> x >> y  >> r >> m_iDefenseGiven >> GraphNodeIndex;

  SetPos(Vector2D(x,y)); 
  SetBRadius(r);
  SetGraphNodeIndex(GraphNodeIndex);

  //create this trigger's region of fluence
  AddCircularTriggerRegion(Pos(), script->GetDouble("DefaultGiverTriggerRange"));

  SetRespawnDelay((unsigned int)(script->GetDouble("Defense_RespawnDelay") * FrameRate));
  SetEntityType(type_defense);
}
