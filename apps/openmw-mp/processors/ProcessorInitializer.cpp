#include "ProcessorInitializer.hpp"

#include "Networking.hpp"
#include "Script/Script.hpp"

#include "PlayerProcessor.hpp"
#include "player/ProcessorChatMsg.hpp"
#include "player/ProcessorGUIMessageBox.hpp"
#include "player/ProcessorPlayerCharGen.hpp"
#include "player/ProcessorPlayerAnimFlags.hpp"
#include "player/ProcessorPlayerAnimPlay.hpp"
#include "player/ProcessorPlayerAttack.hpp"
#include "player/ProcessorPlayerAttribute.hpp"
#include "player/ProcessorPlayerBook.hpp"
#include "player/ProcessorPlayerBounty.hpp"
#include "player/ProcessorPlayerCast.hpp"
#include "player/ProcessorPlayerCellChange.hpp"
#include "player/ProcessorPlayerCellState.hpp"
#include "player/ProcessorPlayerCharClass.hpp"
#include "player/ProcessorPlayerDeath.hpp"
#include "player/ProcessorPlayerDisposition.hpp"
#include "player/ProcessorPlayerEquipment.hpp"
#include "player/ProcessorPlayerFaction.hpp"
#include "player/ProcessorPlayerInventory.hpp"
#include "player/ProcessorPlayerItemUse.hpp"
#include "player/ProcessorPlayerJournal.hpp"
#include "player/ProcessorPlayerPlaceholder.hpp"
#include "player/ProcessorPlayerInput.hpp"
#include "player/ProcessorPlayerLevel.hpp"
#include "player/ProcessorPlayerMiscellaneous.hpp"
#include "player/ProcessorPlayerPosition.hpp"
#include "player/ProcessorPlayerQuickKeys.hpp"
#include "player/ProcessorPlayerReputation.hpp"
#include "player/ProcessorPlayerRest.hpp"
#include "player/ProcessorPlayerResurrect.hpp"
#include "player/ProcessorPlayerShapeshift.hpp"
#include "player/ProcessorPlayerSkill.hpp"
#include "player/ProcessorPlayerSpeech.hpp"
#include "player/ProcessorPlayerSpellbook.hpp"
#include "player/ProcessorPlayerSpellsActive.hpp"
#include "player/ProcessorPlayerStatsDynamic.hpp"
#include "player/ProcessorPlayerTopic.hpp"
#include "ActorProcessor.hpp"
#include "actor/ProcessorActorList.hpp"
#include "actor/ProcessorActorTest.hpp"
#include "actor/ProcessorActorAI.hpp"
#include "actor/ProcessorActorAnimFlags.hpp"
#include "actor/ProcessorActorAnimPlay.hpp"
#include "actor/ProcessorActorAttack.hpp"
#include "actor/ProcessorActorCast.hpp"
#include "actor/ProcessorActorCellChange.hpp"
#include "actor/ProcessorActorDeath.hpp"
#include "actor/ProcessorActorEquipment.hpp"
#include "actor/ProcessorActorStatsDynamic.hpp"
#include "actor/ProcessorActorPosition.hpp"
#include "actor/ProcessorActorSpeech.hpp"
#include "ObjectProcessor.hpp"
#include "object/ProcessorConsoleCommand.hpp"
#include "object/ProcessorContainer.hpp"
#include "object/ProcessorDoorState.hpp"
#include "object/ProcessorMusicPlay.hpp"
#include "object/ProcessorObjectActivate.hpp"
#include "object/ProcessorObjectAnimPlay.hpp"
#include "object/ProcessorObjectDelete.hpp"
#include "object/ProcessorObjectHit.hpp"
#include "object/ProcessorObjectPlace.hpp"
#include "object/ProcessorObjectLock.hpp"
#include "object/ProcessorObjectMiscellaneous.hpp"
#include "object/ProcessorObjectMove.hpp"
#include "object/ProcessorObjectRotate.hpp"
#include "object/ProcessorObjectScale.hpp"
#include "object/ProcessorObjectSound.hpp"
#include "object/ProcessorObjectSpawn.hpp"
#include "object/ProcessorObjectState.hpp"
#include "object/ProcessorObjectTrap.hpp"
#include "object/ProcessorClientScriptLocal.hpp"
#include "object/ProcessorScriptMemberShort.hpp"
#include "object/ProcessorVideoPlay.hpp"
#include "WorldstateProcessor.hpp"
#include "worldstate/ProcessorClientScriptGlobal.hpp"
#include "worldstate/ProcessorRecordDynamic.hpp"
#include "worldstate/ProcessorWorldKillCount.hpp"
#include "worldstate/ProcessorWorldMap.hpp"
#include "worldstate/ProcessorWorldWeather.hpp"

using namespace mwmp;

