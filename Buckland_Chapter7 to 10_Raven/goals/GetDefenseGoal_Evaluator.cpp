#include "GetDefenseGoal_Evaluator.h"
#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include "../Raven_ObjectEnumerations.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"


#include "debug/DebugConsole.h"


double GetDefenseGoal_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
    double Distance = Raven_Feature::DistanceToItem(pBot, type_defense);

    if (Distance == 1)
    {
        return 0;
    }
    else
    {
        const double Tweaker = 0.2;

        double Desirability = Tweaker * (1 - Raven_Feature::Defense(pBot)) /
            (Raven_Feature::DistanceToItem(pBot, type_defense));

        Clamp(Desirability, 0, 1);

        Desirability *= m_dCharacterBias;

        return Desirability;
    }
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void GetDefenseGoal_Evaluator::SetGoal(Raven_Bot* pBot)
{
  pBot->GetBrain()->AddGoal_GetItem(type_defense);
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void GetDefenseGoal_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
    std::string s = "Df";
    gdi->TextAtPos(Position, s + ttos(CalculateDesirability(pBot), 2));
}