void ProcessorInitializer()
{
    PlayerProcessor::AddProcessor(new ProcessorChatMsg());
    PlayerProcessor::AddProcessor(new ProcessorGUIMessageBox());
    PlayerProcessor::AddProcessor(new ProcessorPlayerCharGen());
    PlayerProcessor::AddProcessor(new ProcessorPlayerAnimFlags());
    PlayerProcessor::AddProcessor(new ProcessorPlayerAnimPlay());
    PlayerProcessor::AddProcessor(new ProcessorPlayerAttack());
    PlayerProcessor::AddProcessor(new ProcessorPlayerAttribute());
    PlayerProcessor::AddProcessor(new ProcessorPlayerBook());
    PlayerProcessor::AddProcessor(new ProcessorPlayerBounty());
    PlayerProcessor::AddProcessor(new ProcessorPlayerCast());
    PlayerProcessor::AddProcessor(new ProcessorPlayerCellChange());
    PlayerProcessor::AddProcessor(new ProcessorPlayerCellState());
    PlayerProcessor::AddProcessor(new ProcessorPlayerCharClass());
    PlayerProcessor::AddProcessor(new ProcessorPlayerDeath());
    PlayerProcessor::AddProcessor(new ProcessorPlayerDisposition());
    PlayerProcessor::AddProcessor(new ProcessorPlayerEquipment());
    PlayerProcessor::AddProcessor(new ProcessorPlayerFaction());
    PlayerProcessor::AddProcessor(new ProcessorPlayerInventory());
    PlayerProcessor::AddProcessor(new ProcessorPlayerItemUse());
    PlayerProcessor::AddProcessor(new ProcessorPlayerJournal());
    PlayerProcessor::AddProcessor(new ProcessorPlayerPlaceholder());
    PlayerProcessor::AddProcessor(new ProcessorPlayerInput());
    PlayerProcessor::AddProcessor(new ProcessorPlayerLevel());
    PlayerProcessor::AddProcessor(new ProcessorPlayerMiscellaneous());
    PlayerProcessor::AddProcessor(new ProcessorPlayerPosition());
    PlayerProcessor::AddProcessor(new ProcessorPlayerQuickKeys());
    PlayerProcessor::AddProcessor(new ProcessorPlayerReputation());
    PlayerProcessor::AddProcessor(new ProcessorPlayerRest());
    PlayerProcessor::AddProcessor(new ProcessorPlayerResurrect());
    PlayerProcessor::AddProcessor(new ProcessorPlayerShapeshift());
    PlayerProcessor::AddProcessor(new ProcessorPlayerSkill());
    PlayerProcessor::AddProcessor(new ProcessorPlayerSpeech());
    PlayerProcessor::AddProcessor(new ProcessorPlayerSpellbook());
    PlayerProcessor::AddProcessor(new ProcessorPlayerSpellsActive());
    PlayerProcessor::AddProcessor(new ProcessorPlayerStatsDynamic());
    PlayerProcessor::AddProcessor(new ProcessorPlayerTopic());

    ActorProcessor::AddProcessor(new ProcessorActorList());
    ActorProcessor::AddProcessor(new ProcessorActorAI());
    ActorProcessor::AddProcessor(new ProcessorActorAnimFlags());
    ActorProcessor::AddProcessor(new ProcessorActorAnimPlay());
    ActorProcessor::AddProcessor(new ProcessorActorAttack());
    ActorProcessor::AddProcessor(new ProcessorActorCast());
    ActorProcessor::AddProcessor(new ProcessorActorCellChange());
    ActorProcessor::AddProcessor(new ProcessorActorDeath());
    ActorProcessor::AddProcessor(new ProcessorActorEquipment());
    ActorProcessor::AddProcessor(new ProcessorActorPosition());
    ActorProcessor::AddProcessor(new ProcessorActorSpeech());
    ActorProcessor::AddProcessor(new ProcessorActorStatsDynamic());
    ActorProcessor::AddProcessor(new ProcessorActorTest());

    ObjectProcessor::AddProcessor(new ProcessorConsoleCommand());
    ObjectProcessor::AddProcessor(new ProcessorContainer());
    ObjectProcessor::AddProcessor(new ProcessorDoorState());
    ObjectProcessor::AddProcessor(new ProcessorMusicPlay());
    ObjectProcessor::AddProcessor(new ProcessorObjectActivate());
    ObjectProcessor::AddProcessor(new ProcessorObjectAnimPlay());
    ObjectProcessor::AddProcessor(new ProcessorObjectDelete());
    ObjectProcessor::AddProcessor(new ProcessorObjectHit());
    ObjectProcessor::AddProcessor(new ProcessorObjectLock());
    ObjectProcessor::AddProcessor(new ProcessorObjectMiscellaneous());
    ObjectProcessor::AddProcessor(new ProcessorObjectMove());
    ObjectProcessor::AddProcessor(new ProcessorObjectPlace());
    ObjectProcessor::AddProcessor(new ProcessorObjectRotate());
    ObjectProcessor::AddProcessor(new ProcessorObjectScale());
    ObjectProcessor::AddProcessor(new ProcessorObjectSound());
    ObjectProcessor::AddProcessor(new ProcessorObjectSpawn());
    ObjectProcessor::AddProcessor(new ProcessorObjectState());
    ObjectProcessor::AddProcessor(new ProcessorObjectTrap());
    ObjectProcessor::AddProcessor(new ProcessorClientScriptLocal());
    ObjectProcessor::AddProcessor(new ProcessorScriptMemberShort());
    ObjectProcessor::AddProcessor(new ProcessorVideoPlay());

    WorldstateProcessor::AddProcessor(new ProcessorClientScriptGlobal());
    WorldstateProcessor::AddProcessor(new ProcessorRecordDynamic());
    WorldstateProcessor::AddProcessor(new ProcessorWorldKillCount());
    WorldstateProcessor::AddProcessor(new ProcessorWorldMap());
    WorldstateProcessor::AddProcessor(new ProcessorWorldWeather());
}
