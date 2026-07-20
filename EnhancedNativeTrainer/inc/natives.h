#pragma once

#include "types.h"
#include "nativeCaller.h"

// Generated Sun, 19 Jul 2026 10:47:17 GMT
// https://alloc8or.re/gta5/nativedb/

#ifndef NATIVE_DECL
#if defined(_MSC_VER)
	#define NATIVE_DECL static __forceinline
#elif defined(__clang__) || defined(__GNUC__)
	#define NATIVE_DECL static __attribute__((always_inline)) inline
#else
	#define NATIVE_DECL static inline
#endif
#endif

namespace BUILTIN
{
	NATIVE_DECL void WAIT(int ms) { invoke<Void>(0x4EDE34FBADD967A6, ms); }
	NATIVE_DECL int START_NEW_SCRIPT(const char* scriptName, int stackSize) { return invoke<int>(0xE81651AD79516E48, scriptName, stackSize); }
	NATIVE_DECL int START_NEW_SCRIPT_WITH_ARGS(const char* scriptName, Any* args, int argCount, int stackSize) { return invoke<int>(0xB8BA7F44DF1575E1, scriptName, args, argCount, stackSize); }
	NATIVE_DECL int START_NEW_SCRIPT_WITH_NAME_HASH(Hash scriptHash, int stackSize) { return invoke<int>(0xEB1C67C3A5333A92, scriptHash, stackSize); }
	NATIVE_DECL int START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(Hash scriptHash, Any* args, int argCount, int stackSize) { return invoke<int>(0xC4BB298BD441BE78, scriptHash, args, argCount, stackSize); }
	NATIVE_DECL int TIMERA() { return invoke<int>(0x83666F9FB8FEBD4B); }
	NATIVE_DECL int TIMERB() { return invoke<int>(0xC9D9444186B5A374); }
	NATIVE_DECL void SETTIMERA(int value) { invoke<Void>(0xC1B1E9A034A63A62, value); }
	NATIVE_DECL void SETTIMERB(int value) { invoke<Void>(0x5AE11BC36633DE4E, value); }
	NATIVE_DECL float TIMESTEP() { return invoke<float>(0x0000000050597EE2); }
	NATIVE_DECL float SIN(float value) { return invoke<float>(0x0BADBFA3B172435F, value); }
	NATIVE_DECL float COS(float value) { return invoke<float>(0xD0FFB162F40A139C, value); }
	NATIVE_DECL float SQRT(float value) { return invoke<float>(0x71D93B57D07F9804, value); }
	NATIVE_DECL float POW(float base, float exponent) { return invoke<float>(0xE3621CC40F31FE2E, base, exponent); }
	NATIVE_DECL float LOG10(float value) { return invoke<float>(0xE816E655DE37FE20, value); }
	NATIVE_DECL float VMAG(float x, float y, float z) { return invoke<float>(0x652D2EEEF1D3E62C, x, y, z); }
	NATIVE_DECL float VMAG2(float x, float y, float z) { return invoke<float>(0xA8CEACB4F35AE058, x, y, z); }
	NATIVE_DECL float VDIST(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<float>(0x2A488C176D52CCA5, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL float VDIST2(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<float>(0xB7A628320EFF8E47, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL int SHIFT_LEFT(int value, int bitShift) { return invoke<int>(0xEDD95A39E5544DE8, value, bitShift); }
	NATIVE_DECL int SHIFT_RIGHT(int value, int bitShift) { return invoke<int>(0x97EF1E5BCE9DC075, value, bitShift); }
	NATIVE_DECL int FLOOR(float value) { return invoke<int>(0xF34EE736CF047844, value); }
	NATIVE_DECL int CEIL(float value) { return invoke<int>(0x11E019C8F43ACC8A, value); }
	NATIVE_DECL int ROUND(float value) { return invoke<int>(0xF2DB717A73826179, value); }
	NATIVE_DECL float TO_FLOAT(int value) { return invoke<float>(0xBBDA792448DB5A89, value); }
	NATIVE_DECL void SET_THIS_THREAD_PRIORITY(int priority) { invoke<Void>(0x42B65DEEF2EDF2A1, priority); }
}

namespace APPS
{
	NATIVE_DECL BOOL APP_DATA_VALID() { return invoke<BOOL>(0x846AA8E7D55EE5B6); }
	NATIVE_DECL int APP_GET_INT(const char* property) { return invoke<int>(0xD3A58A12C77D9D4B, property); }
	NATIVE_DECL float APP_GET_FLOAT(const char* property) { return invoke<float>(0x1514FB24C02C2322, property); }
	NATIVE_DECL const char* APP_GET_STRING(const char* property) { return invoke<const char*>(0x749B023950D2311C, property); }
	NATIVE_DECL void APP_SET_INT(const char* property, int value) { invoke<Void>(0x607E8E3D3E4F9611, property, value); }
	NATIVE_DECL void APP_SET_FLOAT(const char* property, float value) { invoke<Void>(0x25D7687C68E0DAA4, property, value); }
	NATIVE_DECL void APP_SET_STRING(const char* property, const char* value) { invoke<Void>(0x3FF2FCEC4B7721B4, property, value); }
	NATIVE_DECL void APP_SET_APP(const char* appName) { invoke<Void>(0xCFD0406ADAF90D2B, appName); }
	NATIVE_DECL void APP_SET_BLOCK(const char* blockName) { invoke<Void>(0x262AB456A3D21F93, blockName); }
	NATIVE_DECL void APP_CLEAR_BLOCK() { invoke<Void>(0x5FE1DF3342DB7DBA); }
	NATIVE_DECL void APP_CLOSE_APP() { invoke<Void>(0xE41C65E07A5F05FC); }
	NATIVE_DECL void APP_CLOSE_BLOCK() { invoke<Void>(0xE8E3FCF72EAC0EF8); }
	NATIVE_DECL BOOL APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT() { return invoke<BOOL>(0x71EEE69745088DA0); }
	NATIVE_DECL BOOL APP_HAS_SYNCED_DATA(const char* appName) { return invoke<BOOL>(0xCA52279A7271517F, appName); }
	NATIVE_DECL void APP_SAVE_DATA() { invoke<Void>(0x95C5D356CDA6E85F); }
	NATIVE_DECL int APP_GET_DELETED_FILE_STATUS() { return invoke<int>(0xC9853A2BE3DED1A6); }
	NATIVE_DECL BOOL APP_DELETE_APP_DATA(const char* appName) { return invoke<BOOL>(0x44151AEA95C8A003, appName); }
}

namespace AUDIO
{
	NATIVE_DECL void PLAY_PED_RINGTONE(const char* ringtoneName, Ped ped, BOOL p2) { invoke<Void>(0xF9E56683CA8E11A5, ringtoneName, ped, p2); }
	NATIVE_DECL BOOL IS_PED_RINGTONE_PLAYING(Ped ped) { return invoke<BOOL>(0x1E8E5E20937E3137, ped); }
	NATIVE_DECL void STOP_PED_RINGTONE(Ped ped) { invoke<Void>(0x6C5AE23EFA885092, ped); }
	NATIVE_DECL BOOL IS_MOBILE_PHONE_CALL_ONGOING() { return invoke<BOOL>(0x7497D2CE2C30D24C); }
	NATIVE_DECL BOOL IS_MOBILE_INTERFERENCE_ACTIVE() { return invoke<BOOL>(0xC8B1B2425604CDD0); }
	NATIVE_DECL int GET_CURRENT_TV_SHOW_PLAY_TIME() { return invoke<int>(0xDD3AA743AB7D4D75); }
	NATIVE_DECL void CREATE_NEW_SCRIPTED_CONVERSATION() { invoke<Void>(0xD2C91A0B572AAE56); }
	NATIVE_DECL void ADD_LINE_TO_CONVERSATION(int index, const char* p1, const char* p2, int p3, int p4, BOOL p5, BOOL p6, BOOL p7, BOOL p8, int p9, BOOL p10, BOOL p11, BOOL p12) { invoke<Void>(0xC5EF963405593646, index, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	NATIVE_DECL void ADD_PED_TO_CONVERSATION(int index, Ped ped, const char* p2) { invoke<Void>(0x95D9F4BC443956E7, index, ped, p2); }
	NATIVE_DECL void SET_POSITION_FOR_NULL_CONV_PED(Any p0, float p1, float p2, float p3) { invoke<Void>(0x33E3C6C6F2F0B506, p0, p1, p2, p3); }
	NATIVE_DECL void SET_ENTITY_FOR_NULL_CONV_PED(int p0, Entity entity) { invoke<Void>(0x892B6AB8F33606F5, p0, entity); }
	NATIVE_DECL void SET_MICROPHONE_POSITION(BOOL toggle, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) { invoke<Void>(0xB6AE90EDDE95C762, toggle, x1, y1, z1, x2, y2, z2, x3, y3, z3); }
	NATIVE_DECL void SET_CONVERSATION_AUDIO_CONTROLLED_BY_ANIM(BOOL p0) { invoke<Void>(0x0B568201DD99F0EB, p0); }
	NATIVE_DECL void SET_CONVERSATION_AUDIO_PLACEHOLDER(BOOL p0) { invoke<Void>(0x61631F5DF50D1C34, p0); }
	NATIVE_DECL void START_SCRIPT_PHONE_CONVERSATION(BOOL p0, BOOL p1) { invoke<Void>(0x252E5F915EABB675, p0, p1); }
	NATIVE_DECL void PRELOAD_SCRIPT_PHONE_CONVERSATION(BOOL p0, BOOL p1) { invoke<Void>(0x6004BCB0E226AAEA, p0, p1); }
	NATIVE_DECL void START_SCRIPT_CONVERSATION(BOOL p0, BOOL p1, BOOL p2, BOOL p3) { invoke<Void>(0x6B17C62C9635D2DC, p0, p1, p2, p3); }
	NATIVE_DECL void PRELOAD_SCRIPT_CONVERSATION(BOOL p0, BOOL p1, BOOL p2, BOOL p3) { invoke<Void>(0x3B3CAD6166916D87, p0, p1, p2, p3); }
	NATIVE_DECL void START_PRELOADED_CONVERSATION() { invoke<Void>(0x23641AFE870AF385); }
	NATIVE_DECL BOOL GET_IS_PRELOADED_CONVERSATION_READY() { return invoke<BOOL>(0xE73364DB90778FFA); }
	NATIVE_DECL BOOL IS_SCRIPTED_CONVERSATION_ONGOING() { return invoke<BOOL>(0x16754C556D2EDE3D); }
	NATIVE_DECL BOOL IS_SCRIPTED_CONVERSATION_LOADED() { return invoke<BOOL>(0xDF0D54BE7A776737); }
	NATIVE_DECL int GET_CURRENT_SCRIPTED_CONVERSATION_LINE() { return invoke<int>(0x480357EE890C295A); }
	NATIVE_DECL void PAUSE_SCRIPTED_CONVERSATION(BOOL p0) { invoke<Void>(0x8530AD776CD72B12, p0); }
	NATIVE_DECL void RESTART_SCRIPTED_CONVERSATION() { invoke<Void>(0x9AEB285D1818C9AC); }
	NATIVE_DECL int STOP_SCRIPTED_CONVERSATION(BOOL p0) { return invoke<int>(0xD79DEEFB53455EBA, p0); }
	NATIVE_DECL void SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE() { invoke<Void>(0x9663FE6B7A61EB00); }
	NATIVE_DECL void INTERRUPT_CONVERSATION(Ped ped, const char* voiceline, const char* speaker) { invoke<Void>(0xA018A12E5C5C2FA6, ped, voiceline, speaker); }
	NATIVE_DECL void INTERRUPT_CONVERSATION_AND_PAUSE(Ped ped, const char* p1, const char* speaker) { invoke<Void>(0x8A694D7A68F8DC38, ped, p1, speaker); }
	NATIVE_DECL int GET_VARIATION_CHOSEN_FOR_SCRIPTED_LINE(Any* p0) { return invoke<int>(0xAA19F5572C38B564, p0); }
	NATIVE_DECL void SET_NO_DUCKING_FOR_CONVERSATION(BOOL p0) { invoke<Void>(0xB542DE8C3D1CB210, p0); }
	NATIVE_DECL void REGISTER_SCRIPT_WITH_AUDIO(int p0) { invoke<Void>(0xC6ED9D5092438D91, p0); }
	NATIVE_DECL void UNREGISTER_SCRIPT_WITH_AUDIO() { invoke<Void>(0xA8638BE228D4751A); }
	NATIVE_DECL BOOL REQUEST_MISSION_AUDIO_BANK(const char* audioBank, BOOL p1, Any p2) { return invoke<BOOL>(0x7345BDD95E62E0F2, audioBank, p1, p2); }
	NATIVE_DECL BOOL REQUEST_AMBIENT_AUDIO_BANK(const char* audioBank, BOOL p1, Any p2) { return invoke<BOOL>(0xFE02FFBED8CA9D99, audioBank, p1, p2); }
	NATIVE_DECL BOOL REQUEST_SCRIPT_AUDIO_BANK(const char* audioBank, BOOL p1, Any p2) { return invoke<BOOL>(0x2F844A8B08D76685, audioBank, p1, p2); }
	NATIVE_DECL BOOL HINT_MISSION_AUDIO_BANK(const char* audioBank, BOOL p1, Any p2) { return invoke<BOOL>(0x40763EA7B9B783E7, audioBank, p1, p2); }
	NATIVE_DECL BOOL HINT_AMBIENT_AUDIO_BANK(const char* audioBank, BOOL p1, Any p2) { return invoke<BOOL>(0x8F8C0E370AE62F5C, audioBank, p1, p2); }
	NATIVE_DECL BOOL HINT_SCRIPT_AUDIO_BANK(const char* audioBank, BOOL p1, Any p2) { return invoke<BOOL>(0xFB380A29641EC31A, audioBank, p1, p2); }
	NATIVE_DECL void RELEASE_MISSION_AUDIO_BANK() { invoke<Void>(0x0EC92A1BF0857187); }
	NATIVE_DECL void RELEASE_AMBIENT_AUDIO_BANK() { invoke<Void>(0x65475A218FFAA93D); }
	NATIVE_DECL void RELEASE_NAMED_SCRIPT_AUDIO_BANK(const char* audioBank) { invoke<Void>(0x77ED170667F50170, audioBank); }
	NATIVE_DECL void RELEASE_SCRIPT_AUDIO_BANK() { invoke<Void>(0x7A2D8AD0A9EB9C3F); }
	NATIVE_DECL void UNHINT_AMBIENT_AUDIO_BANK() { invoke<Void>(0x19AF7ED9B9D23058); }
	NATIVE_DECL void UNHINT_SCRIPT_AUDIO_BANK() { invoke<Void>(0x9AC92EED5E4793AB); }
	NATIVE_DECL void UNHINT_NAMED_SCRIPT_AUDIO_BANK(const char* audioBank) { invoke<Void>(0x11579D940949C49E, audioBank); }
	NATIVE_DECL int GET_SOUND_ID() { return invoke<int>(0x430386FE9BF80B45); }
	NATIVE_DECL void RELEASE_SOUND_ID(int soundId) { invoke<Void>(0x353FC880830B88FA, soundId); }
	NATIVE_DECL void PLAY_SOUND(int soundId, const char* audioName, const char* audioRef, BOOL p3, Any p4, BOOL p5) { invoke<Void>(0x7FF4944CC209192D, soundId, audioName, audioRef, p3, p4, p5); }
	NATIVE_DECL void PLAY_SOUND_FRONTEND(int soundId, const char* audioName, const char* audioRef, BOOL p3) { invoke<Void>(0x67C540AA08E4A6F5, soundId, audioName, audioRef, p3); }
	NATIVE_DECL void PLAY_DEFERRED_SOUND_FRONTEND(const char* soundName, const char* soundsetName) { invoke<Void>(0xCADA5A0D0702381E, soundName, soundsetName); }
	NATIVE_DECL void PLAY_SOUND_FROM_ENTITY(int soundId, const char* audioName, Entity entity, const char* audioRef, BOOL isNetwork, Any p5) { invoke<Void>(0xE65F427EB70AB1ED, soundId, audioName, entity, audioRef, isNetwork, p5); }
	NATIVE_DECL void PLAY_SOUND_FROM_ENTITY_HASH(int soundId, Hash model, Entity entity, Hash soundSetHash, Any p4, Any p5) { invoke<Void>(0x5B9853296731E88D, soundId, model, entity, soundSetHash, p4, p5); }
	NATIVE_DECL void PLAY_SOUND_FROM_COORD(int soundId, const char* audioName, float x, float y, float z, const char* audioRef, BOOL isNetwork, int range, BOOL p8) { invoke<Void>(0x8D8686B622B88120, soundId, audioName, x, y, z, audioRef, isNetwork, range, p8); }
	NATIVE_DECL void UPDATE_SOUND_COORD(int soundId, float x, float y, float z) { invoke<Void>(0x7EC3C679D0E7E46B, soundId, x, y, z); }
	NATIVE_DECL void STOP_SOUND(int soundId) { invoke<Void>(0xA3B0C41BA5CC0BB5, soundId); }
	NATIVE_DECL int GET_NETWORK_ID_FROM_SOUND_ID(int soundId) { return invoke<int>(0x2DE3F0A134FFBC0D, soundId); }
	NATIVE_DECL int GET_SOUND_ID_FROM_NETWORK_ID(int netId) { return invoke<int>(0x75262FD12D0A1C84, netId); }
	NATIVE_DECL void SET_VARIABLE_ON_SOUND(int soundId, const char* variable, float p2) { invoke<Void>(0xAD6B3148A78AE9B6, soundId, variable, p2); }
	NATIVE_DECL void SET_VARIABLE_ON_STREAM(const char* variable, float p1) { invoke<Void>(0x2F9D3834AEB9EF79, variable, p1); }
	NATIVE_DECL void OVERRIDE_UNDERWATER_STREAM(const char* p0, BOOL p1) { invoke<Void>(0xF2A9CDABCEA04BD6, p0, p1); }
	NATIVE_DECL void SET_VARIABLE_ON_UNDER_WATER_STREAM(const char* variableName, float value) { invoke<Void>(0x733ADF241531E5C2, variableName, value); }
	NATIVE_DECL BOOL HAS_SOUND_FINISHED(int soundId) { return invoke<BOOL>(0xFCBDCE714A7C88E5, soundId); }
	NATIVE_DECL void PLAY_PED_AMBIENT_SPEECH_NATIVE(Ped ped, const char* speechName, const char* speechParam, Any p3) { invoke<Void>(0x8E04FEDD28D42462, ped, speechName, speechParam, p3); }
	NATIVE_DECL void PLAY_PED_AMBIENT_SPEECH_AND_CLONE_NATIVE(Ped ped, const char* speechName, const char* speechParam, Any p3) { invoke<Void>(0xC6941B4A3A8FBBB9, ped, speechName, speechParam, p3); }
	NATIVE_DECL void PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE(Ped ped, const char* speechName, const char* voiceName, const char* speechParam, BOOL p4) { invoke<Void>(0x3523634255FC3318, ped, speechName, voiceName, speechParam, p4); }
	NATIVE_DECL void PLAY_AMBIENT_SPEECH_FROM_POSITION_NATIVE(const char* speechName, const char* voiceName, float x, float y, float z, const char* speechParam) { invoke<Void>(0xED640017ED337E45, speechName, voiceName, x, y, z, speechParam); }
	NATIVE_DECL void OVERRIDE_TREVOR_RAGE(const char* voiceEffect) { invoke<Void>(0x13AD665062541A7E, voiceEffect); }
	NATIVE_DECL void RESET_TREVOR_RAGE() { invoke<Void>(0xE78503B10C4314E0); }
	NATIVE_DECL void SET_PLAYER_ANGRY(Ped ped, BOOL toggle) { invoke<Void>(0xEA241BB04110F091, ped, toggle); }
	NATIVE_DECL void PLAY_PAIN(Ped ped, int painID, int p1, Any p3) { invoke<Void>(0xBC9AE166038A5CEC, ped, painID, p1, p3); }
	NATIVE_DECL void RELEASE_WEAPON_AUDIO() { invoke<Void>(0xCE4AC0439F607045); }
	NATIVE_DECL void ACTIVATE_AUDIO_SLOWMO_MODE(const char* mode) { invoke<Void>(0xD01005D2BA2EB778, mode); }
	NATIVE_DECL void DEACTIVATE_AUDIO_SLOWMO_MODE(const char* mode) { invoke<Void>(0xDDC635D5B3262C56, mode); }
	NATIVE_DECL void SET_AMBIENT_VOICE_NAME(Ped ped, const char* name) { invoke<Void>(0x6C8065A3B780185B, ped, name); }
	NATIVE_DECL void SET_AMBIENT_VOICE_NAME_HASH(Ped ped, Hash hash) { invoke<Void>(0x9A53DED9921DE990, ped, hash); }
	NATIVE_DECL Hash GET_AMBIENT_VOICE_NAME_HASH(Ped ped) { return invoke<Hash>(0x5E203DA2BA15D436, ped); }
	NATIVE_DECL void SET_PED_VOICE_FULL(Ped ped) { invoke<Void>(0x40CF0D12D142A9E8, ped); }
	NATIVE_DECL void SET_PED_RACE_AND_VOICE_GROUP(Ped ped, int p1, Hash voiceGroup) { invoke<Void>(0x1B7ABE26CBCBF8C7, ped, p1, voiceGroup); }
	NATIVE_DECL void SET_PED_VOICE_GROUP(Ped ped, Hash voiceGroupHash) { invoke<Void>(0x7CDC8C3B89F661B3, ped, voiceGroupHash); }
	NATIVE_DECL void SET_PED_VOICE_GROUP_FROM_RACE_TO_PVG(Ped ped, Hash voiceGroupHash) { invoke<Void>(0x0BABC1345ABBFB16, ped, voiceGroupHash); }
	NATIVE_DECL void SET_PED_GENDER(Ped ped, BOOL p1) { invoke<Void>(0xA5342D390CDA41D6, ped, p1); }
	NATIVE_DECL void STOP_CURRENT_PLAYING_SPEECH(Ped ped) { invoke<Void>(0x7A73D05A607734C7, ped); }
	NATIVE_DECL void STOP_CURRENT_PLAYING_AMBIENT_SPEECH(Ped ped) { invoke<Void>(0xB8BEC0CA6F0EDB0F, ped); }
	NATIVE_DECL BOOL IS_AMBIENT_SPEECH_PLAYING(Ped ped) { return invoke<BOOL>(0x9072C8B49907BFAD, ped); }
	NATIVE_DECL BOOL IS_SCRIPTED_SPEECH_PLAYING(Ped p0) { return invoke<BOOL>(0xCC9AA18DCC7084F4, p0); }
	NATIVE_DECL BOOL IS_ANY_SPEECH_PLAYING(Ped ped) { return invoke<BOOL>(0x729072355FA39EC9, ped); }
	NATIVE_DECL BOOL IS_ANY_POSITIONAL_SPEECH_PLAYING() { return invoke<BOOL>(0x30CA2EF91D15ADF8); }
	NATIVE_DECL BOOL DOES_CONTEXT_EXIST_FOR_THIS_PED(Ped ped, const char* speechName, BOOL p2) { return invoke<BOOL>(0x49B99BF3FDA89A7A, ped, speechName, p2); }
	NATIVE_DECL BOOL IS_PED_IN_CURRENT_CONVERSATION(Ped ped) { return invoke<BOOL>(0x049E937F18F4020C, ped); }
	NATIVE_DECL void SET_PED_IS_DRUNK(Ped ped, BOOL toggle) { invoke<Void>(0x95D2D383D5396B8A, ped, toggle); }
	NATIVE_DECL void PLAY_ANIMAL_VOCALIZATION(Ped pedHandle, int p1, const char* speechName) { invoke<Void>(0xEE066C7006C49C0A, pedHandle, p1, speechName); }
	NATIVE_DECL BOOL IS_ANIMAL_VOCALIZATION_PLAYING(Ped pedHandle) { return invoke<BOOL>(0xC265DF9FB44A9FBD, pedHandle); }
	NATIVE_DECL void SET_ANIMAL_MOOD(Ped animal, int mood) { invoke<Void>(0xCC97B29285B1DC3B, animal, mood); }
	NATIVE_DECL void PLAY_PED_AUDIO_EVENT_ANIM(Ped pedHandle, const char* audioEvent) { invoke<Void>(0xAD2191A6E3543189, pedHandle, audioEvent); }
	NATIVE_DECL BOOL IS_MOBILE_PHONE_RADIO_ACTIVE() { return invoke<BOOL>(0xB35CE999E8EF317E); }
	NATIVE_DECL void SET_MOBILE_PHONE_RADIO_STATE(BOOL state) { invoke<Void>(0xBF286C554784F3DF, state); }
	NATIVE_DECL int GET_PLAYER_RADIO_STATION_INDEX() { return invoke<int>(0xE8AF77C4C06ADC93); }
	NATIVE_DECL const char* GET_PLAYER_RADIO_STATION_NAME() { return invoke<const char*>(0xF6D733C32076AD03); }
	NATIVE_DECL const char* GET_RADIO_STATION_NAME(int radioStation) { return invoke<const char*>(0xB28ECA15046CA8B9, radioStation); }
	NATIVE_DECL int GET_PLAYER_RADIO_STATION_GENRE() { return invoke<int>(0xA571991A7FE6CCEB); }
	NATIVE_DECL BOOL IS_RADIO_RETUNING() { return invoke<BOOL>(0xA151A7394A214E65); }
	NATIVE_DECL BOOL IS_RADIO_FADED_OUT() { return invoke<BOOL>(0x0626A247D2405330); }
	NATIVE_DECL void SET_RADIO_RETUNE_UP() { invoke<Void>(0xFF266D1D0EB1195D); }
	NATIVE_DECL void SET_RADIO_RETUNE_DOWN() { invoke<Void>(0xDD6BCF9E94425DF9); }
	NATIVE_DECL void SET_RADIO_TO_STATION_NAME(const char* stationName) { invoke<Void>(0xC69EDA28699D5107, stationName); }
	NATIVE_DECL void SET_VEH_RADIO_STATION(Vehicle vehicle, const char* radioStation) { invoke<Void>(0x1B9C0099CB942AC6, vehicle, radioStation); }
	NATIVE_DECL void SET_VEH_HAS_NORMAL_RADIO(Vehicle vehicle) { invoke<Void>(0x3E45765F3FBB582F, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_RADIO_ON(Vehicle vehicle) { return invoke<BOOL>(0x0BE4BE946463F917, vehicle); }
	NATIVE_DECL void SET_VEH_FORCED_RADIO_THIS_FRAME(Vehicle vehicle) { invoke<Void>(0xC1805D05E6D4FE10, vehicle); }
	NATIVE_DECL void SET_EMITTER_RADIO_STATION(const char* emitterName, const char* radioStation, Any p2) { invoke<Void>(0xACF57305B12AF907, emitterName, radioStation, p2); }
	NATIVE_DECL void SET_STATIC_EMITTER_ENABLED(const char* emitterName, BOOL toggle) { invoke<Void>(0x399D2D3B33F1B8EB, emitterName, toggle); }
	NATIVE_DECL void LINK_STATIC_EMITTER_TO_ENTITY(const char* emitterName, Entity entity) { invoke<Void>(0x651D3228960D08AF, emitterName, entity); }
	NATIVE_DECL void SET_RADIO_TO_STATION_INDEX(int radioStation) { invoke<Void>(0xA619B168B8A8570F, radioStation); }
	NATIVE_DECL void SET_FRONTEND_RADIO_ACTIVE(BOOL active) { invoke<Void>(0xF7F26C6E9CC9EBB8, active); }
	NATIVE_DECL void UNLOCK_MISSION_NEWS_STORY(int newsStory) { invoke<Void>(0xB165AB7C248B2DC1, newsStory); }
	NATIVE_DECL BOOL IS_MISSION_NEWS_STORY_UNLOCKED(int newsStory) { return invoke<BOOL>(0x66E49BF55B4B1874, newsStory); }
	NATIVE_DECL int GET_AUDIBLE_MUSIC_TRACK_TEXT_ID() { return invoke<int>(0x50B196FC9ED6545B); }
	NATIVE_DECL void PLAY_END_CREDITS_MUSIC(BOOL play) { invoke<Void>(0xCD536C4D33DCC900, play); }
	NATIVE_DECL void SKIP_RADIO_FORWARD() { invoke<Void>(0x6DDBBDD98E2E9C25); }
	NATIVE_DECL void FREEZE_RADIO_STATION(const char* radioStation) { invoke<Void>(0x344F393B027E38C3, radioStation); }
	NATIVE_DECL void UNFREEZE_RADIO_STATION(const char* radioStation) { invoke<Void>(0xFC00454CF60B91DD, radioStation); }
	NATIVE_DECL void SET_RADIO_AUTO_UNFREEZE(BOOL toggle) { invoke<Void>(0xC1AA9F53CE982990, toggle); }
	NATIVE_DECL void SET_INITIAL_PLAYER_STATION(const char* radioStation) { invoke<Void>(0x88795F13FACDA88D, radioStation); }
	NATIVE_DECL void SET_USER_RADIO_CONTROL_ENABLED(BOOL toggle) { invoke<Void>(0x19F21E63AE6EAE4E, toggle); }
	NATIVE_DECL void SET_RADIO_TRACK(const char* radioStation, const char* radioTrack) { invoke<Void>(0xB39786F201FEE30B, radioStation, radioTrack); }
	NATIVE_DECL void SET_RADIO_TRACK_WITH_START_OFFSET(const char* radioStationName, const char* mixName, int p2) { invoke<Void>(0x2CB0075110BE1E56, radioStationName, mixName, p2); }
	NATIVE_DECL void SET_NEXT_RADIO_TRACK(const char* radioName, const char* radioTrack, const char* p2, const char* p3) { invoke<Void>(0x55ECF4D13D9903B0, radioName, radioTrack, p2, p3); }
	NATIVE_DECL void SET_VEHICLE_RADIO_LOUD(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xBB6F1CAEC68B0BCE, vehicle, toggle); }
	NATIVE_DECL BOOL CAN_VEHICLE_RECEIVE_CB_RADIO(Vehicle vehicle) { return invoke<BOOL>(0x032A116663A4D5AC, vehicle); }
	NATIVE_DECL void SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(BOOL toggle) { invoke<Void>(0x1098355A16064BB3, toggle); }
	NATIVE_DECL BOOL DOES_PLAYER_VEH_HAVE_RADIO() { return invoke<BOOL>(0x109697E2FFBAC8A1); }
	NATIVE_DECL BOOL IS_PLAYER_VEH_RADIO_ENABLE() { return invoke<BOOL>(0x5F43D83FD6738741); }
	NATIVE_DECL void SET_VEHICLE_RADIO_ENABLED(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x3B988190C0AA6C0B, vehicle, toggle); }
	NATIVE_DECL void SET_POSITIONED_PLAYER_VEHICLE_RADIO_EMITTER_ENABLED(Any p0) { invoke<Void>(0xDA07819E452FFE8F, p0); }
	NATIVE_DECL void SET_CUSTOM_RADIO_TRACK_LIST(const char* radioStation, const char* trackListName, BOOL p2) { invoke<Void>(0x4E404A9361F75BB2, radioStation, trackListName, p2); }
	NATIVE_DECL void CLEAR_CUSTOM_RADIO_TRACK_LIST(const char* radioStation) { invoke<Void>(0x1654F24A88A8E3FE, radioStation); }
	NATIVE_DECL int GET_NUM_UNLOCKED_RADIO_STATIONS() { return invoke<int>(0xF1620ECB50E01DE7); }
	NATIVE_DECL int FIND_RADIO_STATION_INDEX(Hash stationNameHash) { return invoke<int>(0x8D67489793FF428B, stationNameHash); }
	NATIVE_DECL void SET_RADIO_STATION_MUSIC_ONLY(const char* radioStation, BOOL toggle) { invoke<Void>(0x774BD811F656A122, radioStation, toggle); }
	NATIVE_DECL void SET_RADIO_FRONTEND_FADE_TIME(float fadeTime) { invoke<Void>(0x2C96CDB04FCA358E, fadeTime); }
	NATIVE_DECL void UNLOCK_RADIO_STATION_TRACK_LIST(const char* radioStation, const char* trackListName) { invoke<Void>(0x031ACB6ABA18C729, radioStation, trackListName); }
	NATIVE_DECL void LOCK_RADIO_STATION_TRACK_LIST(const char* radioStation, const char* trackListName) { invoke<Void>(0xFF5E5EA2DCEEACF3, radioStation, trackListName); }
	NATIVE_DECL void UPDATE_UNLOCKABLE_DJ_RADIO_TRACKS(BOOL enableMixes) { invoke<Void>(0x47AED84213A47510, enableMixes); }
	NATIVE_DECL void LOCK_RADIO_STATION(const char* radioStationName, BOOL toggle) { invoke<Void>(0x477D9DB48F889591, radioStationName, toggle); }
	NATIVE_DECL void SET_RADIO_STATION_AS_FAVOURITE(const char* radioStation, BOOL toggle) { invoke<Void>(0x4CAFEBFA21EC188D, radioStation, toggle); }
	NATIVE_DECL BOOL IS_RADIO_STATION_FAVOURITED(const char* radioStation) { return invoke<BOOL>(0x2B1784DB08AFEA79, radioStation); }
	NATIVE_DECL BOOL GET_NEXT_AUDIBLE_BEAT(float* out1, float* out2, int* out3) { return invoke<BOOL>(0xC64A06D939F826F5, out1, out2, out3); }
	NATIVE_DECL void FORCE_MUSIC_TRACK_LIST(const char* radioStation, const char* trackListName, int milliseconds) { invoke<Void>(0x4E0AF9114608257C, radioStation, trackListName, milliseconds); }
	NATIVE_DECL int GET_CURRENT_TRACK_PLAY_TIME(const char* radioStationName) { return invoke<int>(0x3E65CDE5215832C1, radioStationName); }
	NATIVE_DECL Hash GET_CURRENT_TRACK_SOUND_NAME(const char* radioStationName) { return invoke<Hash>(0x34D66BC058019CE0, radioStationName); }
	NATIVE_DECL void SET_VEHICLE_MISSILE_WARNING_ENABLED(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xF3365489E0DD50F9, vehicle, toggle); }
	NATIVE_DECL void SET_AMBIENT_ZONE_STATE(const char* zoneName, BOOL p1, BOOL p2) { invoke<Void>(0xBDA07E5950085E46, zoneName, p1, p2); }
	NATIVE_DECL void CLEAR_AMBIENT_ZONE_STATE(const char* zoneName, BOOL p1) { invoke<Void>(0x218DD44AAAC964FF, zoneName, p1); }
	NATIVE_DECL void SET_AMBIENT_ZONE_LIST_STATE(const char* ambientZone, BOOL p1, BOOL p2) { invoke<Void>(0x9748FA4DE50CCE3E, ambientZone, p1, p2); }
	NATIVE_DECL void CLEAR_AMBIENT_ZONE_LIST_STATE(const char* ambientZone, BOOL p1) { invoke<Void>(0x120C48C614909FA4, ambientZone, p1); }
	NATIVE_DECL void SET_AMBIENT_ZONE_STATE_PERSISTENT(const char* ambientZone, BOOL p1, BOOL p2) { invoke<Void>(0x1D6650420CEC9D3B, ambientZone, p1, p2); }
	NATIVE_DECL void SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT(const char* ambientZone, BOOL p1, BOOL p2) { invoke<Void>(0xF3638DAE8C4045E1, ambientZone, p1, p2); }
	NATIVE_DECL BOOL IS_AMBIENT_ZONE_ENABLED(const char* ambientZone) { return invoke<BOOL>(0x01E2817A479A7F9B, ambientZone); }
	NATIVE_DECL void REFRESH_CLOSEST_OCEAN_SHORELINE() { invoke<Void>(0x5D2BFAAB8D956E0E); }
	NATIVE_DECL void SET_CUTSCENE_AUDIO_OVERRIDE(const char* name) { invoke<Void>(0x3B4BF5F0859204D9, name); }
	NATIVE_DECL void SET_VARIABLE_ON_SYNCH_SCENE_AUDIO(const char* variableName, float value) { invoke<Void>(0xBCC29F935ED07688, variableName, value); }
	NATIVE_DECL int PLAY_POLICE_REPORT(const char* name, float p1) { return invoke<int>(0xDFEBD56D9BD1EB16, name, p1); }
	NATIVE_DECL void CANCEL_ALL_POLICE_REPORTS() { invoke<Void>(0xB4F90FAF7670B16F); }
	NATIVE_DECL void BLIP_SIREN(Vehicle vehicle) { invoke<Void>(0x1B9025BDA76822B6, vehicle); }
	NATIVE_DECL void OVERRIDE_VEH_HORN(Vehicle vehicle, BOOL override, int hornHash) { invoke<Void>(0x3CDC1E622CCE0356, vehicle, override, hornHash); }
	NATIVE_DECL BOOL IS_HORN_ACTIVE(Vehicle vehicle) { return invoke<BOOL>(0x9D6BFC12B05C6121, vehicle); }
	NATIVE_DECL void SET_AGGRESSIVE_HORNS(BOOL toggle) { invoke<Void>(0x395BF71085D1B1D9, toggle); }
	NATIVE_DECL void SET_RADIO_POSITION_AUDIO_MUTE(BOOL p0) { invoke<Void>(0x02E93C796ABD3A97, p0); }
	NATIVE_DECL void SET_VEHICLE_CONVERSATIONS_PERSIST(BOOL p0, BOOL p1) { invoke<Void>(0x58BB377BEC7CD5F4, p0, p1); }
	NATIVE_DECL void SET_VEHICLE_CONVERSATIONS_PERSIST_NEW(BOOL p0, BOOL p1, BOOL p2) { invoke<Void>(0x9BD7BD55E4533183, p0, p1, p2); }
	NATIVE_DECL BOOL IS_STREAM_PLAYING() { return invoke<BOOL>(0xD11FA52EB849D978); }
	NATIVE_DECL int GET_STREAM_PLAY_TIME() { return invoke<int>(0x4E72BBDBCA58A3DB); }
	NATIVE_DECL BOOL LOAD_STREAM(const char* streamName, const char* soundSet) { return invoke<BOOL>(0x1F1F957154EC51DF, streamName, soundSet); }
	NATIVE_DECL BOOL LOAD_STREAM_WITH_START_OFFSET(const char* streamName, int startOffset, const char* soundSet) { return invoke<BOOL>(0x59C16B79F53B3712, streamName, startOffset, soundSet); }
	NATIVE_DECL void PLAY_STREAM_FROM_PED(Ped ped) { invoke<Void>(0x89049DD63C08B5D1, ped); }
	NATIVE_DECL void PLAY_STREAM_FROM_VEHICLE(Vehicle vehicle) { invoke<Void>(0xB70374A758007DFA, vehicle); }
	NATIVE_DECL void PLAY_STREAM_FROM_OBJECT(Object object) { invoke<Void>(0xEBAA9B64D76356FD, object); }
	NATIVE_DECL void PLAY_STREAM_FRONTEND() { invoke<Void>(0x58FCE43488F9F5F4); }
	NATIVE_DECL void PLAY_STREAM_FROM_POSITION(float x, float y, float z) { invoke<Void>(0x21442F412E8DE56B, x, y, z); }
	NATIVE_DECL void STOP_STREAM() { invoke<Void>(0xA4718A1419D18151); }
	NATIVE_DECL void STOP_PED_SPEAKING(Ped ped, BOOL shaking) { invoke<Void>(0x9D64D7405520E3D3, ped, shaking); }
	NATIVE_DECL void BLOCK_ALL_SPEECH_FROM_PED(Ped ped, BOOL p1, BOOL p2) { invoke<Void>(0xF8AD2EED7C47E8FE, ped, p1, p2); }
	NATIVE_DECL void STOP_PED_SPEAKING_SYNCED(Ped ped, BOOL p1) { invoke<Void>(0xAB6781A5F3101470, ped, p1); }
	NATIVE_DECL void DISABLE_PED_PAIN_AUDIO(Ped ped, BOOL toggle) { invoke<Void>(0xA9A41C1E940FB0E8, ped, toggle); }
	NATIVE_DECL BOOL IS_AMBIENT_SPEECH_DISABLED(Ped ped) { return invoke<BOOL>(0x932C2D096A2C3FFF, ped); }
	NATIVE_DECL void BLOCK_SPEECH_CONTEXT_GROUP(const char* p0, int p1) { invoke<Void>(0xA8A7D434AFB4B97B, p0, p1); }
	NATIVE_DECL void UNBLOCK_SPEECH_CONTEXT_GROUP(const char* p0) { invoke<Void>(0x2ACABED337622DF2, p0); }
	NATIVE_DECL void SET_SIREN_WITH_NO_DRIVER(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x1FEF0683B96EBCF2, vehicle, toggle); }
	NATIVE_DECL void SET_SIREN_BYPASS_MP_DRIVER_CHECK(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xF584CF8529B51434, vehicle, toggle); }
	NATIVE_DECL void TRIGGER_SIREN_AUDIO(Vehicle vehicle) { invoke<Void>(0x66C3FB05206041BA, vehicle); }
	NATIVE_DECL void SET_HORN_PERMANENTLY_ON(Vehicle vehicle) { invoke<Void>(0x9C11908013EA4715, vehicle); }
	NATIVE_DECL void SET_HORN_ENABLED(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x76D683C108594D0E, vehicle, toggle); }
	NATIVE_DECL void SET_AUDIO_VEHICLE_PRIORITY(Vehicle vehicle, Any p1) { invoke<Void>(0xE5564483E407F914, vehicle, p1); }
	NATIVE_DECL void SET_HORN_PERMANENTLY_ON_TIME(Vehicle vehicle, float time) { invoke<Void>(0x9D3AF56E94C9AE98, vehicle, time); }
	NATIVE_DECL void USE_SIREN_AS_HORN(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xFA932DE350266EF8, vehicle, toggle); }
	NATIVE_DECL void FORCE_USE_AUDIO_GAME_OBJECT(Vehicle vehicle, const char* audioName) { invoke<Void>(0x4F0C413926060B38, vehicle, audioName); }
	NATIVE_DECL void PRELOAD_VEHICLE_AUDIO_BANK(Hash vehicleModel) { invoke<Void>(0xCA4CEA6AE0000A7E, vehicleModel); }
	NATIVE_DECL void SET_VEHICLE_STARTUP_REV_SOUND(Vehicle vehicle, const char* p1, const char* p2) { invoke<Void>(0xF1F8157B8C3F171C, vehicle, p1, p2); }
	NATIVE_DECL void RESET_VEHICLE_STARTUP_REV_SOUND(Vehicle vehicle) { invoke<Void>(0xD2DCCD8E16E20997, vehicle); }
	NATIVE_DECL void SET_VEHICLE_FORCE_REVERSE_WARNING(Any p0, Any p1) { invoke<Void>(0x97FFB4ADEED08066, p0, p1); }
	NATIVE_DECL BOOL IS_VEHICLE_AUDIBLY_DAMAGED(Vehicle vehicle) { return invoke<BOOL>(0x5DB8010EE71FDEF2, vehicle); }
	NATIVE_DECL void SET_VEHICLE_AUDIO_ENGINE_DAMAGE_FACTOR(Vehicle vehicle, float damageFactor) { invoke<Void>(0x59E7B488451F4D3A, vehicle, damageFactor); }
	NATIVE_DECL void SET_VEHICLE_AUDIO_BODY_DAMAGE_FACTOR(Vehicle vehicle, float intensity) { invoke<Void>(0x01BB4D577D38BD9E, vehicle, intensity); }
	NATIVE_DECL void _FORCE_VEHICLE_ENGINE_SYNTH(Vehicle vehicle, BOOL force) { invoke<Void>(0xEB7D0E1FCC8FE17A, vehicle, force); }
	NATIVE_DECL void ENABLE_VEHICLE_FANBELT_DAMAGE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x1C073274E065C6D2, vehicle, toggle); }
	NATIVE_DECL void ENABLE_VEHICLE_EXHAUST_POPS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x2BE4BC731D039D5A, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_BOOST_ACTIVE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x4A04DE7CAB2739A1, vehicle, toggle); }
	NATIVE_DECL void SET_PLAYER_VEHICLE_ALARM_AUDIO_ACTIVE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x6FDDAD856E36988A, vehicle, toggle); }
	NATIVE_DECL void SET_SCRIPT_UPDATE_DOOR_AUDIO(Hash doorHash, BOOL toggle) { invoke<Void>(0x06C0023BED16DD6B, doorHash, toggle); }
	NATIVE_DECL void PLAY_VEHICLE_DOOR_OPEN_SOUND(Vehicle vehicle, int doorId) { invoke<Void>(0x3A539D52857EA82D, vehicle, doorId); }
	NATIVE_DECL void PLAY_VEHICLE_DOOR_CLOSE_SOUND(Vehicle vehicle, int doorId) { invoke<Void>(0x62A456AA4769EF34, vehicle, doorId); }
	NATIVE_DECL void ENABLE_STALL_WARNING_SOUNDS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xC15907D667F7CFB2, vehicle, toggle); }
	NATIVE_DECL void _ENABLE_DRAG_RACE_STATIONARY_WARNING_SOUNDS(Vehicle vehicle, BOOL enable) { invoke<Void>(0xBEFB80290414FD4F, vehicle, enable); }
	NATIVE_DECL BOOL IS_GAME_IN_CONTROL_OF_MUSIC() { return invoke<BOOL>(0x6D28DC1671E334FD); }
	NATIVE_DECL void SET_GPS_ACTIVE(BOOL active) { invoke<Void>(0x3BD3F52BA9B1E4E8, active); }
	NATIVE_DECL void PLAY_MISSION_COMPLETE_AUDIO(const char* audioName) { invoke<Void>(0xB138AAB8A70D3C69, audioName); }
	NATIVE_DECL BOOL IS_MISSION_COMPLETE_PLAYING() { return invoke<BOOL>(0x19A30C23F5827F8A); }
	NATIVE_DECL BOOL IS_MISSION_COMPLETE_READY_FOR_UI() { return invoke<BOOL>(0x6F259F82D873B8B8); }
	NATIVE_DECL void BLOCK_DEATH_JINGLE(BOOL toggle) { invoke<Void>(0xF154B8D1775B2DEC, toggle); }
	NATIVE_DECL BOOL START_AUDIO_SCENE(const char* scene) { return invoke<BOOL>(0x013A80FC08F6E4F2, scene); }
	NATIVE_DECL void STOP_AUDIO_SCENE(const char* scene) { invoke<Void>(0xDFE8422B3B94E688, scene); }
	NATIVE_DECL void STOP_AUDIO_SCENES() { invoke<Void>(0xBAC7FC81A75EC1A1); }
	NATIVE_DECL BOOL IS_AUDIO_SCENE_ACTIVE(const char* scene) { return invoke<BOOL>(0xB65B60556E2A9225, scene); }
	NATIVE_DECL void SET_AUDIO_SCENE_VARIABLE(const char* scene, const char* variable, float value) { invoke<Void>(0xEF21A9EF089A2668, scene, variable, value); }
	NATIVE_DECL void SET_AUDIO_SCRIPT_CLEANUP_TIME(int time) { invoke<Void>(0xA5F377B175A699C5, time); }
	NATIVE_DECL void ADD_ENTITY_TO_AUDIO_MIX_GROUP(Entity entity, const char* groupName, float p2) { invoke<Void>(0x153973AB99FE8980, entity, groupName, p2); }
	NATIVE_DECL void REMOVE_ENTITY_FROM_AUDIO_MIX_GROUP(Entity entity, float p1) { invoke<Void>(0x18EB48CFC41F2EA0, entity, p1); }
	NATIVE_DECL BOOL AUDIO_IS_MUSIC_PLAYING() { return invoke<BOOL>(0x845FFC3A4FEEFA3E); }
	NATIVE_DECL BOOL AUDIO_IS_SCRIPTED_MUSIC_PLAYING() { return invoke<BOOL>(0x2DD39BF3E2F9C47F); }
	NATIVE_DECL BOOL PREPARE_MUSIC_EVENT(const char* eventName) { return invoke<BOOL>(0x1E5185B72EF5158A, eventName); }
	NATIVE_DECL BOOL CANCEL_MUSIC_EVENT(const char* eventName) { return invoke<BOOL>(0x5B17A90291133DA5, eventName); }
	NATIVE_DECL BOOL TRIGGER_MUSIC_EVENT(const char* eventName) { return invoke<BOOL>(0x706D57B0F50DA710, eventName); }
	NATIVE_DECL BOOL IS_MUSIC_ONESHOT_PLAYING() { return invoke<BOOL>(0xA097AB275061FB21); }
	NATIVE_DECL int GET_MUSIC_PLAYTIME() { return invoke<int>(0xE7A0D23DC414507B); }
	NATIVE_DECL void SET_GLOBAL_RADIO_SIGNAL_LEVEL(Any p0) { invoke<Void>(0x159B7318403A1CD8, p0); }
	NATIVE_DECL void RECORD_BROKEN_GLASS(float x, float y, float z, float radius) { invoke<Void>(0xFBE20329593DEC9D, x, y, z, radius); }
	NATIVE_DECL void CLEAR_ALL_BROKEN_GLASS() { invoke<Void>(0xB32209EFFDC04913); }
	NATIVE_DECL void SCRIPT_OVERRIDES_WIND_ELEVATION(BOOL p0, Any p1) { invoke<Void>(0x70B8EC8FC108A634, p0, p1); }
	NATIVE_DECL void SET_PED_WALLA_DENSITY(float p0, float p1) { invoke<Void>(0x149AEE66F0CB3A99, p0, p1); }
	NATIVE_DECL void SET_PED_INTERIOR_WALLA_DENSITY(float p0, float p1) { invoke<Void>(0x8BF907833BE275DE, p0, p1); }
	NATIVE_DECL void FORCE_PED_PANIC_WALLA() { invoke<Void>(0x062D5EAD4DA2FA6A); }
	NATIVE_DECL BOOL PREPARE_ALARM(const char* alarmName) { return invoke<BOOL>(0x9D74AE343DB65533, alarmName); }
	NATIVE_DECL void START_ALARM(const char* alarmName, BOOL p2) { invoke<Void>(0x0355EF116C4C97B2, alarmName, p2); }
	NATIVE_DECL void STOP_ALARM(const char* alarmName, BOOL toggle) { invoke<Void>(0xA1CADDCD98415A41, alarmName, toggle); }
	NATIVE_DECL void STOP_ALL_ALARMS(BOOL stop) { invoke<Void>(0x2F794A877ADD4C92, stop); }
	NATIVE_DECL BOOL IS_ALARM_PLAYING(const char* alarmName) { return invoke<BOOL>(0x226435CB96CCFC8C, alarmName); }
	NATIVE_DECL Hash GET_VEHICLE_DEFAULT_HORN(Vehicle vehicle) { return invoke<Hash>(0x02165D55000219AC, vehicle); }
	NATIVE_DECL Hash GET_VEHICLE_DEFAULT_HORN_IGNORE_MODS(Vehicle vehicle) { return invoke<Hash>(0xACB5DCCA1EC76840, vehicle); }
	NATIVE_DECL void RESET_PED_AUDIO_FLAGS(Ped ped) { invoke<Void>(0xF54BB7B61036F335, ped); }
	NATIVE_DECL void SET_PED_FOOTSTEPS_EVENTS_ENABLED(Ped ped, BOOL toggle) { invoke<Void>(0x0653B735BFBDFE87, ped, toggle); }
	NATIVE_DECL void SET_PED_CLOTH_EVENTS_ENABLED(Ped ped, BOOL toggle) { invoke<Void>(0x29DA3CA8D8B2692D, ped, toggle); }
	NATIVE_DECL void OVERRIDE_PLAYER_GROUND_MATERIAL(Hash hash, BOOL toggle) { invoke<Void>(0xD2CC78CD3D0B50F9, hash, toggle); }
	NATIVE_DECL void USE_FOOTSTEP_SCRIPT_SWEETENERS(Ped ped, BOOL p1, Hash hash) { invoke<Void>(0xBF4DC1784BE94DFA, ped, p1, hash); }
	NATIVE_DECL void OVERRIDE_MICROPHONE_SETTINGS(Hash hash, BOOL toggle) { invoke<Void>(0x75773E11BA459E90, hash, toggle); }
	NATIVE_DECL void FREEZE_MICROPHONE() { invoke<Void>(0xD57AAAE0E2214D11); }
	NATIVE_DECL void DISTANT_COP_CAR_SIRENS(BOOL value) { invoke<Void>(0x552369F549563AD5, value); }
	NATIVE_DECL void SET_SIREN_CAN_BE_CONTROLLED_BY_AUDIO(Vehicle vehicle, BOOL p1) { invoke<Void>(0x43FA0DFC5DF87815, vehicle, p1); }
	NATIVE_DECL void ENABLE_STUNT_JUMP_AUDIO() { invoke<Void>(0xB81CF134AEB56FFB); }
	NATIVE_DECL void SET_AUDIO_FLAG(const char* flagName, BOOL toggle) { invoke<Void>(0xB9EFD5C25018725A, flagName, toggle); }
	NATIVE_DECL BOOL PREPARE_SYNCHRONIZED_AUDIO_EVENT(const char* audioEvent, Any p1) { return invoke<BOOL>(0xC7ABCACA4985A766, audioEvent, p1); }
	NATIVE_DECL BOOL PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE(int sceneID, const char* audioEvent) { return invoke<BOOL>(0x029FE7CD1B7E2E75, sceneID, audioEvent); }
	NATIVE_DECL BOOL PLAY_SYNCHRONIZED_AUDIO_EVENT(int sceneID) { return invoke<BOOL>(0x8B2FD4560E55DD2D, sceneID); }
	NATIVE_DECL BOOL STOP_SYNCHRONIZED_AUDIO_EVENT(int sceneID) { return invoke<BOOL>(0x92D6A88E64A94430, sceneID); }
	NATIVE_DECL void INIT_SYNCH_SCENE_AUDIO_WITH_POSITION(const char* audioEvent, float x, float y, float z) { invoke<Void>(0xC8EDE9BDBCCBA6D4, audioEvent, x, y, z); }
	NATIVE_DECL void INIT_SYNCH_SCENE_AUDIO_WITH_ENTITY(const char* audioEvent, Entity entity) { invoke<Void>(0x950A154B8DAB6185, audioEvent, entity); }
	NATIVE_DECL void SET_AUDIO_SPECIAL_EFFECT_MODE(int mode) { invoke<Void>(0x12561FCBB62D5B9C, mode); }
	NATIVE_DECL void SET_PORTAL_SETTINGS_OVERRIDE(const char* p0, const char* p1) { invoke<Void>(0x044DBAD7A7FA2BE5, p0, p1); }
	NATIVE_DECL void SET_INDIVIDUAL_PORTAL_SETTINGS_OVERRIDE(Hash interiorNameHash, int roomIndex, int doorIndex, const char* newPortalSettingsName) { invoke<Void>(0xC9D623C5A3D8FD5D, interiorNameHash, roomIndex, doorIndex, newPortalSettingsName); }
	NATIVE_DECL void REMOVE_PORTAL_SETTINGS_OVERRIDE(const char* p0) { invoke<Void>(0xB4BBFD9CD8B3922B, p0); }
	NATIVE_DECL void REMOVE_INDIVIDUAL_PORTAL_SETTINGS_OVERRIDE(Hash interiorNameHash, int roomIndex, int doorIndex) { invoke<Void>(0x8EF105736194F80C, interiorNameHash, roomIndex, doorIndex); }
	NATIVE_DECL void STOP_SMOKE_GRENADE_EXPLOSION_SOUNDS() { invoke<Void>(0xE4E6DD5566D28C82); }
	NATIVE_DECL int GET_MUSIC_VOL_SLIDER() { return invoke<int>(0x3A48AB4445D499BE); }
	NATIVE_DECL void REQUEST_TENNIS_BANKS(Ped ped) { invoke<Void>(0x4ADA3F19BE4A6047, ped); }
	NATIVE_DECL void UNREQUEST_TENNIS_BANKS() { invoke<Void>(0x0150B6FF25A9E2E5); }
	NATIVE_DECL void SET_SKIP_MINIGUN_SPIN_UP_AUDIO(BOOL p0) { invoke<Void>(0xBEF34B1D9624D5DD, p0); }
	NATIVE_DECL void STOP_CUTSCENE_AUDIO() { invoke<Void>(0x806058BBDC136E06); }
	NATIVE_DECL BOOL HAS_LOADED_MP_DATA_SET() { return invoke<BOOL>(0x544810ED9DB6BBE6); }
	NATIVE_DECL BOOL HAS_LOADED_SP_DATA_SET() { return invoke<BOOL>(0x5B50ABB1FE3746F4); }
	NATIVE_DECL int GET_VEHICLE_HORN_SOUND_INDEX(Vehicle vehicle) { return invoke<int>(0xD53F3A29BCE2580E, vehicle); }
	NATIVE_DECL void SET_VEHICLE_HORN_SOUND_INDEX(Vehicle vehicle, int value) { invoke<Void>(0x0350E7E17BA767D0, vehicle, value); }
}

namespace BRAIN
{
	NATIVE_DECL void ADD_SCRIPT_TO_RANDOM_PED(const char* name, Hash model, float p2, float p3) { invoke<Void>(0x4EE5367468A65CCC, name, model, p2, p3); }
	NATIVE_DECL void REGISTER_OBJECT_SCRIPT_BRAIN(const char* scriptName, Hash modelHash, int p2, float activationRange, int p4, int p5) { invoke<Void>(0x0BE84C318BA6EC22, scriptName, modelHash, p2, activationRange, p4, p5); }
	NATIVE_DECL BOOL IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(Object object) { return invoke<BOOL>(0xCCBA154209823057, object); }
	NATIVE_DECL void REGISTER_WORLD_POINT_SCRIPT_BRAIN(const char* scriptName, float activationRange, int p2) { invoke<Void>(0x3CDC7136613284BD, scriptName, activationRange, p2); }
	NATIVE_DECL BOOL IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE() { return invoke<BOOL>(0xC5042CC6F5E3D450); }
	NATIVE_DECL void ENABLE_SCRIPT_BRAIN_SET(int brainSet) { invoke<Void>(0x67AA4D73F0CFA86B, brainSet); }
	NATIVE_DECL void DISABLE_SCRIPT_BRAIN_SET(int brainSet) { invoke<Void>(0x14D8518E9760F08F, brainSet); }
	NATIVE_DECL void REACTIVATE_ALL_WORLD_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE() { invoke<Void>(0x0B40ED49D7D6FF84); }
	NATIVE_DECL void REACTIVATE_ALL_OBJECT_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE() { invoke<Void>(0x4D953DF78EBF8158); }
	NATIVE_DECL void REACTIVATE_NAMED_WORLD_BRAINS_WAITING_TILL_OUT_OF_RANGE(const char* scriptName) { invoke<Void>(0x6D6840CEE8845831, scriptName); }
	NATIVE_DECL void REACTIVATE_NAMED_OBJECT_BRAINS_WAITING_TILL_OUT_OF_RANGE(const char* scriptName) { invoke<Void>(0x6E91B04E08773030, scriptName); }
}

namespace CAMERA
{
	NATIVE_DECL void RENDER_SCRIPT_CAMS(BOOL render, BOOL ease, int easeTime, BOOL p3, BOOL p4, Any p5) { invoke<Void>(0x07E5B515DB0636FC, render, ease, easeTime, p3, p4, p5); }
	NATIVE_DECL void STOP_RENDERING_SCRIPT_CAMS_USING_CATCH_UP(BOOL render, float p1, int p2, Any p3) { invoke<Void>(0xC819F3CBB62BF692, render, p1, p2, p3); }
	NATIVE_DECL Cam CREATE_CAM(const char* camName, BOOL p1) { return invoke<Cam>(0xC3981DCE61D9E13F, camName, p1); }
	NATIVE_DECL Cam CREATE_CAM_WITH_PARAMS(const char* camName, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fov, BOOL p8, int p9) { return invoke<Cam>(0xB51194800B257161, camName, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9); }
	NATIVE_DECL Cam CREATE_CAMERA(Hash camHash, BOOL p1) { return invoke<Cam>(0x5E3CF89C6BCCA67D, camHash, p1); }
	NATIVE_DECL Cam CREATE_CAMERA_WITH_PARAMS(Hash camHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fov, BOOL p8, Any p9) { return invoke<Cam>(0x6ABFA3E16460F22D, camHash, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9); }
	NATIVE_DECL void DESTROY_CAM(Cam cam, BOOL bScriptHostCam) { invoke<Void>(0x865908C81A2C22E9, cam, bScriptHostCam); }
	NATIVE_DECL void DESTROY_ALL_CAMS(BOOL bScriptHostCam) { invoke<Void>(0x8E5FB15663F79120, bScriptHostCam); }
	NATIVE_DECL BOOL DOES_CAM_EXIST(Cam cam) { return invoke<BOOL>(0xA7A932170592B50E, cam); }
	NATIVE_DECL void SET_CAM_ACTIVE(Cam cam, BOOL active) { invoke<Void>(0x026FB97D0A425F84, cam, active); }
	NATIVE_DECL BOOL IS_CAM_ACTIVE(Cam cam) { return invoke<BOOL>(0xDFB2B516207D3534, cam); }
	NATIVE_DECL BOOL IS_CAM_RENDERING(Cam cam) { return invoke<BOOL>(0x02EC0AF5C5A49B7A, cam); }
	NATIVE_DECL Cam GET_RENDERING_CAM() { return invoke<Cam>(0x5234F9F10919EABA); }
	NATIVE_DECL Vector3 GET_CAM_COORD(Cam cam) { return invoke<Vector3>(0xBAC038F7459AE5AE, cam); }
	NATIVE_DECL Vector3 GET_CAM_ROT(Cam cam, int rotationOrder) { return invoke<Vector3>(0x7D304C1C955E3E12, cam, rotationOrder); }
	NATIVE_DECL float GET_CAM_FOV(Cam cam) { return invoke<float>(0xC3330A45CCCDB26A, cam); }
	NATIVE_DECL float GET_CAM_NEAR_CLIP(Cam cam) { return invoke<float>(0xC520A34DAFBF24B1, cam); }
	NATIVE_DECL float GET_CAM_FAR_CLIP(Cam cam) { return invoke<float>(0xB60A9CFEB21CA6AA, cam); }
	NATIVE_DECL float GET_CAM_NEAR_DOF(Cam cam) { return invoke<float>(0xC2612D223D915A1C, cam); }
	NATIVE_DECL float GET_CAM_FAR_DOF(Cam cam) { return invoke<float>(0x255F8DAFD540D397, cam); }
	NATIVE_DECL float GET_CAM_DOF_STRENGTH(Cam cam) { return invoke<float>(0x06D153C0B99B6128, cam); }
	NATIVE_DECL void SET_CAM_PARAMS(Cam cam, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fieldOfView, Any p8, int p9, int p10, int p11) { invoke<Void>(0xBFD8727AEA3CCEBA, cam, posX, posY, posZ, rotX, rotY, rotZ, fieldOfView, p8, p9, p10, p11); }
	NATIVE_DECL void SET_CAM_COORD(Cam cam, float posX, float posY, float posZ) { invoke<Void>(0x4D41783FB745E42E, cam, posX, posY, posZ); }
	NATIVE_DECL void SET_CAM_ROT(Cam cam, float rotX, float rotY, float rotZ, int rotationOrder) { invoke<Void>(0x85973643155D0B07, cam, rotX, rotY, rotZ, rotationOrder); }
	NATIVE_DECL void SET_CAM_FOV(Cam cam, float fieldOfView) { invoke<Void>(0xB13C14F66A00D047, cam, fieldOfView); }
	NATIVE_DECL void SET_CAM_NEAR_CLIP(Cam cam, float nearClip) { invoke<Void>(0xC7848EFCCC545182, cam, nearClip); }
	NATIVE_DECL void SET_CAM_FAR_CLIP(Cam cam, float farClip) { invoke<Void>(0xAE306F2A904BF86E, cam, farClip); }
	NATIVE_DECL void FORCE_CAM_FAR_CLIP(Cam cam, float p1) { invoke<Void>(0xAABD62873FFB1A33, cam, p1); }
	NATIVE_DECL void SET_CAM_MOTION_BLUR_STRENGTH(Cam cam, float strength) { invoke<Void>(0x6F0F77FBA9A8F2E6, cam, strength); }
	NATIVE_DECL void SET_CAM_NEAR_DOF(Cam cam, float nearDOF) { invoke<Void>(0x3FA4BF0A7AB7DE2C, cam, nearDOF); }
	NATIVE_DECL void SET_CAM_FAR_DOF(Cam cam, float farDOF) { invoke<Void>(0xEDD91296CD01AEE0, cam, farDOF); }
	NATIVE_DECL void SET_CAM_DOF_STRENGTH(Cam cam, float dofStrength) { invoke<Void>(0x5EE29B4D7D5DF897, cam, dofStrength); }
	NATIVE_DECL void SET_CAM_DOF_PLANES(Cam cam, float p1, float p2, float p3, float p4) { invoke<Void>(0x3CF48F6F96E749DC, cam, p1, p2, p3, p4); }
	NATIVE_DECL void SET_CAM_USE_SHALLOW_DOF_MODE(Cam cam, BOOL toggle) { invoke<Void>(0x16A96863A17552BB, cam, toggle); }
	NATIVE_DECL void SET_USE_HI_DOF() { invoke<Void>(0xA13B0222F3D94A94); }
	NATIVE_DECL void SET_USE_HI_DOF_ON_SYNCED_SCENE_THIS_UPDATE() { invoke<Void>(0x731A880555DA3647); }
	NATIVE_DECL void SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE(Cam camera, float p1) { invoke<Void>(0xF55E4046F6F831DC, camera, p1); }
	NATIVE_DECL void SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE_BLEND_LEVEL(Any p0, float p1) { invoke<Void>(0xE111A7C0D200CBC5, p0, p1); }
	NATIVE_DECL void SET_CAM_DOF_FNUMBER_OF_LENS(Cam camera, float p1) { invoke<Void>(0x7DD234D6F3914C5B, camera, p1); }
	NATIVE_DECL void SET_CAM_DOF_FOCAL_LENGTH_MULTIPLIER(Cam camera, float multiplier) { invoke<Void>(0x47B595D60664CFFA, camera, multiplier); }
	NATIVE_DECL void SET_CAM_DOF_FOCUS_DISTANCE_BIAS(Cam camera, float p1) { invoke<Void>(0xC669EEA5D031B7DE, camera, p1); }
	NATIVE_DECL void SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(Cam camera, float p1) { invoke<Void>(0xC3654A441402562D, camera, p1); }
	NATIVE_DECL void SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(Cam camera, float p1) { invoke<Void>(0x2C654B4943BDDF7C, camera, p1); }
	NATIVE_DECL void SET_CAM_DOF_SHOULD_KEEP_LOOK_AT_TARGET_IN_FOCUS(Cam camera, BOOL state) { invoke<Void>(0x7CF3AF51DCFE4108, camera, state); }
	NATIVE_DECL void ATTACH_CAM_TO_ENTITY(Cam cam, Entity entity, float xOffset, float yOffset, float zOffset, BOOL isRelative) { invoke<Void>(0xFEDB7D269E8C60E3, cam, entity, xOffset, yOffset, zOffset, isRelative); }
	NATIVE_DECL void ATTACH_CAM_TO_PED_BONE(Cam cam, Ped ped, int boneIndex, float x, float y, float z, BOOL heading) { invoke<Void>(0x61A3DBA14AB7F411, cam, ped, boneIndex, x, y, z, heading); }
	NATIVE_DECL void HARD_ATTACH_CAM_TO_PED_BONE(Cam cam, Ped ped, int boneIndex, float p3, float p4, float p5, float p6, float p7, float p8, BOOL p9) { invoke<Void>(0x149916F50C34A40D, cam, ped, boneIndex, p3, p4, p5, p6, p7, p8, p9); }
	NATIVE_DECL void HARD_ATTACH_CAM_TO_ENTITY(Cam cam, Entity entity, float xRot, float yRot, float zRot, float xOffset, float yOffset, float zOffset, BOOL isRelative) { invoke<Void>(0x202A5ED9CE01D6E7, cam, entity, xRot, yRot, zRot, xOffset, yOffset, zOffset, isRelative); }
	NATIVE_DECL void ATTACH_CAM_TO_VEHICLE_BONE(Cam cam, Vehicle vehicle, int boneIndex, BOOL relativeRotation, float rotX, float rotY, float rotZ, float offsetX, float offsetY, float offsetZ, BOOL fixedDirection) { invoke<Void>(0x8DB3F12A02CAEF72, cam, vehicle, boneIndex, relativeRotation, rotX, rotY, rotZ, offsetX, offsetY, offsetZ, fixedDirection); }
	NATIVE_DECL void DETACH_CAM(Cam cam) { invoke<Void>(0xA2FABBE87F4BAD82, cam); }
	NATIVE_DECL void SET_CAM_INHERIT_ROLL_VEHICLE(Cam cam, BOOL p1) { invoke<Void>(0x45F1DE9C34B93AE6, cam, p1); }
	NATIVE_DECL void POINT_CAM_AT_COORD(Cam cam, float x, float y, float z) { invoke<Void>(0xF75497BB865F0803, cam, x, y, z); }
	NATIVE_DECL void POINT_CAM_AT_ENTITY(Cam cam, Entity entity, float p2, float p3, float p4, BOOL p5) { invoke<Void>(0x5640BFF86B16E8DC, cam, entity, p2, p3, p4, p5); }
	NATIVE_DECL void POINT_CAM_AT_PED_BONE(Cam cam, Ped ped, int boneIndex, float x, float y, float z, BOOL p6) { invoke<Void>(0x68B2B5F33BA63C41, cam, ped, boneIndex, x, y, z, p6); }
	NATIVE_DECL void STOP_CAM_POINTING(Cam cam) { invoke<Void>(0xF33AB75780BA57DE, cam); }
	NATIVE_DECL void SET_CAM_AFFECTS_AIMING(Cam cam, BOOL toggle) { invoke<Void>(0x8C1DC7770C51DC8D, cam, toggle); }
	NATIVE_DECL void SET_CAM_CONTROLS_MINI_MAP_HEADING(Cam cam, BOOL toggle) { invoke<Void>(0x661B5C8654ADD825, cam, toggle); }
	NATIVE_DECL void SET_CAM_IS_INSIDE_VEHICLE(Cam cam, BOOL toggle) { invoke<Void>(0xA2767257A320FC82, cam, toggle); }
	NATIVE_DECL void ALLOW_MOTION_BLUR_DECAY(Any p0, BOOL p1) { invoke<Void>(0x271017B9BA825366, p0, p1); }
	NATIVE_DECL void SET_CAM_DEBUG_NAME(Cam camera, const char* name) { invoke<Void>(0x1B93E0107865DD40, camera, name); }
	NATIVE_DECL Cam GET_DEBUG_CAM() { return invoke<Cam>(0x77C3CEC46BE286F6); }
	NATIVE_DECL void ADD_CAM_SPLINE_NODE(Cam camera, float x, float y, float z, float xRot, float yRot, float zRot, int length, int smoothingStyle, int rotationOrder) { invoke<Void>(0x8609C75EC438FB3B, camera, x, y, z, xRot, yRot, zRot, length, smoothingStyle, rotationOrder); }
	NATIVE_DECL void ADD_CAM_SPLINE_NODE_USING_CAMERA_FRAME(Cam cam, Cam cam2, int length, int p3) { invoke<Void>(0x0A9F2A468B328E74, cam, cam2, length, p3); }
	NATIVE_DECL void ADD_CAM_SPLINE_NODE_USING_CAMERA(Cam cam, Cam cam2, int length, int p3) { invoke<Void>(0x0FB82563989CF4FB, cam, cam2, length, p3); }
	NATIVE_DECL void ADD_CAM_SPLINE_NODE_USING_GAMEPLAY_FRAME(Cam cam, int length, int p2) { invoke<Void>(0x609278246A29CA34, cam, length, p2); }
	NATIVE_DECL void SET_CAM_SPLINE_PHASE(Cam cam, float p1) { invoke<Void>(0x242B5874F0A4E052, cam, p1); }
	NATIVE_DECL float GET_CAM_SPLINE_PHASE(Cam cam) { return invoke<float>(0xB5349E36C546509A, cam); }
	NATIVE_DECL float GET_CAM_SPLINE_NODE_PHASE(Cam cam) { return invoke<float>(0xD9D0E694C8282C96, cam); }
	NATIVE_DECL void SET_CAM_SPLINE_DURATION(Cam cam, int timeDuration) { invoke<Void>(0x1381539FEE034CDA, cam, timeDuration); }
	NATIVE_DECL void SET_CAM_SPLINE_SMOOTHING_STYLE(Cam cam, int smoothingStyle) { invoke<Void>(0xD1B0F412F109EA5D, cam, smoothingStyle); }
	NATIVE_DECL int GET_CAM_SPLINE_NODE_INDEX(Cam cam) { return invoke<int>(0xB22B17DF858716A6, cam); }
	NATIVE_DECL void SET_CAM_SPLINE_NODE_EASE(Cam cam, int easingFunction, int p2, float p3) { invoke<Void>(0x83B8201ED82A9A2D, cam, easingFunction, p2, p3); }
	NATIVE_DECL void SET_CAM_SPLINE_NODE_VELOCITY_SCALE(Cam cam, int p1, float scale) { invoke<Void>(0xA6385DEB180F319F, cam, p1, scale); }
	NATIVE_DECL void OVERRIDE_CAM_SPLINE_VELOCITY(Cam cam, int p1, float p2, float p3) { invoke<Void>(0x40B62FA033EB0346, cam, p1, p2, p3); }
	NATIVE_DECL void OVERRIDE_CAM_SPLINE_MOTION_BLUR(Cam cam, int p1, float p2, float p3) { invoke<Void>(0x7DCF7C708D292D55, cam, p1, p2, p3); }
	NATIVE_DECL void SET_CAM_SPLINE_NODE_EXTRA_FLAGS(Cam cam, int p1, int flags) { invoke<Void>(0x7BF1A54AE67AC070, cam, p1, flags); }
	NATIVE_DECL BOOL IS_CAM_SPLINE_PAUSED(Cam cam) { return invoke<BOOL>(0x0290F35C0AD97864, cam); }
	NATIVE_DECL void INTERPOLATE_CAMERA_WITH_PARAMS(Cam camera, float camPosX, float camPosY, float camPosZ, float camRotX, float camRotY, float camRotZ, float fov, int duration, int posCurveType, int rotCurveType, int rotOrder, int fovCurveType) { invoke<Void>(0xDDA77EE33C005AAF, camera, camPosX, camPosY, camPosZ, camRotX, camRotY, camRotZ, fov, duration, posCurveType, rotCurveType, rotOrder, fovCurveType); }
	NATIVE_DECL void _ACTIVATE_CAM_WITH_INTERP_AND_FOV_CURVE(Cam camTo, Cam camFrom, int duration, int easeLocation, int easeRotation, int easeFov) { invoke<Void>(0x34CFC4C2A38E83E3, camTo, camFrom, duration, easeLocation, easeRotation, easeFov); }
	NATIVE_DECL void SET_CAM_ACTIVE_WITH_INTERP(Cam camTo, Cam camFrom, int duration, int easeLocation, int easeRotation) { invoke<Void>(0x9FBDA379383A52A4, camTo, camFrom, duration, easeLocation, easeRotation); }
	NATIVE_DECL BOOL IS_CAM_INTERPOLATING(Cam cam) { return invoke<BOOL>(0x036F97C908C2B52C, cam); }
	NATIVE_DECL void SHAKE_CAM(Cam cam, const char* type, float amplitude) { invoke<Void>(0x6A25241C340D3822, cam, type, amplitude); }
	NATIVE_DECL void ANIMATED_SHAKE_CAM(Cam cam, const char* p1, const char* p2, const char* p3, float amplitude) { invoke<Void>(0xA2746EEAE3E577CD, cam, p1, p2, p3, amplitude); }
	NATIVE_DECL BOOL IS_CAM_SHAKING(Cam cam) { return invoke<BOOL>(0x6B24BFE83A2BE47B, cam); }
	NATIVE_DECL void SET_CAM_SHAKE_AMPLITUDE(Cam cam, float amplitude) { invoke<Void>(0xD93DB43B82BC0D00, cam, amplitude); }
	NATIVE_DECL void STOP_CAM_SHAKING(Cam cam, BOOL p1) { invoke<Void>(0xBDECF64367884AC3, cam, p1); }
	NATIVE_DECL void SHAKE_SCRIPT_GLOBAL(const char* p0, float p1) { invoke<Void>(0xF4C8CF9E353AFECA, p0, p1); }
	NATIVE_DECL void ANIMATED_SHAKE_SCRIPT_GLOBAL(const char* p0, const char* p1, const char* p2, float p3) { invoke<Void>(0xC2EAE3FB8CDBED31, p0, p1, p2, p3); }
	NATIVE_DECL BOOL IS_SCRIPT_GLOBAL_SHAKING() { return invoke<BOOL>(0xC912AF078AF19212); }
	NATIVE_DECL void STOP_SCRIPT_GLOBAL_SHAKING(BOOL p0) { invoke<Void>(0x1C9D7949FA533490, p0); }
	NATIVE_DECL void TRIGGER_VEHICLE_PART_BROKEN_CAMERA_SHAKE(Vehicle vehicle, int p1, float p2) { invoke<Void>(0x5D96CFB59DA076A0, vehicle, p1, p2); }
	NATIVE_DECL BOOL PLAY_CAM_ANIM(Cam cam, const char* animName, const char* animDictionary, float x, float y, float z, float xRot, float yRot, float zRot, BOOL p9, int p10) { return invoke<BOOL>(0x9A2D0FB2E7852392, cam, animName, animDictionary, x, y, z, xRot, yRot, zRot, p9, p10); }
	NATIVE_DECL BOOL IS_CAM_PLAYING_ANIM(Cam cam, const char* animName, const char* animDictionary) { return invoke<BOOL>(0xC90621D8A0CEECF2, cam, animName, animDictionary); }
	NATIVE_DECL void SET_CAM_ANIM_CURRENT_PHASE(Cam cam, float phase) { invoke<Void>(0x4145A4C44FF3B5A6, cam, phase); }
	NATIVE_DECL float GET_CAM_ANIM_CURRENT_PHASE(Cam cam) { return invoke<float>(0xA10B2DB49E92A6B0, cam); }
	NATIVE_DECL BOOL PLAY_SYNCHRONIZED_CAM_ANIM(Any p0, Any p1, const char* animName, const char* animDictionary) { return invoke<BOOL>(0xE32EFE9AB4A9AA0C, p0, p1, animName, animDictionary); }
	NATIVE_DECL void SET_FLY_CAM_HORIZONTAL_RESPONSE(Cam cam, float p1, float p2, float p3) { invoke<Void>(0x503F5920162365B2, cam, p1, p2, p3); }
	NATIVE_DECL void SET_FLY_CAM_VERTICAL_RESPONSE(Cam cam, float p1, float p2, float p3) { invoke<Void>(0xE827B9382CFB41BA, cam, p1, p2, p3); }
	NATIVE_DECL void SET_FLY_CAM_MAX_HEIGHT(Cam cam, float height) { invoke<Void>(0xF9D02130ECDD1D77, cam, height); }
	NATIVE_DECL void SET_FLY_CAM_COORD_AND_CONSTRAIN(Cam cam, float x, float y, float z) { invoke<Void>(0xC91C6C55199308CA, cam, x, y, z); }
	NATIVE_DECL void SET_FLY_CAM_VERTICAL_CONTROLS_THIS_UPDATE(Cam cam) { invoke<Void>(0xC8B5C4A79CC18B94, cam); }
	NATIVE_DECL BOOL WAS_FLY_CAM_CONSTRAINED_ON_PREVIOUS_UDPATE(Cam cam) { return invoke<BOOL>(0x5C48A1D6E3B33179, cam); }
	NATIVE_DECL BOOL IS_SCREEN_FADED_OUT() { return invoke<BOOL>(0xB16FCE9DDC7BA182); }
	NATIVE_DECL BOOL IS_SCREEN_FADED_IN() { return invoke<BOOL>(0x5A859503B0C08678); }
	NATIVE_DECL BOOL IS_SCREEN_FADING_OUT() { return invoke<BOOL>(0x797AC7CB535BA28F); }
	NATIVE_DECL BOOL IS_SCREEN_FADING_IN() { return invoke<BOOL>(0x5C544BC6C57AC575); }
	NATIVE_DECL void DO_SCREEN_FADE_IN(int duration) { invoke<Void>(0xD4E8E24955024033, duration); }
	NATIVE_DECL void DO_SCREEN_FADE_OUT(int duration) { invoke<Void>(0x891B5B39AC6302AF, duration); }
	NATIVE_DECL void SET_WIDESCREEN_BORDERS(BOOL p0, int p1) { invoke<Void>(0xDCD4EA924F42D01A, p0, p1); }
	NATIVE_DECL BOOL ARE_WIDESCREEN_BORDERS_ACTIVE() { return invoke<BOOL>(0x4879E4FE39074CDF); }
	NATIVE_DECL Vector3 GET_GAMEPLAY_CAM_COORD() { return invoke<Vector3>(0x14D6F5678D8F1B37); }
	NATIVE_DECL Vector3 GET_GAMEPLAY_CAM_ROT(int rotationOrder) { return invoke<Vector3>(0x837765A25378F0BB, rotationOrder); }
	NATIVE_DECL float GET_GAMEPLAY_CAM_FOV() { return invoke<float>(0x65019750A0324133); }
	NATIVE_DECL void SET_GAMEPLAY_CAM_MOTION_BLUR_SCALING_THIS_UPDATE(float p0) { invoke<Void>(0x487A82C650EB7799, p0); }
	NATIVE_DECL void SET_GAMEPLAY_CAM_MAX_MOTION_BLUR_STRENGTH_THIS_UPDATE(float p0) { invoke<Void>(0x0225778816FDC28C, p0); }
	NATIVE_DECL float GET_GAMEPLAY_CAM_RELATIVE_HEADING() { return invoke<float>(0x743607648ADD4587); }
	NATIVE_DECL void SET_GAMEPLAY_CAM_RELATIVE_HEADING(float heading) { invoke<Void>(0xB4EC2312F4E5B1F1, heading); }
	NATIVE_DECL float GET_GAMEPLAY_CAM_RELATIVE_PITCH() { return invoke<float>(0x3A6867B4845BEDA2); }
	NATIVE_DECL void SET_GAMEPLAY_CAM_RELATIVE_PITCH(float angle, float scalingFactor) { invoke<Void>(0x6D0858B8EDFD2B7D, angle, scalingFactor); }
	NATIVE_DECL void RESET_GAMEPLAY_CAM_FULL_ATTACH_PARENT_TRANSFORM_TIMER() { invoke<Void>(0x7295C203DD659DFE); }
	NATIVE_DECL void FORCE_CAMERA_RELATIVE_HEADING_AND_PITCH(float roll, float pitch, float yaw) { invoke<Void>(0x48608C3464F58AB4, roll, pitch, yaw); }
	NATIVE_DECL void FORCE_BONNET_CAMERA_RELATIVE_HEADING_AND_PITCH(float p0, float p1) { invoke<Void>(0x28B022A17B068A3A, p0, p1); }
	NATIVE_DECL void SET_FIRST_PERSON_SHOOTER_CAMERA_HEADING(float yaw) { invoke<Void>(0x103991D4A307D472, yaw); }
	NATIVE_DECL void SET_FIRST_PERSON_SHOOTER_CAMERA_PITCH(float pitch) { invoke<Void>(0x759E13EBC1C15C5A, pitch); }
	NATIVE_DECL void SET_SCRIPTED_CAMERA_IS_FIRST_PERSON_THIS_FRAME(BOOL p0) { invoke<Void>(0x469F2ECDEC046337, p0); }
	NATIVE_DECL void SHAKE_GAMEPLAY_CAM(const char* shakeName, float intensity) { invoke<Void>(0xFD55E49555E017CF, shakeName, intensity); }
	NATIVE_DECL BOOL IS_GAMEPLAY_CAM_SHAKING() { return invoke<BOOL>(0x016C090630DF1F89); }
	NATIVE_DECL void SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(float amplitude) { invoke<Void>(0xA87E00932DB4D85D, amplitude); }
	NATIVE_DECL void STOP_GAMEPLAY_CAM_SHAKING(BOOL p0) { invoke<Void>(0x0EF93E9F3D08C178, p0); }
	NATIVE_DECL void SET_GAMEPLAY_CAM_FOLLOW_PED_THIS_UPDATE(Ped ped) { invoke<Void>(0x8BBACBF51DA047A8, ped); }
	NATIVE_DECL BOOL IS_GAMEPLAY_CAM_RENDERING() { return invoke<BOOL>(0x39B5D1B10383F0C8); }
	NATIVE_DECL BOOL IS_INTERPOLATING_FROM_SCRIPT_CAMS() { return invoke<BOOL>(0x3044240D2E0FA842); }
	NATIVE_DECL BOOL IS_INTERPOLATING_TO_SCRIPT_CAMS() { return invoke<BOOL>(0x705A276EBFF3133D); }
	NATIVE_DECL void SET_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_STATE(BOOL p0) { invoke<Void>(0xDB90C6CCA48940F1, p0); }
	NATIVE_DECL void DISABLE_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_THIS_UPDATE() { invoke<Void>(0xEA7F0AD7E9BA676F); }
	NATIVE_DECL BOOL IS_GAMEPLAY_CAM_LOOKING_BEHIND() { return invoke<BOOL>(0x70FDA869F3317EA9); }
	NATIVE_DECL void SET_GAMEPLAY_CAM_IGNORE_ENTITY_COLLISION_THIS_UPDATE(Entity entity) { invoke<Void>(0x2AED6301F67007D5, entity); }
	NATIVE_DECL void DISABLE_CAM_COLLISION_FOR_OBJECT(Entity entity) { invoke<Void>(0x49482F9FCD825AAA, entity); }
	NATIVE_DECL void BYPASS_CAMERA_COLLISION_BUOYANCY_TEST_THIS_UPDATE() { invoke<Void>(0xA7092AFE81944852); }
	NATIVE_DECL void SET_GAMEPLAY_CAM_ENTITY_TO_LIMIT_FOCUS_OVER_BOUNDING_SPHERE_THIS_UPDATE(Entity entity) { invoke<Void>(0xFD3151CD37EA2245, entity); }
	NATIVE_DECL void DISABLE_FIRST_PERSON_CAMERA_WATER_CLIPPING_TEST_THIS_UPDATE() { invoke<Void>(0xB1381B97F70C7B30); }
	NATIVE_DECL void SET_FOLLOW_CAM_IGNORE_ATTACH_PARENT_MOVEMENT_THIS_UPDATE() { invoke<Void>(0xDD79DF9F4D26E1C9); }
	NATIVE_DECL BOOL IS_SPHERE_VISIBLE(float x, float y, float z, float radius) { return invoke<BOOL>(0xE33D59DA70B58FDF, x, y, z, radius); }
	NATIVE_DECL BOOL IS_FOLLOW_PED_CAM_ACTIVE() { return invoke<BOOL>(0xC6D3D26810C8E0F9); }
	NATIVE_DECL BOOL SET_FOLLOW_PED_CAM_THIS_UPDATE(const char* camName, int p1) { return invoke<BOOL>(0x44A113DD6FFC48D1, camName, p1); }
	NATIVE_DECL void USE_SCRIPT_CAM_FOR_AMBIENT_POPULATION_ORIGIN_THIS_FRAME(BOOL p0, BOOL p1) { invoke<Void>(0x271401846BD26E92, p0, p1); }
	NATIVE_DECL void SET_FOLLOW_PED_CAM_LADDER_ALIGN_THIS_UPDATE() { invoke<Void>(0xC8391C309684595A); }
	NATIVE_DECL void SET_THIRD_PERSON_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(float minimum, float maximum) { invoke<Void>(0x8F993D26E0CA5E8E, minimum, maximum); }
	NATIVE_DECL void SET_THIRD_PERSON_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(float minimum, float maximum) { invoke<Void>(0xA516C198B7DCA1E1, minimum, maximum); }
	NATIVE_DECL void SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE(float p0, float distance) { invoke<Void>(0xDF2E1F7742402E81, p0, distance); }
	NATIVE_DECL float _GET_THIRD_PERSON_CAM_MIN_ORBIT_DISTANCE_SPRING() { return invoke<float>(0xBC456FB703431785); }
	NATIVE_DECL float _GET_THIRD_PERSON_CAM_MAX_ORBIT_DISTANCE_SPRING() { return invoke<float>(0xD4592A16D36673ED); }
	NATIVE_DECL void SET_IN_VEHICLE_CAM_STATE_THIS_UPDATE(Vehicle p0, int p1) { invoke<Void>(0xE9EA16D6E54CDCA4, p0, p1); }
	NATIVE_DECL void DISABLE_ON_FOOT_FIRST_PERSON_VIEW_THIS_UPDATE() { invoke<Void>(0xDE2EF5DA284CC8DF); }
	NATIVE_DECL void DISABLE_FIRST_PERSON_FLASH_EFFECT_THIS_UPDATE() { invoke<Void>(0x59424BD75174C9B1); }
	NATIVE_DECL void BLOCK_FIRST_PERSON_ORIENTATION_RESET_THIS_UPDATE() { invoke<Void>(0x9F97DA93681F87EA); }
	NATIVE_DECL int GET_FOLLOW_PED_CAM_ZOOM_LEVEL() { return invoke<int>(0x33E6C8EFD0CD93E9); }
	NATIVE_DECL int GET_FOLLOW_PED_CAM_VIEW_MODE() { return invoke<int>(0x8D4D46230B2C353A); }
	NATIVE_DECL void SET_FOLLOW_PED_CAM_VIEW_MODE(int viewMode) { invoke<Void>(0x5A4F9EDF1673F704, viewMode); }
	NATIVE_DECL BOOL IS_FOLLOW_VEHICLE_CAM_ACTIVE() { return invoke<BOOL>(0xCBBDE6D335D6D496); }
	NATIVE_DECL void SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_THIS_UPDATE(BOOL p0) { invoke<Void>(0x91EF6EE6419E5B97, p0); }
	NATIVE_DECL void SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_EVERY_UPDATE(BOOL p0, BOOL p1) { invoke<Void>(0x9DFE13ECDC1EC196, p0, p1); }
	NATIVE_DECL BOOL SET_TABLE_GAMES_CAMERA_THIS_UPDATE(Hash hash) { return invoke<BOOL>(0x79C0E43EB9B944E2, hash); }
	NATIVE_DECL int GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL() { return invoke<int>(0xEE82280AB767B690); }
	NATIVE_DECL void SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(int zoomLevel) { invoke<Void>(0x19464CB6E4078C8A, zoomLevel); }
	NATIVE_DECL int GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() { return invoke<int>(0xA4FF579AC0E3AAAE); }
	NATIVE_DECL void SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(int viewMode) { invoke<Void>(0xAC253D7842768F48, viewMode); }
	NATIVE_DECL int GET_CAM_VIEW_MODE_FOR_CONTEXT(int context) { return invoke<int>(0xEE778F8C7E1142E2, context); }
	NATIVE_DECL void SET_CAM_VIEW_MODE_FOR_CONTEXT(int context, int viewMode) { invoke<Void>(0x2A2173E46DAECD12, context, viewMode); }
	NATIVE_DECL int GET_CAM_ACTIVE_VIEW_MODE_CONTEXT() { return invoke<int>(0x19CAFA3C87F7C2FF); }
	NATIVE_DECL void USE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE() { invoke<Void>(0x6493CF69859B116A); }
	NATIVE_DECL void USE_DEDICATED_STUNT_CAMERA_THIS_UPDATE(const char* camName) { invoke<Void>(0x425A920FDB9A0DDA, camName); }
	NATIVE_DECL void FORCE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE() { invoke<Void>(0x0AA27680A0BD43FA); }
	NATIVE_DECL void SET_FOLLOW_VEHICLE_CAM_SEAT_THIS_UPDATE(int seatIndex) { invoke<Void>(0x5C90CAB09951A12F, seatIndex); }
	NATIVE_DECL BOOL IS_AIM_CAM_ACTIVE() { return invoke<BOOL>(0x68EDDA28A5976D07); }
	NATIVE_DECL BOOL IS_AIM_CAM_ACTIVE_IN_ACCURATE_MODE() { return invoke<BOOL>(0x74BD83EA840F6BC9); }
	NATIVE_DECL BOOL IS_FIRST_PERSON_AIM_CAM_ACTIVE() { return invoke<BOOL>(0x5E346D934122613F); }
	NATIVE_DECL void DISABLE_AIM_CAM_THIS_UPDATE() { invoke<Void>(0x1A31FE0049E542F6); }
	NATIVE_DECL float GET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR() { return invoke<float>(0x7EC52CC40597D170); }
	NATIVE_DECL void SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR(float zoomFactor) { invoke<Void>(0x70894BD0915C5BCA, zoomFactor); }
	NATIVE_DECL void SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR_LIMITS_THIS_UPDATE(float p0, float p1) { invoke<Void>(0xCED08CBE8EBB97C7, p0, p1); }
	NATIVE_DECL void SET_FIRST_PERSON_AIM_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(float p0, float p1) { invoke<Void>(0x2F7F2B26DD3F18EE, p0, p1); }
	NATIVE_DECL void SET_FIRST_PERSON_AIM_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(float p0, float p1) { invoke<Void>(0xBCFC632DB7673BF0, p0, p1); }
	NATIVE_DECL void SET_FIRST_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(float p0) { invoke<Void>(0x0AF7B437918103B3, p0); }
	NATIVE_DECL void SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(float p0) { invoke<Void>(0x42156508606DE65E, p0); }
	NATIVE_DECL void SET_ALLOW_CUSTOM_VEHICLE_DRIVE_BY_CAM_THIS_UPDATE(BOOL p0) { invoke<Void>(0x4008EDF7D6E48175, p0); }
	NATIVE_DECL void FORCE_TIGHTSPACE_CUSTOM_FRAMING_THIS_UPDATE() { invoke<Void>(0x380B4968D1E09E55); }
	NATIVE_DECL Vector3 GET_FINAL_RENDERED_CAM_COORD() { return invoke<Vector3>(0xA200EB1EE790F448); }
	NATIVE_DECL Vector3 GET_FINAL_RENDERED_CAM_ROT(int rotationOrder) { return invoke<Vector3>(0x5B4E4C817FCC2DFB, rotationOrder); }
	NATIVE_DECL Vector3 GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_ROT(Player player, int rotationOrder) { return invoke<Vector3>(0x26903D9CD1175F2C, player, rotationOrder); }
	NATIVE_DECL float GET_FINAL_RENDERED_CAM_FOV() { return invoke<float>(0x80EC114669DAEFF4); }
	NATIVE_DECL float GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_FOV(Player player) { return invoke<float>(0x5F35F6732C3FBBA0, player); }
	NATIVE_DECL float GET_FINAL_RENDERED_CAM_NEAR_CLIP() { return invoke<float>(0xD0082607100D7193); }
	NATIVE_DECL float GET_FINAL_RENDERED_CAM_FAR_CLIP() { return invoke<float>(0xDFC8CBC606FDB0FC); }
	NATIVE_DECL float GET_FINAL_RENDERED_CAM_NEAR_DOF() { return invoke<float>(0xA03502FC581F7D9B); }
	NATIVE_DECL float GET_FINAL_RENDERED_CAM_FAR_DOF() { return invoke<float>(0x9780F32BCAF72431); }
	NATIVE_DECL float GET_FINAL_RENDERED_CAM_MOTION_BLUR_STRENGTH() { return invoke<float>(0x162F9D995753DC19); }
	NATIVE_DECL void SET_GAMEPLAY_COORD_HINT(float x, float y, float z, int duration, int blendOutDuration, int blendInDuration, int p6) { invoke<Void>(0xD51ADCD2D8BC0FB3, x, y, z, duration, blendOutDuration, blendInDuration, p6); }
	NATIVE_DECL void SET_GAMEPLAY_PED_HINT(Ped ped, float x1, float y1, float z1, BOOL p4, int duration, int blendOutDuration, int blendInDuration) { invoke<Void>(0x2B486269ACD548D3, ped, x1, y1, z1, p4, duration, blendOutDuration, blendInDuration); }
	NATIVE_DECL void SET_GAMEPLAY_VEHICLE_HINT(Vehicle vehicle, float offsetX, float offsetY, float offsetZ, BOOL p4, int time, int easeInTime, int easeOutTime) { invoke<Void>(0xA2297E18F3E71C2E, vehicle, offsetX, offsetY, offsetZ, p4, time, easeInTime, easeOutTime); }
	NATIVE_DECL void SET_GAMEPLAY_OBJECT_HINT(Object object, float xOffset, float yOffset, float zOffset, BOOL p4, int time, int easeInTime, int easeOutTime) { invoke<Void>(0x83E87508A2CA2AC6, object, xOffset, yOffset, zOffset, p4, time, easeInTime, easeOutTime); }
	NATIVE_DECL void SET_GAMEPLAY_ENTITY_HINT(Entity entity, float xOffset, float yOffset, float zOffset, BOOL p4, int time, int easeInTime, int easeOutTime, int p8) { invoke<Void>(0x189E955A8313E298, entity, xOffset, yOffset, zOffset, p4, time, easeInTime, easeOutTime, p8); }
	NATIVE_DECL BOOL IS_GAMEPLAY_HINT_ACTIVE() { return invoke<BOOL>(0xE520FF1AD2785B40); }
	NATIVE_DECL void STOP_GAMEPLAY_HINT(BOOL p0) { invoke<Void>(0xF46C581C61718916, p0); }
	NATIVE_DECL void STOP_GAMEPLAY_HINT_BEING_CANCELLED_THIS_UPDATE(BOOL p0) { invoke<Void>(0xCCD078C2665D2973, p0); }
	NATIVE_DECL void STOP_CODE_GAMEPLAY_HINT(BOOL p0) { invoke<Void>(0x247ACBC4ABBC9D1C, p0); }
	NATIVE_DECL BOOL IS_CODE_GAMEPLAY_HINT_ACTIVE() { return invoke<BOOL>(0xBF72910D0F26F025); }
	NATIVE_DECL void SET_GAMEPLAY_HINT_FOV(float FOV) { invoke<Void>(0x513403FB9C56211F, FOV); }
	NATIVE_DECL void SET_GAMEPLAY_HINT_FOLLOW_DISTANCE_SCALAR(float value) { invoke<Void>(0xF8BDBF3D573049A1, value); }
	NATIVE_DECL void SET_GAMEPLAY_HINT_BASE_ORBIT_PITCH_OFFSET(float value) { invoke<Void>(0xD1F8363DFAD03848, value); }
	NATIVE_DECL void SET_GAMEPLAY_HINT_CAMERA_RELATIVE_SIDE_OFFSET(float xOffset) { invoke<Void>(0x5D7B620DAE436138, xOffset); }
	NATIVE_DECL void SET_GAMEPLAY_HINT_CAMERA_RELATIVE_VERTICAL_OFFSET(float yOffset) { invoke<Void>(0xC92717EF615B6704, yOffset); }
	NATIVE_DECL void SET_GAMEPLAY_HINT_CAMERA_BLEND_TO_FOLLOW_PED_MEDIUM_VIEW_MODE(BOOL toggle) { invoke<Void>(0xE3433EADAAF7EE40, toggle); }
	NATIVE_DECL void SET_CINEMATIC_BUTTON_ACTIVE(BOOL p0) { invoke<Void>(0x51669F7D1FB53D9F, p0); }
	NATIVE_DECL BOOL IS_CINEMATIC_CAM_RENDERING() { return invoke<BOOL>(0xB15162CB5826E9E8); }
	NATIVE_DECL void SHAKE_CINEMATIC_CAM(const char* shakeType, float amount) { invoke<Void>(0xDCE214D9ED58F3CF, shakeType, amount); }
	NATIVE_DECL BOOL IS_CINEMATIC_CAM_SHAKING() { return invoke<BOOL>(0xBBC08F6B4CB8FF0A); }
	NATIVE_DECL void SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(float p0) { invoke<Void>(0xC724C701C30B2FE7, p0); }
	NATIVE_DECL void STOP_CINEMATIC_CAM_SHAKING(BOOL p0) { invoke<Void>(0x2238E588E588A6D7, p0); }
	NATIVE_DECL void DISABLE_CINEMATIC_BONNET_CAMERA_THIS_UPDATE() { invoke<Void>(0xADFF1B2A555F5FBA); }
	NATIVE_DECL void DISABLE_CINEMATIC_VEHICLE_IDLE_MODE_THIS_UPDATE() { invoke<Void>(0x62ECFCFDEE7885D6); }
	NATIVE_DECL void INVALIDATE_CINEMATIC_VEHICLE_IDLE_MODE() { invoke<Void>(0x9E4CFFF989258472); }
	NATIVE_DECL void INVALIDATE_IDLE_CAM() { invoke<Void>(0xF4F2C0D4EE209E20); }
	NATIVE_DECL BOOL IS_CINEMATIC_IDLE_CAM_RENDERING() { return invoke<BOOL>(0xCA9D2AA3E326D720); }
	NATIVE_DECL BOOL IS_CINEMATIC_FIRST_PERSON_VEHICLE_INTERIOR_CAM_RENDERING() { return invoke<BOOL>(0x4F32C0D5A90A9B40); }
	NATIVE_DECL void CREATE_CINEMATIC_SHOT(Hash p0, int time, BOOL p2, Entity entity) { invoke<Void>(0x741B0129D4560F31, p0, time, p2, entity); }
	NATIVE_DECL BOOL IS_CINEMATIC_SHOT_ACTIVE(Hash p0) { return invoke<BOOL>(0xCC9F3371A7C28BC9, p0); }
	NATIVE_DECL void STOP_CINEMATIC_SHOT(Hash p0) { invoke<Void>(0x7660C6E75D3A078E, p0); }
	NATIVE_DECL void FORCE_CINEMATIC_RENDERING_THIS_UPDATE(BOOL toggle) { invoke<Void>(0xA41BCD7213805AAC, toggle); }
	NATIVE_DECL void SET_CINEMATIC_NEWS_CHANNEL_ACTIVE_THIS_UPDATE() { invoke<Void>(0xDC9DA9E8789F5246); }
	NATIVE_DECL void SET_CINEMATIC_MODE_ACTIVE(BOOL toggle) { invoke<Void>(0xDCF0754AC3D6FD4E, toggle); }
	NATIVE_DECL BOOL IS_IN_VEHICLE_MOBILE_PHONE_CAMERA_RENDERING() { return invoke<BOOL>(0x1F2300CB7FA7B7F6); }
	NATIVE_DECL BOOL DISABLE_CINEMATIC_SLOW_MO_THIS_UPDATE() { return invoke<BOOL>(0x17FCA7199A530203); }
	NATIVE_DECL BOOL IS_BONNET_CINEMATIC_CAM_RENDERING() { return invoke<BOOL>(0xD7360051C885628B); }
	NATIVE_DECL BOOL IS_CINEMATIC_CAM_INPUT_ACTIVE() { return invoke<BOOL>(0xF5F1E89A970B7796); }
	NATIVE_DECL void IGNORE_MENU_PREFERENCE_FOR_BONNET_CAMERA_THIS_UPDATE() { invoke<Void>(0x7B8A361C1813FBEF); }
	NATIVE_DECL void BYPASS_CUTSCENE_CAM_RENDERING_THIS_UPDATE() { invoke<Void>(0xDB629FFD9285FA06); }
	NATIVE_DECL void STOP_CUTSCENE_CAM_SHAKING(Any p0) { invoke<Void>(0x324C5AA411DA7737, p0); }
	NATIVE_DECL void SET_CUTSCENE_CAM_FAR_CLIP_THIS_UPDATE(float p0) { invoke<Void>(0x12DED8CA53D47EA5, p0); }
	NATIVE_DECL Ped GET_FOCUS_PED_ON_SCREEN(float p0, int p1, float p2, float p3, float p4, float p5, float p6, int p7, int p8) { return invoke<Ped>(0x89215EC747DF244A, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL void DISABLE_NEAR_CLIP_SCAN_THIS_UPDATE() { invoke<Void>(0x5A43C76F7FC7BA5F); }
	NATIVE_DECL void SET_CAM_DEATH_FAIL_EFFECT_STATE(int p0) { invoke<Void>(0x80C8B1846639BB19, p0); }
	NATIVE_DECL void SET_FIRST_PERSON_FLASH_EFFECT_TYPE(Any p0) { invoke<Void>(0x5C41E6BABC9E2112, p0); }
	NATIVE_DECL void SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_NAME(const char* vehicleName) { invoke<Void>(0x21E253A7F8DA5DFB, vehicleName); }
	NATIVE_DECL void SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_HASH(Hash vehicleModel) { invoke<Void>(0x11FA5D3479C7DD47, vehicleModel); }
	NATIVE_DECL BOOL IS_ALLOWED_INDEPENDENT_CAMERA_MODES() { return invoke<BOOL>(0xEAF0FA793D05C592); }
	NATIVE_DECL void CAMERA_PREVENT_COLLISION_SETTINGS_FOR_TRIPLEHEAD_IN_INTERIORS_THIS_UPDATE() { invoke<Void>(0x62374889A4D59F72); }
	NATIVE_DECL float REPLAY_GET_MAX_DISTANCE_ALLOWED_FROM_PLAYER() { return invoke<float>(0x8BFCEB5EA1B161B6); }
}

namespace CLOCK
{
	NATIVE_DECL void SET_CLOCK_TIME(int hour, int minute, int second) { invoke<Void>(0x47C3B5848C3E45D8, hour, minute, second); }
	NATIVE_DECL void PAUSE_CLOCK(BOOL toggle) { invoke<Void>(0x4055E40BD2DBEC1D, toggle); }
	NATIVE_DECL void ADVANCE_CLOCK_TIME_TO(int hour, int minute, int second) { invoke<Void>(0xC8CA9670B9D83B3B, hour, minute, second); }
	NATIVE_DECL void ADD_TO_CLOCK_TIME(int hours, int minutes, int seconds) { invoke<Void>(0xD716F30D8C8980E2, hours, minutes, seconds); }
	NATIVE_DECL int GET_CLOCK_HOURS() { return invoke<int>(0x25223CA6B4D20B7F); }
	NATIVE_DECL int GET_CLOCK_MINUTES() { return invoke<int>(0x13D2B8ADD79640F2); }
	NATIVE_DECL int GET_CLOCK_SECONDS() { return invoke<int>(0x494E97C2EF27C470); }
	NATIVE_DECL void SET_CLOCK_DATE(int day, int month, int year) { invoke<Void>(0xB096419DF0D06CE7, day, month, year); }
	NATIVE_DECL int GET_CLOCK_DAY_OF_WEEK() { return invoke<int>(0xD972E4BD7AEB235F); }
	NATIVE_DECL int GET_CLOCK_DAY_OF_MONTH() { return invoke<int>(0x3D10BC92A4DB1D35); }
	NATIVE_DECL int GET_CLOCK_MONTH() { return invoke<int>(0xBBC72712E80257A1); }
	NATIVE_DECL int GET_CLOCK_YEAR() { return invoke<int>(0x961777E64BDAF717); }
	NATIVE_DECL int GET_MILLISECONDS_PER_GAME_MINUTE() { return invoke<int>(0x2F8B4D1C595B11DB); }
	NATIVE_DECL void GET_POSIX_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second) { invoke<Void>(0xDA488F299A5B164E, year, month, day, hour, minute, second); }
	NATIVE_DECL void GET_UTC_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second) { invoke<Void>(0x8117E09A19EEF4D3, year, month, day, hour, minute, second); }
	NATIVE_DECL void GET_LOCAL_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second) { invoke<Void>(0x50C7A99057A69748, year, month, day, hour, minute, second); }
}

namespace CUTSCENE
{
	NATIVE_DECL void REQUEST_CUTSCENE(const char* cutsceneName, int flags) { invoke<Void>(0x7A86743F475D9E09, cutsceneName, flags); }
	NATIVE_DECL void REQUEST_CUTSCENE_WITH_PLAYBACK_LIST(const char* cutsceneName, int playbackFlags, int flags) { invoke<Void>(0xC23DE0E91C30B58C, cutsceneName, playbackFlags, flags); }
	NATIVE_DECL void REMOVE_CUTSCENE() { invoke<Void>(0x440AF51A3462B86F); }
	NATIVE_DECL BOOL HAS_CUTSCENE_LOADED() { return invoke<BOOL>(0xC59F528E9AB9F339); }
	NATIVE_DECL BOOL HAS_THIS_CUTSCENE_LOADED(const char* cutsceneName) { return invoke<BOOL>(0x228D3D94F8A11C3C, cutsceneName); }
	NATIVE_DECL void SET_SCRIPT_CAN_START_CUTSCENE(int threadId) { invoke<Void>(0x8D9DF6ECA8768583, threadId); }
	NATIVE_DECL BOOL CAN_REQUEST_ASSETS_FOR_CUTSCENE_ENTITY() { return invoke<BOOL>(0xB56BBBCC2955D9CB); }
	NATIVE_DECL BOOL IS_CUTSCENE_PLAYBACK_FLAG_SET(int flag) { return invoke<BOOL>(0x71B74D2AE19338D0, flag); }
	NATIVE_DECL void SET_CUTSCENE_ENTITY_STREAMING_FLAGS(const char* cutsceneEntName, int p1, int p2) { invoke<Void>(0x4C61C75BEE8184C2, cutsceneEntName, p1, p2); }
	NATIVE_DECL void REQUEST_CUT_FILE(const char* cutsceneName) { invoke<Void>(0x06A3524161C502BA, cutsceneName); }
	NATIVE_DECL BOOL HAS_CUT_FILE_LOADED(const char* cutsceneName) { return invoke<BOOL>(0xA1C996C2A744262E, cutsceneName); }
	NATIVE_DECL void REMOVE_CUT_FILE(const char* cutsceneName) { invoke<Void>(0xD00D76A7DFC9D852, cutsceneName); }
	NATIVE_DECL Vector3 GET_CUT_FILE_OFFSET(const char* cutsceneName, int index) { return invoke<Vector3>(0x1FA904B60E492336, cutsceneName, index); }
	NATIVE_DECL int GET_CUT_FILE_CONCAT_COUNT(const char* cutsceneName) { return invoke<int>(0x0ABC54DE641DC0FC, cutsceneName); }
	NATIVE_DECL void START_CUTSCENE(int flags) { invoke<Void>(0x186D5CB5E7B0FF7B, flags); }
	NATIVE_DECL void START_CUTSCENE_AT_COORDS(float x, float y, float z, int flags) { invoke<Void>(0x1C9ADDA3244A1FBF, x, y, z, flags); }
	NATIVE_DECL void STOP_CUTSCENE(BOOL p0) { invoke<Void>(0xC7272775B4DC786E, p0); }
	NATIVE_DECL void STOP_CUTSCENE_IMMEDIATELY() { invoke<Void>(0xD220BDD222AC4A1E); }
	NATIVE_DECL void SET_CUTSCENE_ORIGIN(float x, float y, float z, float p3, int p4) { invoke<Void>(0xB812B3FD1C01CF27, x, y, z, p3, p4); }
	NATIVE_DECL void SET_CUTSCENE_ORIGIN_AND_ORIENTATION(float x1, float y1, float z1, float x2, float y2, float z2, int p6) { invoke<Void>(0x011883F41211432A, x1, y1, z1, x2, y2, z2, p6); }
	NATIVE_DECL int GET_CUTSCENE_TIME() { return invoke<int>(0xE625BEABBAFFDAB9); }
	NATIVE_DECL int GET_CUTSCENE_PLAY_TIME() { return invoke<int>(0x710286BC5EF4D6E1); }
	NATIVE_DECL int GET_CUTSCENE_TOTAL_DURATION() { return invoke<int>(0xEE53B14A19E480D4); }
	NATIVE_DECL int GET_CUTSCENE_END_TIME() { return invoke<int>(0x971D7B15BCDBEF99); }
	NATIVE_DECL int GET_CUTSCENE_PLAY_DURATION() { return invoke<int>(0x5D583F71C901F2A3); }
	NATIVE_DECL BOOL WAS_CUTSCENE_SKIPPED() { return invoke<BOOL>(0x40C8656EDAEDD569); }
	NATIVE_DECL BOOL HAS_CUTSCENE_FINISHED() { return invoke<BOOL>(0x7C0A893088881D57); }
	NATIVE_DECL BOOL IS_CUTSCENE_ACTIVE() { return invoke<BOOL>(0x991251AFC3981F84); }
	NATIVE_DECL BOOL IS_CUTSCENE_PLAYING() { return invoke<BOOL>(0xD3C2E180A40F031E); }
	NATIVE_DECL int GET_CUTSCENE_SECTION_PLAYING() { return invoke<int>(0x49010A6A396553D8); }
	NATIVE_DECL Entity GET_ENTITY_INDEX_OF_CUTSCENE_ENTITY(const char* cutsceneEntName, Hash modelHash) { return invoke<Entity>(0x0A2E9FDB9A8C62F6, cutsceneEntName, modelHash); }
	NATIVE_DECL int GET_CUTSCENE_CONCAT_SECTION_PLAYING() { return invoke<int>(0x583DF8E3D4AFBD98); }
	NATIVE_DECL BOOL IS_CUTSCENE_AUTHORIZED(const char* cutsceneName) { return invoke<BOOL>(0x4CEBC1ED31E8925E, cutsceneName); }
	NATIVE_DECL int DOES_CUTSCENE_HANDLE_EXIST(int cutsceneHandle) { return invoke<int>(0x4FCD976DA686580C, cutsceneHandle); }
	NATIVE_DECL void REGISTER_ENTITY_FOR_CUTSCENE(Ped cutscenePed, const char* cutsceneEntName, int p2, Hash modelHash, int p4) { invoke<Void>(0xE40C1C56DF95C2E8, cutscenePed, cutsceneEntName, p2, modelHash, p4); }
	NATIVE_DECL Entity GET_ENTITY_INDEX_OF_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash) { return invoke<Entity>(0xC0741A26499654CD, cutsceneEntName, modelHash); }
	NATIVE_DECL void SET_VEHICLE_MODEL_PLAYER_WILL_EXIT_SCENE(Hash modelHash) { invoke<Void>(0x7F96F23FA9B73327, modelHash); }
	NATIVE_DECL void SET_CUTSCENE_TRIGGER_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { invoke<Void>(0x9896CE4721BE84BA, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL BOOL CAN_SET_ENTER_STATE_FOR_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash) { return invoke<BOOL>(0x645D0B458D8E17B5, cutsceneEntName, modelHash); }
	NATIVE_DECL BOOL CAN_SET_EXIT_STATE_FOR_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash) { return invoke<BOOL>(0x4C6A6451C79E4662, cutsceneEntName, modelHash); }
	NATIVE_DECL BOOL CAN_SET_EXIT_STATE_FOR_CAMERA(BOOL p0) { return invoke<BOOL>(0xB2CBCD0930DFB420, p0); }
	NATIVE_DECL void SET_PAD_CAN_SHAKE_DURING_CUTSCENE(BOOL toggle) { invoke<Void>(0xC61B86C9F61EB404, toggle); }
	NATIVE_DECL void SET_CUTSCENE_FADE_VALUES(BOOL p0, BOOL p1, BOOL p2, BOOL p3) { invoke<Void>(0x8093F23ABACCC7D4, p0, p1, p2, p3); }
	NATIVE_DECL void SET_CUTSCENE_MULTIHEAD_FADE(BOOL p0, BOOL p1, BOOL p2, BOOL p3) { invoke<Void>(0x20746F7B1032A3C7, p0, p1, p2, p3); }
	NATIVE_DECL void SET_CUTSCENE_MULTIHEAD_FADE_MANUAL(BOOL p0) { invoke<Void>(0x06EE9048FD080382, p0); }
	NATIVE_DECL BOOL IS_MULTIHEAD_FADE_UP() { return invoke<BOOL>(0xA0FE76168A189DDB); }
	NATIVE_DECL void NETWORK_SET_MOCAP_CUTSCENE_CAN_BE_SKIPPED(BOOL toggle) { invoke<Void>(0x2F137B508DE238F2, toggle); }
	NATIVE_DECL void SET_CAR_GENERATORS_CAN_UPDATE_DURING_CUTSCENE(BOOL p0) { invoke<Void>(0xE36A98D8AB3D3C66, p0); }
	NATIVE_DECL BOOL CAN_USE_MOBILE_PHONE_DURING_CUTSCENE() { return invoke<BOOL>(0x5EDEF0CF8C1DAB3C); }
	NATIVE_DECL void SET_CUTSCENE_CAN_BE_SKIPPED(BOOL p0) { invoke<Void>(0x41FAA8FB2ECE8720, p0); }
	NATIVE_DECL void SET_CAN_DISPLAY_MINIMAP_DURING_CUTSCENE_THIS_UPDATE() { invoke<Void>(0x2131046957F31B04); }
	NATIVE_DECL void SET_CUTSCENE_PED_COMPONENT_VARIATION(const char* cutsceneEntName, int componentId, int drawableId, int textureId, Hash modelHash) { invoke<Void>(0xBA01E7B6DEEFBBC9, cutsceneEntName, componentId, drawableId, textureId, modelHash); }
	NATIVE_DECL void SET_CUTSCENE_PED_COMPONENT_VARIATION_FROM_PED(const char* cutsceneEntName, Ped ped, Hash modelHash) { invoke<Void>(0x2A56C06EBEF2B0D9, cutsceneEntName, ped, modelHash); }
	NATIVE_DECL BOOL DOES_CUTSCENE_ENTITY_EXIST(const char* cutsceneEntName, Hash modelHash) { return invoke<BOOL>(0x499EF20C5DB25C59, cutsceneEntName, modelHash); }
	NATIVE_DECL void SET_CUTSCENE_PED_PROP_VARIATION(const char* cutsceneEntName, int componentId, int drawableId, int textureId, Hash modelHash) { invoke<Void>(0x0546524ADE2E9723, cutsceneEntName, componentId, drawableId, textureId, modelHash); }
	NATIVE_DECL BOOL HAS_CUTSCENE_CUT_THIS_FRAME() { return invoke<BOOL>(0x708BDD8CD795B043); }
}

namespace DATAFILE
{
	NATIVE_DECL void DATAFILE_WATCH_REQUEST_ID(int requestId) { invoke<Void>(0xAD6875BBC0FC899C, requestId); }
	NATIVE_DECL void DATAFILE_CLEAR_WATCH_LIST() { invoke<Void>(0x6CC86E78358D5119); }
	NATIVE_DECL BOOL DATAFILE_IS_VALID_REQUEST_ID(int index) { return invoke<BOOL>(0xFCCAE5B92A830878, index); }
	NATIVE_DECL BOOL DATAFILE_HAS_LOADED_FILE_DATA(int requestId) { return invoke<BOOL>(0x15FF52B809DB2353, requestId); }
	NATIVE_DECL BOOL DATAFILE_HAS_VALID_FILE_DATA(int requestId) { return invoke<BOOL>(0xF8CC1EBE0B62E29F, requestId); }
	NATIVE_DECL BOOL DATAFILE_SELECT_ACTIVE_FILE(int requestId, Any p1) { return invoke<BOOL>(0x22DA66936E0FFF37, requestId, p1); }
	NATIVE_DECL BOOL DATAFILE_DELETE_REQUESTED_FILE(int requestId) { return invoke<BOOL>(0x8F5EA1C01D65A100, requestId); }
	NATIVE_DECL BOOL UGC_CREATE_CONTENT(Any* data, int dataCount, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, BOOL publish, Any p7) { return invoke<BOOL>(0xC84527E235FCA219, data, dataCount, contentName, description, tagsCsv, contentTypeName, publish, p7); }
	NATIVE_DECL BOOL UGC_CREATE_MISSION(const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, BOOL publish, Any p5) { return invoke<BOOL>(0xA5EFC3E847D60507, contentName, description, tagsCsv, contentTypeName, publish, p5); }
	NATIVE_DECL BOOL UGC_UPDATE_CONTENT(const char* contentId, Any* data, int dataCount, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, Any p7) { return invoke<BOOL>(0x648E7A5434AF7969, contentId, data, dataCount, contentName, description, tagsCsv, contentTypeName, p7); }
	NATIVE_DECL BOOL UGC_UPDATE_MISSION(const char* contentId, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, Any p5) { return invoke<BOOL>(0x4645DE9980999E93, contentId, contentName, description, tagsCsv, contentTypeName, p5); }
	NATIVE_DECL BOOL UGC_SET_PLAYER_DATA(const char* contentId, float rating, const char* contentTypeName, Any p3) { return invoke<BOOL>(0x692D808C34A82143, contentId, rating, contentTypeName, p3); }
	NATIVE_DECL BOOL DATAFILE_SELECT_UGC_DATA(int p0, Any p1) { return invoke<BOOL>(0xA69AC4ADE82B57A4, p0, p1); }
	NATIVE_DECL BOOL DATAFILE_SELECT_UGC_STATS(int p0, BOOL p1, Any p2) { return invoke<BOOL>(0x9CB0BFA7A9342C3D, p0, p1, p2); }
	NATIVE_DECL BOOL DATAFILE_SELECT_UGC_PLAYER_DATA(int p0, Any p1) { return invoke<BOOL>(0x52818819057F2B40, p0, p1); }
	NATIVE_DECL BOOL DATAFILE_SELECT_CREATOR_STATS(int p0, Any p1) { return invoke<BOOL>(0x01095C95CD46B624, p0, p1); }
	NATIVE_DECL BOOL DATAFILE_LOAD_OFFLINE_UGC(const char* filename, Any p1) { return invoke<BOOL>(0xC5238C011AF405E4, filename, p1); }
	NATIVE_DECL void DATAFILE_CREATE(int p0) { invoke<Void>(0xD27058A1CA2B13EE, p0); }
	NATIVE_DECL void DATAFILE_DELETE(int p0) { invoke<Void>(0x9AB9C1CFC8862DFB, p0); }
	NATIVE_DECL void DATAFILE_STORE_MISSION_HEADER(int p0) { invoke<Void>(0x2ED61456317B8178, p0); }
	NATIVE_DECL void DATAFILE_FLUSH_MISSION_HEADER() { invoke<Void>(0xC55854C7D7274882); }
	NATIVE_DECL Any* DATAFILE_GET_FILE_DICT(int p0) { return invoke<Any*>(0x906B778CA1DC72B6, p0); }
	NATIVE_DECL BOOL DATAFILE_START_SAVE_TO_CLOUD(const char* filename, Any p1) { return invoke<BOOL>(0x83BCCE3224735F05, filename, p1); }
	NATIVE_DECL BOOL DATAFILE_UPDATE_SAVE_TO_CLOUD(BOOL* p0) { return invoke<BOOL>(0x4DFDD9EB705F8140, p0); }
	NATIVE_DECL BOOL DATAFILE_IS_SAVE_PENDING() { return invoke<BOOL>(0xBEDB96A7584AA8CF); }
	NATIVE_DECL BOOL DATAFILE_LOAD_OFFLINE_UGC_FOR_ADDITIONAL_DATA_FILE(Any p0, Any p1) { return invoke<BOOL>(0xA6EEF01087181EDD, p0, p1); }
	NATIVE_DECL void DATAFILE_DELETE_FOR_ADDITIONAL_DATA_FILE(Any p0) { invoke<Void>(0x6AD0BD5E087866CB, p0); }
	NATIVE_DECL Any* DATAFILE_GET_FILE_DICT_FOR_ADDITIONAL_DATA_FILE(Any p0) { return invoke<Any*>(0xDBF860CF1DB8E599, p0); }
	NATIVE_DECL void DATADICT_SET_BOOL(Any* objectData, const char* key, BOOL value) { invoke<Void>(0x35124302A556A325, objectData, key, value); }
	NATIVE_DECL void DATADICT_SET_INT(Any* objectData, const char* key, int value) { invoke<Void>(0xE7E035450A7948D5, objectData, key, value); }
	NATIVE_DECL void DATADICT_SET_FLOAT(Any* objectData, const char* key, float value) { invoke<Void>(0xC27E1CC2D795105E, objectData, key, value); }
	NATIVE_DECL void DATADICT_SET_STRING(Any* objectData, const char* key, const char* value) { invoke<Void>(0x8FF3847DADD8E30C, objectData, key, value); }
	NATIVE_DECL void DATADICT_SET_VECTOR(Any* objectData, const char* key, float valueX, float valueY, float valueZ) { invoke<Void>(0x4CD49B76338C7DEE, objectData, key, valueX, valueY, valueZ); }
	NATIVE_DECL Any* DATADICT_CREATE_DICT(Any* objectData, const char* key) { return invoke<Any*>(0xA358F56F10732EE1, objectData, key); }
	NATIVE_DECL Any* DATADICT_CREATE_ARRAY(Any* objectData, const char* key) { return invoke<Any*>(0x5B11728527CA6E5F, objectData, key); }
	NATIVE_DECL BOOL DATADICT_GET_BOOL(Any* objectData, const char* key) { return invoke<BOOL>(0x1186940ED72FFEEC, objectData, key); }
	NATIVE_DECL int DATADICT_GET_INT(Any* objectData, const char* key) { return invoke<int>(0x78F06F6B1FB5A80C, objectData, key); }
	NATIVE_DECL float DATADICT_GET_FLOAT(Any* objectData, const char* key) { return invoke<float>(0x06610343E73B9727, objectData, key); }
	NATIVE_DECL const char* DATADICT_GET_STRING(Any* objectData, const char* key) { return invoke<const char*>(0x3D2FD9E763B24472, objectData, key); }
	NATIVE_DECL Vector3 DATADICT_GET_VECTOR(Any* objectData, const char* key) { return invoke<Vector3>(0x46CD3CB66E0825CC, objectData, key); }
	NATIVE_DECL Any* DATADICT_GET_DICT(Any* objectData, const char* key) { return invoke<Any*>(0xB6B9DDC412FCEEE2, objectData, key); }
	NATIVE_DECL Any* DATADICT_GET_ARRAY(Any* objectData, const char* key) { return invoke<Any*>(0x7A983AA9DA2659ED, objectData, key); }
	NATIVE_DECL int DATADICT_GET_TYPE(Any* objectData, const char* key) { return invoke<int>(0x031C55ED33227371, objectData, key); }
	NATIVE_DECL void DATAARRAY_ADD_BOOL(Any* arrayData, BOOL value) { invoke<Void>(0xF8B0F5A43E928C76, arrayData, value); }
	NATIVE_DECL void DATAARRAY_ADD_INT(Any* arrayData, int value) { invoke<Void>(0xCABDB751D86FE93B, arrayData, value); }
	NATIVE_DECL void DATAARRAY_ADD_FLOAT(Any* arrayData, float value) { invoke<Void>(0x57A995FD75D37F56, arrayData, value); }
	NATIVE_DECL void DATAARRAY_ADD_STRING(Any* arrayData, const char* value) { invoke<Void>(0x2F0661C155AEEEAA, arrayData, value); }
	NATIVE_DECL void DATAARRAY_ADD_VECTOR(Any* arrayData, float valueX, float valueY, float valueZ) { invoke<Void>(0x407F8D034F70F0C2, arrayData, valueX, valueY, valueZ); }
	NATIVE_DECL Any* DATAARRAY_ADD_DICT(Any* arrayData) { return invoke<Any*>(0x6889498B3E19C797, arrayData); }
	NATIVE_DECL BOOL DATAARRAY_GET_BOOL(Any* arrayData, int arrayIndex) { return invoke<BOOL>(0x50C1B2874E50C114, arrayData, arrayIndex); }
	NATIVE_DECL int DATAARRAY_GET_INT(Any* arrayData, int arrayIndex) { return invoke<int>(0x3E5AE19425CD74BE, arrayData, arrayIndex); }
	NATIVE_DECL float DATAARRAY_GET_FLOAT(Any* arrayData, int arrayIndex) { return invoke<float>(0xC0C527B525D7CFB5, arrayData, arrayIndex); }
	NATIVE_DECL const char* DATAARRAY_GET_STRING(Any* arrayData, int arrayIndex) { return invoke<const char*>(0xD3F2FFEB8D836F52, arrayData, arrayIndex); }
	NATIVE_DECL Vector3 DATAARRAY_GET_VECTOR(Any* arrayData, int arrayIndex) { return invoke<Vector3>(0x8D2064E5B64A628A, arrayData, arrayIndex); }
	NATIVE_DECL Any* DATAARRAY_GET_DICT(Any* arrayData, int arrayIndex) { return invoke<Any*>(0x8B5FADCC4E3A145F, arrayData, arrayIndex); }
	NATIVE_DECL int DATAARRAY_GET_COUNT(Any* arrayData) { return invoke<int>(0x065DB281590CEA2D, arrayData); }
	NATIVE_DECL int DATAARRAY_GET_TYPE(Any* arrayData, int arrayIndex) { return invoke<int>(0x3A0014ADB172A3C5, arrayData, arrayIndex); }
}

namespace DECORATOR
{
	NATIVE_DECL BOOL DECOR_SET_TIME(Entity entity, const char* propertyName, int timestamp) { return invoke<BOOL>(0x95AED7B8E39ECAA4, entity, propertyName, timestamp); }
	NATIVE_DECL BOOL DECOR_SET_BOOL(Entity entity, const char* propertyName, BOOL value) { return invoke<BOOL>(0x6B1E8E2ED1335B71, entity, propertyName, value); }
	NATIVE_DECL BOOL DECOR_SET_FLOAT(Entity entity, const char* propertyName, float value) { return invoke<BOOL>(0x211AB1DD8D0F363A, entity, propertyName, value); }
	NATIVE_DECL BOOL DECOR_SET_INT(Entity entity, const char* propertyName, int value) { return invoke<BOOL>(0x0CE3AA5E1CA19E10, entity, propertyName, value); }
	NATIVE_DECL BOOL DECOR_GET_BOOL(Entity entity, const char* propertyName) { return invoke<BOOL>(0xDACE671663F2F5DB, entity, propertyName); }
	NATIVE_DECL float DECOR_GET_FLOAT(Entity entity, const char* propertyName) { return invoke<float>(0x6524A2F114706F43, entity, propertyName); }
	NATIVE_DECL int DECOR_GET_INT(Entity entity, const char* propertyName) { return invoke<int>(0xA06C969B02A97298, entity, propertyName); }
	NATIVE_DECL BOOL DECOR_EXIST_ON(Entity entity, const char* propertyName) { return invoke<BOOL>(0x05661B80A8C9165F, entity, propertyName); }
	NATIVE_DECL BOOL DECOR_REMOVE(Entity entity, const char* propertyName) { return invoke<BOOL>(0x00EE9F297C738720, entity, propertyName); }
	NATIVE_DECL void DECOR_REGISTER(const char* propertyName, int type) { invoke<Void>(0x9FD90732F56403CE, propertyName, type); }
	NATIVE_DECL BOOL DECOR_IS_REGISTERED_AS_TYPE(const char* propertyName, int type) { return invoke<BOOL>(0x4F14F9F870D6FBC8, propertyName, type); }
	NATIVE_DECL void DECOR_REGISTER_LOCK() { invoke<Void>(0xA9D14EEA259F9248); }
}

namespace DLC
{
	NATIVE_DECL BOOL ARE_ANY_CCS_PENDING() { return invoke<BOOL>(0x241FCA5B1AA14F75); }
	NATIVE_DECL BOOL IS_DLC_PRESENT(Hash dlcHash) { return invoke<BOOL>(0x812595A0644CE1DE, dlcHash); }
	NATIVE_DECL BOOL DLC_CHECK_CLOUD_DATA_CORRECT() { return invoke<BOOL>(0xF2E07819EF1A5289); }
	NATIVE_DECL int GET_EXTRACONTENT_CLOUD_RESULT() { return invoke<int>(0x9489659372A81585); }
	NATIVE_DECL BOOL DLC_CHECK_COMPAT_PACK_CONFIGURATION() { return invoke<BOOL>(0xA213B11DFF526300); }
	NATIVE_DECL BOOL GET_EVER_HAD_BAD_PACK_ORDER() { return invoke<BOOL>(0x8D30F648014A92B5); }
	NATIVE_DECL BOOL GET_IS_LOADING_SCREEN_ACTIVE() { return invoke<BOOL>(0x10D0A8F259E93EC9); }
	NATIVE_DECL BOOL GET_IS_INITIAL_LOADING_SCREEN_ACTIVE() { return invoke<BOOL>(0xC4637A6D03C24CC3); }
	NATIVE_DECL BOOL HAS_CLOUD_REQUESTS_FINISHED(BOOL* p0, int unused) { return invoke<BOOL>(0x46E2B844905BC5F0, p0, unused); }
	NATIVE_DECL void ON_ENTER_SP() { invoke<Void>(0xD7C10C4A637992C9); }
	NATIVE_DECL void ON_ENTER_MP() { invoke<Void>(0x0888C3502DBBEEF5); }
}

namespace ENTITY
{
	NATIVE_DECL BOOL DOES_ENTITY_EXIST(Entity entity) { return invoke<BOOL>(0x7239B21A38F536BA, entity); }
	NATIVE_DECL BOOL DOES_ENTITY_BELONG_TO_THIS_SCRIPT(Entity entity, BOOL p1) { return invoke<BOOL>(0xDDE6DF5AE89981D2, entity, p1); }
	NATIVE_DECL BOOL DOES_ENTITY_HAVE_DRAWABLE(Entity entity) { return invoke<BOOL>(0x060D6E96F8B8E48D, entity); }
	NATIVE_DECL BOOL DOES_ENTITY_HAVE_PHYSICS(Entity entity) { return invoke<BOOL>(0xDA95EA3317CC5064, entity); }
	NATIVE_DECL BOOL DOES_ENTITY_HAVE_SKELETON(Entity entity) { return invoke<BOOL>(0x764EB96874EFFDC1, entity); }
	NATIVE_DECL BOOL DOES_ENTITY_HAVE_ANIM_DIRECTOR(Entity entity) { return invoke<BOOL>(0x2158E81A6AF65EA9, entity); }
	NATIVE_DECL BOOL HAS_ENTITY_ANIM_FINISHED(Entity entity, const char* animDict, const char* animName, int p3) { return invoke<BOOL>(0x20B711662962B472, entity, animDict, animName, p3); }
	NATIVE_DECL BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(Entity entity) { return invoke<BOOL>(0x95EB9964FF5C5C65, entity); }
	NATIVE_DECL BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(Entity entity) { return invoke<BOOL>(0x605F5A140F202491, entity); }
	NATIVE_DECL BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(Entity entity) { return invoke<BOOL>(0xDFD5033FDBA0A9C8, entity); }
	NATIVE_DECL BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(Entity entity1, Entity entity2, BOOL p2) { return invoke<BOOL>(0xC86D67D52A707CF8, entity1, entity2, p2); }
	NATIVE_DECL BOOL HAS_ENTITY_CLEAR_LOS_TO_ENTITY(Entity entity1, Entity entity2, int traceType) { return invoke<BOOL>(0xFCDFF7B72D23A1AC, entity1, entity2, traceType); }
	NATIVE_DECL BOOL HAS_ENTITY_CLEAR_LOS_TO_ENTITY_ADJUST_FOR_COVER(Entity entity1, Entity entity2, int traceType) { return invoke<BOOL>(0x394BDE2A7BBA031E, entity1, entity2, traceType); }
	NATIVE_DECL BOOL HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(Entity entity1, Entity entity2) { return invoke<BOOL>(0x0267D00AF114F17A, entity1, entity2); }
	NATIVE_DECL BOOL HAS_ENTITY_COLLIDED_WITH_ANYTHING(Entity entity) { return invoke<BOOL>(0x8BAD02F0368D9E14, entity); }
	NATIVE_DECL Entity _GET_LAST_ENTITY_HIT_BY_ENTITY(Entity entity) { return invoke<Entity>(0xA75EE4F689B85391, entity); }
	NATIVE_DECL Hash GET_LAST_MATERIAL_HIT_BY_ENTITY(Entity entity) { return invoke<Hash>(0x5C3D0A935F535C4C, entity); }
	NATIVE_DECL Vector3 GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(Entity entity) { return invoke<Vector3>(0xE465D4AB7CA6AE72, entity); }
	NATIVE_DECL void FORCE_ENTITY_AI_AND_ANIMATION_UPDATE(Entity entity) { invoke<Void>(0x40FDEDB72F8293B2, entity); }
	NATIVE_DECL float GET_ENTITY_ANIM_CURRENT_TIME(Entity entity, const char* animDict, const char* animName) { return invoke<float>(0x346D81500D088F42, entity, animDict, animName); }
	NATIVE_DECL float GET_ENTITY_ANIM_TOTAL_TIME(Entity entity, const char* animDict, const char* animName) { return invoke<float>(0x50BD2730B191E360, entity, animDict, animName); }
	NATIVE_DECL float GET_ANIM_DURATION(const char* animDict, const char* animName) { return invoke<float>(0xFEDDF04D62B8D790, animDict, animName); }
	NATIVE_DECL Entity GET_ENTITY_ATTACHED_TO(Entity entity) { return invoke<Entity>(0x48C2BED9180FE123, entity); }
	NATIVE_DECL Vector3 GET_ENTITY_COORDS(Entity entity, BOOL alive) { return invoke<Vector3>(0x3FEF770D40960D5A, entity, alive); }
	NATIVE_DECL Vector3 GET_ENTITY_FORWARD_VECTOR(Entity entity) { return invoke<Vector3>(0x0A794A5A57F8DF91, entity); }
	NATIVE_DECL float GET_ENTITY_FORWARD_X(Entity entity) { return invoke<float>(0x8BB4EF4214E0E6D5, entity); }
	NATIVE_DECL float GET_ENTITY_FORWARD_Y(Entity entity) { return invoke<float>(0x866A4A5FAE349510, entity); }
	NATIVE_DECL float GET_ENTITY_HEADING(Entity entity) { return invoke<float>(0xE83D4F9BA2A38914, entity); }
	NATIVE_DECL float GET_ENTITY_HEADING_FROM_EULERS(Entity entity) { return invoke<float>(0x846BF6291198A71E, entity); }
	NATIVE_DECL int GET_ENTITY_HEALTH(Entity entity) { return invoke<int>(0xEEF059FAD016D209, entity); }
	NATIVE_DECL int GET_ENTITY_MAX_HEALTH(Entity entity) { return invoke<int>(0x15D757606D170C3C, entity); }
	NATIVE_DECL void SET_ENTITY_MAX_HEALTH(Entity entity, int value) { invoke<Void>(0x166E7CF68597D8B5, entity, value); }
	NATIVE_DECL float GET_ENTITY_HEIGHT(Entity entity, float X, float Y, float Z, BOOL atTop, BOOL inWorldCoords) { return invoke<float>(0x5A504562485944DD, entity, X, Y, Z, atTop, inWorldCoords); }
	NATIVE_DECL float GET_ENTITY_HEIGHT_ABOVE_GROUND(Entity entity) { return invoke<float>(0x1DD55701034110E5, entity); }
	NATIVE_DECL void GET_ENTITY_MATRIX(Entity entity, Vector3* forwardVector, Vector3* rightVector, Vector3* upVector, Vector3* position) { invoke<Void>(0xECB2FC7235A7D137, entity, forwardVector, rightVector, upVector, position); }
	NATIVE_DECL Hash GET_ENTITY_MODEL(Entity entity) { return invoke<Hash>(0x9F47B058362C84B5, entity); }
	NATIVE_DECL Vector3 GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(Entity entity, float posX, float posY, float posZ) { return invoke<Vector3>(0x2274BC1C4885E333, entity, posX, posY, posZ); }
	NATIVE_DECL Vector3 GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Entity entity, float offsetX, float offsetY, float offsetZ) { return invoke<Vector3>(0x1899F328B0E12848, entity, offsetX, offsetY, offsetZ); }
	NATIVE_DECL float GET_ENTITY_PITCH(Entity entity) { return invoke<float>(0xD45DC2893621E1FE, entity); }
	NATIVE_DECL void GET_ENTITY_QUATERNION(Entity entity, float* x, float* y, float* z, float* w) { invoke<Void>(0x7B3703D2D32DFA18, entity, x, y, z, w); }
	NATIVE_DECL float GET_ENTITY_ROLL(Entity entity) { return invoke<float>(0x831E0242595560DF, entity); }
	NATIVE_DECL Vector3 GET_ENTITY_ROTATION(Entity entity, int rotationOrder) { return invoke<Vector3>(0xAFBD61CC738D9EB9, entity, rotationOrder); }
	NATIVE_DECL Vector3 GET_ENTITY_ROTATION_VELOCITY(Entity entity) { return invoke<Vector3>(0x213B91045D09B983, entity); }
	NATIVE_DECL const char* GET_ENTITY_SCRIPT(Entity entity, ScrHandle* script) { return invoke<const char*>(0xA6E9C38DB51D7748, entity, script); }
	NATIVE_DECL float GET_ENTITY_SPEED(Entity entity) { return invoke<float>(0xD5037BA82E12416F, entity); }
	NATIVE_DECL Vector3 GET_ENTITY_SPEED_VECTOR(Entity entity, BOOL relative) { return invoke<Vector3>(0x9A8D700A51CB7B0D, entity, relative); }
	NATIVE_DECL float GET_ENTITY_UPRIGHT_VALUE(Entity entity) { return invoke<float>(0x95EED5A694951F9F, entity); }
	NATIVE_DECL Vector3 GET_ENTITY_VELOCITY(Entity entity) { return invoke<Vector3>(0x4805D2B1D8CF94A9, entity); }
	NATIVE_DECL Object GET_OBJECT_INDEX_FROM_ENTITY_INDEX(Entity entity) { return invoke<Object>(0xD7E3B9735C0F89D6, entity); }
	NATIVE_DECL Ped GET_PED_INDEX_FROM_ENTITY_INDEX(Entity entity) { return invoke<Ped>(0x04A2A40C73395041, entity); }
	NATIVE_DECL Vehicle GET_VEHICLE_INDEX_FROM_ENTITY_INDEX(Entity entity) { return invoke<Vehicle>(0x4B53F92932ADFAC0, entity); }
	NATIVE_DECL Vector3 GET_WORLD_POSITION_OF_ENTITY_BONE(Entity entity, int boneIndex) { return invoke<Vector3>(0x44A8FCB8ED227738, entity, boneIndex); }
	NATIVE_DECL Player GET_NEAREST_PLAYER_TO_ENTITY(Entity entity) { return invoke<Player>(0x7196842CB375CDB3, entity); }
	NATIVE_DECL Player GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM(Entity entity, int team) { return invoke<Player>(0x4DC9A62F844D9337, entity, team); }
	NATIVE_DECL int GET_NEAREST_PARTICIPANT_TO_ENTITY(Entity entity) { return invoke<int>(0xFFBD7052D65BE0FF, entity); }
	NATIVE_DECL int GET_ENTITY_TYPE(Entity entity) { return invoke<int>(0x8ACD366038D14505, entity); }
	NATIVE_DECL int GET_ENTITY_POPULATION_TYPE(Entity entity) { return invoke<int>(0xF6F5161F4534EDFF, entity); }
	NATIVE_DECL BOOL IS_AN_ENTITY(ScrHandle handle) { return invoke<BOOL>(0x731EC8A916BD11A1, handle); }
	NATIVE_DECL BOOL IS_ENTITY_A_PED(Entity entity) { return invoke<BOOL>(0x524AC5ECEA15343E, entity); }
	NATIVE_DECL BOOL IS_ENTITY_A_MISSION_ENTITY(Entity entity) { return invoke<BOOL>(0x0A7B270912999B3C, entity); }
	NATIVE_DECL BOOL IS_ENTITY_A_VEHICLE(Entity entity) { return invoke<BOOL>(0x6AC7003FA6E5575E, entity); }
	NATIVE_DECL BOOL IS_ENTITY_AN_OBJECT(Entity entity) { return invoke<BOOL>(0x8D68C8FD0FACA94E, entity); }
	NATIVE_DECL BOOL IS_ENTITY_AT_COORD(Entity entity, float xPos, float yPos, float zPos, float xSize, float ySize, float zSize, BOOL p7, BOOL p8, int p9) { return invoke<BOOL>(0x20B60995556D004F, entity, xPos, yPos, zPos, xSize, ySize, zSize, p7, p8, p9); }
	NATIVE_DECL BOOL IS_ENTITY_AT_ENTITY(Entity entity1, Entity entity2, float xSize, float ySize, float zSize, BOOL p5, BOOL p6, int p7) { return invoke<BOOL>(0x751B70C3D034E187, entity1, entity2, xSize, ySize, zSize, p5, p6, p7); }
	NATIVE_DECL BOOL IS_ENTITY_ATTACHED(Entity entity) { return invoke<BOOL>(0xB346476EF1A64897, entity); }
	NATIVE_DECL BOOL IS_ENTITY_ATTACHED_TO_ANY_OBJECT(Entity entity) { return invoke<BOOL>(0xCF511840CEEDE0CC, entity); }
	NATIVE_DECL BOOL IS_ENTITY_ATTACHED_TO_ANY_PED(Entity entity) { return invoke<BOOL>(0xB1632E9A5F988D11, entity); }
	NATIVE_DECL BOOL IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(Entity entity) { return invoke<BOOL>(0x26AA915AD89BFB4B, entity); }
	NATIVE_DECL BOOL IS_ENTITY_ATTACHED_TO_ENTITY(Entity from, Entity to) { return invoke<BOOL>(0xEFBE71898A993728, from, to); }
	NATIVE_DECL BOOL IS_ENTITY_DEAD(Entity entity, BOOL p1) { return invoke<BOOL>(0x5F9532F3B5CC2551, entity, p1); }
	NATIVE_DECL BOOL IS_ENTITY_IN_AIR(Entity entity) { return invoke<BOOL>(0x886E37EC497200B6, entity); }
	NATIVE_DECL BOOL IS_ENTITY_IN_ANGLED_AREA(Entity entity, float x1, float y1, float z1, float x2, float y2, float z2, float width, BOOL debug, BOOL includeZ, Any p10) { return invoke<BOOL>(0x51210CED3DA1C78A, entity, x1, y1, z1, x2, y2, z2, width, debug, includeZ, p10); }
	NATIVE_DECL BOOL IS_ENTITY_IN_AREA(Entity entity, float x1, float y1, float z1, float x2, float y2, float z2, BOOL p7, BOOL p8, Any p9) { return invoke<BOOL>(0x54736AA40E271165, entity, x1, y1, z1, x2, y2, z2, p7, p8, p9); }
	NATIVE_DECL BOOL IS_ENTITY_IN_ZONE(Entity entity, const char* zone) { return invoke<BOOL>(0xB6463CF6AF527071, entity, zone); }
	NATIVE_DECL BOOL IS_ENTITY_IN_WATER(Entity entity) { return invoke<BOOL>(0xCFB0A0D8EDD145A3, entity); }
	NATIVE_DECL float GET_ENTITY_SUBMERGED_LEVEL(Entity entity) { return invoke<float>(0xE81AFC1BC4CC41CE, entity); }
	NATIVE_DECL void SET_ENTITY_REQUIRES_MORE_EXPENSIVE_RIVER_CHECK(Entity entity, BOOL toggle) { invoke<Void>(0x694E00132F2823ED, entity, toggle); }
	NATIVE_DECL BOOL IS_ENTITY_ON_SCREEN(Entity entity) { return invoke<BOOL>(0xE659E47AF827484B, entity); }
	NATIVE_DECL BOOL IS_ENTITY_PLAYING_ANIM(Entity entity, const char* animDict, const char* animName, int taskFlag) { return invoke<BOOL>(0x1F0B79228E461EC9, entity, animDict, animName, taskFlag); }
	NATIVE_DECL BOOL IS_ENTITY_STATIC(Entity entity) { return invoke<BOOL>(0x1218E6886D3D8327, entity); }
	NATIVE_DECL BOOL IS_ENTITY_TOUCHING_ENTITY(Entity entity, Entity targetEntity) { return invoke<BOOL>(0x17FFC1B2BA35A494, entity, targetEntity); }
	NATIVE_DECL BOOL IS_ENTITY_TOUCHING_MODEL(Entity entity, Hash modelHash) { return invoke<BOOL>(0x0F42323798A58C8C, entity, modelHash); }
	NATIVE_DECL BOOL IS_ENTITY_UPRIGHT(Entity entity, float angle) { return invoke<BOOL>(0x5333F526F6AB19AA, entity, angle); }
	NATIVE_DECL BOOL IS_ENTITY_UPSIDEDOWN(Entity entity) { return invoke<BOOL>(0x1DBD58820FA61D71, entity); }
	NATIVE_DECL BOOL IS_ENTITY_VISIBLE(Entity entity) { return invoke<BOOL>(0x47D6F43D77935C75, entity); }
	NATIVE_DECL BOOL IS_ENTITY_VISIBLE_TO_SCRIPT(Entity entity) { return invoke<BOOL>(0xD796CB5BA8F20E32, entity); }
	NATIVE_DECL BOOL IS_ENTITY_OCCLUDED(Entity entity) { return invoke<BOOL>(0xE31C2C72B8692B64, entity); }
	NATIVE_DECL BOOL WOULD_ENTITY_BE_OCCLUDED(Hash entityModelHash, float x, float y, float z, BOOL p4) { return invoke<BOOL>(0xEE5D2A122E09EC42, entityModelHash, x, y, z, p4); }
	NATIVE_DECL BOOL IS_ENTITY_WAITING_FOR_WORLD_COLLISION(Entity entity) { return invoke<BOOL>(0xD05BFF0C0A12C68F, entity); }
	NATIVE_DECL BOOL _IS_ENTITY_FIXED(Entity entity) { return invoke<BOOL>(0xDA5EF4092EDB83F4, entity); }
	NATIVE_DECL void APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(Entity entity, int forceType, float x, float y, float z, BOOL p5, BOOL isDirectionRel, BOOL isForceRel, BOOL p8) { invoke<Void>(0x18FF00FC7EFF559E, entity, forceType, x, y, z, p5, isDirectionRel, isForceRel, p8); }
	NATIVE_DECL void APPLY_FORCE_TO_ENTITY(Entity entity, int forceFlags, float x, float y, float z, float offX, float offY, float offZ, int boneIndex, BOOL isDirectionRel, BOOL ignoreUpVec, BOOL isForceRel, BOOL p12, BOOL p13) { invoke<Void>(0xC5F68BE9613E2D18, entity, forceFlags, x, y, z, offX, offY, offZ, boneIndex, isDirectionRel, ignoreUpVec, isForceRel, p12, p13); }
	NATIVE_DECL void ATTACH_ENTITY_TO_ENTITY(Entity entity1, Entity entity2, int boneIndex, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, BOOL p9, BOOL useSoftPinning, BOOL collision, BOOL isPed, int vertexIndex, BOOL fixedRot, Any p15) { invoke<Void>(0x6B9BBD38AB0796DF, entity1, entity2, boneIndex, xPos, yPos, zPos, xRot, yRot, zRot, p9, useSoftPinning, collision, isPed, vertexIndex, fixedRot, p15); }
	NATIVE_DECL void ATTACH_ENTITY_BONE_TO_ENTITY_BONE(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, BOOL p4, BOOL p5) { invoke<Void>(0x5C48B75732C8456C, entity1, entity2, boneIndex1, boneIndex2, p4, p5); }
	NATIVE_DECL void ATTACH_ENTITY_BONE_TO_ENTITY_BONE_Y_FORWARD(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, BOOL p4, BOOL p5) { invoke<Void>(0xFD1695C5D3B05439, entity1, entity2, boneIndex1, boneIndex2, p4, p5); }
	NATIVE_DECL void ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, float xPos1, float yPos1, float zPos1, float xPos2, float yPos2, float zPos2, float xRot, float yRot, float zRot, float breakForce, BOOL fixedRot, BOOL p15, BOOL collision, BOOL p17, int p18) { invoke<Void>(0xC3675780C92F90F9, entity1, entity2, boneIndex1, boneIndex2, xPos1, yPos1, zPos1, xPos2, yPos2, zPos2, xRot, yRot, zRot, breakForce, fixedRot, p15, collision, p17, p18); }
	NATIVE_DECL void ATTACH_ENTITY_TO_ENTITY_PHYSICALLY_OVERRIDE_INVERSE_MASS(Entity firstEntityIndex, Entity secondEntityIndex, int firstEntityBoneIndex, int secondEntityBoneIndex, float secondEntityOffsetX, float secondEntityOffsetY, float secondEntityOffsetZ, float firstEntityOffsetX, float firstEntityOffsetY, float firstEntityOffsetZ, float vecRotationX, float vecRotationY, float vecRotationZ, float physicalStrength, BOOL constrainRotation, BOOL doInitialWarp, BOOL collideWithEntity, BOOL addInitialSeperation, int rotOrder, float invMassScaleA, float invMassScaleB) { invoke<Void>(0x168A09D1B25B0BA4, firstEntityIndex, secondEntityIndex, firstEntityBoneIndex, secondEntityBoneIndex, secondEntityOffsetX, secondEntityOffsetY, secondEntityOffsetZ, firstEntityOffsetX, firstEntityOffsetY, firstEntityOffsetZ, vecRotationX, vecRotationY, vecRotationZ, physicalStrength, constrainRotation, doInitialWarp, collideWithEntity, addInitialSeperation, rotOrder, invMassScaleA, invMassScaleB); }
	NATIVE_DECL void PROCESS_ENTITY_ATTACHMENTS(Entity entity) { invoke<Void>(0xF4080490ADC51C6F, entity); }
	NATIVE_DECL int GET_ENTITY_BONE_INDEX_BY_NAME(Entity entity, const char* boneName) { return invoke<int>(0xFB71170B7E76ACBA, entity, boneName); }
	NATIVE_DECL void CLEAR_ENTITY_LAST_DAMAGE_ENTITY(Entity entity) { invoke<Void>(0xA72CD9CA74A5ECBA, entity); }
	NATIVE_DECL void DELETE_ENTITY(Entity* entity) { invoke<Void>(0xAE3CBE5BF394C9C9, entity); }
	NATIVE_DECL void DETACH_ENTITY(Entity entity, BOOL dynamic, BOOL collision) { invoke<Void>(0x961AC54BF0613F5D, entity, dynamic, collision); }
	NATIVE_DECL void FREEZE_ENTITY_POSITION(Entity entity, BOOL toggle) { invoke<Void>(0x428CA6DBD1094446, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(Entity entity, BOOL toggle) { invoke<Void>(0x3910051CCECDB00C, entity, toggle); }
	NATIVE_DECL BOOL PLAY_ENTITY_ANIM(Entity entity, const char* animName, const char* animDict, float p3, BOOL loop, BOOL stayInAnim, BOOL p6, float delta, Any bitset) { return invoke<BOOL>(0x7FB218262B810701, entity, animName, animDict, p3, loop, stayInAnim, p6, delta, bitset); }
	NATIVE_DECL BOOL PLAY_SYNCHRONIZED_ENTITY_ANIM(Entity entity, int syncedScene, const char* animation, const char* propName, float p4, float p5, Any p6, float p7) { return invoke<BOOL>(0xC77720A12FE14A86, entity, syncedScene, animation, propName, p4, p5, p6, p7); }
	NATIVE_DECL BOOL PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM(float x1, float y1, float z1, float x2, Any y2, float z2, const char* p6, const char* p7, float p8, float p9, Any p10, float p11) { return invoke<BOOL>(0xB9C54555ED30FBC4, x1, y1, z1, x2, y2, z2, p6, p7, p8, p9, p10, p11); }
	NATIVE_DECL BOOL STOP_SYNCHRONIZED_MAP_ENTITY_ANIM(float x1, float y1, float z1, float x2, Any y2, float z2) { return invoke<BOOL>(0x11E79CAB7183B6F5, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL BOOL STOP_ENTITY_ANIM(Entity entity, const char* animation, const char* animGroup, float p3) { return invoke<BOOL>(0x28004F88151E03E0, entity, animation, animGroup, p3); }
	NATIVE_DECL BOOL STOP_SYNCHRONIZED_ENTITY_ANIM(Entity entity, float p1, BOOL p2) { return invoke<BOOL>(0x43D3807C077261E3, entity, p1, p2); }
	NATIVE_DECL BOOL HAS_ANIM_EVENT_FIRED(Entity entity, Hash actionHash) { return invoke<BOOL>(0xEAF4CD9EA3E7E922, entity, actionHash); }
	NATIVE_DECL BOOL FIND_ANIM_EVENT_PHASE(const char* animDictionary, const char* animName, const char* p2, Any* p3, Any* p4) { return invoke<BOOL>(0x07F1BE2BCCAA27A7, animDictionary, animName, p2, p3, p4); }
	NATIVE_DECL void SET_ENTITY_ANIM_CURRENT_TIME(Entity entity, const char* animDictionary, const char* animName, float time) { invoke<Void>(0x4487C259F0F70977, entity, animDictionary, animName, time); }
	NATIVE_DECL void SET_ENTITY_ANIM_SPEED(Entity entity, const char* animDictionary, const char* animName, float speedMultiplier) { invoke<Void>(0x28D1A16553C51776, entity, animDictionary, animName, speedMultiplier); }
	NATIVE_DECL void SET_ENTITY_AS_MISSION_ENTITY(Entity entity, BOOL bScriptHostObject, BOOL bGrabFromOtherScript) { invoke<Void>(0xAD738C3085FE7E11, entity, bScriptHostObject, bGrabFromOtherScript); }
	NATIVE_DECL void SET_ENTITY_AS_NO_LONGER_NEEDED(Entity* entity) { invoke<Void>(0xB736A491E64A32CF, entity); }
	NATIVE_DECL void SET_PED_AS_NO_LONGER_NEEDED(Ped* ped) { invoke<Void>(0x2595DD4236549CE3, ped); }
	NATIVE_DECL void SET_VEHICLE_AS_NO_LONGER_NEEDED(Vehicle* vehicle) { invoke<Void>(0x629BFA74418D6239, vehicle); }
	NATIVE_DECL void SET_OBJECT_AS_NO_LONGER_NEEDED(Object* object) { invoke<Void>(0x3AE22DEB5BA5A3E6, object); }
	NATIVE_DECL void SET_ENTITY_CAN_BE_DAMAGED(Entity entity, BOOL toggle) { invoke<Void>(0x1760FFA8AB074D66, entity, toggle); }
	NATIVE_DECL BOOL GET_ENTITY_CAN_BE_DAMAGED(Entity entity) { return invoke<BOOL>(0xD95CC5D2AB15A09F, entity); }
	NATIVE_DECL void SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, BOOL bCanBeDamaged, int relGroup) { invoke<Void>(0xE22D8FDE858B8119, entity, bCanBeDamaged, relGroup); }
	NATIVE_DECL void SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_SCRIPT_PARTICIPANTS(Entity entity, BOOL toggle) { invoke<Void>(0x352E2B5CF420BF3B, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(Entity entity, BOOL toggle) { invoke<Void>(0xD3997889736FD899, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_COLLISION(Entity entity, BOOL toggle, BOOL keepPhysics) { invoke<Void>(0x1A9205C1B9EE827F, entity, toggle, keepPhysics); }
	NATIVE_DECL BOOL GET_ENTITY_COLLISION_DISABLED(Entity entity) { return invoke<BOOL>(0xCCF1E97BEFDAE480, entity); }
	NATIVE_DECL void SET_ENTITY_COMPLETELY_DISABLE_COLLISION(Entity entity, BOOL toggle, BOOL keepPhysics) { invoke<Void>(0x9EBC85ED0FFFE51C, entity, toggle, keepPhysics); }
	NATIVE_DECL void SET_ENTITY_COORDS(Entity entity, float xPos, float yPos, float zPos, BOOL xAxis, BOOL yAxis, BOOL zAxis, BOOL clearArea) { invoke<Void>(0x06843DA7060A026B, entity, xPos, yPos, zPos, xAxis, yAxis, zAxis, clearArea); }
	NATIVE_DECL void SET_ENTITY_COORDS_WITHOUT_PLANTS_RESET(Entity entity, float xPos, float yPos, float zPos, BOOL alive, BOOL deadFlag, BOOL ragdollFlag, BOOL clearArea) { invoke<Void>(0x621873ECE1178967, entity, xPos, yPos, zPos, alive, deadFlag, ragdollFlag, clearArea); }
	NATIVE_DECL void SET_ENTITY_COORDS_NO_OFFSET(Entity entity, float xPos, float yPos, float zPos, BOOL xAxis, BOOL yAxis, BOOL zAxis) { invoke<Void>(0x239A3351AC1DA385, entity, xPos, yPos, zPos, xAxis, yAxis, zAxis); }
	NATIVE_DECL void SET_ENTITY_DYNAMIC(Entity entity, BOOL toggle) { invoke<Void>(0x1718DE8E3F2823CA, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_HEADING(Entity entity, float heading) { invoke<Void>(0x8E2530AA8ADA980E, entity, heading); }
	NATIVE_DECL void SET_ENTITY_HEALTH(Entity entity, int health, Entity instigator, Hash weaponType) { invoke<Void>(0x6B76DC1F3AE6E6A3, entity, health, instigator, weaponType); }
	NATIVE_DECL void SET_ENTITY_INVINCIBLE(Entity entity, BOOL toggle, BOOL dontResetOnCleanup) { invoke<Void>(0x3882114BDE571AD4, entity, toggle, dontResetOnCleanup); }
	NATIVE_DECL void SET_ENTITY_IS_TARGET_PRIORITY(Entity entity, BOOL p1, float p2) { invoke<Void>(0xEA02E132F5C68722, entity, p1, p2); }
	NATIVE_DECL void SET_ENTITY_LIGHTS(Entity entity, BOOL toggle) { invoke<Void>(0x7CFBA6A80BDF3874, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_LOAD_COLLISION_FLAG(Entity entity, BOOL toggle, Any p2) { invoke<Void>(0x0DC7CABAB1E9B67E, entity, toggle, p2); }
	NATIVE_DECL BOOL HAS_COLLISION_LOADED_AROUND_ENTITY(Entity entity) { return invoke<BOOL>(0xE9676F61BC0B3321, entity); }
	NATIVE_DECL void SET_ENTITY_MAX_SPEED(Entity entity, float speed) { invoke<Void>(0x0E46A3FCBDE2A1B1, entity, speed); }
	NATIVE_DECL void SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(Entity entity, BOOL toggle) { invoke<Void>(0x79F020FF9EDC0748, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, BOOL p1, Any p2) { invoke<Void>(0x7022BD828FA0B082, entity, p1, p2); }
	NATIVE_DECL void SET_ENTITY_PROOFS(Entity entity, BOOL bulletProof, BOOL fireProof, BOOL explosionProof, BOOL collisionProof, BOOL meleeProof, BOOL steamProof, BOOL dontResetOnCleanup, BOOL waterProof) { invoke<Void>(0xFAEE099C6F890BB8, entity, bulletProof, fireProof, explosionProof, collisionProof, meleeProof, steamProof, dontResetOnCleanup, waterProof); }
	NATIVE_DECL BOOL GET_ENTITY_PROOFS(Entity entity, BOOL* bulletProof, BOOL* fireProof, BOOL* explosionProof, BOOL* collisionProof, BOOL* meleeProof, BOOL* steamProof, BOOL* p7, BOOL* drownProof) { return invoke<BOOL>(0xBE8CD9BE829BBEBF, entity, bulletProof, fireProof, explosionProof, collisionProof, meleeProof, steamProof, p7, drownProof); }
	NATIVE_DECL void SET_ENTITY_QUATERNION(Entity entity, float x, float y, float z, float w) { invoke<Void>(0x77B21BE7AC540F07, entity, x, y, z, w); }
	NATIVE_DECL void SET_ENTITY_RECORDS_COLLISIONS(Entity entity, BOOL toggle) { invoke<Void>(0x0A50A1EEDAD01E65, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_ROTATION(Entity entity, float pitch, float roll, float yaw, int rotationOrder, BOOL p5) { invoke<Void>(0x8524A8B0171D5E07, entity, pitch, roll, yaw, rotationOrder, p5); }
	NATIVE_DECL void SET_ENTITY_VISIBLE(Entity entity, BOOL toggle, BOOL p2) { invoke<Void>(0xEA1C610A04DB6BBB, entity, toggle, p2); }
	NATIVE_DECL void SET_ENTITY_WATER_REFLECTION_FLAG(Entity entity, BOOL toggle) { invoke<Void>(0xC34BC448DA29F5E9, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_MIRROR_REFLECTION_FLAG(Entity entity, BOOL p1) { invoke<Void>(0xE66377CDDADA4810, entity, p1); }
	NATIVE_DECL void SET_ENTITY_VELOCITY(Entity entity, float x, float y, float z) { invoke<Void>(0x1C99BB7B6E96D16F, entity, x, y, z); }
	NATIVE_DECL void SET_ENTITY_ANGULAR_VELOCITY(Entity entity, float x, float y, float z) { invoke<Void>(0x8339643499D1222E, entity, x, y, z); }
	NATIVE_DECL void SET_ENTITY_HAS_GRAVITY(Entity entity, BOOL toggle) { invoke<Void>(0x4A4722448F18EEF5, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_DRAWABLE_LOD_THRESHOLDS(Entity entity, int highLod, int medLod, int lowLod, int vlowLod) { invoke<Void>(0xC12A19AC871A59C1, entity, highLod, medLod, lowLod, vlowLod); }
	NATIVE_DECL void SET_ENTITY_LOD_DIST(Entity entity, int value) { invoke<Void>(0x5927F96A78577363, entity, value); }
	NATIVE_DECL int GET_ENTITY_LOD_DIST(Entity entity) { return invoke<int>(0x4159C2762B5791D6, entity); }
	NATIVE_DECL void SET_ENTITY_ALPHA(Entity entity, int alphaLevel, BOOL skin) { invoke<Void>(0x44A0870B7E92D7C0, entity, alphaLevel, skin); }
	NATIVE_DECL int GET_ENTITY_ALPHA(Entity entity) { return invoke<int>(0x5A47B3B5E63E94C6, entity); }
	NATIVE_DECL void RESET_ENTITY_ALPHA(Entity entity) { invoke<Void>(0x9B1E824FFBB7027A, entity); }
	NATIVE_DECL void RESET_PICKUP_ENTITY_GLOW(Entity entity) { invoke<Void>(0x490861B88F4FD846, entity); }
	NATIVE_DECL void SET_PICKUP_COLLIDES_WITH_PROJECTILES(Any p0, Any p1) { invoke<Void>(0xCEA7C8E1B48FF68C, p0, p1); }
	NATIVE_DECL void SET_ENTITY_SORT_BIAS(Entity entity, float p1) { invoke<Void>(0x5C3B791D580E0BC2, entity, p1); }
	NATIVE_DECL void SET_ENTITY_ALWAYS_PRERENDER(Entity entity, BOOL toggle) { invoke<Void>(0xACAD101E1FB66689, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_RENDER_SCORCHED(Entity entity, BOOL toggle) { invoke<Void>(0x730F5F8D3F0F2050, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_TRAFFICLIGHT_OVERRIDE(Entity entity, int state) { invoke<Void>(0x57C5DB656185EAC4, entity, state); }
	NATIVE_DECL void SET_ENTITY_IS_IN_VEHICLE(Entity entity) { invoke<Void>(0x78E8E3A640178255, entity); }
	NATIVE_DECL void CREATE_MODEL_SWAP(float x, float y, float z, float radius, Hash originalModel, Hash newModel, BOOL p6) { invoke<Void>(0x92C47782FDA8B2A3, x, y, z, radius, originalModel, newModel, p6); }
	NATIVE_DECL void REMOVE_MODEL_SWAP(float x, float y, float z, float radius, Hash originalModel, Hash newModel, BOOL p6) { invoke<Void>(0x033C0F9A64E229AE, x, y, z, radius, originalModel, newModel, p6); }
	NATIVE_DECL void CREATE_MODEL_HIDE(float x, float y, float z, float radius, Hash modelHash, BOOL p5) { invoke<Void>(0x8A97BCA30A0CE478, x, y, z, radius, modelHash, p5); }
	NATIVE_DECL void CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS(float x, float y, float z, float radius, Hash modelHash, BOOL p5) { invoke<Void>(0x3A52AE588830BF7F, x, y, z, radius, modelHash, p5); }
	NATIVE_DECL void REMOVE_MODEL_HIDE(float x, float y, float z, float radius, Hash modelHash, BOOL p5) { invoke<Void>(0xD9E3006FB3CBD765, x, y, z, radius, modelHash, p5); }
	NATIVE_DECL void CREATE_FORCED_OBJECT(float x, float y, float z, Any p3, Hash modelHash, BOOL p5) { invoke<Void>(0x150E808B375A385A, x, y, z, p3, modelHash, p5); }
	NATIVE_DECL void REMOVE_FORCED_OBJECT(float x, float y, float z, float p3, Hash modelHash) { invoke<Void>(0x61B6775E83C0DB6F, x, y, z, p3, modelHash); }
	NATIVE_DECL void SET_ENTITY_NO_COLLISION_ENTITY(Entity entity1, Entity entity2, BOOL thisFrameOnly) { invoke<Void>(0xA53ED5520C07654A, entity1, entity2, thisFrameOnly); }
	NATIVE_DECL void _SET_ENTITY_NO_COLLISION_WITH_NETWORKED_ENTITY(Entity entity1, Entity entity2) { invoke<Void>(0x0A27A7827347B3B1, entity1, entity2); }
	NATIVE_DECL void SET_ENTITY_MOTION_BLUR(Entity entity, BOOL toggle) { invoke<Void>(0x295D82A8559F9150, entity, toggle); }
	NATIVE_DECL void SET_CAN_AUTO_VAULT_ON_ENTITY(Entity entity, BOOL toggle) { invoke<Void>(0xE12ABE5E3A389A6C, entity, toggle); }
	NATIVE_DECL void SET_CAN_CLIMB_ON_ENTITY(Entity entity, BOOL toggle) { invoke<Void>(0xA80AE305E0A3044F, entity, toggle); }
	NATIVE_DECL void SET_WAIT_FOR_COLLISIONS_BEFORE_PROBE(Entity entity, BOOL toggle) { invoke<Void>(0xDC6F8601FAF2E893, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_NOWEAPONDECALS(Entity entity, BOOL p1) { invoke<Void>(0x2C2E3DC128F44309, entity, p1); }
	NATIVE_DECL void SET_ENTITY_USE_MAX_DISTANCE_FOR_WATER_REFLECTION(Entity entity, BOOL p1) { invoke<Void>(0x1A092BB0C3808B96, entity, p1); }
	NATIVE_DECL Vector3 GET_ENTITY_BONE_ROTATION(Entity entity, int boneIndex) { return invoke<Vector3>(0xCE6294A232D03786, entity, boneIndex); }
	NATIVE_DECL Vector3 GET_ENTITY_BONE_POSTION(Entity entity, int boneIndex) { return invoke<Vector3>(0x46F8696933A63C9B, entity, boneIndex); }
	NATIVE_DECL Vector3 GET_ENTITY_BONE_OBJECT_ROTATION(Entity entity, int boneIndex) { return invoke<Vector3>(0xBD8D32550E5CEBFE, entity, boneIndex); }
	NATIVE_DECL Vector3 GET_ENTITY_BONE_OBJECT_POSTION(Entity entity, int boneIndex) { return invoke<Vector3>(0xCF1247CC86961FD6, entity, boneIndex); }
	NATIVE_DECL int GET_ENTITY_BONE_COUNT(Entity entity) { return invoke<int>(0xB328DCC3A3AA401B, entity); }
	NATIVE_DECL void ENABLE_ENTITY_BULLET_COLLISION(Entity entity) { invoke<Void>(0x6CE177D014502E8A, entity); }
	NATIVE_DECL void SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_ENTITY(Entity entity1, Entity entity2) { invoke<Void>(0xB17BC6453F6CF5AC, entity1, entity2); }
	NATIVE_DECL void SET_ENTITY_CANT_CAUSE_COLLISION_DAMAGED_ENTITY(Entity entity1, Entity entity2) { invoke<Void>(0x68B562E124CC0AEF, entity1, entity2); }
	NATIVE_DECL void SET_ALLOW_MIGRATE_TO_SPECTATOR(Entity entity, Any p1) { invoke<Void>(0x36F32DE87082343E, entity, p1); }
	NATIVE_DECL Entity GET_ENTITY_OF_TYPE_ATTACHED_TO_ENTITY(Entity entity, Hash modelHash) { return invoke<Entity>(0x1F922734E259BD26, entity, modelHash); }
	NATIVE_DECL Entity _GET_CHILD_ATTACHMENT(Entity entity) { return invoke<Entity>(0xD35ECEBF6FB2C261, entity); }
	NATIVE_DECL void SET_PICK_UP_BY_CARGOBOB_DISABLED(Entity entity, BOOL toggle) { invoke<Void>(0xD7B80E7C3BEFC396, entity, toggle); }
}

namespace EVENT
{
	NATIVE_DECL void SET_DECISION_MAKER(Ped ped, Hash name) { invoke<Void>(0xB604A2942ADED0EE, ped, name); }
	NATIVE_DECL void CLEAR_DECISION_MAKER_EVENT_RESPONSE(Hash name, int eventType) { invoke<Void>(0x4FC9381A7AEE8968, name, eventType); }
	NATIVE_DECL void BLOCK_DECISION_MAKER_EVENT(Hash name, int eventType) { invoke<Void>(0xE42FCDFD0E4196F7, name, eventType); }
	NATIVE_DECL void UNBLOCK_DECISION_MAKER_EVENT(Hash name, int eventType) { invoke<Void>(0xD7CD9CF34F2C99E8, name, eventType); }
	NATIVE_DECL int ADD_SHOCKING_EVENT_AT_POSITION(int eventType, float x, float y, float z, float duration) { return invoke<int>(0xD9F8455409B525E9, eventType, x, y, z, duration); }
	NATIVE_DECL int ADD_SHOCKING_EVENT_FOR_ENTITY(int eventType, Entity entity, float duration) { return invoke<int>(0x7FD8F3BE76F89422, eventType, entity, duration); }
	NATIVE_DECL BOOL IS_SHOCKING_EVENT_IN_SPHERE(int eventType, float x, float y, float z, float radius) { return invoke<BOOL>(0x1374ABB7C15BAB92, eventType, x, y, z, radius); }
	NATIVE_DECL BOOL REMOVE_SHOCKING_EVENT(ScrHandle event) { return invoke<BOOL>(0x2CDA538C44C6CCE5, event); }
	NATIVE_DECL void REMOVE_ALL_SHOCKING_EVENTS(BOOL p0) { invoke<Void>(0xEAABE8FDFA21274C, p0); }
	NATIVE_DECL void REMOVE_SHOCKING_EVENT_SPAWN_BLOCKING_AREAS() { invoke<Void>(0x340F1415B68AEADE); }
	NATIVE_DECL void SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME() { invoke<Void>(0x2F9A292AD0A3BD89); }
	NATIVE_DECL void SUPPRESS_SHOCKING_EVENT_TYPE_NEXT_FRAME(int eventType) { invoke<Void>(0x3FD2EC8BF1F1CF30, eventType); }
	NATIVE_DECL void SUPPRESS_AGITATION_EVENTS_NEXT_FRAME() { invoke<Void>(0x5F3B7749C112D552); }
}

namespace EXTRAMETADATA
{
	NATIVE_DECL int GET_NUM_TATTOO_SHOP_DLC_ITEMS(int character) { return invoke<int>(0x278F76C3B0A8F109, character); }
	NATIVE_DECL BOOL GET_TATTOO_SHOP_DLC_ITEM_DATA(int characterType, int decorationIndex, Any* outComponent) { return invoke<BOOL>(0xFF56381874F82086, characterType, decorationIndex, outComponent); }
	NATIVE_DECL int GET_TATTOO_SHOP_DLC_ITEM_INDEX(Hash overlayHash, Any p1, int character) { return invoke<int>(0x10144267DD22866C, overlayHash, p1, character); }
	NATIVE_DECL void INIT_SHOP_PED_COMPONENT(Any* outComponent) { invoke<Void>(0x1E8C308FD312C036, outComponent); }
	NATIVE_DECL void INIT_SHOP_PED_PROP(Any* outProp) { invoke<Void>(0xEB0A2B758F7B850F, outProp); }
	NATIVE_DECL int SETUP_SHOP_PED_APPAREL_QUERY(int p0, int p1, int p2, int p3) { return invoke<int>(0x50F457823CE6EB5F, p0, p1, p2, p3); }
	NATIVE_DECL int SETUP_SHOP_PED_APPAREL_QUERY_TU(int character, int p1, int p2, BOOL p3, int p4, int componentId) { return invoke<int>(0x9BDF59818B1E38C1, character, p1, p2, p3, p4, componentId); }
	NATIVE_DECL void GET_SHOP_PED_QUERY_COMPONENT(int componentId, Any* outComponent) { invoke<Void>(0x249E310B2D920699, componentId, outComponent); }
	NATIVE_DECL int GET_SHOP_PED_QUERY_COMPONENT_INDEX(Hash componentHash) { return invoke<int>(0x96E2929292A4DB77, componentHash); }
	NATIVE_DECL void GET_SHOP_PED_COMPONENT(Hash componentHash, Any* outComponent) { invoke<Void>(0x74C0E2A57EC66760, componentHash, outComponent); }
	NATIVE_DECL void GET_SHOP_PED_QUERY_PROP(int componentId, Any* outProp) { invoke<Void>(0xDE44A00999B2837D, componentId, outProp); }
	NATIVE_DECL int GET_SHOP_PED_QUERY_PROP_INDEX(Hash componentHash) { return invoke<int>(0x6CEBE002E58DEE97, componentHash); }
	NATIVE_DECL void GET_SHOP_PED_PROP(Hash componentHash, Any* outProp) { invoke<Void>(0x5D5CAFF661DDF6FC, componentHash, outProp); }
	NATIVE_DECL Hash GET_HASH_NAME_FOR_COMPONENT(Entity entity, int componentId, int drawableVariant, int textureVariant) { return invoke<Hash>(0x0368B3A838070348, entity, componentId, drawableVariant, textureVariant); }
	NATIVE_DECL Hash GET_HASH_NAME_FOR_PROP(Entity entity, int componentId, int propIndex, int propTextureIndex) { return invoke<Hash>(0x5D6160275CAEC8DD, entity, componentId, propIndex, propTextureIndex); }
	NATIVE_DECL int GET_SHOP_PED_APPAREL_VARIANT_COMPONENT_COUNT(Hash componentHash) { return invoke<int>(0xC17AD0E5752BECDA, componentHash); }
	NATIVE_DECL int GET_SHOP_PED_APPAREL_VARIANT_PROP_COUNT(Hash propHash) { return invoke<int>(0xD40AAC51E8E4C663, propHash); }
	NATIVE_DECL void GET_VARIANT_COMPONENT(Hash componentHash, int variantComponentIndex, Hash* nameHash, int* enumValue, int* componentType) { invoke<Void>(0x6E11F282F11863B6, componentHash, variantComponentIndex, nameHash, enumValue, componentType); }
	NATIVE_DECL void GET_VARIANT_PROP(Hash componentHash, int variantPropIndex, Hash* nameHash, int* enumValue, int* anchorPoint) { invoke<Void>(0xD81B7F27BC773E66, componentHash, variantPropIndex, nameHash, enumValue, anchorPoint); }
	NATIVE_DECL int GET_SHOP_PED_APPAREL_FORCED_COMPONENT_COUNT(Hash componentHash) { return invoke<int>(0xC6B9DB42C04DD8C3, componentHash); }
	NATIVE_DECL int GET_SHOP_PED_APPAREL_FORCED_PROP_COUNT(Hash componentHash) { return invoke<int>(0x017568A8182D98A6, componentHash); }
	NATIVE_DECL void GET_FORCED_COMPONENT(Hash componentHash, int forcedComponentIndex, Hash* nameHash, int* enumValue, int* componentType) { invoke<Void>(0x6C93ED8C2F74859B, componentHash, forcedComponentIndex, nameHash, enumValue, componentType); }
	NATIVE_DECL void GET_FORCED_PROP(Hash componentHash, int forcedPropIndex, Hash* nameHash, int* enumValue, int* anchorPoint) { invoke<Void>(0xE1CA84EBF72E691D, componentHash, forcedPropIndex, nameHash, enumValue, anchorPoint); }
	NATIVE_DECL BOOL DOES_SHOP_PED_APPAREL_HAVE_RESTRICTION_TAG(Hash componentHash, Hash restrictionTagHash, int componentId) { return invoke<BOOL>(0x341DE7ED1D2A1BFD, componentHash, restrictionTagHash, componentId); }
	NATIVE_DECL BOOL DOES_CURRENT_PED_COMPONENT_HAVE_RESTRICTION_TAG(Ped ped, int componentId, Hash restrictionTagHash) { return invoke<BOOL>(0x7796B21B76221BC5, ped, componentId, restrictionTagHash); }
	NATIVE_DECL BOOL DOES_CURRENT_PED_PROP_HAVE_RESTRICTION_TAG(Ped ped, int componentId, Hash restrictionTagHash) { return invoke<BOOL>(0xD726BAB4554DA580, ped, componentId, restrictionTagHash); }
	NATIVE_DECL int SETUP_SHOP_PED_OUTFIT_QUERY(int character, BOOL p1) { return invoke<int>(0xF3FBE2D50A6A8C28, character, p1); }
	NATIVE_DECL void GET_SHOP_PED_QUERY_OUTFIT(int outfitIndex, Any* outfit) { invoke<Void>(0x6D793F03A631FE56, outfitIndex, outfit); }
	NATIVE_DECL void GET_SHOP_PED_OUTFIT(Any p0, Any* p1) { invoke<Void>(0xB7952076E444979D, p0, p1); }
	NATIVE_DECL int GET_SHOP_PED_OUTFIT_LOCATE(Any p0) { return invoke<int>(0x073CA26B079F956E, p0); }
	NATIVE_DECL BOOL GET_SHOP_PED_OUTFIT_PROP_VARIANT(Hash outfitHash, int variantIndex, Any* outPropVariant) { return invoke<BOOL>(0xA9F9C2E0FDE11CBB, outfitHash, variantIndex, outPropVariant); }
	NATIVE_DECL BOOL GET_SHOP_PED_OUTFIT_COMPONENT_VARIANT(Hash outfitHash, int variantIndex, Any* outComponentVariant) { return invoke<BOOL>(0x19F2A026EDF0013F, outfitHash, variantIndex, outComponentVariant); }
	NATIVE_DECL int GET_NUM_DLC_VEHICLES() { return invoke<int>(0xA7A866D21CD2329B); }
	NATIVE_DECL Hash GET_DLC_VEHICLE_MODEL(int dlcVehicleIndex) { return invoke<Hash>(0xECC01B7C5763333C, dlcVehicleIndex); }
	NATIVE_DECL BOOL GET_DLC_VEHICLE_DATA(int dlcVehicleIndex, Any* outData) { return invoke<BOOL>(0x33468EDC08E371F6, dlcVehicleIndex, outData); }
	NATIVE_DECL int GET_DLC_VEHICLE_FLAGS(int dlcVehicleIndex) { return invoke<int>(0x5549EE11FA22FCF2, dlcVehicleIndex); }
	NATIVE_DECL int GET_NUM_DLC_WEAPONS() { return invoke<int>(0xEE47635F352DA367); }
	NATIVE_DECL int GET_NUM_DLC_WEAPONS_SP() { return invoke<int>(0x4160B65AE085B5A9); }
	NATIVE_DECL BOOL GET_DLC_WEAPON_DATA(int dlcWeaponIndex, Any* outData) { return invoke<BOOL>(0x79923CD21BECE14E, dlcWeaponIndex, outData); }
	NATIVE_DECL BOOL GET_DLC_WEAPON_DATA_SP(int dlcWeaponIndex, Any* outData) { return invoke<BOOL>(0x310836EE7129BA33, dlcWeaponIndex, outData); }
	NATIVE_DECL int GET_NUM_DLC_WEAPON_COMPONENTS(int dlcWeaponIndex) { return invoke<int>(0x405425358A7D61FE, dlcWeaponIndex); }
	NATIVE_DECL int GET_NUM_DLC_WEAPON_COMPONENTS_SP(int dlcWeaponIndex) { return invoke<int>(0xAD2A7A6DFF55841B, dlcWeaponIndex); }
	NATIVE_DECL BOOL GET_DLC_WEAPON_COMPONENT_DATA(int dlcWeaponIndex, int dlcWeapCompIndex, Any* ComponentDataPtr) { return invoke<BOOL>(0x6CF598A2957C2BF8, dlcWeaponIndex, dlcWeapCompIndex, ComponentDataPtr); }
	NATIVE_DECL BOOL GET_DLC_WEAPON_COMPONENT_DATA_SP(int dlcWeaponIndex, int dlcWeapCompIndex, Any* ComponentDataPtr) { return invoke<BOOL>(0x31D5E073B6F93CDC, dlcWeaponIndex, dlcWeapCompIndex, ComponentDataPtr); }
	NATIVE_DECL BOOL IS_CONTENT_ITEM_LOCKED(Hash itemHash) { return invoke<BOOL>(0xD4D7B033C3AA243C, itemHash); }
	NATIVE_DECL BOOL IS_DLC_VEHICLE_MOD(Hash hash) { return invoke<BOOL>(0x0564B9FF9631B82C, hash); }
	NATIVE_DECL Hash GET_DLC_VEHICLE_MOD_LOCK_HASH(Hash hash) { return invoke<Hash>(0xC098810437312FFF, hash); }
	NATIVE_DECL void EXECUTE_CONTENT_CHANGESET_GROUP_FOR_ALL(Hash hash) { invoke<Void>(0x6BEDF5769AC2DC07, hash); }
	NATIVE_DECL void REVERT_CONTENT_CHANGESET_GROUP_FOR_ALL(Hash hash) { invoke<Void>(0x3C1978285B036B25, hash); }
}

namespace FIRE
{
	NATIVE_DECL FireId START_SCRIPT_FIRE(float X, float Y, float Z, int maxChildren, BOOL isGasFire) { return invoke<FireId>(0x6B83617E04503888, X, Y, Z, maxChildren, isGasFire); }
	NATIVE_DECL void REMOVE_SCRIPT_FIRE(FireId fireHandle) { invoke<Void>(0x7FF548385680673F, fireHandle); }
	NATIVE_DECL FireId START_ENTITY_FIRE(Entity entity) { return invoke<FireId>(0xF6A9D9708F6F23DF, entity); }
	NATIVE_DECL void STOP_ENTITY_FIRE(Entity entity) { invoke<Void>(0x7F0DD2EBBB651AFF, entity); }
	NATIVE_DECL BOOL IS_ENTITY_ON_FIRE(Entity entity) { return invoke<BOOL>(0x28D3FED7190D3A0B, entity); }
	NATIVE_DECL int GET_NUMBER_OF_FIRES_IN_RANGE(float x, float y, float z, float radius) { return invoke<int>(0x50CAD495A460B305, x, y, z, radius); }
	NATIVE_DECL void SET_FLAMMABILITY_MULTIPLIER(float p0) { invoke<Void>(0x8F390AC4155099BA, p0); }
	NATIVE_DECL void STOP_FIRE_IN_RANGE(float x, float y, float z, float radius) { invoke<Void>(0x056A8A219B8E829F, x, y, z, radius); }
	NATIVE_DECL BOOL GET_CLOSEST_FIRE_POS(Vector3* outPosition, float x, float y, float z) { return invoke<BOOL>(0x352A9F6BCF90081F, outPosition, x, y, z); }
	NATIVE_DECL void ADD_EXPLOSION(float x, float y, float z, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake, BOOL noDamage) { invoke<Void>(0xE3AD2BDBAEE269AC, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake, noDamage); }
	NATIVE_DECL void ADD_OWNED_EXPLOSION(Ped ped, float x, float y, float z, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake) { invoke<Void>(0x172AA1B624FA1013, ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake); }
	NATIVE_DECL void ADD_EXPLOSION_WITH_USER_VFX(float x, float y, float z, int explosionType, Hash explosionFx, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake) { invoke<Void>(0x36DD3FE58B5E5212, x, y, z, explosionType, explosionFx, damageScale, isAudible, isInvisible, cameraShake); }
	NATIVE_DECL BOOL IS_EXPLOSION_IN_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<BOOL>(0x2E2EBA0EE7CED0E0, explosionType, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL BOOL IS_EXPLOSION_ACTIVE_IN_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<BOOL>(0x6070104B699B2EF4, explosionType, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL BOOL IS_EXPLOSION_IN_SPHERE(int explosionType, float x, float y, float z, float radius) { return invoke<BOOL>(0xAB0F816885B0E483, explosionType, x, y, z, radius); }
	NATIVE_DECL Entity GET_OWNER_OF_EXPLOSION_IN_SPHERE(int explosionType, float x, float y, float z, float radius) { return invoke<Entity>(0xB3CD51E3DB86F176, explosionType, x, y, z, radius); }
	NATIVE_DECL BOOL IS_EXPLOSION_IN_ANGLED_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2, float width) { return invoke<BOOL>(0xA079A6C51525DC4B, explosionType, x1, y1, z1, x2, y2, z2, width); }
	NATIVE_DECL Entity GET_OWNER_OF_EXPLOSION_IN_ANGLED_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2, float radius) { return invoke<Entity>(0x14BA4BA137AF6CEC, explosionType, x1, y1, z1, x2, y2, z2, radius); }
	NATIVE_DECL void _NETWORK_EXPECT_EXPLOSION_EVENTS_FOR_PLAYER(BOOL expect, Player player) { invoke<Void>(0x5241DB47A8B8AD54, expect, player); }
	NATIVE_DECL int _GET_MAXIMUM_NUMBER_OF_WATER_CANNONS() { return invoke<int>(0x56581E7E219D6263); }
	NATIVE_DECL Vector3 _GET_WATER_CANNON_COORDS(int index) { return invoke<Vector3>(0xE61CBD3ED80E7327, index); }
}

namespace GRAPHICS
{
	NATIVE_DECL void SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE(BOOL enabled) { invoke<Void>(0x175B6BFC15CDD0C5, enabled); }
	NATIVE_DECL void DRAW_DEBUG_LINE(float x1, float y1, float z1, float x2, float y2, float z2, int r, int g, int b, int alpha) { invoke<Void>(0x7FDFADE676AA3CB0, x1, y1, z1, x2, y2, z2, r, g, b, alpha); }
	NATIVE_DECL void DRAW_DEBUG_LINE_WITH_TWO_COLOURS(float x1, float y1, float z1, float x2, float y2, float z2, int r1, int g1, int b1, int r2, int g2, int b2, int alpha1, int alpha2) { invoke<Void>(0xD8B9A8AC5608FF94, x1, y1, z1, x2, y2, z2, r1, g1, b1, r2, g2, b2, alpha1, alpha2); }
	NATIVE_DECL void DRAW_DEBUG_SPHERE(float x, float y, float z, float radius, int red, int green, int blue, int alpha) { invoke<Void>(0xAAD68E1AB39DA632, x, y, z, radius, red, green, blue, alpha); }
	NATIVE_DECL void DRAW_DEBUG_BOX(float x1, float y1, float z1, float x2, float y2, float z2, int r, int g, int b, int alpha) { invoke<Void>(0x083A2CA4F2E573BD, x1, y1, z1, x2, y2, z2, r, g, b, alpha); }
	NATIVE_DECL void DRAW_DEBUG_CROSS(float x, float y, float z, float size, int red, int green, int blue, int alpha) { invoke<Void>(0x73B1189623049839, x, y, z, size, red, green, blue, alpha); }
	NATIVE_DECL void DRAW_DEBUG_TEXT(const char* text, float x, float y, float z, int red, int green, int blue, int alpha) { invoke<Void>(0x3903E216620488E8, text, x, y, z, red, green, blue, alpha); }
	NATIVE_DECL void DRAW_DEBUG_TEXT_2D(const char* text, float x, float y, float z, int red, int green, int blue, int alpha) { invoke<Void>(0xA3BB2E9555C05A8F, text, x, y, z, red, green, blue, alpha); }
	NATIVE_DECL void DRAW_LINE(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha) { invoke<Void>(0x6B7256074AE34680, x1, y1, z1, x2, y2, z2, red, green, blue, alpha); }
	NATIVE_DECL void DRAW_POLY(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int red, int green, int blue, int alpha) { invoke<Void>(0xAC26716048436851, x1, y1, z1, x2, y2, z2, x3, y3, z3, red, green, blue, alpha); }
	NATIVE_DECL void DRAW_TEXTURED_POLY(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int red, int green, int blue, int alpha, const char* textureDict, const char* textureName, float u1, float v1, float w1, float u2, float v2, float w2, float u3, float v3, float w3) { invoke<Void>(0x29280002282F1928, x1, y1, z1, x2, y2, z2, x3, y3, z3, red, green, blue, alpha, textureDict, textureName, u1, v1, w1, u2, v2, w2, u3, v3, w3); }
	NATIVE_DECL void DRAW_TEXTURED_POLY_WITH_THREE_COLOURS(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float red1, float green1, float blue1, int alpha1, float red2, float green2, float blue2, int alpha2, float red3, float green3, float blue3, int alpha3, const char* textureDict, const char* textureName, float u1, float v1, float w1, float u2, float v2, float w2, float u3, float v3, float w3) { invoke<Void>(0x736D7AA1B750856B, x1, y1, z1, x2, y2, z2, x3, y3, z3, red1, green1, blue1, alpha1, red2, green2, blue2, alpha2, red3, green3, blue3, alpha3, textureDict, textureName, u1, v1, w1, u2, v2, w2, u3, v3, w3); }
	NATIVE_DECL void DRAW_BOX(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha) { invoke<Void>(0xD3A9971CADAC7252, x1, y1, z1, x2, y2, z2, red, green, blue, alpha); }
	NATIVE_DECL void SET_BACKFACECULLING(BOOL toggle) { invoke<Void>(0x23BA6B0C2AD7B0D3, toggle); }
	NATIVE_DECL void SET_DEPTHWRITING(BOOL toggle) { invoke<Void>(0xC5C8F970D4EDFF71, toggle); }
	NATIVE_DECL void _SET_BLEND_STATE_NORMAL() { invoke<Void>(0x976D155439608592); }
	NATIVE_DECL void _SET_BLEND_STATE_ALPHA_ADDITIVE() { invoke<Void>(0x01677A72A8BDCD1A); }
	NATIVE_DECL BOOL BEGIN_TAKE_MISSION_CREATOR_PHOTO() { return invoke<BOOL>(0x1DD2139A9A20DCE8); }
	NATIVE_DECL int GET_STATUS_OF_TAKE_MISSION_CREATOR_PHOTO() { return invoke<int>(0x90A78ECAA4E78453); }
	NATIVE_DECL void FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO() { invoke<Void>(0x0A46AF8A78DC5E0A); }
	NATIVE_DECL BOOL LOAD_MISSION_CREATOR_PHOTO(Any* p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x4862437A486F91B0, p0, p1, p2, p3); }
	NATIVE_DECL int GET_STATUS_OF_LOAD_MISSION_CREATOR_PHOTO(Any* p0) { return invoke<int>(0x1670F8D05056F257, p0); }
	NATIVE_DECL BOOL BEGIN_CREATE_MISSION_CREATOR_PHOTO_PREVIEW() { return invoke<BOOL>(0x7FA5D82B8F58EC06); }
	NATIVE_DECL int GET_STATUS_OF_CREATE_MISSION_CREATOR_PHOTO_PREVIEW() { return invoke<int>(0x5B0316762AFD4A64); }
	NATIVE_DECL void FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO_PREVIEW() { invoke<Void>(0x346EF3ECAAAB149E); }
	NATIVE_DECL BOOL BEGIN_TAKE_HIGH_QUALITY_PHOTO() { return invoke<BOOL>(0xA67C35C56EB1BD9D); }
	NATIVE_DECL int GET_STATUS_OF_TAKE_HIGH_QUALITY_PHOTO() { return invoke<int>(0x0D6CA79EEEBD8CA3); }
	NATIVE_DECL void FREE_MEMORY_FOR_HIGH_QUALITY_PHOTO() { invoke<Void>(0xD801CC02177FA3F1); }
	NATIVE_DECL void SET_TAKEN_PHOTO_IS_MUGSHOT(BOOL toggle) { invoke<Void>(0x1BBC135A4D25EDDE, toggle); }
	NATIVE_DECL void SET_ARENA_THEME_AND_VARIATION_FOR_TAKEN_PHOTO(Any p0, int p1) { invoke<Void>(0xF3F776ADA161E47D, p0, p1); }
	NATIVE_DECL void SET_ON_ISLAND_X_FOR_TAKEN_PHOTO(Any p0) { invoke<Void>(0xADD6627C4D325458, p0); }
	NATIVE_DECL BOOL SAVE_HIGH_QUALITY_PHOTO(int unused) { return invoke<BOOL>(0x3DEC726C25A11BAC, unused); }
	NATIVE_DECL int GET_STATUS_OF_SAVE_HIGH_QUALITY_PHOTO() { return invoke<int>(0x0C0C4E81E1AC60A0); }
	NATIVE_DECL BOOL BEGIN_CREATE_LOW_QUALITY_COPY_OF_PHOTO(Any p0) { return invoke<BOOL>(0x759650634F07B6B4, p0); }
	NATIVE_DECL int GET_STATUS_OF_CREATE_LOW_QUALITY_COPY_OF_PHOTO(int p0) { return invoke<int>(0xCB82A0BF0E3E3265, p0); }
	NATIVE_DECL void FREE_MEMORY_FOR_LOW_QUALITY_PHOTO() { invoke<Void>(0x6A12D88881435DCA); }
	NATIVE_DECL void DRAW_LOW_QUALITY_PHOTO_TO_PHONE(BOOL p0, BOOL p1) { invoke<Void>(0x1072F115DAB0717E, p0, p1); }
	NATIVE_DECL int GET_MAXIMUM_NUMBER_OF_PHOTOS() { return invoke<int>(0x34D23450F028B0BF); }
	NATIVE_DECL int GET_MAXIMUM_NUMBER_OF_CLOUD_PHOTOS() { return invoke<int>(0xDC54A7AF8B3A14EF); }
	NATIVE_DECL int GET_CURRENT_NUMBER_OF_CLOUD_PHOTOS() { return invoke<int>(0x473151EBC762C6DA); }
	NATIVE_DECL BOOL QUEUE_OPERATION_TO_CREATE_SORTED_LIST_OF_PHOTOS(Any p0) { return invoke<BOOL>(0x2A893980E96B659A, p0); }
	NATIVE_DECL int GET_STATUS_OF_SORTED_LIST_OPERATION(Any p0) { return invoke<int>(0xF5BED327CEA362B1, p0); }
	NATIVE_DECL void CLEAR_STATUS_OF_SORTED_LIST_OPERATION() { invoke<Void>(0x4AF92ACD3141D96C); }
	NATIVE_DECL BOOL DOES_THIS_PHOTO_SLOT_CONTAIN_A_VALID_PHOTO(Any p0) { return invoke<BOOL>(0xE791DF1F73ED2C8B, p0); }
	NATIVE_DECL BOOL LOAD_HIGH_QUALITY_PHOTO(Any p0) { return invoke<BOOL>(0xEC72C258667BE5EA, p0); }
	NATIVE_DECL int GET_LOAD_HIGH_QUALITY_PHOTO_STATUS(int p0) { return invoke<int>(0x40AFB081F8ADD4EE, p0); }
	NATIVE_DECL void DRAW_LIGHT_WITH_RANGEEX(float x, float y, float z, int r, int g, int b, float range, float intensity, float shadow) { invoke<Void>(0xF49E9A9716A04595, x, y, z, r, g, b, range, intensity, shadow); }
	NATIVE_DECL void DRAW_LIGHT_WITH_RANGE(float posX, float posY, float posZ, int colorR, int colorG, int colorB, float range, float intensity) { invoke<Void>(0xF2A1B2771A01DBD4, posX, posY, posZ, colorR, colorG, colorB, range, intensity); }
	NATIVE_DECL void DRAW_SPOT_LIGHT(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float distance, float brightness, float hardness, float radius, float falloff) { invoke<Void>(0xD0F64B265C8C8B33, posX, posY, posZ, dirX, dirY, dirZ, colorR, colorG, colorB, distance, brightness, hardness, radius, falloff); }
	NATIVE_DECL void DRAW_SHADOWED_SPOT_LIGHT(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float distance, float brightness, float roundness, float radius, float falloff, int shadowId) { invoke<Void>(0x5BCA583A583194DB, posX, posY, posZ, dirX, dirY, dirZ, colorR, colorG, colorB, distance, brightness, roundness, radius, falloff, shadowId); }
	NATIVE_DECL void _DRAW_CAPSULE_LIGHT(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float falloff, float intensity, float capsuleExtent, float exponent) { invoke<Void>(0x330F4FA20FB57738, posX, posY, posZ, dirX, dirY, dirZ, colorR, colorG, colorB, falloff, intensity, capsuleExtent, exponent); }
	NATIVE_DECL void FADE_UP_PED_LIGHT(float p0) { invoke<Void>(0xC9B18B4619F48F7B, p0); }
	NATIVE_DECL void UPDATE_LIGHTS_ON_ENTITY(Entity entity) { invoke<Void>(0xDEADC0DEDEADC0DE, entity); }
	NATIVE_DECL void _UPDATE_LIGHTS_LOCATION_FROM_ENTITY(Entity entity) { invoke<Void>(0x988C5FE3B815C998, entity); }
	NATIVE_DECL void SET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE(Any p0) { invoke<Void>(0x9641588DAB93B4B5, p0); }
	NATIVE_DECL float GET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE() { return invoke<float>(0x393BD2275CEB7793); }
	NATIVE_DECL void DRAW_MARKER(int type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, int red, int green, int blue, int alpha, BOOL bobUpAndDown, BOOL faceCamera, int p19, BOOL rotate, const char* textureDict, const char* textureName, BOOL drawOnEnts) { invoke<Void>(0x28477EC23D892089, type, posX, posY, posZ, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, red, green, blue, alpha, bobUpAndDown, faceCamera, p19, rotate, textureDict, textureName, drawOnEnts); }
	NATIVE_DECL void DRAW_MARKER_EX(int type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, int red, int green, int blue, int alpha, BOOL bobUpAndDown, BOOL faceCamera, Any p19, BOOL rotate, const char* textureDict, const char* textureName, BOOL drawOnEnts, BOOL p24, BOOL p25) { invoke<Void>(0xE82728F0DE75D13A, type, posX, posY, posZ, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, red, green, blue, alpha, bobUpAndDown, faceCamera, p19, rotate, textureDict, textureName, drawOnEnts, p24, p25); }
	NATIVE_DECL void DRAW_MARKER_SPHERE(float x, float y, float z, float radius, int red, int green, int blue, float alpha) { invoke<Void>(0x799017F9E3B10112, x, y, z, radius, red, green, blue, alpha); }
	NATIVE_DECL void _DRAW_MARKER_GLOW(float x, float y, float z, float size, int red, int green, int blue, float intensity) { invoke<Void>(0xE59B0A106CC15FC2, x, y, z, size, red, green, blue, intensity); }
	NATIVE_DECL void _MAKE_GLOWS_ADDITIVE(BOOL toggle) { invoke<Void>(0xDC60226A3F4D9F42, toggle); }
	NATIVE_DECL int CREATE_CHECKPOINT(int type, float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float diameter, int red, int green, int blue, int alpha, int reserved) { return invoke<int>(0x0134F0835AB6BFCB, type, posX1, posY1, posZ1, posX2, posY2, posZ2, diameter, red, green, blue, alpha, reserved); }
	NATIVE_DECL void SET_CHECKPOINT_INSIDE_CYLINDER_HEIGHT_SCALE(int checkpoint, float scale) { invoke<Void>(0x4B5B4DA5D79F1943, checkpoint, scale); }
	NATIVE_DECL void SET_CHECKPOINT_INSIDE_CYLINDER_SCALE(int checkpoint, float scale) { invoke<Void>(0x44621483FF966526, checkpoint, scale); }
	NATIVE_DECL void SET_CHECKPOINT_CYLINDER_HEIGHT(int checkpoint, float nearHeight, float farHeight, float radius) { invoke<Void>(0x2707AAE9D9297D89, checkpoint, nearHeight, farHeight, radius); }
	NATIVE_DECL void SET_CHECKPOINT_RGBA(int checkpoint, int red, int green, int blue, int alpha) { invoke<Void>(0x7167371E8AD747F7, checkpoint, red, green, blue, alpha); }
	NATIVE_DECL void SET_CHECKPOINT_RGBA2(int checkpoint, int red, int green, int blue, int alpha) { invoke<Void>(0xB9EA40907C680580, checkpoint, red, green, blue, alpha); }
	NATIVE_DECL void SET_CHECKPOINT_CLIPPLANE_WITH_POS_NORM(int checkpoint, float posX, float posY, float posZ, float unkX, float unkY, float unkZ) { invoke<Void>(0xF51D36185993515D, checkpoint, posX, posY, posZ, unkX, unkY, unkZ); }
	NATIVE_DECL void SET_CHECKPOINT_FORCE_OLD_ARROW_POINTING(int checkpoint) { invoke<Void>(0xFCF6788FC4860CD4, checkpoint); }
	NATIVE_DECL void SET_CHECKPOINT_DECAL_ROT_ALIGNED_TO_CAMERA_ROT(int checkpoint) { invoke<Void>(0x615D3925E87A3B26, checkpoint); }
	NATIVE_DECL void SET_CHECKPOINT_FORCE_DIRECTION(int checkpoint) { invoke<Void>(0xDB1EA9411C8911EC, checkpoint); }
	NATIVE_DECL void SET_CHECKPOINT_DIRECTION(int checkpoint, float posX, float posY, float posZ) { invoke<Void>(0x3C788E7F6438754D, checkpoint, posX, posY, posZ); }
	NATIVE_DECL void DELETE_CHECKPOINT(int checkpoint) { invoke<Void>(0xF5ED37F54CD4D52E, checkpoint); }
	NATIVE_DECL void DONT_RENDER_IN_GAME_UI(BOOL p0) { invoke<Void>(0x22A249A53034450A, p0); }
	NATIVE_DECL void FORCE_RENDER_IN_GAME_UI(BOOL toggle) { invoke<Void>(0xDC459CFA0CCE245B, toggle); }
	NATIVE_DECL void REQUEST_STREAMED_TEXTURE_DICT(const char* textureDict, BOOL p1) { invoke<Void>(0xDFA2EF8E04127DD5, textureDict, p1); }
	NATIVE_DECL BOOL HAS_STREAMED_TEXTURE_DICT_LOADED(const char* textureDict) { return invoke<BOOL>(0x0145F696AAAAD2E4, textureDict); }
	NATIVE_DECL void SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(const char* textureDict) { invoke<Void>(0xBE2CACCF5A8AA805, textureDict); }
	NATIVE_DECL void DRAW_RECT(float x, float y, float width, float height, int r, int g, int b, int a, BOOL p8) { invoke<Void>(0x3A618A217E5154F0, x, y, width, height, r, g, b, a, p8); }
	NATIVE_DECL void SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU(BOOL toggle) { invoke<Void>(0xC6372ECD45D73BCD, toggle); }
	NATIVE_DECL void SET_SCRIPT_GFX_DRAW_ORDER(int drawOrder) { invoke<Void>(0x61BB1D9B3A95D802, drawOrder); }
	NATIVE_DECL void SET_SCRIPT_GFX_ALIGN(int horizontalAlign, int verticalAlign) { invoke<Void>(0xB8A850F20A067EB6, horizontalAlign, verticalAlign); }
	NATIVE_DECL void RESET_SCRIPT_GFX_ALIGN() { invoke<Void>(0xE3A3DB414A373DAB); }
	NATIVE_DECL void SET_SCRIPT_GFX_ALIGN_PARAMS(float x, float y, float w, float h) { invoke<Void>(0xF5A2C681787E579D, x, y, w, h); }
	NATIVE_DECL void GET_SCRIPT_GFX_ALIGN_POSITION(float x, float y, float* calculatedX, float* calculatedY) { invoke<Void>(0x6DD8F5AA635EB4B2, x, y, calculatedX, calculatedY); }
	NATIVE_DECL float GET_SAFE_ZONE_SIZE() { return invoke<float>(0xBAF107B6BB2C97F0); }
	NATIVE_DECL void DRAW_SPRITE(const char* textureDict, const char* textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha, BOOL p11, Any p12) { invoke<Void>(0xE7FFAE5EBF23D890, textureDict, textureName, screenX, screenY, width, height, heading, red, green, blue, alpha, p11, p12); }
	NATIVE_DECL void DRAW_SPRITE_ARX(const char* textureDict, const char* textureName, float x, float y, float width, float height, float p6, int red, int green, int blue, int alpha, Any p11, Any p12) { invoke<Void>(0x2D3B147AFAD49DE0, textureDict, textureName, x, y, width, height, p6, red, green, blue, alpha, p11, p12); }
	NATIVE_DECL void DRAW_SPRITE_NAMED_RENDERTARGET(const char* textureDict, const char* textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha, Any p11) { invoke<Void>(0x2BC54A8188768488, textureDict, textureName, screenX, screenY, width, height, heading, red, green, blue, alpha, p11); }
	NATIVE_DECL void DRAW_SPRITE_ARX_WITH_UV(const char* textureDict, const char* textureName, float x, float y, float width, float height, float u1, float v1, float u2, float v2, float heading, int red, int green, int blue, int alpha, Any p15) { invoke<Void>(0x95812F9B26074726, textureDict, textureName, x, y, width, height, u1, v1, u2, v2, heading, red, green, blue, alpha, p15); }
	NATIVE_DECL void _CALCULATE_LINE_ORIENTATION_FROM_RENDERED_CAMERA(Vector3* result, float x1, float y1, float z1, float x2, float y2, float z2) { invoke<Void>(0x9F7996F4E32B3026, result, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL void _CALCULATE_ROTATED_VECTOR(Vector3* direction, float roll, float pitch, float yaw) { invoke<Void>(0xA7804512D1FDD22A, direction, roll, pitch, yaw); }
	NATIVE_DECL int ADD_ENTITY_ICON(Entity entity, const char* icon) { return invoke<int>(0x9CD43EEE12BF4DD0, entity, icon); }
	NATIVE_DECL void SET_ENTITY_ICON_VISIBILITY(Entity entity, BOOL toggle) { invoke<Void>(0xE0E8BEECCA96BA31, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_ICON_COLOR(Entity entity, int red, int green, int blue, int alpha) { invoke<Void>(0x1D5F595CCAE2E238, entity, red, green, blue, alpha); }
	NATIVE_DECL void SET_DRAW_ORIGIN(float x, float y, float z, BOOL p3) { invoke<Void>(0xAA0008F3BBB8F416, x, y, z, p3); }
	NATIVE_DECL void CLEAR_DRAW_ORIGIN() { invoke<Void>(0xFF0B610F6BE0D7AF); }
	NATIVE_DECL int SET_BINK_MOVIE(const char* name) { return invoke<int>(0x338D9F609FD632DB, name); }
	NATIVE_DECL void PLAY_BINK_MOVIE(int binkMovie) { invoke<Void>(0x70D2CC8A542A973C, binkMovie); }
	NATIVE_DECL void STOP_BINK_MOVIE(int binkMovie) { invoke<Void>(0x63606A61DE68898A, binkMovie); }
	NATIVE_DECL void RELEASE_BINK_MOVIE(int binkMovie) { invoke<Void>(0x04D950EEFA4EED8C, binkMovie); }
	NATIVE_DECL void DRAW_BINK_MOVIE(int binkMovie, float p1, float p2, float p3, float p4, float p5, int r, int g, int b, int a) { invoke<Void>(0x7118E83EEB9F7238, binkMovie, p1, p2, p3, p4, p5, r, g, b, a); }
	NATIVE_DECL void SET_BINK_MOVIE_TIME(int binkMovie, float progress) { invoke<Void>(0x0CB6B3446855B57A, binkMovie, progress); }
	NATIVE_DECL float GET_BINK_MOVIE_TIME(int binkMovie) { return invoke<float>(0x8E17DDD6B9D5BF29, binkMovie); }
	NATIVE_DECL void SET_BINK_MOVIE_VOLUME(int binkMovie, float value) { invoke<Void>(0xAFF33B1178172223, binkMovie, value); }
	NATIVE_DECL void ATTACH_TV_AUDIO_TO_ENTITY(Entity entity) { invoke<Void>(0x845BAD77CC770633, entity); }
	NATIVE_DECL void SET_BINK_MOVIE_AUDIO_FRONTEND(int binkMovie, BOOL p1) { invoke<Void>(0xF816F2933752322D, binkMovie, p1); }
	NATIVE_DECL void SET_TV_AUDIO_FRONTEND(BOOL toggle) { invoke<Void>(0x113D2C5DC57E1774, toggle); }
	NATIVE_DECL void SET_BINK_SHOULD_SKIP(int binkMovie, BOOL bShouldSkip) { invoke<Void>(0x6805D58CAA427B72, binkMovie, bShouldSkip); }
	NATIVE_DECL int LOAD_MOVIE_MESH_SET(const char* movieMeshSetName) { return invoke<int>(0xB66064452270E8F1, movieMeshSetName); }
	NATIVE_DECL void RELEASE_MOVIE_MESH_SET(int movieMeshSet) { invoke<Void>(0xEB119AA014E89183, movieMeshSet); }
	NATIVE_DECL int QUERY_MOVIE_MESH_SET_STATE(Any p0) { return invoke<int>(0x9B6E70C5CEEF4EEB, p0); }
	NATIVE_DECL void GET_SCREEN_RESOLUTION(int* x, int* y) { invoke<Void>(0x888D57E407E63624, x, y); }
	NATIVE_DECL void GET_ACTUAL_SCREEN_RESOLUTION(int* x, int* y) { invoke<Void>(0x873C9F3104101DD3, x, y); }
	NATIVE_DECL float GET_ASPECT_RATIO(BOOL b) { return invoke<float>(0xF1307EF624A80D87, b); }
	NATIVE_DECL float GET_SCREEN_ASPECT_RATIO() { return invoke<float>(0xB2EBE8CBC58B90E9); }
	NATIVE_DECL BOOL GET_IS_WIDESCREEN() { return invoke<BOOL>(0x30CF4BDA4FCB1905); }
	NATIVE_DECL BOOL GET_IS_HIDEF() { return invoke<BOOL>(0x84ED31191CC5D2C9); }
	NATIVE_DECL void ADJUST_NEXT_POS_SIZE_AS_NORMALIZED_16_9() { invoke<Void>(0xEFABC7722293DA7C); }
	NATIVE_DECL void SET_NIGHTVISION(BOOL toggle) { invoke<Void>(0x18F621F7A5B1F85D, toggle); }
	NATIVE_DECL BOOL GET_REQUESTINGNIGHTVISION() { return invoke<BOOL>(0x35FB78DC42B7BD21); }
	NATIVE_DECL BOOL GET_USINGNIGHTVISION() { return invoke<BOOL>(0x2202A3F42C8E5F79); }
	NATIVE_DECL void SET_EXPOSURETWEAK(BOOL toggle) { invoke<Void>(0xEF398BEEE4EF45F9, toggle); }
	NATIVE_DECL void FORCE_EXPOSURE_READBACK(BOOL toggle) { invoke<Void>(0x814AF7DCAACC597B, toggle); }
	NATIVE_DECL void OVERRIDE_NIGHTVISION_LIGHT_RANGE(float p0) { invoke<Void>(0x43FA7CBE20DAB219, p0); }
	NATIVE_DECL void SET_NOISEOVERIDE(BOOL toggle) { invoke<Void>(0xE787BF1C5CF823C9, toggle); }
	NATIVE_DECL void SET_NOISINESSOVERIDE(float value) { invoke<Void>(0xCB6A7C3BB17A0C67, value); }
	NATIVE_DECL BOOL GET_SCREEN_COORD_FROM_WORLD_COORD(float worldX, float worldY, float worldZ, float* screenX, float* screenY) { return invoke<BOOL>(0x34E82F05DF2974F5, worldX, worldY, worldZ, screenX, screenY); }
	NATIVE_DECL Vector3 GET_TEXTURE_RESOLUTION(const char* textureDict, const char* textureName) { return invoke<Vector3>(0x35736EE65BD00C11, textureDict, textureName); }
	NATIVE_DECL BOOL OVERRIDE_PED_CREW_LOGO_TEXTURE(Ped ped, const char* txd, const char* txn) { return invoke<BOOL>(0x95EB5E34F821BABE, ped, txd, txn); }
	NATIVE_DECL void SET_DISTANCE_BLUR_STRENGTH_OVERRIDE(float p0) { invoke<Void>(0xE2892E7E55D7073A, p0); }
	NATIVE_DECL void SET_FLASH(float p0, float p1, float fadeIn, float duration, float fadeOut) { invoke<Void>(0x0AB84296FED9CFC6, p0, p1, fadeIn, duration, fadeOut); }
	NATIVE_DECL void DISABLE_OCCLUSION_THIS_FRAME() { invoke<Void>(0x3669F1B198DCAA4F); }
	NATIVE_DECL void SET_ARTIFICIAL_LIGHTS_STATE(BOOL state) { invoke<Void>(0x1268615ACE24D504, state); }
	NATIVE_DECL void SET_ARTIFICIAL_VEHICLE_LIGHTS_STATE(BOOL toggle) { invoke<Void>(0xE2B187C0939B3D32, toggle); }
	NATIVE_DECL void DISABLE_HDTEX_THIS_FRAME() { invoke<Void>(0xC35A6D07C93802B2); }
	NATIVE_DECL int CREATE_TRACKED_POINT() { return invoke<int>(0xE2C9439ED45DEA60); }
	NATIVE_DECL void SET_TRACKED_POINT_INFO(int point, float x, float y, float z, float radius) { invoke<Void>(0x164ECBB3CF750CB0, point, x, y, z, radius); }
	NATIVE_DECL BOOL IS_TRACKED_POINT_VISIBLE(int point) { return invoke<BOOL>(0xC45CCDAAC9221CA8, point); }
	NATIVE_DECL void DESTROY_TRACKED_POINT(int point) { invoke<Void>(0xB25DC90BAD56CA42, point); }
	NATIVE_DECL int SET_GRASS_CULL_SPHERE(float p0, float p1, float p2, float p3) { return invoke<int>(0xBE197EAA669238F4, p0, p1, p2, p3); }
	NATIVE_DECL void REMOVE_GRASS_CULL_SPHERE(int handle) { invoke<Void>(0x61F95E5BB3E0A8C6, handle); }
	NATIVE_DECL void PROCGRASS_ENABLE_CULLSPHERE(int handle, float x, float y, float z, float scale) { invoke<Void>(0xAE51BC858F32BA66, handle, x, y, z, scale); }
	NATIVE_DECL void PROCGRASS_DISABLE_CULLSPHERE(int handle) { invoke<Void>(0x649C97D52332341A, handle); }
	NATIVE_DECL BOOL PROCGRASS_IS_CULLSPHERE_ENABLED(int handle) { return invoke<BOOL>(0x2C42340F916C5930, handle); }
	NATIVE_DECL void PROCGRASS_ENABLE_AMBSCALESCAN() { invoke<Void>(0x14FC5833464340A8); }
	NATIVE_DECL void PROCGRASS_DISABLE_AMBSCALESCAN() { invoke<Void>(0x0218BA067D249DEA); }
	NATIVE_DECL void DISABLE_PROCOBJ_CREATION() { invoke<Void>(0x1612C45F9E3E0D44); }
	NATIVE_DECL void ENABLE_PROCOBJ_CREATION() { invoke<Void>(0x5DEBD9C4DC995692); }
	NATIVE_DECL void GRASSBATCH_ENABLE_FLATTENING_EXT_IN_SPHERE(float x, float y, float z, Any p3, float p4, float p5, float p6, float scale) { invoke<Void>(0xAAE9BE70EC7C69AB, x, y, z, p3, p4, p5, p6, scale); }
	NATIVE_DECL void GRASSBATCH_ENABLE_FLATTENING_IN_SPHERE(float x, float y, float z, float radius, float p4, float p5, float p6) { invoke<Void>(0x6D955F6A9E0295B1, x, y, z, radius, p4, p5, p6); }
	NATIVE_DECL void GRASSBATCH_DISABLE_FLATTENING() { invoke<Void>(0x302C91AB2D477F7E); }
	NATIVE_DECL void CASCADE_SHADOWS_INIT_SESSION() { invoke<Void>(0x03FC694AE06C5A20); }
	NATIVE_DECL void CASCADE_SHADOWS_SET_CASCADE_BOUNDS(Any p0, BOOL p1, float p2, float p3, float p4, float p5, BOOL p6, float p7) { invoke<Void>(0xD2936CAB8B58FCBD, p0, p1, p2, p3, p4, p5, p6, p7); }
	NATIVE_DECL void CASCADE_SHADOWS_SET_CASCADE_BOUNDS_SCALE(float p0) { invoke<Void>(0x5F0F3F56635809EF, p0); }
	NATIVE_DECL void CASCADE_SHADOWS_SET_ENTITY_TRACKER_SCALE(float p0) { invoke<Void>(0x5E9DAF5A20F15908, p0); }
	NATIVE_DECL void CASCADE_SHADOWS_SET_SPLIT_Z_EXP_WEIGHT(float p0) { invoke<Void>(0x36F6626459D91457, p0); }
	NATIVE_DECL void CASCADE_SHADOWS_SET_BOUND_POSITION(Any p0) { invoke<Void>(0x259BA6D4E6F808F1, p0); }
	NATIVE_DECL void CASCADE_SHADOWS_ENABLE_ENTITY_TRACKER(BOOL toggle) { invoke<Void>(0x80ECBC0C856D3B0B, toggle); }
	NATIVE_DECL void CASCADE_SHADOWS_SET_SCREEN_SIZE_CHECK_ENABLED(BOOL p0) { invoke<Void>(0x25FC3E33A31AD0C9, p0); }
	NATIVE_DECL void CASCADE_SHADOWS_SET_SHADOW_SAMPLE_TYPE(const char* type) { invoke<Void>(0xB11D94BC55F41932, type); }
	NATIVE_DECL void CASCADE_SHADOWS_CLEAR_SHADOW_SAMPLE_TYPE() { invoke<Void>(0x27CB772218215325); }
	NATIVE_DECL void CASCADE_SHADOWS_SET_AIRCRAFT_MODE(BOOL p0) { invoke<Void>(0x6DDBF9DFFC4AC080, p0); }
	NATIVE_DECL void CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_MODE(BOOL p0) { invoke<Void>(0xD39D13C9FEBF0511, p0); }
	NATIVE_DECL void CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_VALUE(float p0) { invoke<Void>(0x02AC28F3A01FA04A, p0); }
	NATIVE_DECL void CASCADE_SHADOWS_ENABLE_FREEZER(BOOL p0) { invoke<Void>(0x0AE73D8DF3A762B2, p0); }
	NATIVE_DECL void WATER_REFLECTION_SET_SCRIPT_OBJECT_VISIBILITY(Any p0) { invoke<Void>(0xCA465D9CC0D231BA, p0); }
	NATIVE_DECL void GOLF_TRAIL_SET_ENABLED(BOOL toggle) { invoke<Void>(0xA51C4B86B71652AE, toggle); }
	NATIVE_DECL void GOLF_TRAIL_SET_PATH(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8) { invoke<Void>(0x312342E1A4874F3F, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL void GOLF_TRAIL_SET_RADIUS(float p0, float p1, float p2) { invoke<Void>(0x2485D34E50A22E84, p0, p1, p2); }
	NATIVE_DECL void GOLF_TRAIL_SET_COLOUR(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11) { invoke<Void>(0x12995F2E53FFA601, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	NATIVE_DECL void GOLF_TRAIL_SET_TESSELLATION(int p0, int p1) { invoke<Void>(0xDBAA5EC848BA2D46, p0, p1); }
	NATIVE_DECL void GOLF_TRAIL_SET_FIXED_CONTROL_POINT_ENABLE(BOOL p0) { invoke<Void>(0xC0416B061F2B7E5E, p0); }
	NATIVE_DECL void GOLF_TRAIL_SET_FIXED_CONTROL_POINT(int type, float xPos, float yPos, float zPos, float p4, int red, int green, int blue, int alpha) { invoke<Void>(0xB1BB03742917A5D6, type, xPos, yPos, zPos, p4, red, green, blue, alpha); }
	NATIVE_DECL void GOLF_TRAIL_SET_SHADER_PARAMS(float p0, float p1, float p2, float p3, float p4) { invoke<Void>(0x9CFDD90B2B844BF7, p0, p1, p2, p3, p4); }
	NATIVE_DECL void GOLF_TRAIL_SET_FACING(BOOL p0) { invoke<Void>(0x06F761EA47C1D3ED, p0); }
	NATIVE_DECL float GOLF_TRAIL_GET_MAX_HEIGHT() { return invoke<float>(0xA4819F5E23E2FFAD); }
	NATIVE_DECL Vector3 GOLF_TRAIL_GET_VISUAL_CONTROL_POINT(int p0) { return invoke<Vector3>(0xA4664972A9B8F8BA, p0); }
	NATIVE_DECL void SET_SEETHROUGH(BOOL toggle) { invoke<Void>(0x7E08924259E08CE0, toggle); }
	NATIVE_DECL BOOL GET_USINGSEETHROUGH() { return invoke<BOOL>(0x44B80ABAB9D80BD3); }
	NATIVE_DECL void SEETHROUGH_RESET() { invoke<Void>(0x70A64C0234EF522C); }
	NATIVE_DECL void SEETHROUGH_SET_FADE_STARTDISTANCE(float distance) { invoke<Void>(0xA78DE25577300BA1, distance); }
	NATIVE_DECL void SEETHROUGH_SET_FADE_ENDDISTANCE(float distance) { invoke<Void>(0x9D75795B9DC6EBBF, distance); }
	NATIVE_DECL float SEETHROUGH_GET_MAX_THICKNESS() { return invoke<float>(0x43DBAE39626CE83F); }
	NATIVE_DECL void SEETHROUGH_SET_MAX_THICKNESS(float thickness) { invoke<Void>(0x0C8FAC83902A62DF, thickness); }
	NATIVE_DECL void SEETHROUGH_SET_NOISE_MIN(float amount) { invoke<Void>(0xFF5992E1C9E65D05, amount); }
	NATIVE_DECL void SEETHROUGH_SET_NOISE_MAX(float amount) { invoke<Void>(0xFEBFBFDFB66039DE, amount); }
	NATIVE_DECL void SEETHROUGH_SET_HILIGHT_INTENSITY(float intensity) { invoke<Void>(0x19E50EB6E33E1D28, intensity); }
	NATIVE_DECL void SEETHROUGH_SET_HIGHLIGHT_NOISE(float noise) { invoke<Void>(0x1636D7FC127B10D2, noise); }
	NATIVE_DECL void SEETHROUGH_SET_HEATSCALE(int index, float heatScale) { invoke<Void>(0xD7D0B00177485411, index, heatScale); }
	NATIVE_DECL void SEETHROUGH_SET_COLOR_NEAR(int red, int green, int blue) { invoke<Void>(0x1086127B3A63505E, red, green, blue); }
	NATIVE_DECL void SET_MOTIONBLUR_MAX_VEL_SCALER(float p0) { invoke<Void>(0xB3C641F3630BF6DA, p0); }
	NATIVE_DECL float GET_MOTIONBLUR_MAX_VEL_SCALER() { return invoke<float>(0xE59343E9E96529E7); }
	NATIVE_DECL void SET_FORCE_MOTIONBLUR(BOOL toggle) { invoke<Void>(0x6A51F78772175A51, toggle); }
	NATIVE_DECL void TOGGLE_PLAYER_DAMAGE_OVERLAY(BOOL toggle) { invoke<Void>(0xE63D7C6EECECB66B, toggle); }
	NATIVE_DECL void RESET_ADAPTATION(int p0) { invoke<Void>(0xE3E2C1B4C59DBC77, p0); }
	NATIVE_DECL BOOL TRIGGER_SCREENBLUR_FADE_IN(float transitionTime) { return invoke<BOOL>(0xA328A24AAA6B7FDC, transitionTime); }
	NATIVE_DECL BOOL TRIGGER_SCREENBLUR_FADE_OUT(float transitionTime) { return invoke<BOOL>(0xEFACC8AEF94430D5, transitionTime); }
	NATIVE_DECL void DISABLE_SCREENBLUR_FADE() { invoke<Void>(0xDE81239437E8C5A8); }
	NATIVE_DECL float GET_SCREENBLUR_FADE_CURRENT_TIME() { return invoke<float>(0x5CCABFFCA31DDE33); }
	NATIVE_DECL BOOL IS_SCREENBLUR_FADE_RUNNING() { return invoke<BOOL>(0x7B226C785A52A0A9); }
	NATIVE_DECL void TOGGLE_PAUSED_RENDERPHASES(BOOL toggle) { invoke<Void>(0xDFC252D8A3E15AB7, toggle); }
	NATIVE_DECL BOOL GET_TOGGLE_PAUSED_RENDERPHASES_STATUS() { return invoke<BOOL>(0xEB3DAC2C86001E5E); }
	NATIVE_DECL void RESET_PAUSED_RENDERPHASES() { invoke<Void>(0xE1C8709406F2C41C); }
	NATIVE_DECL void GRAB_PAUSEMENU_OWNERSHIP() { invoke<Void>(0x851CD923176EBA7C); }
	NATIVE_DECL void SET_HIDOF_OVERRIDE(BOOL p0, BOOL p1, float nearplaneOut, float nearplaneIn, float farplaneOut, float farplaneIn) { invoke<Void>(0xBA3D65906822BED5, p0, p1, nearplaneOut, nearplaneIn, farplaneOut, farplaneIn); }
	NATIVE_DECL void SET_LOCK_ADAPTIVE_DOF_DISTANCE(BOOL p0) { invoke<Void>(0xB569F41F3E7E83A4, p0); }
	NATIVE_DECL BOOL PHONEPHOTOEDITOR_TOGGLE(BOOL p0) { return invoke<BOOL>(0x7AC24EAB6D74118D, p0); }
	NATIVE_DECL BOOL PHONEPHOTOEDITOR_IS_ACTIVE() { return invoke<BOOL>(0xBCEDB009461DA156); }
	NATIVE_DECL BOOL PHONEPHOTOEDITOR_SET_FRAME_TXD(const char* textureDict, BOOL p1) { return invoke<BOOL>(0x27FEB5254759CDE3, textureDict, p1); }
	NATIVE_DECL BOOL START_PARTICLE_FX_NON_LOOPED_AT_COORD(const char* effectName, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale, BOOL xAxis, BOOL yAxis, BOOL zAxis) { return invoke<BOOL>(0x25129531F77B9ED3, effectName, xPos, yPos, zPos, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis); }
	NATIVE_DECL BOOL START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(const char* effectName, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale, BOOL xAxis, BOOL yAxis, BOOL zAxis, BOOL p11) { return invoke<BOOL>(0xF56B8137DF10135D, effectName, xPos, yPos, zPos, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, p11); }
	NATIVE_DECL BOOL START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, BOOL axisX, BOOL axisY, BOOL axisZ) { return invoke<BOOL>(0x0E7E72961BA18619, effectName, ped, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ); }
	NATIVE_DECL BOOL START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, BOOL axisX, BOOL axisY, BOOL axisZ) { return invoke<BOOL>(0xA41B6A43642AC2CF, effectName, ped, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ); }
	NATIVE_DECL BOOL START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scale, BOOL axisX, BOOL axisY, BOOL axisZ) { return invoke<BOOL>(0x0D53A3B8DA0809D2, effectName, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, scale, axisX, axisY, axisZ); }
	NATIVE_DECL BOOL START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scale, BOOL axisX, BOOL axisY, BOOL axisZ) { return invoke<BOOL>(0xC95EB1DB6E92113D, effectName, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, scale, axisX, axisY, axisZ); }
	NATIVE_DECL BOOL START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, BOOL axisX, BOOL axisY, BOOL axisZ) { return invoke<BOOL>(0x02B1F2A72E0F5325, effectName, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ); }
	NATIVE_DECL void SET_PARTICLE_FX_NON_LOOPED_COLOUR(float r, float g, float b) { invoke<Void>(0x26143A59EF48B262, r, g, b); }
	NATIVE_DECL void SET_PARTICLE_FX_NON_LOOPED_ALPHA(float alpha) { invoke<Void>(0x77168D722C58B2FC, alpha); }
	NATIVE_DECL void SET_PARTICLE_FX_NON_LOOPED_SCALE(float scale) { invoke<Void>(0xB7EF5850C39FABCA, scale); }
	NATIVE_DECL void SET_PARTICLE_FX_NON_LOOPED_EMITTER_SIZE(float p0, float p1, float scale) { invoke<Void>(0x1E2E01C00837D26E, p0, p1, scale); }
	NATIVE_DECL void SET_PARTICLE_FX_FORCE_VEHICLE_INTERIOR(BOOL toggle) { invoke<Void>(0x8CDE909A0370BB3A, toggle); }
	NATIVE_DECL int START_PARTICLE_FX_LOOPED_AT_COORD(const char* effectName, float x, float y, float z, float xRot, float yRot, float zRot, float scale, BOOL xAxis, BOOL yAxis, BOOL zAxis, BOOL p11) { return invoke<int>(0xE184F4F0DC5910E7, effectName, x, y, z, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, p11); }
	NATIVE_DECL int START_PARTICLE_FX_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, BOOL xAxis, BOOL yAxis, BOOL zAxis) { return invoke<int>(0xF28DA9F38CD1787C, effectName, ped, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis); }
	NATIVE_DECL int START_PARTICLE_FX_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, BOOL xAxis, BOOL yAxis, BOOL zAxis) { return invoke<int>(0x1AE42C1660FD6517, effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis); }
	NATIVE_DECL int START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, BOOL xAxis, BOOL yAxis, BOOL zAxis) { return invoke<int>(0xC6EB449E33977F0B, effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis); }
	NATIVE_DECL int START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, BOOL xAxis, BOOL yAxis, BOOL zAxis, float r, float g, float b, float a) { return invoke<int>(0x6F60E89A7B64EE1D, effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, r, g, b, a); }
	NATIVE_DECL int START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, BOOL xAxis, BOOL yAxis, BOOL zAxis, float r, float g, float b, float a) { return invoke<int>(0xDDE23F30CC5A0F03, effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis, r, g, b, a); }
	NATIVE_DECL void STOP_PARTICLE_FX_LOOPED(int ptfxHandle, BOOL p1) { invoke<Void>(0x8F75998877616996, ptfxHandle, p1); }
	NATIVE_DECL void REMOVE_PARTICLE_FX(int ptfxHandle, BOOL p1) { invoke<Void>(0xC401503DFE8D53CF, ptfxHandle, p1); }
	NATIVE_DECL void REMOVE_PARTICLE_FX_FROM_ENTITY(Entity entity) { invoke<Void>(0xB8FEAEEBCC127425, entity); }
	NATIVE_DECL void REMOVE_PARTICLE_FX_IN_RANGE(float X, float Y, float Z, float radius) { invoke<Void>(0xDD19FA1C6D657305, X, Y, Z, radius); }
	NATIVE_DECL void FORCE_PARTICLE_FX_IN_VEHICLE_INTERIOR(Any p0, Any p1) { invoke<Void>(0xBA0127DA25FD54C9, p0, p1); }
	NATIVE_DECL BOOL DOES_PARTICLE_FX_LOOPED_EXIST(int ptfxHandle) { return invoke<BOOL>(0x74AFEF0D2E1E409B, ptfxHandle); }
	NATIVE_DECL void SET_PARTICLE_FX_LOOPED_OFFSETS(int ptfxHandle, float x, float y, float z, float rotX, float rotY, float rotZ) { invoke<Void>(0xF7DDEBEC43483C43, ptfxHandle, x, y, z, rotX, rotY, rotZ); }
	NATIVE_DECL void SET_PARTICLE_FX_LOOPED_EVOLUTION(int ptfxHandle, const char* propertyName, float amount, BOOL noNetwork) { invoke<Void>(0x5F0C4B5B1C393BE2, ptfxHandle, propertyName, amount, noNetwork); }
	NATIVE_DECL void SET_PARTICLE_FX_LOOPED_COLOUR(int ptfxHandle, float r, float g, float b, BOOL p4) { invoke<Void>(0x7F8F65877F88783B, ptfxHandle, r, g, b, p4); }
	NATIVE_DECL void SET_PARTICLE_FX_LOOPED_ALPHA(int ptfxHandle, float alpha) { invoke<Void>(0x726845132380142E, ptfxHandle, alpha); }
	NATIVE_DECL void SET_PARTICLE_FX_LOOPED_SCALE(int ptfxHandle, float scale) { invoke<Void>(0xB44250AAA456492D, ptfxHandle, scale); }
	NATIVE_DECL void SET_PARTICLE_FX_LOOPED_FAR_CLIP_DIST(int ptfxHandle, float range) { invoke<Void>(0xDCB194B85EF7B541, ptfxHandle, range); }
	NATIVE_DECL void _SET_PARTICLE_FX_LOOPED_CAMERA_BIAS(int ptfxHandle, float p1) { invoke<Void>(0x4100BF0346A8D2C3, ptfxHandle, p1); }
	NATIVE_DECL void SET_PARTICLE_FX_CAM_INSIDE_VEHICLE(BOOL p0) { invoke<Void>(0xEEC4047028426510, p0); }
	NATIVE_DECL void SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE(Vehicle vehicle, BOOL p1) { invoke<Void>(0xACEE6F360FC1F6B6, vehicle, p1); }
	NATIVE_DECL void SET_PARTICLE_FX_SHOOTOUT_BOAT(Any p0) { invoke<Void>(0x96EF97DAEB89BEF5, p0); }
	NATIVE_DECL void CLEAR_PARTICLE_FX_SHOOTOUT_BOAT() { invoke<Void>(0x2A251AA48B2B46DB); }
	NATIVE_DECL void SET_PARTICLE_FX_BLOOD_SCALE(Any p0) { invoke<Void>(0x908311265D42A820, p0); }
	NATIVE_DECL void DISABLE_IN_WATER_PTFX(BOOL toggle) { invoke<Void>(0xCFD16F0DB5A3535C, toggle); }
	NATIVE_DECL void DISABLE_DOWNWASH_PTFX(BOOL toggle) { invoke<Void>(0x5F6DF3D92271E8A1, toggle); }
	NATIVE_DECL void SET_PARTICLE_FX_SLIPSTREAM_LODRANGE_SCALE(float scale) { invoke<Void>(0x2B40A97646381508, scale); }
	NATIVE_DECL void ENABLE_CLOWN_BLOOD_VFX(BOOL toggle) { invoke<Void>(0xD821490579791273, toggle); }
	NATIVE_DECL void ENABLE_ALIEN_BLOOD_VFX(BOOL toggle) { invoke<Void>(0x9DCE1F0F78260875, toggle); }
	NATIVE_DECL void SET_PARTICLE_FX_BULLET_IMPACT_SCALE(float scale) { invoke<Void>(0x27E32866E9A5C416, scale); }
	NATIVE_DECL void SET_PARTICLE_FX_BULLET_IMPACT_LODRANGE_SCALE(float p0) { invoke<Void>(0xBB90E12CAC1DAB25, p0); }
	NATIVE_DECL void SET_PARTICLE_FX_BULLET_TRACE_NO_ANGLE_REJECT(BOOL p0) { invoke<Void>(0xCA4AE345A153D573, p0); }
	NATIVE_DECL void SET_PARTICLE_FX_BANG_SCRAPE_LODRANGE_SCALE(float p0) { invoke<Void>(0x54E22EA2C1956A8D, p0); }
	NATIVE_DECL void SET_PARTICLE_FX_FOOT_LODRANGE_SCALE(float p0) { invoke<Void>(0x949F397A288B28B3, p0); }
	NATIVE_DECL void SET_PARTICLE_FX_FOOT_OVERRIDE_NAME(const char* p0) { invoke<Void>(0xBA3D194057C79A7B, p0); }
	NATIVE_DECL void SET_SKIDMARK_RANGE_SCALE(float scale) { invoke<Void>(0x5DBF05DB5926D089, scale); }
	NATIVE_DECL void SET_PTFX_FORCE_VEHICLE_INTERIOR_FLAG(Any p0) { invoke<Void>(0xC6730E0D14E50703, p0); }
	NATIVE_DECL void REGISTER_POSTFX_BULLET_IMPACT(float weaponWorldPosX, float weaponWorldPosY, float weaponWorldPosZ, float intensity) { invoke<Void>(0x170911F37F646F29, weaponWorldPosX, weaponWorldPosY, weaponWorldPosZ, intensity); }
	NATIVE_DECL void FORCE_POSTFX_BULLET_IMPACTS_AFTER_HUD(BOOL p0) { invoke<Void>(0x9B079E5221D984D3, p0); }
	NATIVE_DECL void USE_PARTICLE_FX_ASSET(const char* name) { invoke<Void>(0x6C38AF3693A69A91, name); }
	NATIVE_DECL void SET_PARTICLE_FX_OVERRIDE(const char* oldAsset, const char* newAsset) { invoke<Void>(0xEA1E2D93F6F75ED9, oldAsset, newAsset); }
	NATIVE_DECL void RESET_PARTICLE_FX_OVERRIDE(const char* name) { invoke<Void>(0x89C8553DD3274AAE, name); }
	NATIVE_DECL int _START_VEHICLE_PARTICLE_FX_LOOPED(Vehicle vehicle, const char* effectName, BOOL frontBack, BOOL leftRight, BOOL localOnly) { return invoke<int>(0xDF269BE2909E181A, vehicle, effectName, frontBack, leftRight, localOnly); }
	NATIVE_DECL void SET_WEATHER_PTFX_USE_OVERRIDE_SETTINGS(BOOL p0) { invoke<Void>(0xA46B73FAA3460AE1, p0); }
	NATIVE_DECL void SET_WEATHER_PTFX_OVERRIDE_CURR_LEVEL(float p0) { invoke<Void>(0xF78B803082D4386F, p0); }
	NATIVE_DECL void WASH_DECALS_IN_RANGE(float x, float y, float z, float range, float p4) { invoke<Void>(0x9C30613D50A6ADEF, x, y, z, range, p4); }
	NATIVE_DECL void WASH_DECALS_FROM_VEHICLE(Vehicle vehicle, float p1) { invoke<Void>(0x5B712761429DBC14, vehicle, p1); }
	NATIVE_DECL void FADE_DECALS_IN_RANGE(float x, float y, float z, float p3, float p4) { invoke<Void>(0xD77EDADB0420E6E0, x, y, z, p3, p4); }
	NATIVE_DECL void REMOVE_DECALS_IN_RANGE(float x, float y, float z, float range) { invoke<Void>(0x5D6B2D4830A67C62, x, y, z, range); }
	NATIVE_DECL void REMOVE_DECALS_FROM_OBJECT(Object obj) { invoke<Void>(0xCCF71CBDDF5B6CB9, obj); }
	NATIVE_DECL void REMOVE_DECALS_FROM_OBJECT_FACING(Object obj, float x, float y, float z) { invoke<Void>(0xA6F6F70FDC6D144C, obj, x, y, z); }
	NATIVE_DECL void REMOVE_DECALS_FROM_VEHICLE(Vehicle vehicle) { invoke<Void>(0xE91F1B65F2B48D57, vehicle); }
	NATIVE_DECL int ADD_DECAL(int decalType, float posX, float posY, float posZ, float p4, float p5, float p6, float p7, float p8, float p9, float width, float height, float rCoef, float gCoef, float bCoef, float opacity, float timeout, BOOL p17, BOOL p18, BOOL p19) { return invoke<int>(0xB302244A1839BDAD, decalType, posX, posY, posZ, p4, p5, p6, p7, p8, p9, width, height, rCoef, gCoef, bCoef, opacity, timeout, p17, p18, p19); }
	NATIVE_DECL int ADD_PETROL_DECAL(float x, float y, float z, float groundLvl, float width, float transparency) { return invoke<int>(0x4F5212C7AD880DF8, x, y, z, groundLvl, width, transparency); }
	NATIVE_DECL int ADD_OIL_DECAL(float x, float y, float z, float groundLvl, float width, float transparency) { return invoke<int>(0x126D7F89FE859A5E, x, y, z, groundLvl, width, transparency); }
	NATIVE_DECL void START_PETROL_TRAIL_DECALS(float p0) { invoke<Void>(0x99AC7F0D8B9C893D, p0); }
	NATIVE_DECL void ADD_PETROL_TRAIL_DECAL_INFO(float x, float y, float z, float p3) { invoke<Void>(0x967278682CB6967A, x, y, z, p3); }
	NATIVE_DECL void END_PETROL_TRAIL_DECALS() { invoke<Void>(0x0A123435A26C36CD); }
	NATIVE_DECL void REMOVE_DECAL(int decal) { invoke<Void>(0xED3F346429CCD659, decal); }
	NATIVE_DECL BOOL IS_DECAL_ALIVE(int decal) { return invoke<BOOL>(0xC694D74949CAFD0C, decal); }
	NATIVE_DECL float GET_DECAL_WASH_LEVEL(int decal) { return invoke<float>(0x323F647679A09103, decal); }
	NATIVE_DECL void SET_DISABLE_PETROL_DECALS_IGNITING_THIS_FRAME() { invoke<Void>(0xD9454B5752C857DC); }
	NATIVE_DECL void SET_DISABLE_PETROL_DECALS_RECYCLING_THIS_FRAME() { invoke<Void>(0x27CFB1B1E078CB2D); }
	NATIVE_DECL void SET_DISABLE_DECAL_RENDERING_THIS_FRAME() { invoke<Void>(0x4B5CFC83122DF602); }
	NATIVE_DECL BOOL GET_IS_PETROL_DECAL_IN_RANGE(float xCoord, float yCoord, float zCoord, float radius) { return invoke<BOOL>(0x2F09F7976C512404, xCoord, yCoord, zCoord, radius); }
	NATIVE_DECL void PATCH_DECAL_DIFFUSE_MAP(int decalType, const char* textureDict, const char* textureName) { invoke<Void>(0x8A35C742130C6080, decalType, textureDict, textureName); }
	NATIVE_DECL void UNPATCH_DECAL_DIFFUSE_MAP(int decalType) { invoke<Void>(0xB7ED70C49521A61D, decalType); }
	NATIVE_DECL void MOVE_VEHICLE_DECALS(Any p0, Any p1) { invoke<Void>(0x84C8D7C2D30D3280, p0, p1); }
	NATIVE_DECL BOOL ADD_VEHICLE_CREW_EMBLEM(Vehicle vehicle, Ped ped, int boneIndex, float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3, float scale, Any p13, int alpha) { return invoke<BOOL>(0x428BDCB9DA58DA53, vehicle, ped, boneIndex, x1, x2, x3, y1, y2, y3, z1, z2, z3, scale, p13, alpha); }
	NATIVE_DECL BOOL ABORT_VEHICLE_CREW_EMBLEM_REQUEST(int* p0) { return invoke<BOOL>(0x82ACC484FFA3B05F, p0); }
	NATIVE_DECL void REMOVE_VEHICLE_CREW_EMBLEM(Vehicle vehicle, int p1) { invoke<Void>(0xD2300034310557E4, vehicle, p1); }
	NATIVE_DECL int GET_VEHICLE_CREW_EMBLEM_REQUEST_STATE(Vehicle vehicle, int p1) { return invoke<int>(0xFE26117A5841B2FF, vehicle, p1); }
	NATIVE_DECL BOOL DOES_VEHICLE_HAVE_CREW_EMBLEM(Vehicle vehicle, int p1) { return invoke<BOOL>(0x060D935D3981A275, vehicle, p1); }
	NATIVE_DECL void DISABLE_COMPOSITE_SHOTGUN_DECALS(BOOL toggle) { invoke<Void>(0x0E4299C549F0D1F1, toggle); }
	NATIVE_DECL void DISABLE_SCUFF_DECALS(BOOL toggle) { invoke<Void>(0x02369D5C8A51FDCF, toggle); }
	NATIVE_DECL void SET_DECAL_BULLET_IMPACT_RANGE_SCALE(float p0) { invoke<Void>(0x46D1A61A21F566FC, p0); }
	NATIVE_DECL void OVERRIDE_INTERIOR_SMOKE_NAME(const char* name) { invoke<Void>(0x2A2A52824DB96700, name); }
	NATIVE_DECL void OVERRIDE_INTERIOR_SMOKE_LEVEL(float level) { invoke<Void>(0x1600FD8CF72EBC12, level); }
	NATIVE_DECL void OVERRIDE_INTERIOR_SMOKE_END() { invoke<Void>(0xEFB55E7C25D3B3BE); }
	NATIVE_DECL void REGISTER_NOIR_LENS_EFFECT() { invoke<Void>(0xA44FF770DFBC5DAE); }
	NATIVE_DECL void DISABLE_VEHICLE_DISTANTLIGHTS(BOOL toggle) { invoke<Void>(0xC9F98AC1884E73A2, toggle); }
	NATIVE_DECL void RENDER_SHADOWED_LIGHTS_WITH_NO_SHADOWS(BOOL p0) { invoke<Void>(0x03300B57FCAC6DDB, p0); }
	NATIVE_DECL void REQUEST_EARLY_LIGHT_CHECK() { invoke<Void>(0x98EDF76A7271E4F2); }
	NATIVE_DECL void USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(BOOL toggle) { invoke<Void>(0xAEEDAD1420C65CC0, toggle); }
	NATIVE_DECL void _FORCE_ALLOW_SNOW_FOOT_VFX_ON_ICE(BOOL toggle) { invoke<Void>(0xA342A3763B3AFB6C, toggle); }
	NATIVE_DECL void USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(BOOL toggle) { invoke<Void>(0x4CC7F0FEA5283FE0, toggle); }
	NATIVE_DECL void DISABLE_REGION_VFX(Any p0) { invoke<Void>(0xEFD97FF47B745B8D, p0); }
	NATIVE_DECL void _FORCE_GROUND_SNOW_PASS(BOOL toggle) { invoke<Void>(0x6E9EF3A33C8899F8, toggle); }
	NATIVE_DECL void PRESET_INTERIOR_AMBIENT_CACHE(const char* timecycleModifierName) { invoke<Void>(0xD7021272EB0A451E, timecycleModifierName); }
	NATIVE_DECL void SET_TIMECYCLE_MODIFIER(const char* modifierName) { invoke<Void>(0x2C933ABF17A1DF41, modifierName); }
	NATIVE_DECL void SET_TIMECYCLE_MODIFIER_STRENGTH(float strength) { invoke<Void>(0x82E7FFCD5B2326B3, strength); }
	NATIVE_DECL void SET_TRANSITION_TIMECYCLE_MODIFIER(const char* modifierName, float transition) { invoke<Void>(0x3BCF567485E1971C, modifierName, transition); }
	NATIVE_DECL void SET_TRANSITION_OUT_OF_TIMECYCLE_MODIFIER(float strength) { invoke<Void>(0x1CBA05AE7BD7EE05, strength); }
	NATIVE_DECL void CLEAR_TIMECYCLE_MODIFIER() { invoke<Void>(0x0F07E7745A236711); }
	NATIVE_DECL int GET_TIMECYCLE_MODIFIER_INDEX() { return invoke<int>(0xFDF3D97C674AFB66); }
	NATIVE_DECL int GET_TIMECYCLE_TRANSITION_MODIFIER_INDEX() { return invoke<int>(0x459FD2C8D0AB78BC); }
	NATIVE_DECL BOOL GET_IS_TIMECYCLE_TRANSITIONING_OUT() { return invoke<BOOL>(0x98D18905BF723B99); }
	NATIVE_DECL void PUSH_TIMECYCLE_MODIFIER() { invoke<Void>(0x58F735290861E6B4); }
	NATIVE_DECL void POP_TIMECYCLE_MODIFIER() { invoke<Void>(0x3C8938D7D872211E); }
	NATIVE_DECL void SET_CURRENT_PLAYER_TCMODIFIER(const char* modifierName) { invoke<Void>(0xBBF327DED94E4DEB, modifierName); }
	NATIVE_DECL void SET_PLAYER_TCMODIFIER_TRANSITION(float value) { invoke<Void>(0xBDEB86F4D5809204, value); }
	NATIVE_DECL void SET_NEXT_PLAYER_TCMODIFIER(const char* modifierName) { invoke<Void>(0xBF59707B3E5ED531, modifierName); }
	NATIVE_DECL void ADD_TCMODIFIER_OVERRIDE(const char* modifierName1, const char* modifierName2) { invoke<Void>(0x1A8E2C8B9CF4549C, modifierName1, modifierName2); }
	NATIVE_DECL void CLEAR_ALL_TCMODIFIER_OVERRIDES(const char* p0) { invoke<Void>(0x15E33297C3E8DC60, p0); }
	NATIVE_DECL void SET_EXTRA_TCMODIFIER(const char* modifierName) { invoke<Void>(0x5096FD9CCB49056D, modifierName); }
	NATIVE_DECL void CLEAR_EXTRA_TCMODIFIER() { invoke<Void>(0x92CCC17A7A2285DA); }
	NATIVE_DECL int GET_EXTRA_TCMODIFIER() { return invoke<int>(0xBB0527EC6341496D); }
	NATIVE_DECL void ENABLE_MOON_CYCLE_OVERRIDE(float strength) { invoke<Void>(0x2C328AF17210F009, strength); }
	NATIVE_DECL void DISABLE_MOON_CYCLE_OVERRIDE() { invoke<Void>(0x2BF72AD5B41AA739); }
	NATIVE_DECL int REQUEST_SCALEFORM_MOVIE(const char* scaleformName) { return invoke<int>(0x11FE353CF9733E6F, scaleformName); }
	NATIVE_DECL int REQUEST_SCALEFORM_MOVIE_WITH_IGNORE_SUPER_WIDESCREEN(const char* scaleformName) { return invoke<int>(0x65E7E78842E74CDB, scaleformName); }
	NATIVE_DECL int REQUEST_SCALEFORM_MOVIE_INSTANCE(const char* scaleformName) { return invoke<int>(0xC514489CFB8AF806, scaleformName); }
	NATIVE_DECL int REQUEST_SCALEFORM_MOVIE_SKIP_RENDER_WHILE_PAUSED(const char* scaleformName) { return invoke<int>(0xBD06C611BB9048C2, scaleformName); }
	NATIVE_DECL BOOL HAS_SCALEFORM_MOVIE_LOADED(int scaleformHandle) { return invoke<BOOL>(0x85F01B8D5B90570E, scaleformHandle); }
	NATIVE_DECL BOOL _HAS_SCALEFORM_MOVIE_NAMED_LOADED(int* scaleformHandle, const char* scaleformName) { return invoke<BOOL>(0x9743BCCF7CD6E1F6, scaleformHandle, scaleformName); }
	NATIVE_DECL BOOL IS_ACTIVE_SCALEFORM_MOVIE_DELETING(int scaleformHandle) { return invoke<BOOL>(0x2FCB133CA50A49EB, scaleformHandle); }
	NATIVE_DECL BOOL IS_SCALEFORM_MOVIE_DELETING(int scaleformHandle) { return invoke<BOOL>(0x86255B1FC929E33E, scaleformHandle); }
	NATIVE_DECL BOOL HAS_SCALEFORM_MOVIE_FILENAME_LOADED(const char* scaleformName) { return invoke<BOOL>(0x0C1C5D756FB5F337, scaleformName); }
	NATIVE_DECL BOOL HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT(int scaleformHandle) { return invoke<BOOL>(0x8217150E1217EBFD, scaleformHandle); }
	NATIVE_DECL void SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(int* scaleformHandle) { invoke<Void>(0x1D132D614DD86811, scaleformHandle); }
	NATIVE_DECL void _SET_SCALEFORM_MOVIE_NAMED_AS_NO_LONGER_NEEDED(int scaleformHandle, const char* scaleformName) { invoke<Void>(0x2FDFB1B04C76E9C3, scaleformHandle, scaleformName); }
	NATIVE_DECL void SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME(int scaleform, BOOL toggle) { invoke<Void>(0x6D8EB211944DCE08, scaleform, toggle); }
	NATIVE_DECL void SET_SCALEFORM_MOVIE_TO_USE_LARGE_RT(int scaleformHandle, BOOL toggle) { invoke<Void>(0x32F34FF7F617643B, scaleformHandle, toggle); }
	NATIVE_DECL void SET_SCALEFORM_MOVIE_TO_USE_SUPER_LARGE_RT(int scaleformHandle, BOOL toggle) { invoke<Void>(0xE6A9F00D4240B519, scaleformHandle, toggle); }
	NATIVE_DECL void DRAW_SCALEFORM_MOVIE(int scaleformHandle, float x, float y, float width, float height, int red, int green, int blue, int alpha, int p9) { invoke<Void>(0x54972ADAF0294A93, scaleformHandle, x, y, width, height, red, green, blue, alpha, p9); }
	NATIVE_DECL void DRAW_SCALEFORM_MOVIE_FULLSCREEN(int scaleform, int red, int green, int blue, int alpha, int p5) { invoke<Void>(0x0DF606929C105BE1, scaleform, red, green, blue, alpha, p5); }
	NATIVE_DECL void DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED(int scaleform1, int scaleform2, int red, int green, int blue, int alpha) { invoke<Void>(0xCF537FDE4FBD4CE5, scaleform1, scaleform2, red, green, blue, alpha); }
	NATIVE_DECL void DRAW_SCALEFORM_MOVIE_3D(int scaleform, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float p7, float p8, float p9, float scaleX, float scaleY, float scaleZ, int rotationOrder) { invoke<Void>(0x87D51D72255D4E78, scaleform, posX, posY, posZ, rotX, rotY, rotZ, p7, p8, p9, scaleX, scaleY, scaleZ, rotationOrder); }
	NATIVE_DECL void DRAW_SCALEFORM_MOVIE_3D_SOLID(int scaleform, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float p7, float p8, float p9, float scaleX, float scaleY, float scaleZ, int rotationOrder) { invoke<Void>(0x1CE592FDC749D6F5, scaleform, posX, posY, posZ, rotX, rotY, rotZ, p7, p8, p9, scaleX, scaleY, scaleZ, rotationOrder); }
	NATIVE_DECL void CALL_SCALEFORM_MOVIE_METHOD(int scaleform, const char* method) { invoke<Void>(0xFBD96D87AC96D533, scaleform, method); }
	NATIVE_DECL void CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER(int scaleform, const char* methodName, float param1, float param2, float param3, float param4, float param5) { invoke<Void>(0xD0837058AE2E4BEE, scaleform, methodName, param1, param2, param3, param4, param5); }
	NATIVE_DECL void CALL_SCALEFORM_MOVIE_METHOD_WITH_STRING(int scaleform, const char* methodName, const char* param1, const char* param2, const char* param3, const char* param4, const char* param5) { invoke<Void>(0x51BC1ED3CC44E8F7, scaleform, methodName, param1, param2, param3, param4, param5); }
	NATIVE_DECL void CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER_AND_STRING(int scaleform, const char* methodName, float floatParam1, float floatParam2, float floatParam3, float floatParam4, float floatParam5, const char* stringParam1, const char* stringParam2, const char* stringParam3, const char* stringParam4, const char* stringParam5) { invoke<Void>(0xEF662D8D57E290B1, scaleform, methodName, floatParam1, floatParam2, floatParam3, floatParam4, floatParam5, stringParam1, stringParam2, stringParam3, stringParam4, stringParam5); }
	NATIVE_DECL BOOL BEGIN_SCALEFORM_SCRIPT_HUD_MOVIE_METHOD(int hudComponent, const char* methodName) { return invoke<BOOL>(0x98C494FD5BDFBFD5, hudComponent, methodName); }
	NATIVE_DECL BOOL BEGIN_SCALEFORM_MOVIE_METHOD(int scaleform, const char* methodName) { return invoke<BOOL>(0xF6E48914C7A8694E, scaleform, methodName); }
	NATIVE_DECL BOOL BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND(const char* methodName) { return invoke<BOOL>(0xAB58C27C2E6123C6, methodName); }
	NATIVE_DECL BOOL BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER(const char* methodName) { return invoke<BOOL>(0xB9449845F73F5E9C, methodName); }
	NATIVE_DECL void END_SCALEFORM_MOVIE_METHOD() { invoke<Void>(0xC6796A8FFA375E53); }
	NATIVE_DECL int END_SCALEFORM_MOVIE_METHOD_RETURN_VALUE() { return invoke<int>(0xC50AA39A577AF886); }
	NATIVE_DECL BOOL IS_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_READY(int methodReturn) { return invoke<BOOL>(0x768FF8961BA904D6, methodReturn); }
	NATIVE_DECL int GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT(int methodReturn) { return invoke<int>(0x2DE7EFA66B906036, methodReturn); }
	NATIVE_DECL BOOL GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL(int methodReturn) { return invoke<BOOL>(0xD80A80346A45D761, methodReturn); }
	NATIVE_DECL const char* GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING(int methodReturn) { return invoke<const char*>(0xE1E258829A885245, methodReturn); }
	NATIVE_DECL void SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(int value) { invoke<Void>(0xC3D0841A0CC546A6, value); }
	NATIVE_DECL void SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(float value) { invoke<Void>(0xD69736AAE04DB51A, value); }
	NATIVE_DECL void SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(BOOL value) { invoke<Void>(0xC58424BA936EB458, value); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_SCALEFORM_STRING(const char* componentType) { invoke<Void>(0x80338406F3475E55, componentType); }
	NATIVE_DECL void END_TEXT_COMMAND_SCALEFORM_STRING() { invoke<Void>(0x362E2D3FE93A9959); }
	NATIVE_DECL void END_TEXT_COMMAND_UNPARSED_SCALEFORM_STRING() { invoke<Void>(0xAE4E8157D9ECF087); }
	NATIVE_DECL void SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(const char* string) { invoke<Void>(0x77FE3402004CD1B0, string); }
	NATIVE_DECL void SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(const char* string) { invoke<Void>(0xBA7148484BD90365, string); }
	NATIVE_DECL void SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(const char* string) { invoke<Void>(0xE83A3E3557A56640, string); }
	NATIVE_DECL BOOL DOES_LATEST_BRIEF_STRING_EXIST(int p0) { return invoke<BOOL>(0x5E657EF1099EDD65, p0); }
	NATIVE_DECL void SCALEFORM_MOVIE_METHOD_ADD_PARAM_LATEST_BRIEF_STRING(int value) { invoke<Void>(0xEC52C631A1831C03, value); }
	NATIVE_DECL void REQUEST_SCALEFORM_SCRIPT_HUD_MOVIE(int hudComponent) { invoke<Void>(0x9304881D6F6537EA, hudComponent); }
	NATIVE_DECL BOOL HAS_SCALEFORM_SCRIPT_HUD_MOVIE_LOADED(int hudComponent) { return invoke<BOOL>(0xDF6E5987D2B4D140, hudComponent); }
	NATIVE_DECL void REMOVE_SCALEFORM_SCRIPT_HUD_MOVIE(int hudComponent) { invoke<Void>(0xF44A5456AC3F4F97, hudComponent); }
	NATIVE_DECL BOOL PASS_KEYBOARD_INPUT_TO_SCALEFORM(int scaleformHandle) { return invoke<BOOL>(0xD1C7CB175E012964, scaleformHandle); }
	NATIVE_DECL void SET_TV_CHANNEL(int channel) { invoke<Void>(0xBAABBB23EB6E484E, channel); }
	NATIVE_DECL int GET_TV_CHANNEL() { return invoke<int>(0xFC1E275A90D39995); }
	NATIVE_DECL void SET_TV_VOLUME(float volume) { invoke<Void>(0x2982BF73F66E9DDC, volume); }
	NATIVE_DECL float GET_TV_VOLUME() { return invoke<float>(0x2170813D3DD8661B); }
	NATIVE_DECL void DRAW_TV_CHANNEL(float xPos, float yPos, float xScale, float yScale, float rotation, int red, int green, int blue, int alpha) { invoke<Void>(0xFDDC2B4ED3C69DF0, xPos, yPos, xScale, yScale, rotation, red, green, blue, alpha); }
	NATIVE_DECL void SET_TV_CHANNEL_PLAYLIST(int tvChannel, const char* playlistName, BOOL restart) { invoke<Void>(0xF7B38B8305F1FE8B, tvChannel, playlistName, restart); }
	NATIVE_DECL void SET_TV_CHANNEL_PLAYLIST_AT_HOUR(int tvChannel, const char* playlistName, int hour) { invoke<Void>(0x2201C576FACAEBE8, tvChannel, playlistName, hour); }
	NATIVE_DECL Any _SET_TV_CHANNEL_PLAYLIST_DIRTY(int tvChannel, BOOL p1) { return invoke<Any>(0xEE831F15A8D0D94A, tvChannel, p1); }
	NATIVE_DECL void CLEAR_TV_CHANNEL_PLAYLIST(int tvChannel) { invoke<Void>(0xBEB3D46BB7F043C0, tvChannel); }
	NATIVE_DECL BOOL IS_PLAYLIST_ON_CHANNEL(int tvChannel, Any p1) { return invoke<BOOL>(0x1F710BFF7DAE6261, tvChannel, p1); }
	NATIVE_DECL BOOL IS_TVSHOW_CURRENTLY_PLAYING(Hash videoCliphash) { return invoke<BOOL>(0x0AD973CA1E077B60, videoCliphash); }
	NATIVE_DECL void ENABLE_MOVIE_KEYFRAME_WAIT(BOOL toggle) { invoke<Void>(0x74C180030FDE4B69, toggle); }
	NATIVE_DECL void SET_TV_PLAYER_WATCHING_THIS_FRAME(Any p0) { invoke<Void>(0xD1C55B110E4DF534, p0); }
	NATIVE_DECL Hash GET_CURRENT_TV_CLIP_NAMEHASH() { return invoke<Hash>(0x30432A0118736E00); }
	NATIVE_DECL void ENABLE_MOVIE_SUBTITLES(BOOL toggle) { invoke<Void>(0x873FA65C778AD970, toggle); }
	NATIVE_DECL BOOL UI3DSCENE_IS_AVAILABLE() { return invoke<BOOL>(0xD3A10FC7FD8D98CD); }
	NATIVE_DECL BOOL UI3DSCENE_PUSH_PRESET(const char* presetName) { return invoke<BOOL>(0xF1CEA8A4198D8E9A, presetName); }
	NATIVE_DECL BOOL UI3DSCENE_ASSIGN_PED_TO_SLOT(const char* presetName, Ped ped, int slot, float posX, float posY, float posZ) { return invoke<BOOL>(0x98C4FE6EC34154CA, presetName, ped, slot, posX, posY, posZ); }
	NATIVE_DECL void UI3DSCENE_CLEAR_PATCHED_DATA() { invoke<Void>(0x7A42B2E236E71415); }
	NATIVE_DECL void UI3DSCENE_MAKE_PUSHED_PRESET_PERSISTENT(BOOL toggle) { invoke<Void>(0x108BE26959A9D9BB, toggle); }
	NATIVE_DECL void TERRAINGRID_ACTIVATE(BOOL toggle) { invoke<Void>(0xA356990E161C9E65, toggle); }
	NATIVE_DECL void TERRAINGRID_SET_PARAMS(float x, float y, float z, float forwardX, float forwardY, float forwardZ, float sizeX, float sizeY, float sizeZ, float gridScale, float glowIntensity, float normalHeight, float heightDiff) { invoke<Void>(0x1C4FC5752BCD8E48, x, y, z, forwardX, forwardY, forwardZ, sizeX, sizeY, sizeZ, gridScale, glowIntensity, normalHeight, heightDiff); }
	NATIVE_DECL void TERRAINGRID_SET_COLOURS(int lowR, int lowG, int lowB, int lowAlpha, int r, int g, int b, int alpha, int highR, int highG, int highB, int highAlpha) { invoke<Void>(0x5CE62918F8D703C7, lowR, lowG, lowB, lowAlpha, r, g, b, alpha, highR, highG, highB, highAlpha); }
	NATIVE_DECL void ANIMPOSTFX_PLAY(const char* effectName, int duration, BOOL looped) { invoke<Void>(0x2206BF9A37B7F724, effectName, duration, looped); }
	NATIVE_DECL void ANIMPOSTFX_STOP(const char* effectName) { invoke<Void>(0x068E835A1D0DC0E3, effectName); }
	NATIVE_DECL float ANIMPOSTFX_GET_CURRENT_TIME(const char* effectName) { return invoke<float>(0xE35B38A27E8E7179, effectName); }
	NATIVE_DECL BOOL ANIMPOSTFX_IS_RUNNING(const char* effectName) { return invoke<BOOL>(0x36AD3E690DA5ACEB, effectName); }
	NATIVE_DECL void ANIMPOSTFX_STOP_ALL() { invoke<Void>(0xB4EDDC19532BFB85); }
	NATIVE_DECL void ANIMPOSTFX_STOP_AND_FLUSH_REQUESTS(const char* effectName) { invoke<Void>(0xD2209BE128B5418C, effectName); }
}

namespace GTA
{
	NATIVE_DECL void CREATE_MOBILE_PHONE(int phoneType) { invoke<Void>(0xA4E8E696C532FBC7, phoneType); }
	NATIVE_DECL void DESTROY_MOBILE_PHONE() { invoke<Void>(0x3BC861DF703E5097); }
	NATIVE_DECL void SET_MOBILE_PHONE_SCALE(float scale) { invoke<Void>(0xCBDD322A73D6D932, scale); }
	NATIVE_DECL void SET_MOBILE_PHONE_ROTATION(float rotX, float rotY, float rotZ, Any p3) { invoke<Void>(0xBB779C0CA917E865, rotX, rotY, rotZ, p3); }
	NATIVE_DECL void GET_MOBILE_PHONE_ROTATION(Vector3* rotation, Vehicle p1) { invoke<Void>(0x1CEFB61F193070AE, rotation, p1); }
	NATIVE_DECL void SET_MOBILE_PHONE_POSITION(float posX, float posY, float posZ) { invoke<Void>(0x693A5C6D6734085B, posX, posY, posZ); }
	NATIVE_DECL void GET_MOBILE_PHONE_POSITION(Vector3* position) { invoke<Void>(0x584FDFDA48805B86, position); }
	NATIVE_DECL void SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN(BOOL toggle) { invoke<Void>(0xF511F759238A5122, toggle); }
	NATIVE_DECL BOOL CAN_PHONE_BE_SEEN_ON_SCREEN() { return invoke<BOOL>(0xC4E2813898C97A4B); }
	NATIVE_DECL void SET_MOBILE_PHONE_DOF_STATE(BOOL toggle) { invoke<Void>(0x375A706A5C2FD084, toggle); }
	NATIVE_DECL void CELL_SET_INPUT(int direction) { invoke<Void>(0x95C9E72F3D7DEC9B, direction); }
	NATIVE_DECL void CELL_HORIZONTAL_MODE_TOGGLE(BOOL toggle) { invoke<Void>(0x44E44169EF70138E, toggle); }
	NATIVE_DECL void CELL_CAM_ACTIVATE(BOOL p0, BOOL p1) { invoke<Void>(0xFDE8F069C542D126, p0, p1); }
	NATIVE_DECL void CELL_CAM_ACTIVATE_SELFIE_MODE(BOOL toggle) { invoke<Void>(0x015C49A93E3E086E, toggle); }
	NATIVE_DECL void CELL_CAM_ACTIVATE_SHALLOW_DOF_MODE(BOOL toggle) { invoke<Void>(0xA2CCBE62CD4C91A4, toggle); }
	NATIVE_DECL void CELL_CAM_SET_SELFIE_MODE_SIDE_OFFSET_SCALING(float p0) { invoke<Void>(0x1B0B4AEED5B9B41C, p0); }
	NATIVE_DECL void CELL_CAM_SET_SELFIE_MODE_HORZ_PAN_OFFSET(float horizontalPan) { invoke<Void>(0x53F4892D18EC90A4, horizontalPan); }
	NATIVE_DECL void CELL_CAM_SET_SELFIE_MODE_VERT_PAN_OFFSET(float vertPan) { invoke<Void>(0x3117D84EFA60F77B, vertPan); }
	NATIVE_DECL void CELL_CAM_SET_SELFIE_MODE_ROLL_OFFSET(float roll) { invoke<Void>(0x15E69E2802C24B8D, roll); }
	NATIVE_DECL void CELL_CAM_SET_SELFIE_MODE_DISTANCE_SCALING(float distanceScaling) { invoke<Void>(0xAC2890471901861C, distanceScaling); }
	NATIVE_DECL void CELL_CAM_SET_SELFIE_MODE_HEAD_YAW_OFFSET(float yaw) { invoke<Void>(0xD6ADE981781FCA09, yaw); }
	NATIVE_DECL void CELL_CAM_SET_SELFIE_MODE_HEAD_ROLL_OFFSET(float roll) { invoke<Void>(0xF1E22DC13F5EEBAD, roll); }
	NATIVE_DECL void CELL_CAM_SET_SELFIE_MODE_HEAD_PITCH_OFFSET(float pitch) { invoke<Void>(0x466DA42C89865553, pitch); }
	NATIVE_DECL BOOL CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK(Entity entity) { return invoke<BOOL>(0x439E9BC95B7E7FBE, entity); }
	NATIVE_DECL void GET_MOBILE_PHONE_RENDER_ID(int* renderId) { invoke<Void>(0xB4A53E05F68B6FA1, renderId); }
}

namespace HUD
{
	NATIVE_DECL void BEGIN_TEXT_COMMAND_BUSYSPINNER_ON(const char* string) { invoke<Void>(0xABA17D7CE615ADBF, string); }
	NATIVE_DECL void END_TEXT_COMMAND_BUSYSPINNER_ON(int busySpinnerType) { invoke<Void>(0xBD12F8228410D9B4, busySpinnerType); }
	NATIVE_DECL void BUSYSPINNER_OFF() { invoke<Void>(0x10D373323E5B9C0D); }
	NATIVE_DECL void PRELOAD_BUSYSPINNER() { invoke<Void>(0xC65AB383CD91DF98); }
	NATIVE_DECL BOOL BUSYSPINNER_IS_ON() { return invoke<BOOL>(0xD422FCC5F239A915); }
	NATIVE_DECL BOOL BUSYSPINNER_IS_DISPLAYING() { return invoke<BOOL>(0xB2A592B04648A9CB); }
	NATIVE_DECL void DISABLE_PAUSEMENU_SPINNER(BOOL p0) { invoke<Void>(0x9245E81072704B8A, p0); }
	NATIVE_DECL void SET_MOUSE_CURSOR_THIS_FRAME() { invoke<Void>(0xAAE7CE1D63167423); }
	NATIVE_DECL void SET_MOUSE_CURSOR_STYLE(int spriteId) { invoke<Void>(0x8DB8CFFD58B62552, spriteId); }
	NATIVE_DECL void SET_MOUSE_CURSOR_VISIBLE(BOOL toggle) { invoke<Void>(0x98215325A695E78A, toggle); }
	NATIVE_DECL BOOL IS_MOUSE_ROLLED_OVER_INSTRUCTIONAL_BUTTONS() { return invoke<BOOL>(0x3D9ACB1EB139E702); }
	NATIVE_DECL BOOL GET_MOUSE_EVENT(int scaleformHandle, Any* p1, Any* p2, Any* p3) { return invoke<BOOL>(0x632B2940C67F4EA9, scaleformHandle, p1, p2, p3); }
	NATIVE_DECL void THEFEED_ONLY_SHOW_TOOLTIPS(BOOL toggle) { invoke<Void>(0x6F1554B0CC2089FA, toggle); }
	NATIVE_DECL void THEFEED_SET_SCRIPTED_MENU_HEIGHT(float pos) { invoke<Void>(0x55598D21339CB998, pos); }
	NATIVE_DECL void THEFEED_HIDE() { invoke<Void>(0x32888337579A5970); }
	NATIVE_DECL void THEFEED_HIDE_THIS_FRAME() { invoke<Void>(0x25F87B30C382FCA7); }
	NATIVE_DECL void THEFEED_SHOW() { invoke<Void>(0x15CFA549788D35EF); }
	NATIVE_DECL void THEFEED_FLUSH_QUEUE() { invoke<Void>(0xA8FDB297A8D25FBA); }
	NATIVE_DECL void THEFEED_REMOVE_ITEM(int notificationId) { invoke<Void>(0xBE4390CB40B3E627, notificationId); }
	NATIVE_DECL void THEFEED_FORCE_RENDER_ON() { invoke<Void>(0xA13C11E1B5C06BFC); }
	NATIVE_DECL void THEFEED_FORCE_RENDER_OFF() { invoke<Void>(0x583049884A2EEE3C); }
	NATIVE_DECL void THEFEED_PAUSE() { invoke<Void>(0xFDB423997FA30340); }
	NATIVE_DECL void THEFEED_RESUME() { invoke<Void>(0xE1CD1E48E025E661); }
	NATIVE_DECL BOOL THEFEED_IS_PAUSED() { return invoke<BOOL>(0xA9CBFD40B3FA3010); }
	NATIVE_DECL void THEFEED_REPORT_LOGO_ON() { invoke<Void>(0xD4438C0564490E63); }
	NATIVE_DECL void THEFEED_REPORT_LOGO_OFF() { invoke<Void>(0xB695E2CD0A2DA9EE); }
	NATIVE_DECL int THEFEED_GET_LAST_SHOWN_PHONE_ACTIVATABLE_FEED_ID() { return invoke<int>(0x82352748437638CA); }
	NATIVE_DECL void THEFEED_AUTO_POST_GAMETIPS_ON() { invoke<Void>(0x56C8B608CFD49854); }
	NATIVE_DECL void THEFEED_AUTO_POST_GAMETIPS_OFF() { invoke<Void>(0xADED7F5748ACAFE6); }
	NATIVE_DECL void THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(int hudColorIndex) { invoke<Void>(0x92F0DA1E27DB96DC, hudColorIndex); }
	NATIVE_DECL void THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE(int red, int green, int blue, int alpha) { invoke<Void>(0x17430B918701C342, red, green, blue, alpha); }
	NATIVE_DECL void THEFEED_SET_FLASH_DURATION_PARAMETER_FOR_NEXT_MESSAGE(int count) { invoke<Void>(0x17AD8C9706BDD88A, count); }
	NATIVE_DECL void THEFEED_SET_VIBRATE_PARAMETER_FOR_NEXT_MESSAGE(BOOL toggle) { invoke<Void>(0x4A0C7C9BB10ABB36, toggle); }
	NATIVE_DECL void THEFEED_RESET_ALL_PARAMETERS() { invoke<Void>(0xFDD85225B2DEA55E); }
	NATIVE_DECL void THEFEED_FREEZE_NEXT_POST() { invoke<Void>(0xFDEC055AB549E328); }
	NATIVE_DECL void THEFEED_CLEAR_FROZEN_POST() { invoke<Void>(0x80FE4F3AB4E1B62A); }
	NATIVE_DECL void THEFEED_SET_SNAP_FEED_ITEM_POSITIONS(BOOL p0) { invoke<Void>(0xBAE4F9B97CD43B30, p0); }
	NATIVE_DECL void THEFEED_UPDATE_ITEM_TEXTURE(const char* txdString1, const char* txnString1, const char* txdString2, const char* txnString2) { invoke<Void>(0x317EBA71D7543F52, txdString1, txnString1, txdString2, txnString2); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_THEFEED_POST(const char* text) { invoke<Void>(0x202709F4C58A0424, text); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_STATS(const char* statTitle, int iconEnum, BOOL stepVal, int barValue, BOOL isImportant, const char* pictureTextureDict, const char* pictureTextureName) { return invoke<int>(0x2B7E9A4EAAA93C89, statTitle, iconEnum, stepVal, barValue, isImportant, pictureTextureDict, pictureTextureName); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT(const char* txdName, const char* textureName, BOOL flash, int iconType, const char* sender, const char* subject) { return invoke<int>(0x1CCD9A37359072CF, txdName, textureName, flash, iconType, sender, subject); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_SUBTITLE_LABEL(const char* txdName, const char* textureName, BOOL flash, int iconType, const char* sender, const char* subject) { return invoke<int>(0xC6F580E4C94926AC, txdName, textureName, flash, iconType, sender, subject); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_TU(const char* txdName, const char* textureName, BOOL flash, int iconType, const char* sender, const char* subject, float duration) { return invoke<int>(0x1E6611149DB3DB6B, txdName, textureName, flash, iconType, sender, subject, duration); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG(const char* txdName, const char* textureName, BOOL flash, int iconType, const char* sender, const char* subject, float duration, const char* clanTag) { return invoke<int>(0x5CBF7BADE20DB93E, txdName, textureName, flash, iconType, sender, subject, duration, clanTag); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON(const char* txdName, const char* textureName, BOOL flash, int iconType1, const char* sender, const char* subject, float duration, const char* clanTag, int iconType2, int p9) { return invoke<int>(0x531B84E7DA981FB6, txdName, textureName, flash, iconType1, sender, subject, duration, clanTag, iconType2, p9); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_TICKER(BOOL blink, BOOL p1) { return invoke<int>(0x2ED7843F8F801023, blink, p1); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_TICKER_FORCED(BOOL blink, BOOL p1) { return invoke<int>(0x44FA03975424A0EE, blink, p1); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_TICKER_WITH_TOKENS(BOOL blink, BOOL p1) { return invoke<int>(0x378E809BF61EC840, blink, p1); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_AWARD(const char* textureDict, const char* textureName, int rpBonus, int colorOverlay, const char* titleLabel) { return invoke<int>(0xAA295B6F28BD587D, textureDict, textureName, rpBonus, colorOverlay, titleLabel); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_CREWTAG(BOOL p0, BOOL p1, int* p2, int p3, BOOL isLeader, BOOL unk0, int clanDesc, int R, int G, int B) { return invoke<int>(0x97C9E4E7024A8F2C, p0, p1, p2, p3, isLeader, unk0, clanDesc, R, G, B); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_CREWTAG_WITH_GAME_NAME(BOOL p0, BOOL p1, int* p2, int p3, BOOL isLeader, BOOL unk0, int clanDesc, const char* playerName, int R, int G, int B) { return invoke<int>(0x137BC35589E34E1E, p0, p1, p2, p3, isLeader, unk0, clanDesc, playerName, R, G, B); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_UNLOCK(const char* gxtLabel1, int p1, const char* gxtLabel2) { return invoke<int>(0x33EE12743CCD6343, gxtLabel1, p1, gxtLabel2); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU(const char* gxtLabel1, int p1, const char* gxtLabel2, int p3) { return invoke<int>(0xC8F3AAF93D0600BF, gxtLabel1, p1, gxtLabel2, p3); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU_WITH_COLOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x7AE0589093A2E088, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_MPTICKER(BOOL blink, BOOL p1) { return invoke<int>(0xF020C96915705B3A, blink, p1); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_CREW_RANKUP_WITH_LITERAL_FLAG(const char* p0, const char* p1, const char* p2, BOOL p3, BOOL p4) { return invoke<int>(0x8EFCCF6EC66D85E4, p0, p1, p2, p3, p4); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_VERSUS_TU(const char* txdName1, const char* textureName1, int count1, const char* txdName2, const char* textureName2, int count2, int hudColor1, int hudColor2) { return invoke<int>(0xB6871B0555B02996, txdName1, textureName1, count1, txdName2, textureName2, count2, hudColor1, hudColor2); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_REPLAY(int type, int image, const char* text) { return invoke<int>(0xD202B92CBF1D816F, type, image, text); }
	NATIVE_DECL int END_TEXT_COMMAND_THEFEED_POST_REPLAY_INPUT(int type, const char* button, const char* text) { return invoke<int>(0xDD6CB2CCE7C2735C, type, button, text); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_PRINT(const char* GxtEntry) { invoke<Void>(0xB87A37EEB7FAA67D, GxtEntry); }
	NATIVE_DECL void END_TEXT_COMMAND_PRINT(int duration, BOOL drawImmediately) { invoke<Void>(0x9D77056A530643F6, duration, drawImmediately); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED(const char* text) { invoke<Void>(0x853648FD1063A213, text); }
	NATIVE_DECL BOOL END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED() { return invoke<BOOL>(0x8A9BA1AB3E237613); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_DISPLAY_TEXT(const char* text) { invoke<Void>(0x25FBB336DF1804CB, text); }
	NATIVE_DECL void END_TEXT_COMMAND_DISPLAY_TEXT(float x, float y, int p2) { invoke<Void>(0xCD015E5BB0D96A57, x, y, p2); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(const char* text) { invoke<Void>(0x54CE8AC98E120CAB, text); }
	NATIVE_DECL float END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(BOOL p0) { return invoke<float>(0x85F061DA64ED2F67, p0); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(const char* entry) { invoke<Void>(0x521FB041D93DD0E4, entry); }
	NATIVE_DECL int END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(float x, float y) { return invoke<int>(0x9040DFB09BE75706, x, y); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_DISPLAY_HELP(const char* inputType) { invoke<Void>(0x8509B634FBE7DA11, inputType); }
	NATIVE_DECL void END_TEXT_COMMAND_DISPLAY_HELP(int p0, BOOL loop, BOOL beep, int shape) { invoke<Void>(0x238FFE5C7B0498A6, p0, loop, beep, shape); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(const char* labelName) { invoke<Void>(0x0A24DA3A41B718F5, labelName); }
	NATIVE_DECL BOOL END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(int p0) { return invoke<BOOL>(0x10BDDBFC529428DD, p0); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_SET_BLIP_NAME(const char* textLabel) { invoke<Void>(0xF9113A30DE5C6670, textLabel); }
	NATIVE_DECL void END_TEXT_COMMAND_SET_BLIP_NAME(Blip blip) { invoke<Void>(0xBC38B49BCB83BC9B, blip); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS(const char* p0) { invoke<Void>(0x23D69E0465570028, p0); }
	NATIVE_DECL void END_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS(BOOL p0) { invoke<Void>(0xCFDBDF5AE59BA0F4, p0); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_CLEAR_PRINT(const char* text) { invoke<Void>(0xE124FA80A759019C, text); }
	NATIVE_DECL void END_TEXT_COMMAND_CLEAR_PRINT() { invoke<Void>(0xFCC75460ABA29378); }
	NATIVE_DECL void BEGIN_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT(const char* gxtEntry) { invoke<Void>(0x8F9EE5687F8EECCD, gxtEntry); }
	NATIVE_DECL void END_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT(int p0) { invoke<Void>(0xA86911979638106F, p0); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_INTEGER(int value) { invoke<Void>(0x03B504CF259931BC, value); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_FLOAT(float value, int decimalPlaces) { invoke<Void>(0xE7DCB5B874BCD96E, value, decimalPlaces); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL(const char* labelName) { invoke<Void>(0xC63CD5D2920ACBE7, labelName); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY(Hash gxtEntryHash) { invoke<Void>(0x17299B63C7683A2B, gxtEntryHash); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME(Blip blip) { invoke<Void>(0x80EAD8E2E1D5D52E, blip); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const char* text) { invoke<Void>(0x6C188BE134E074AA, text); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_SUBSTRING_TIME(int timestamp, int flags) { invoke<Void>(0x1115F16B8AB9E8BF, timestamp, flags); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_FORMATTED_INTEGER(int value, BOOL commaSeparated) { invoke<Void>(0x0E4C749FF9DE9CC4, value, commaSeparated); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_SUBSTRING_PHONE_NUMBER(const char* p0, int p1) { invoke<Void>(0x761B77454205A61D, p0, p1); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(const char* website) { invoke<Void>(0x94CF4AC034C9C986, website); }
	NATIVE_DECL void ADD_TEXT_COMPONENT_SUBSTRING_KEYBOARD_DISPLAY(const char* string) { invoke<Void>(0x5F68520888E69014, string); }
	NATIVE_DECL void SET_COLOUR_OF_NEXT_TEXT_COMPONENT(int hudColor) { invoke<Void>(0x39BBF623FC803EAC, hudColor); }
	NATIVE_DECL const char* GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME(const char* text, int position, int length) { return invoke<const char*>(0x169BD9382084C8C0, text, position, length); }
	NATIVE_DECL const char* GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_WITH_BYTE_LIMIT(const char* text, int position, int length, int maxLength) { return invoke<const char*>(0xB2798643312205C5, text, position, length, maxLength); }
	NATIVE_DECL const char* GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_BYTES(const char* text, int startPosition, int endPosition) { return invoke<const char*>(0xCE94AEBA5D82908A, text, startPosition, endPosition); }
	NATIVE_DECL const char* GET_FILENAME_FOR_AUDIO_CONVERSATION(const char* labelName) { return invoke<const char*>(0x7B5280EBA9840C72, labelName); }
	NATIVE_DECL void CLEAR_PRINTS() { invoke<Void>(0xCC33FA791322B9D9); }
	NATIVE_DECL void CLEAR_BRIEF() { invoke<Void>(0x9D292F73ADBD9313); }
	NATIVE_DECL void CLEAR_ALL_HELP_MESSAGES() { invoke<Void>(0x6178F68A87A4D3A0); }
	NATIVE_DECL void CLEAR_THIS_PRINT(const char* p0) { invoke<Void>(0xCF708001E1E536DD, p0); }
	NATIVE_DECL void CLEAR_SMALL_PRINTS() { invoke<Void>(0x2CEA2839313C09AC); }
	NATIVE_DECL BOOL DOES_TEXT_BLOCK_EXIST(const char* gxt) { return invoke<BOOL>(0x1C7302E725259789, gxt); }
	NATIVE_DECL void REQUEST_ADDITIONAL_TEXT(const char* gxt, int slot) { invoke<Void>(0x71A78003C8E71424, gxt, slot); }
	NATIVE_DECL void REQUEST_ADDITIONAL_TEXT_FOR_DLC(const char* gxt, int slot) { invoke<Void>(0x6009F9F1AE90D8A6, gxt, slot); }
	NATIVE_DECL BOOL HAS_ADDITIONAL_TEXT_LOADED(int slot) { return invoke<BOOL>(0x02245FE4BED318B8, slot); }
	NATIVE_DECL void CLEAR_ADDITIONAL_TEXT(int p0, BOOL p1) { invoke<Void>(0x2A179DF17CCF04CD, p0, p1); }
	NATIVE_DECL BOOL IS_STREAMING_ADDITIONAL_TEXT(int p0) { return invoke<BOOL>(0x8B6817B71B85EBF0, p0); }
	NATIVE_DECL BOOL HAS_THIS_ADDITIONAL_TEXT_LOADED(const char* gxt, int slot) { return invoke<BOOL>(0xADBF060E2B30C5BC, gxt, slot); }
	NATIVE_DECL BOOL IS_MESSAGE_BEING_DISPLAYED() { return invoke<BOOL>(0x7984C03AA5CC2F41); }
	NATIVE_DECL BOOL DOES_TEXT_LABEL_EXIST(const char* gxt) { return invoke<BOOL>(0xAC09CA973C564252, gxt); }
	NATIVE_DECL const char* GET_FIRST_N_CHARACTERS_OF_LITERAL_STRING(const char* string, int length) { return invoke<const char*>(0x98C3CF913D895111, string, length); }
	NATIVE_DECL int GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(const char* gxt) { return invoke<int>(0x801BD273D3A23F74, gxt); }
	NATIVE_DECL int GET_LENGTH_OF_LITERAL_STRING(const char* string) { return invoke<int>(0xF030907CCBB8A9FD, string); }
	NATIVE_DECL int GET_LENGTH_OF_LITERAL_STRING_IN_BYTES(const char* string) { return invoke<int>(0x43E4111189E54F0E, string); }
	NATIVE_DECL const char* GET_STREET_NAME_FROM_HASH_KEY(Hash hash) { return invoke<const char*>(0xD0EF8A959B8A4CB9, hash); }
	NATIVE_DECL BOOL IS_HUD_PREFERENCE_SWITCHED_ON() { return invoke<BOOL>(0x1930DFA731813EC4); }
	NATIVE_DECL BOOL IS_RADAR_PREFERENCE_SWITCHED_ON() { return invoke<BOOL>(0x9EB6522EA68F22FE); }
	NATIVE_DECL BOOL IS_SUBTITLE_PREFERENCE_SWITCHED_ON() { return invoke<BOOL>(0xAD6DACA4BA53E0A4); }
	NATIVE_DECL void DISPLAY_HUD(BOOL toggle) { invoke<Void>(0xA6294919E56FF02A, toggle); }
	NATIVE_DECL void DISPLAY_HUD_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME() { invoke<Void>(0x7669F9E39DC17063); }
	NATIVE_DECL void DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME() { invoke<Void>(0x402F9ED62087E898); }
	NATIVE_DECL void DISPLAY_RADAR(BOOL toggle) { invoke<Void>(0xA0EBB943C300E693, toggle); }
	NATIVE_DECL void SET_FAKE_SPECTATOR_MODE(BOOL toggle) { invoke<Void>(0xCD74233600C4EA6B, toggle); }
	NATIVE_DECL BOOL GET_FAKE_SPECTATOR_MODE() { return invoke<BOOL>(0xC2D2AD9EAAE265B8); }
	NATIVE_DECL BOOL IS_HUD_HIDDEN() { return invoke<BOOL>(0xA86478C6958735C5); }
	NATIVE_DECL BOOL IS_RADAR_HIDDEN() { return invoke<BOOL>(0x157F93B036700462); }
	NATIVE_DECL BOOL IS_MINIMAP_RENDERING() { return invoke<BOOL>(0xAF754F20EB5CD51A); }
	NATIVE_DECL void USE_VEHICLE_TARGETING_RETICULE(Any p0) { invoke<Void>(0x0C698D8F099174C7, p0); }
	NATIVE_DECL void _USE_VEHICLE_TARGETING_RETICULE_ON_VEHICLES(BOOL enable) { invoke<Void>(0x1BC0EA2912708625, enable); }
	NATIVE_DECL void ADD_VALID_VEHICLE_HIT_HASH(Any p0) { invoke<Void>(0xE4C3B169876D33D7, p0); }
	NATIVE_DECL void CLEAR_VALID_VEHICLE_HIT_HASHES() { invoke<Void>(0xEB81A3DADD503187); }
	NATIVE_DECL void SET_BLIP_ROUTE(Blip blip, BOOL enabled) { invoke<Void>(0x4F7D8A9BFB0B43E9, blip, enabled); }
	NATIVE_DECL void CLEAR_ALL_BLIP_ROUTES() { invoke<Void>(0xD12882D3FF82BF11); }
	NATIVE_DECL void SET_BLIP_ROUTE_COLOUR(Blip blip, int colour) { invoke<Void>(0x837155CD2F63DA09, blip, colour); }
	NATIVE_DECL void SET_FORCE_SHOW_GPS(BOOL toggle) { invoke<Void>(0x2790F4B17D098E26, toggle); }
	NATIVE_DECL void SET_USE_SET_DESTINATION_IN_PAUSE_MAP(BOOL toggle) { invoke<Void>(0x6CDD58146A436083, toggle); }
	NATIVE_DECL void SET_BLOCK_WANTED_FLASH(BOOL disabled) { invoke<Void>(0xD1942374085C8469, disabled); }
	NATIVE_DECL void ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(BOOL p0) { invoke<Void>(0x60296AF4BA14ABC5, p0); }
	NATIVE_DECL void FORCE_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS_LIST(int p0) { invoke<Void>(0x57D760D55F54E071, p0); }
	NATIVE_DECL void SET_RADAR_ZOOM_PRECISE(float zoom) { invoke<Void>(0xBD12C5EEE184C337, zoom); }
	NATIVE_DECL void SET_RADAR_ZOOM(int zoomLevel) { invoke<Void>(0x096EF57A0C999BBA, zoomLevel); }
	NATIVE_DECL void SET_RADAR_ZOOM_TO_BLIP(Blip blip, float zoom) { invoke<Void>(0xF98E4B3E56AFC7B1, blip, zoom); }
	NATIVE_DECL void SET_RADAR_ZOOM_TO_DISTANCE(float zoom) { invoke<Void>(0xCB7CC0D58405AD41, zoom); }
	NATIVE_DECL void UPDATE_RADAR_ZOOM_TO_BLIP() { invoke<Void>(0xD2049635DEB9C375); }
	NATIVE_DECL void GET_HUD_COLOUR(int hudColorIndex, int* r, int* g, int* b, int* a) { invoke<Void>(0x7C9C91AB74A0360F, hudColorIndex, r, g, b, a); }
	NATIVE_DECL void SET_SCRIPT_VARIABLE_HUD_COLOUR(int r, int g, int b, int a) { invoke<Void>(0xD68A5FF8A3A89874, r, g, b, a); }
	NATIVE_DECL void SET_SECOND_SCRIPT_VARIABLE_HUD_COLOUR(int r, int g, int b, int a) { invoke<Void>(0x16A304E6CB2BFAB9, r, g, b, a); }
	NATIVE_DECL void REPLACE_HUD_COLOUR(int hudColorIndex, int hudColorIndex2) { invoke<Void>(0x1CCC708F0F850613, hudColorIndex, hudColorIndex2); }
	NATIVE_DECL void REPLACE_HUD_COLOUR_WITH_RGBA(int hudColorIndex, int r, int g, int b, int a) { invoke<Void>(0xF314CF4F0211894E, hudColorIndex, r, g, b, a); }
	NATIVE_DECL void SET_ABILITY_BAR_VISIBILITY(BOOL visible) { invoke<Void>(0x1DFEDD15019315A9, visible); }
	NATIVE_DECL void SET_ALLOW_ABILITY_BAR(BOOL toggle) { invoke<Void>(0x889329C80FE5963C, toggle); }
	NATIVE_DECL void FLASH_ABILITY_BAR(int millisecondsToFlash) { invoke<Void>(0x02CFBA0C9E9275CE, millisecondsToFlash); }
	NATIVE_DECL void SET_ABILITY_BAR_VALUE(float p0, float p1) { invoke<Void>(0x9969599CCFF5D85E, p0, p1); }
	NATIVE_DECL void FLASH_WANTED_DISPLAY(BOOL p0) { invoke<Void>(0xA18AFB39081B6A1F, p0); }
	NATIVE_DECL void FORCE_OFF_WANTED_STAR_FLASH(BOOL toggle) { invoke<Void>(0xBA8D65C1C65702E5, toggle); }
	NATIVE_DECL void SET_CUSTOM_MP_HUD_COLOR(int hudColorId) { invoke<Void>(0x2ACCB195F3CCD9DE, hudColorId); }
	NATIVE_DECL float GET_RENDERED_TEXT_PADDING_SIZE() { return invoke<float>(0xD6FAD05D855AF80F); }
	NATIVE_DECL float GET_RENDERED_CHARACTER_HEIGHT(float size, int font) { return invoke<float>(0xDB88A37483346780, size, font); }
	NATIVE_DECL void SET_TEXT_SCALE(float scale, float size) { invoke<Void>(0x07C837F9A01C34C9, scale, size); }
	NATIVE_DECL void SET_TEXT_COLOUR(int red, int green, int blue, int alpha) { invoke<Void>(0xBE6B23FFA53FB442, red, green, blue, alpha); }
	NATIVE_DECL void SET_TEXT_CENTRE(BOOL align) { invoke<Void>(0xC02F4DBFB51D988B, align); }
	NATIVE_DECL void SET_TEXT_RIGHT_JUSTIFY(BOOL toggle) { invoke<Void>(0x6B3C4650BC8BEE47, toggle); }
	NATIVE_DECL void SET_TEXT_JUSTIFICATION(int justifyType) { invoke<Void>(0x4E096588B13FFECA, justifyType); }
	NATIVE_DECL void SET_TEXT_LINE_HEIGHT_MULT(float lineHeightMult) { invoke<Void>(0x9F4624F76E6953D1, lineHeightMult); }
	NATIVE_DECL void SET_TEXT_WRAP(float start, float end) { invoke<Void>(0x63145D9C883A1A70, start, end); }
	NATIVE_DECL void SET_TEXT_LEADING(int p0) { invoke<Void>(0xA50ABC31E3CDFAFF, p0); }
	NATIVE_DECL void SET_TEXT_PROPORTIONAL(BOOL p0) { invoke<Void>(0x038C1F517D7FDCF8, p0); }
	NATIVE_DECL void SET_TEXT_FONT(int fontType) { invoke<Void>(0x66E0276CC5F6B9DA, fontType); }
	NATIVE_DECL void SET_TEXT_DROP_SHADOW() { invoke<Void>(0x1CA3E9EAC9D93E5E); }
	NATIVE_DECL void SET_TEXT_DROPSHADOW(int distance, int r, int g, int b, int a) { invoke<Void>(0x465C84BC39F1C351, distance, r, g, b, a); }
	NATIVE_DECL void SET_TEXT_OUTLINE() { invoke<Void>(0x2513DFB0FB8400FE); }
	NATIVE_DECL void SET_TEXT_EDGE(int p0, int r, int g, int b, int a) { invoke<Void>(0x441603240D202FA6, p0, r, g, b, a); }
	NATIVE_DECL void SET_TEXT_RENDER_ID(int renderId) { invoke<Void>(0x5F15302936E07111, renderId); }
	NATIVE_DECL int GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID() { return invoke<int>(0x52F0982D7FD156B6); }
	NATIVE_DECL BOOL REGISTER_NAMED_RENDERTARGET(const char* name, BOOL p1) { return invoke<BOOL>(0x57D9C12635E25CE3, name, p1); }
	NATIVE_DECL BOOL IS_NAMED_RENDERTARGET_REGISTERED(const char* name) { return invoke<BOOL>(0x78DCDC15C9F116B4, name); }
	NATIVE_DECL BOOL RELEASE_NAMED_RENDERTARGET(const char* name) { return invoke<BOOL>(0xE9F6FFE837354DD4, name); }
	NATIVE_DECL void LINK_NAMED_RENDERTARGET(Hash modelHash) { invoke<Void>(0xF6C09E276AEB3F2D, modelHash); }
	NATIVE_DECL int GET_NAMED_RENDERTARGET_RENDER_ID(const char* name) { return invoke<int>(0x1A6478B61C6BDC3B, name); }
	NATIVE_DECL BOOL IS_NAMED_RENDERTARGET_LINKED(Hash modelHash) { return invoke<BOOL>(0x113750538FA31298, modelHash); }
	NATIVE_DECL void CLEAR_HELP(BOOL toggle) { invoke<Void>(0x8DFCED7A656F8802, toggle); }
	NATIVE_DECL BOOL IS_HELP_MESSAGE_ON_SCREEN() { return invoke<BOOL>(0xDAD37F45428801AE); }
	NATIVE_DECL BOOL HAS_SCRIPT_HIDDEN_HELP_THIS_FRAME() { return invoke<BOOL>(0x214CD562A939246A); }
	NATIVE_DECL BOOL IS_HELP_MESSAGE_BEING_DISPLAYED() { return invoke<BOOL>(0x4D79439A6B55AC67); }
	NATIVE_DECL BOOL IS_HELP_MESSAGE_FADING_OUT() { return invoke<BOOL>(0x327EDEEEAC55C369); }
	NATIVE_DECL void SET_HELP_MESSAGE_STYLE(int style, int hudColor, int alpha, int p3, int p4) { invoke<Void>(0xB9C362BABECDDC7A, style, hudColor, alpha, p3, p4); }
	NATIVE_DECL int GET_STANDARD_BLIP_ENUM_ID() { return invoke<int>(0x4A9923385BDB9DAD); }
	NATIVE_DECL int GET_WAYPOINT_BLIP_ENUM_ID() { return invoke<int>(0x186E5D252FA50E7D); }
	NATIVE_DECL int GET_NUMBER_OF_ACTIVE_BLIPS() { return invoke<int>(0x9A3FF3DE163034E8); }
	NATIVE_DECL Blip GET_NEXT_BLIP_INFO_ID(int blipSprite) { return invoke<Blip>(0x14F96AA50D6FBEA7, blipSprite); }
	NATIVE_DECL Blip GET_FIRST_BLIP_INFO_ID(int blipSprite) { return invoke<Blip>(0x1BEDE233E6CD2A1F, blipSprite); }
	NATIVE_DECL Blip GET_CLOSEST_BLIP_INFO_ID(int blipSprite) { return invoke<Blip>(0xD484BF71050CA1EE, blipSprite); }
	NATIVE_DECL Vector3 GET_BLIP_INFO_ID_COORD(Blip blip) { return invoke<Vector3>(0xFA7C7F0AADF25D09, blip); }
	NATIVE_DECL int GET_BLIP_INFO_ID_DISPLAY(Blip blip) { return invoke<int>(0x1E314167F701DC3B, blip); }
	NATIVE_DECL int GET_BLIP_INFO_ID_TYPE(Blip blip) { return invoke<int>(0xBE9B0959FFD0779B, blip); }
	NATIVE_DECL Entity GET_BLIP_INFO_ID_ENTITY_INDEX(Blip blip) { return invoke<Entity>(0x4BA4E2553AFEDC2C, blip); }
	NATIVE_DECL Pickup GET_BLIP_INFO_ID_PICKUP_INDEX(Blip blip) { return invoke<Pickup>(0x9B6786E4C03DD382, blip); }
	NATIVE_DECL Blip GET_BLIP_FROM_ENTITY(Entity entity) { return invoke<Blip>(0xBC8DBDCA2436F7E8, entity); }
	NATIVE_DECL Blip ADD_BLIP_FOR_RADIUS(float posX, float posY, float posZ, float radius) { return invoke<Blip>(0x46818D79B1F7499A, posX, posY, posZ, radius); }
	NATIVE_DECL Blip ADD_BLIP_FOR_AREA(float x, float y, float z, float width, float height) { return invoke<Blip>(0xCE5D0E5E315DB238, x, y, z, width, height); }
	NATIVE_DECL Blip ADD_BLIP_FOR_ENTITY(Entity entity) { return invoke<Blip>(0x5CDE92C702A8FCE7, entity); }
	NATIVE_DECL Blip ADD_BLIP_FOR_PICKUP(Pickup pickup) { return invoke<Blip>(0xBE339365C863BD36, pickup); }
	NATIVE_DECL Blip ADD_BLIP_FOR_COORD(float x, float y, float z) { return invoke<Blip>(0x5A039BB0BCA604B6, x, y, z); }
	NATIVE_DECL void TRIGGER_SONAR_BLIP(float posX, float posY, float posZ, float radius, int p4) { invoke<Void>(0x72DD432F3CDFC0EE, posX, posY, posZ, radius, p4); }
	NATIVE_DECL void ALLOW_SONAR_BLIPS(BOOL toggle) { invoke<Void>(0x60734CC207C9833C, toggle); }
	NATIVE_DECL void SET_BLIP_COORDS(Blip blip, float posX, float posY, float posZ) { invoke<Void>(0xAE2AF67E9D9AF65D, blip, posX, posY, posZ); }
	NATIVE_DECL Vector3 GET_BLIP_COORDS(Blip blip) { return invoke<Vector3>(0x586AFE3FF72D996E, blip); }
	NATIVE_DECL void SET_BLIP_SPRITE(Blip blip, int spriteId) { invoke<Void>(0xDF735600A4696DAF, blip, spriteId); }
	NATIVE_DECL int GET_BLIP_SPRITE(Blip blip) { return invoke<int>(0x1FC877464A04FC4F, blip); }
	NATIVE_DECL void SET_COP_BLIP_SPRITE(int p0, float p1) { invoke<Void>(0x9FCB3CBFB3EAD69A, p0, p1); }
	NATIVE_DECL void SET_COP_BLIP_SPRITE_AS_STANDARD() { invoke<Void>(0xB7B873520C84C118); }
	NATIVE_DECL void SET_BLIP_NAME_FROM_TEXT_FILE(Blip blip, const char* gxtEntry) { invoke<Void>(0xEAA0FFE120D92784, blip, gxtEntry); }
	NATIVE_DECL void SET_BLIP_NAME_TO_PLAYER_NAME(Blip blip, Player player) { invoke<Void>(0x127DE7B20C60A6A3, blip, player); }
	NATIVE_DECL void SET_BLIP_ALPHA(Blip blip, int alpha) { invoke<Void>(0x45FF974EEE1C8734, blip, alpha); }
	NATIVE_DECL int GET_BLIP_ALPHA(Blip blip) { return invoke<int>(0x970F608F0EE6C885, blip); }
	NATIVE_DECL void SET_BLIP_FADE(Blip blip, int opacity, int duration) { invoke<Void>(0x2AEE8F8390D2298C, blip, opacity, duration); }
	NATIVE_DECL int GET_BLIP_FADE_DIRECTION(Blip blip) { return invoke<int>(0x2C173AE2BDB9385E, blip); }
	NATIVE_DECL void SET_BLIP_ROTATION(Blip blip, int rotation) { invoke<Void>(0xF87683CDF73C3F6E, blip, rotation); }
	NATIVE_DECL void SET_BLIP_ROTATION_WITH_FLOAT(Blip blip, float heading) { invoke<Void>(0xA8B6AFDAC320AC87, blip, heading); }
	NATIVE_DECL int GET_BLIP_ROTATION(Blip blip) { return invoke<int>(0x003E92BA477F9D7F, blip); }
	NATIVE_DECL void SET_BLIP_FLASH_TIMER(Blip blip, int duration) { invoke<Void>(0xD3CD6FD297AE87CC, blip, duration); }
	NATIVE_DECL void SET_BLIP_FLASH_INTERVAL(Blip blip, Any p1) { invoke<Void>(0xAA51DB313C010A7E, blip, p1); }
	NATIVE_DECL void SET_BLIP_COLOUR(Blip blip, int color) { invoke<Void>(0x03D7FB09E75D6B7E, blip, color); }
	NATIVE_DECL void SET_BLIP_SECONDARY_COLOUR(Blip blip, int r, int g, int b) { invoke<Void>(0x14892474891E09EB, blip, r, g, b); }
	NATIVE_DECL int GET_BLIP_COLOUR(Blip blip) { return invoke<int>(0xDF729E8D20CF7327, blip); }
	NATIVE_DECL int GET_BLIP_HUD_COLOUR(Blip blip) { return invoke<int>(0x729B5F1EFBC0AAEE, blip); }
	NATIVE_DECL BOOL IS_BLIP_SHORT_RANGE(Blip blip) { return invoke<BOOL>(0xDA5F8727EB75B926, blip); }
	NATIVE_DECL BOOL IS_BLIP_ON_MINIMAP(Blip blip) { return invoke<BOOL>(0xE41CA53051197A27, blip); }
	NATIVE_DECL BOOL DOES_BLIP_HAVE_GPS_ROUTE(Blip blip) { return invoke<BOOL>(0xDD2238F57B977751, blip); }
	NATIVE_DECL void SET_BLIP_HIDDEN_ON_LEGEND(Blip blip, BOOL toggle) { invoke<Void>(0x54318C915D27E4CE, blip, toggle); }
	NATIVE_DECL void SET_BLIP_HIGH_DETAIL(Blip blip, BOOL toggle) { invoke<Void>(0xE2590BC29220CEBB, blip, toggle); }
	NATIVE_DECL void SET_BLIP_AS_MISSION_CREATOR_BLIP(Blip blip, BOOL toggle) { invoke<Void>(0x24AC0137444F9FD5, blip, toggle); }
	NATIVE_DECL BOOL IS_MISSION_CREATOR_BLIP(Blip blip) { return invoke<BOOL>(0x26F49BF3381D933D, blip); }
	NATIVE_DECL Blip GET_NEW_SELECTED_MISSION_CREATOR_BLIP() { return invoke<Blip>(0x5C90988E7C8E1AF4); }
	NATIVE_DECL BOOL IS_HOVERING_OVER_MISSION_CREATOR_BLIP() { return invoke<BOOL>(0x4167EFE0527D706E); }
	NATIVE_DECL void SHOW_START_MISSION_INSTRUCTIONAL_BUTTON(BOOL toggle) { invoke<Void>(0xF1A6C18B35BCADE6, toggle); }
	NATIVE_DECL void SHOW_CONTACT_INSTRUCTIONAL_BUTTON(BOOL toggle) { invoke<Void>(0xC772A904CDE1186F, toggle); }
	NATIVE_DECL void _SHOW_PURCHASE_INSTRUCTIONAL_BUTTON(BOOL toggle) { invoke<Void>(0xF6865E26067B708C, toggle); }
	NATIVE_DECL void RELOAD_MAP_MENU() { invoke<Void>(0x2916A928514C9827); }
	NATIVE_DECL void SET_BLIP_MARKER_LONG_DISTANCE(Any p0, Any p1) { invoke<Void>(0xB552929B85FC27EC, p0, p1); }
	NATIVE_DECL void SET_BLIP_FLASHES(Blip blip, BOOL toggle) { invoke<Void>(0xB14552383D39CE3E, blip, toggle); }
	NATIVE_DECL void SET_BLIP_FLASHES_ALTERNATE(Blip blip, BOOL toggle) { invoke<Void>(0x2E8D9498C56DD0D1, blip, toggle); }
	NATIVE_DECL BOOL IS_BLIP_FLASHING(Blip blip) { return invoke<BOOL>(0xA5E41FD83AD6CEF0, blip); }
	NATIVE_DECL void SET_BLIP_AS_SHORT_RANGE(Blip blip, BOOL toggle) { invoke<Void>(0xBE8BE4FE60E27B72, blip, toggle); }
	NATIVE_DECL void SET_BLIP_SCALE(Blip blip, float scale) { invoke<Void>(0xD38744167B2FA257, blip, scale); }
	NATIVE_DECL void SET_BLIP_SCALE_2D(Blip blip, float xScale, float yScale) { invoke<Void>(0xCD6524439909C979, blip, xScale, yScale); }
	NATIVE_DECL void SET_BLIP_PRIORITY(Blip blip, int priority) { invoke<Void>(0xAE9FC9EF6A9FAC79, blip, priority); }
	NATIVE_DECL void SET_BLIP_DISPLAY(Blip blip, int displayId) { invoke<Void>(0x9029B2F3DA924928, blip, displayId); }
	NATIVE_DECL void SET_BLIP_CATEGORY(Blip blip, int index) { invoke<Void>(0x234CDD44D996FD9A, blip, index); }
	NATIVE_DECL void REMOVE_BLIP(Blip* blip) { invoke<Void>(0x86A652570E5F25DD, blip); }
	NATIVE_DECL void SET_BLIP_AS_FRIENDLY(Blip blip, BOOL toggle) { invoke<Void>(0x6F6F290102C02AB4, blip, toggle); }
	NATIVE_DECL void PULSE_BLIP(Blip blip) { invoke<Void>(0x742D6FD43115AF73, blip); }
	NATIVE_DECL void SHOW_NUMBER_ON_BLIP(Blip blip, int number) { invoke<Void>(0xA3C0B359DCB848B6, blip, number); }
	NATIVE_DECL void HIDE_NUMBER_ON_BLIP(Blip blip) { invoke<Void>(0x532CFF637EF80148, blip); }
	NATIVE_DECL void SHOW_HEIGHT_ON_BLIP(Blip blip, BOOL toggle) { invoke<Void>(0x75A16C3DA34F1245, blip, toggle); }
	NATIVE_DECL void SHOW_TICK_ON_BLIP(Blip blip, BOOL toggle) { invoke<Void>(0x74513EA3E505181E, blip, toggle); }
	NATIVE_DECL void SHOW_GOLD_TICK_ON_BLIP(Blip blip, BOOL toggle) { invoke<Void>(0xCAC2031EBF79B1A8, blip, toggle); }
	NATIVE_DECL void SHOW_FOR_SALE_ICON_ON_BLIP(Blip blip, BOOL toggle) { invoke<Void>(0x19BD6E3C0E16A8FA, blip, toggle); }
	NATIVE_DECL void SHOW_HEADING_INDICATOR_ON_BLIP(Blip blip, BOOL toggle) { invoke<Void>(0x5FBCA48327B914DF, blip, toggle); }
	NATIVE_DECL void SHOW_OUTLINE_INDICATOR_ON_BLIP(Blip blip, BOOL toggle) { invoke<Void>(0xB81656BC81FE24D1, blip, toggle); }
	NATIVE_DECL void SHOW_FRIEND_INDICATOR_ON_BLIP(Blip blip, BOOL toggle) { invoke<Void>(0x23C3EB807312F01A, blip, toggle); }
	NATIVE_DECL void SHOW_CREW_INDICATOR_ON_BLIP(Blip blip, BOOL toggle) { invoke<Void>(0xDCFB5D4DB8BF367E, blip, toggle); }
	NATIVE_DECL void SET_BLIP_EXTENDED_HEIGHT_THRESHOLD(Blip blip, BOOL toggle) { invoke<Void>(0xC4278F70131BAA6D, blip, toggle); }
	NATIVE_DECL void SET_BLIP_SHORT_HEIGHT_THRESHOLD(Any p0, Any p1) { invoke<Void>(0x4B5B620C9B59ED34, p0, p1); }
	NATIVE_DECL void SET_BLIP_USE_HEIGHT_INDICATOR_ON_EDGE(Blip blip, Any p1) { invoke<Void>(0x2C9F302398E13141, blip, p1); }
	NATIVE_DECL void SET_BLIP_AS_MINIMAL_ON_EDGE(Blip blip, BOOL toggle) { invoke<Void>(0x2B6D467DAB714E8D, blip, toggle); }
	NATIVE_DECL void SET_RADIUS_BLIP_EDGE(Blip blip, BOOL toggle) { invoke<Void>(0x25615540D894B814, blip, toggle); }
	NATIVE_DECL BOOL DOES_BLIP_EXIST(Blip blip) { return invoke<BOOL>(0xA6DB27D19ECBB7DA, blip); }
	NATIVE_DECL void SET_WAYPOINT_OFF() { invoke<Void>(0xA7E4E2D361C2627F); }
	NATIVE_DECL void DELETE_WAYPOINTS_FROM_THIS_PLAYER() { invoke<Void>(0xD8E694757BCEA8E9); }
	NATIVE_DECL void REFRESH_WAYPOINT() { invoke<Void>(0x81FA173F170560D1); }
	NATIVE_DECL BOOL IS_WAYPOINT_ACTIVE() { return invoke<BOOL>(0x1DD1F58F493F1DA5); }
	NATIVE_DECL void SET_NEW_WAYPOINT(float x, float y) { invoke<Void>(0xFE43368D2AA4F2FC, x, y); }
	NATIVE_DECL int GET_WAYPOINT_CLEAR_ON_ARRIVAL_MODE() { return invoke<int>(0xF46851AB8B02EF40); }
	NATIVE_DECL void SET_WAYPOINT_CLEAR_ON_ARRIVAL_MODE(int mode) { invoke<Void>(0x3FFC556B62146F75, mode); }
	NATIVE_DECL void SET_BLIP_BRIGHT(Blip blip, BOOL toggle) { invoke<Void>(0xB203913733F27884, blip, toggle); }
	NATIVE_DECL void SET_BLIP_SHOW_CONE(Blip blip, BOOL toggle, int hudColorIndex) { invoke<Void>(0x13127EC3665E8EE1, blip, toggle, hudColorIndex); }
	NATIVE_DECL void REMOVE_COP_BLIP_FROM_PED(Ped ped) { invoke<Void>(0xC594B315EDF2D4AF, ped); }
	NATIVE_DECL void SETUP_FAKE_CONE_DATA(Blip blip, float p1, float p2, float p3, float p4, float p5, float p6, Any p7, int p8) { invoke<Void>(0xF83D0FEBE75E62C9, blip, p1, p2, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL void REMOVE_FAKE_CONE_DATA(Blip blip) { invoke<Void>(0x35A3CD97B2C0A6D2, blip); }
	NATIVE_DECL void CLEAR_FAKE_CONE_ARRAY() { invoke<Void>(0x8410C5E0CD847B9D); }
	NATIVE_DECL void _SET_BLIP_GPS_ROUTE_DISPLAY_DISTANCE(Blip blip, int blipChangeParam46, BOOL blipChangeParam47) { invoke<Void>(0x25D984CFB64ED6DE, blip, blipChangeParam46, blipChangeParam47); }
	NATIVE_DECL BOOL SET_MINIMAP_COMPONENT(int componentId, BOOL toggle, int overrideColor) { return invoke<BOOL>(0x75A9A10948D1DEA6, componentId, toggle, overrideColor); }
	NATIVE_DECL void SET_MINIMAP_SONAR_SWEEP(BOOL toggle) { invoke<Void>(0x6B50FC8749632EC1, toggle); }
	NATIVE_DECL void SHOW_ACCOUNT_PICKER() { invoke<Void>(0x60E892BA4F5BDCA4); }
	NATIVE_DECL Blip GET_MAIN_PLAYER_BLIP_ID() { return invoke<Blip>(0xDCD4EC3F419D02FA); }
	NATIVE_DECL void SET_PM_WARNINGSCREEN_ACTIVE(BOOL p0) { invoke<Void>(0x41350B4FC28E3941, p0); }
	NATIVE_DECL void HIDE_LOADING_ON_FADE_THIS_FRAME() { invoke<Void>(0x4B0311D3CDC4648F); }
	NATIVE_DECL void SET_RADAR_AS_INTERIOR_THIS_FRAME(Hash interior, float x, float y, int z, int zoom) { invoke<Void>(0x59E727A1C9D3E31A, interior, x, y, z, zoom); }
	NATIVE_DECL void SET_INSIDE_VERY_SMALL_INTERIOR(BOOL toggle) { invoke<Void>(0x504DFE62A1692296, toggle); }
	NATIVE_DECL void SET_INSIDE_VERY_LARGE_INTERIOR(BOOL toggle) { invoke<Void>(0x7EC8ABA5E74B3D7A, toggle); }
	NATIVE_DECL void SET_RADAR_AS_EXTERIOR_THIS_FRAME() { invoke<Void>(0xE81B7D2A3DAB2D81); }
	NATIVE_DECL void SET_FAKE_PAUSEMAP_PLAYER_POSITION_THIS_FRAME(float x, float y) { invoke<Void>(0x77E2DD177910E1CF, x, y); }
	NATIVE_DECL void SET_FAKE_GPS_PLAYER_POSITION_THIS_FRAME(float x, float y, float z) { invoke<Void>(0xA17784FCA9548D15, x, y, z); }
	NATIVE_DECL BOOL IS_PAUSEMAP_IN_INTERIOR_MODE() { return invoke<BOOL>(0x9049FE339D5F6F6F); }
	NATIVE_DECL void HIDE_MINIMAP_EXTERIOR_MAP_THIS_FRAME() { invoke<Void>(0x5FBAE526203990C9); }
	NATIVE_DECL void HIDE_MINIMAP_INTERIOR_MAP_THIS_FRAME() { invoke<Void>(0x20FE7FDFEEAD38C0); }
	NATIVE_DECL void SET_USE_ISLAND_MAP(BOOL toggle) { invoke<Void>(0x5E1460624D194A38, toggle); }
	NATIVE_DECL void _SET_PAUSE_EXTERIOR_RENDERING_WHILE_IN_INTERIOR() { invoke<Void>(0x35CCE12EAECB4A51); }
	NATIVE_DECL void DONT_TILT_MINIMAP_THIS_FRAME() { invoke<Void>(0x6D14BFDC33B34F55); }
	NATIVE_DECL void DONT_ZOOM_MINIMAP_WHEN_RUNNING_THIS_FRAME() { invoke<Void>(0x89DA85D949CE57A0); }
	NATIVE_DECL void DONT_ZOOM_MINIMAP_WHEN_SNIPING_THIS_FRAME() { invoke<Void>(0x55F5A5F07134DE60); }
	NATIVE_DECL void SET_WIDESCREEN_FORMAT(Any p0) { invoke<Void>(0xC3B07BA00A83B0F1, p0); }
	NATIVE_DECL void DISPLAY_AREA_NAME(BOOL toggle) { invoke<Void>(0x276B6CE369C33678, toggle); }
	NATIVE_DECL void DISPLAY_CASH(BOOL toggle) { invoke<Void>(0x96DEC8D5430208B7, toggle); }
	NATIVE_DECL void USE_FAKE_MP_CASH(BOOL toggle) { invoke<Void>(0x170F541E1CADD1DE, toggle); }
	NATIVE_DECL void CHANGE_FAKE_MP_CASH(int cash, int bank) { invoke<Void>(0x0772DF77852C2E30, cash, bank); }
	NATIVE_DECL void DISPLAY_AMMO_THIS_FRAME(BOOL display) { invoke<Void>(0xA5E78BA2B1331C55, display); }
	NATIVE_DECL void DISPLAY_SNIPER_SCOPE_THIS_FRAME() { invoke<Void>(0x73115226F4814E62); }
	NATIVE_DECL void HIDE_HUD_AND_RADAR_THIS_FRAME() { invoke<Void>(0x719FF505F097FD20); }
	NATIVE_DECL void ALLOW_DISPLAY_OF_MULTIPLAYER_CASH_TEXT(BOOL allow) { invoke<Void>(0xE67C6DFD386EA5E7, allow); }
	NATIVE_DECL void SET_MULTIPLAYER_WALLET_CASH() { invoke<Void>(0xC2D15BEF167E27BC); }
	NATIVE_DECL void REMOVE_MULTIPLAYER_WALLET_CASH() { invoke<Void>(0x95CF81BD06EE1887); }
	NATIVE_DECL void SET_MULTIPLAYER_BANK_CASH() { invoke<Void>(0xDD21B55DF695CD0A); }
	NATIVE_DECL void REMOVE_MULTIPLAYER_BANK_CASH() { invoke<Void>(0xC7C6789AA1CFEDD0); }
	NATIVE_DECL void SET_MULTIPLAYER_HUD_CASH(int p0, BOOL p1) { invoke<Void>(0xFD1D220394BCB824, p0, p1); }
	NATIVE_DECL void REMOVE_MULTIPLAYER_HUD_CASH() { invoke<Void>(0x968F270E39141ECA); }
	NATIVE_DECL void HIDE_HELP_TEXT_THIS_FRAME() { invoke<Void>(0xD46923FC481CA285); }
	NATIVE_DECL BOOL IS_IME_IN_PROGRESS() { return invoke<BOOL>(0x801879A9B4F4B2FB); }
	NATIVE_DECL void DISPLAY_HELP_TEXT_THIS_FRAME(const char* message, BOOL curvedWindow) { invoke<Void>(0x960C9FF8F616E41C, message, curvedWindow); }
	NATIVE_DECL void HUD_FORCE_WEAPON_WHEEL(BOOL show) { invoke<Void>(0xEB354E5376BC81A7, show); }
	NATIVE_DECL void HUD_FORCE_SPECIAL_VEHICLE_WEAPON_WHEEL() { invoke<Void>(0x488043841BBE156F); }
	NATIVE_DECL void HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME() { invoke<Void>(0x0AFC4AF510774B47); }
	NATIVE_DECL Hash HUD_GET_WEAPON_WHEEL_CURRENTLY_HIGHLIGHTED() { return invoke<Hash>(0xA48931185F0536FE); }
	NATIVE_DECL void HUD_SET_WEAPON_WHEEL_TOP_SLOT(Hash weaponHash) { invoke<Void>(0x72C1056D678BB7D8, weaponHash); }
	NATIVE_DECL Hash HUD_GET_WEAPON_WHEEL_TOP_SLOT(int weaponTypeIndex) { return invoke<Hash>(0xA13E93403F26C812, weaponTypeIndex); }
	NATIVE_DECL void HUD_SHOWING_CHARACTER_SWITCH_SELECTION(BOOL toggle) { invoke<Void>(0x14C9FDCC41F81F63, toggle); }
	NATIVE_DECL void SET_GPS_FLAGS(int p0, float p1) { invoke<Void>(0x5B440763A4C8D15B, p0, p1); }
	NATIVE_DECL void CLEAR_GPS_FLAGS() { invoke<Void>(0x21986729D6A3A830); }
	NATIVE_DECL void SET_RACE_TRACK_RENDER(BOOL toggle) { invoke<Void>(0x1EAC5F91BCBC5073, toggle); }
	NATIVE_DECL void CLEAR_GPS_RACE_TRACK() { invoke<Void>(0x7AA5B4CE533C858B); }
	NATIVE_DECL void START_GPS_CUSTOM_ROUTE(int hudColor, BOOL displayOnFoot, BOOL followPlayer) { invoke<Void>(0xDB34E8D56FC13B08, hudColor, displayOnFoot, followPlayer); }
	NATIVE_DECL void ADD_POINT_TO_GPS_CUSTOM_ROUTE(float x, float y, float z) { invoke<Void>(0x311438A071DD9B1A, x, y, z); }
	NATIVE_DECL void SET_GPS_CUSTOM_ROUTE_RENDER(BOOL toggle, int radarThickness, int mapThickness) { invoke<Void>(0x900086F371220B6F, toggle, radarThickness, mapThickness); }
	NATIVE_DECL void CLEAR_GPS_CUSTOM_ROUTE() { invoke<Void>(0xE6DE0561D9232A64); }
	NATIVE_DECL void START_GPS_MULTI_ROUTE(int hudColor, BOOL routeFromPlayer, BOOL displayOnFoot) { invoke<Void>(0x3D3D15AF7BCAAF83, hudColor, routeFromPlayer, displayOnFoot); }
	NATIVE_DECL void ADD_POINT_TO_GPS_MULTI_ROUTE(float x, float y, float z) { invoke<Void>(0xA905192A6781C41B, x, y, z); }
	NATIVE_DECL void SET_GPS_MULTI_ROUTE_RENDER(BOOL toggle) { invoke<Void>(0x3DDA37128DD1ACA8, toggle); }
	NATIVE_DECL void CLEAR_GPS_MULTI_ROUTE() { invoke<Void>(0x67EEDEA1B9BAFD94); }
	NATIVE_DECL void CLEAR_GPS_PLAYER_WAYPOINT() { invoke<Void>(0xFF4FB7C8CDFA3DA7); }
	NATIVE_DECL void SET_GPS_FLASHES(BOOL toggle) { invoke<Void>(0x320D0E0D936A0E9B, toggle); }
	NATIVE_DECL void SET_PLAYER_ICON_COLOUR(int color) { invoke<Void>(0x7B21E0BB01E8224A, color); }
	NATIVE_DECL void FLASH_MINIMAP_DISPLAY() { invoke<Void>(0xF2DD778C22B15BDA); }
	NATIVE_DECL void FLASH_MINIMAP_DISPLAY_WITH_COLOR(int hudColorIndex) { invoke<Void>(0x6B1DE27EE78E6A19, hudColorIndex); }
	NATIVE_DECL void TOGGLE_STEALTH_RADAR(BOOL toggle) { invoke<Void>(0x6AFDFB93754950C7, toggle); }
	NATIVE_DECL void SET_MINIMAP_IN_SPECTATOR_MODE(BOOL toggle, Ped ped) { invoke<Void>(0x1A5CD7752DD28CD3, toggle, ped); }
	NATIVE_DECL void SET_MISSION_NAME(BOOL p0, const char* name) { invoke<Void>(0x5F28ECF5FC84772F, p0, name); }
	NATIVE_DECL void SET_MISSION_NAME_FOR_UGC_MISSION(BOOL p0, const char* name) { invoke<Void>(0xE45087D85F468BC2, p0, name); }
	NATIVE_DECL void SET_DESCRIPTION_FOR_UGC_MISSION_EIGHT_STRINGS(BOOL p0, const char* p1, const char* p2, const char* p3, const char* p4, const char* p5, const char* p6, const char* p7, const char* p8) { invoke<Void>(0x817B86108EB94E51, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL void SET_MINIMAP_BLOCK_WAYPOINT(BOOL toggle) { invoke<Void>(0x58FADDED207897DC, toggle); }
	NATIVE_DECL void SET_MINIMAP_IN_PROLOGUE(BOOL toggle) { invoke<Void>(0x9133955F1A2DA957, toggle); }
	NATIVE_DECL void SET_MINIMAP_BACKGROUND_HIDDEN(BOOL toggle) { invoke<Void>(0xB09D42557C45EBA1, toggle); }
	NATIVE_DECL void SET_MINIMAP_HIDE_FOW(BOOL toggle) { invoke<Void>(0xF8DEE0A5600CBB93, toggle); }
	NATIVE_DECL float GET_MINIMAP_FOW_DISCOVERY_RATIO() { return invoke<float>(0xE0130B41D3CF4574); }
	NATIVE_DECL BOOL GET_MINIMAP_FOW_COORDINATE_IS_REVEALED(float x, float y, float z) { return invoke<BOOL>(0x6E31B91145873922, x, y, z); }
	NATIVE_DECL void SET_MINIMAP_FOW_DO_NOT_UPDATE(BOOL p0) { invoke<Void>(0x62E849B7EB28E770, p0); }
	NATIVE_DECL void SET_MINIMAP_FOW_REVEAL_COORDINATE(float x, float y, float z) { invoke<Void>(0x0923DBF87DFF735E, x, y, z); }
	NATIVE_DECL void SET_MINIMAP_GOLF_COURSE(int hole) { invoke<Void>(0x71BDB63DBAF8DA59, hole); }
	NATIVE_DECL void SET_MINIMAP_GOLF_COURSE_OFF() { invoke<Void>(0x35EDD5B2E3FF01C0); }
	NATIVE_DECL void LOCK_MINIMAP_ANGLE(int angle) { invoke<Void>(0x299FAEBB108AE05B, angle); }
	NATIVE_DECL void UNLOCK_MINIMAP_ANGLE() { invoke<Void>(0x8183455E16C42E3A); }
	NATIVE_DECL void LOCK_MINIMAP_POSITION(float x, float y) { invoke<Void>(0x1279E861A329E73F, x, y); }
	NATIVE_DECL void UNLOCK_MINIMAP_POSITION() { invoke<Void>(0x3E93E06DB8EF1F30); }
	NATIVE_DECL void SET_FAKE_MINIMAP_MAX_ALTIMETER_HEIGHT(float altitude, BOOL p1, Any p2) { invoke<Void>(0xD201F3FF917A506D, altitude, p1, p2); }
	NATIVE_DECL void SET_HEALTH_HUD_DISPLAY_VALUES(int health, int capacity, BOOL wasAdded) { invoke<Void>(0x3F5CC444DCAAA8F2, health, capacity, wasAdded); }
	NATIVE_DECL void SET_MAX_HEALTH_HUD_DISPLAY(int maximumValue) { invoke<Void>(0x975D66A0BC17064C, maximumValue); }
	NATIVE_DECL void SET_MAX_ARMOUR_HUD_DISPLAY(int maximumValue) { invoke<Void>(0x06A320535F5F0248, maximumValue); }
	NATIVE_DECL void SET_BIGMAP_ACTIVE(BOOL toggleBigMap, BOOL showFullMap) { invoke<Void>(0x231C8F89D0539D8F, toggleBigMap, showFullMap); }
	NATIVE_DECL BOOL IS_HUD_COMPONENT_ACTIVE(int id) { return invoke<BOOL>(0xBC4C9EA5391ECC0D, id); }
	NATIVE_DECL BOOL IS_SCRIPTED_HUD_COMPONENT_ACTIVE(int id) { return invoke<BOOL>(0xDD100EB17A94FF65, id); }
	NATIVE_DECL void HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME(int id) { invoke<Void>(0xE374C498D8BADC14, id); }
	NATIVE_DECL void SHOW_SCRIPTED_HUD_COMPONENT_THIS_FRAME(int id) { invoke<Void>(0x4F38DCA127DAAEA2, id); }
	NATIVE_DECL BOOL IS_SCRIPTED_HUD_COMPONENT_HIDDEN_THIS_FRAME(int id) { return invoke<BOOL>(0x09C0403ED9A751C2, id); }
	NATIVE_DECL void HIDE_HUD_COMPONENT_THIS_FRAME(int id) { invoke<Void>(0x6806C51AD12B83B8, id); }
	NATIVE_DECL BOOL IS_HUD_COMPONENT_HIDDEN_THIS_FRAME(int id) { return invoke<BOOL>(0x8EDC335C943465C8, id); }
	NATIVE_DECL void SHOW_HUD_COMPONENT_THIS_FRAME(int id) { invoke<Void>(0x0B4DF1FA60C0E664, id); }
	NATIVE_DECL void HIDE_STREET_AND_CAR_NAMES_THIS_FRAME() { invoke<Void>(0xA4DEDE28B1814289); }
	NATIVE_DECL void RESET_RETICULE_VALUES() { invoke<Void>(0x12782CE0A636E9F0); }
	NATIVE_DECL void RESET_HUD_COMPONENT_VALUES(int id) { invoke<Void>(0x450930E616475D0D, id); }
	NATIVE_DECL void SET_HUD_COMPONENT_POSITION(int id, float x, float y) { invoke<Void>(0xAABB1F56E2A17CED, id, x, y); }
	NATIVE_DECL Vector3 GET_HUD_COMPONENT_POSITION(int id) { return invoke<Vector3>(0x223CA69A8C4417FD, id); }
	NATIVE_DECL void CLEAR_REMINDER_MESSAGE() { invoke<Void>(0xB57D8DD645CFA2CF); }
	NATIVE_DECL int GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(float worldX, float worldY, float worldZ, float* screenX, float* screenY) { return invoke<int>(0xF9904D11F1ACBEC3, worldX, worldY, worldZ, screenX, screenY); }
	NATIVE_DECL void OPEN_REPORTUGC_MENU() { invoke<Void>(0x523A590C1A3CC0D3); }
	NATIVE_DECL void FORCE_CLOSE_REPORTUGC_MENU() { invoke<Void>(0xEE4C0E6DBC6F2C6F); }
	NATIVE_DECL BOOL IS_REPORTUGC_MENU_OPEN() { return invoke<BOOL>(0x9135584D09A3437E); }
	NATIVE_DECL int _REPORT_NOMINATED_JOB(const char* jobNominated, Any* p1) { return invoke<int>(0x764EED2568508F13, jobNominated, p1); }
	NATIVE_DECL int _GET_NOMINATED_JOB_REPORT_STATUS(int index) { return invoke<int>(0xA3C8062CAB30E8A9, index); }
	NATIVE_DECL BOOL IS_FLOATING_HELP_TEXT_ON_SCREEN(int hudIndex) { return invoke<BOOL>(0x2432784ACA090DA4, hudIndex); }
	NATIVE_DECL void SET_FLOATING_HELP_TEXT_SCREEN_POSITION(int hudIndex, float x, float y) { invoke<Void>(0x7679CC1BCEBE3D4C, hudIndex, x, y); }
	NATIVE_DECL void SET_FLOATING_HELP_TEXT_WORLD_POSITION(int hudIndex, float x, float y, float z) { invoke<Void>(0x784BA7E0ECEB4178, hudIndex, x, y, z); }
	NATIVE_DECL void SET_FLOATING_HELP_TEXT_TO_ENTITY(int hudIndex, Entity entity, float offsetX, float offsetY) { invoke<Void>(0xB094BC1DB4018240, hudIndex, entity, offsetX, offsetY); }
	NATIVE_DECL void SET_FLOATING_HELP_TEXT_STYLE(int hudIndex, int p1, int p2, int p3, int p4, int p5) { invoke<Void>(0x788E7FD431BD67F1, hudIndex, p1, p2, p3, p4, p5); }
	NATIVE_DECL void CLEAR_FLOATING_HELP(int hudIndex, BOOL p1) { invoke<Void>(0x50085246ABD3FEFA, hudIndex, p1); }
	NATIVE_DECL void CREATE_MP_GAMER_TAG_WITH_CREW_COLOR(Player player, const char* username, BOOL pointedClanTag, BOOL isRockstarClan, const char* clanTag, int clanFlag, int r, int g, int b) { invoke<Void>(0x6DD05E9D83EFA4C9, player, username, pointedClanTag, isRockstarClan, clanTag, clanFlag, r, g, b); }
	NATIVE_DECL BOOL IS_MP_GAMER_TAG_MOVIE_ACTIVE() { return invoke<BOOL>(0x6E0EB3EB47C8D7AA); }
	NATIVE_DECL int CREATE_FAKE_MP_GAMER_TAG(Ped ped, const char* username, BOOL pointedClanTag, BOOL isRockstarClan, const char* clanTag, int clanFlag) { return invoke<int>(0xBFEFE3321A3F5015, ped, username, pointedClanTag, isRockstarClan, clanTag, clanFlag); }
	NATIVE_DECL void REMOVE_MP_GAMER_TAG(int gamerTagId) { invoke<Void>(0x31698AA80E0223F8, gamerTagId); }
	NATIVE_DECL BOOL IS_MP_GAMER_TAG_ACTIVE(int gamerTagId) { return invoke<BOOL>(0x4E929E7A5796FD26, gamerTagId); }
	NATIVE_DECL BOOL IS_MP_GAMER_TAG_FREE(int gamerTagId) { return invoke<BOOL>(0x595B5178E412E199, gamerTagId); }
	NATIVE_DECL void SET_MP_GAMER_TAG_VISIBILITY(int gamerTagId, int component, BOOL toggle, Any p3) { invoke<Void>(0x63BB75ABEDC1F6A0, gamerTagId, component, toggle, p3); }
	NATIVE_DECL void SET_ALL_MP_GAMER_TAGS_VISIBILITY(int gamerTagId, BOOL toggle) { invoke<Void>(0xEE76FF7E6A0166B0, gamerTagId, toggle); }
	NATIVE_DECL void SET_MP_GAMER_TAGS_SHOULD_USE_VEHICLE_HEALTH(int gamerTagId, BOOL toggle) { invoke<Void>(0xA67F9C46D612B6F1, gamerTagId, toggle); }
	NATIVE_DECL void SET_MP_GAMER_TAGS_SHOULD_USE_POINTS_HEALTH(int gamerTagId, BOOL toggle) { invoke<Void>(0xD29EC58C2F6B5014, gamerTagId, toggle); }
	NATIVE_DECL void SET_MP_GAMER_TAGS_POINT_HEALTH(int gamerTagId, int value, int maximumValue) { invoke<Void>(0x1563FE35E9928E67, gamerTagId, value, maximumValue); }
	NATIVE_DECL void SET_MP_GAMER_TAG_COLOUR(int gamerTagId, int component, int hudColorIndex) { invoke<Void>(0x613ED644950626AE, gamerTagId, component, hudColorIndex); }
	NATIVE_DECL void SET_MP_GAMER_TAG_HEALTH_BAR_COLOUR(int gamerTagId, int hudColorIndex) { invoke<Void>(0x3158C77A7E888AB4, gamerTagId, hudColorIndex); }
	NATIVE_DECL void SET_MP_GAMER_TAG_ALPHA(int gamerTagId, int component, int alpha) { invoke<Void>(0xD48FE545CD46F857, gamerTagId, component, alpha); }
	NATIVE_DECL void SET_MP_GAMER_TAG_WANTED_LEVEL(int gamerTagId, int wantedlvl) { invoke<Void>(0xCF228E2AA03099C3, gamerTagId, wantedlvl); }
	NATIVE_DECL void SET_MP_GAMER_TAG_NUM_PACKAGES(int gamerTagId, int p1) { invoke<Void>(0x9C16459B2324B2CF, gamerTagId, p1); }
	NATIVE_DECL void SET_MP_GAMER_TAG_NAME(int gamerTagId, const char* string) { invoke<Void>(0xDEA2B8283BAA3944, gamerTagId, string); }
	NATIVE_DECL BOOL IS_UPDATING_MP_GAMER_TAG_NAME_AND_CREW_DETAILS(int gamerTagId) { return invoke<BOOL>(0xEB709A36958ABE0D, gamerTagId); }
	NATIVE_DECL void SET_MP_GAMER_TAG_BIG_TEXT(int gamerTagId, const char* string) { invoke<Void>(0x7B7723747CCB55B6, gamerTagId, string); }
	NATIVE_DECL int GET_CURRENT_WEBPAGE_ID() { return invoke<int>(0x01A358D9128B7A86); }
	NATIVE_DECL int GET_CURRENT_WEBSITE_ID() { return invoke<int>(0x97D47996FC48CBAD); }
	NATIVE_DECL int GET_GLOBAL_ACTIONSCRIPT_FLAG(int flagIndex) { return invoke<int>(0xE3B05614DCE1D014, flagIndex); }
	NATIVE_DECL void RESET_GLOBAL_ACTIONSCRIPT_FLAG(int flagIndex) { invoke<Void>(0xB99C4E4D9499DF29, flagIndex); }
	NATIVE_DECL BOOL IS_WARNING_MESSAGE_READY_FOR_CONTROL() { return invoke<BOOL>(0xAF42195A42C63BBA); }
	NATIVE_DECL void SET_WARNING_MESSAGE(const char* titleMsg, int flags, const char* promptMsg, BOOL p3, int p4, const char* p5, const char* p6, BOOL showBackground, int errorCode) { invoke<Void>(0x7B1776B3B53F8D74, titleMsg, flags, promptMsg, p3, p4, p5, p6, showBackground, errorCode); }
	NATIVE_DECL void SET_WARNING_MESSAGE_WITH_HEADER(const char* entryHeader, const char* entryLine1, int instructionalKey, const char* entryLine2, BOOL p4, Any p5, Any* showBackground, Any* p7, BOOL p8, Any p9) { invoke<Void>(0xDC38CC1E35B6A5D7, entryHeader, entryLine1, instructionalKey, entryLine2, p4, p5, showBackground, p7, p8, p9); }
	NATIVE_DECL void SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS(const char* entryHeader, const char* entryLine1, int instructionalKey, const char* entryLine2, BOOL p4, Any p5, Any additionalIntInfo, const char* additionalTextInfoLine1, const char* additionalTextInfoLine2, BOOL showBackground, int errorCode) { invoke<Void>(0x701919482C74B5AB, entryHeader, entryLine1, instructionalKey, entryLine2, p4, p5, additionalIntInfo, additionalTextInfoLine1, additionalTextInfoLine2, showBackground, errorCode); }
	NATIVE_DECL void SET_WARNING_MESSAGE_WITH_HEADER_EXTENDED(const char* entryHeader, const char* entryLine1, int flags, const char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL showBg, Any p9, Any p10) { invoke<Void>(0x38B55259C2E078ED, entryHeader, entryLine1, flags, entryLine2, p4, p5, p6, p7, showBg, p9, p10); }
	NATIVE_DECL void SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS_EXTENDED(const char* labelTitle, const char* labelMessage, int p2, int p3, const char* labelMessage2, BOOL p5, int p6, int p7, const char* p8, const char* p9, BOOL background, int errorCode) { invoke<Void>(0x15803FEC3B9A872B, labelTitle, labelMessage, p2, p3, labelMessage2, p5, p6, p7, p8, p9, background, errorCode); }
	NATIVE_DECL Hash GET_WARNING_SCREEN_MESSAGE_HASH() { return invoke<Hash>(0x81DF9ABA6C83DFF9); }
	NATIVE_DECL BOOL SET_WARNING_MESSAGE_OPTION_ITEMS(int index, const char* name, int cash, int rp, int lvl, int colour) { return invoke<BOOL>(0x0C5A80A9E096D529, index, name, cash, rp, lvl, colour); }
	NATIVE_DECL BOOL SET_WARNING_MESSAGE_OPTION_HIGHLIGHT(Any p0) { return invoke<BOOL>(0xDAF87174BE7454FF, p0); }
	NATIVE_DECL void REMOVE_WARNING_MESSAGE_OPTION_ITEMS() { invoke<Void>(0x6EF54AB721DC6242); }
	NATIVE_DECL BOOL IS_WARNING_MESSAGE_ACTIVE() { return invoke<BOOL>(0xE18B138FABC53103); }
	NATIVE_DECL void CLEAR_DYNAMIC_PAUSE_MENU_ERROR_MESSAGE() { invoke<Void>(0x7792424AA0EAC32E); }
	NATIVE_DECL void CUSTOM_MINIMAP_SET_ACTIVE(BOOL toggle) { invoke<Void>(0x5354C5BA2EA868A4, toggle); }
	NATIVE_DECL void CUSTOM_MINIMAP_SET_BLIP_OBJECT(int spriteId) { invoke<Void>(0x1EAE6DD17B7A5EFA, spriteId); }
	NATIVE_DECL int CUSTOM_MINIMAP_CREATE_BLIP(float x, float y, float z) { return invoke<int>(0x551DF99658DB6EE8, x, y, z); }
	NATIVE_DECL void CUSTOM_MINIMAP_CLEAR_BLIPS() { invoke<Void>(0x2708FC083123F9FF); }
	NATIVE_DECL BOOL FORCE_SONAR_BLIPS_THIS_FRAME() { return invoke<BOOL>(0x1121BFA1A1A522A8); }
	NATIVE_DECL Blip GET_NORTH_BLID_INDEX() { return invoke<Blip>(0x3F0CF9CB7E589B88); }
	NATIVE_DECL void DISPLAY_PLAYER_NAME_TAGS_ON_BLIPS(BOOL toggle) { invoke<Void>(0x82CEDC33687E1F50, toggle); }
	NATIVE_DECL void DRAW_FRONTEND_BACKGROUND_THIS_FRAME() { invoke<Void>(0x211C4EF450086857); }
	NATIVE_DECL void DRAW_HUD_OVER_FADE_THIS_FRAME() { invoke<Void>(0xBF4F34A85CA2970C); }
	NATIVE_DECL void ACTIVATE_FRONTEND_MENU(Hash menuhash, BOOL togglePause, int component) { invoke<Void>(0xEF01D36B9C9D0C7B, menuhash, togglePause, component); }
	NATIVE_DECL void RESTART_FRONTEND_MENU(Hash menuHash, int p1) { invoke<Void>(0x10706DC6AD2D49C0, menuHash, p1); }
	NATIVE_DECL Hash GET_CURRENT_FRONTEND_MENU_VERSION() { return invoke<Hash>(0x2309595AD6145265); }
	NATIVE_DECL void SET_PAUSE_MENU_ACTIVE(BOOL toggle) { invoke<Void>(0xDF47FC56C71569CF, toggle); }
	NATIVE_DECL void DISABLE_FRONTEND_THIS_FRAME() { invoke<Void>(0x6D3465A73092F0E6); }
	NATIVE_DECL void SUPPRESS_FRONTEND_RENDERING_THIS_FRAME() { invoke<Void>(0xBA751764F0821256); }
	NATIVE_DECL void ALLOW_PAUSE_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME() { invoke<Void>(0xCC3FDDED67BCFC63); }
	NATIVE_DECL void SET_FRONTEND_ACTIVE(BOOL active) { invoke<Void>(0x745711A75AB09277, active); }
	NATIVE_DECL BOOL IS_PAUSE_MENU_ACTIVE() { return invoke<BOOL>(0xB0034A223497FFCB); }
	NATIVE_DECL BOOL IS_STORE_PENDING_NETWORK_SHUTDOWN_TO_OPEN() { return invoke<BOOL>(0x2F057596F2BD0061); }
	NATIVE_DECL int GET_PAUSE_MENU_STATE() { return invoke<int>(0x272ACD84970869C5); }
	NATIVE_DECL Vector3 GET_PAUSE_MENU_POSITION() { return invoke<Vector3>(0x5BFF36D6ED83E0AE); }
	NATIVE_DECL BOOL IS_PAUSE_MENU_RESTARTING() { return invoke<BOOL>(0x1C491717107431C7); }
	NATIVE_DECL void FORCE_SCRIPTED_GFX_WHEN_FRONTEND_ACTIVE(const char* p0) { invoke<Void>(0x2162C446DFDF38FD, p0); }
	NATIVE_DECL void PAUSE_MENUCEPTION_GO_DEEPER(int page) { invoke<Void>(0x77F16B447824DA6C, page); }
	NATIVE_DECL void PAUSE_MENUCEPTION_THE_KICK() { invoke<Void>(0xCDCA26E80FAECB8F); }
	NATIVE_DECL void PAUSE_TOGGLE_FULLSCREEN_MAP(Any p0) { invoke<Void>(0x2DE6C5E2E996F178, p0); }
	NATIVE_DECL void PAUSE_MENU_ACTIVATE_CONTEXT(Hash contextHash) { invoke<Void>(0xDD564BDD0472C936, contextHash); }
	NATIVE_DECL void PAUSE_MENU_DEACTIVATE_CONTEXT(Hash contextHash) { invoke<Void>(0x444D8CF241EC25C5, contextHash); }
	NATIVE_DECL BOOL PAUSE_MENU_IS_CONTEXT_ACTIVE(Hash contextHash) { return invoke<BOOL>(0x84698AB38D0C6636, contextHash); }
	NATIVE_DECL BOOL PAUSE_MENU_IS_CONTEXT_MENU_ACTIVE() { return invoke<BOOL>(0x2A25ADC48F87841F); }
	NATIVE_DECL int PAUSE_MENU_GET_HAIR_COLOUR_INDEX() { return invoke<int>(0xDE03620F8703A9DF); }
	NATIVE_DECL int PAUSE_MENU_GET_MOUSE_HOVER_INDEX() { return invoke<int>(0x359AF31A4B52F5ED); }
	NATIVE_DECL int PAUSE_MENU_GET_MOUSE_HOVER_UNIQUE_ID() { return invoke<int>(0x13C4B962653A5280); }
	NATIVE_DECL BOOL PAUSE_MENU_GET_MOUSE_CLICK_EVENT(Any* p0, Any* p1, Any* p2) { return invoke<BOOL>(0xC8E1071177A23BE5, p0, p1, p2); }
	NATIVE_DECL void PAUSE_MENU_REDRAW_INSTRUCTIONAL_BUTTONS(int p0) { invoke<Void>(0x4895BDEA16E7C080, p0); }
	NATIVE_DECL void PAUSE_MENU_SET_BUSY_SPINNER(BOOL p0, int position, int spinnerIndex) { invoke<Void>(0xC78E239AC5B2DDB9, p0, position, spinnerIndex); }
	NATIVE_DECL void PAUSE_MENU_SET_WARN_ON_TAB_CHANGE(BOOL p0) { invoke<Void>(0xF06EBB91A81E09E3, p0); }
	NATIVE_DECL BOOL IS_FRONTEND_READY_FOR_CONTROL() { return invoke<BOOL>(0x3BAB9A4E4F2FF5C7); }
	NATIVE_DECL void TAKE_CONTROL_OF_FRONTEND() { invoke<Void>(0xEC9264727EEC0F28); }
	NATIVE_DECL void RELEASE_CONTROL_OF_FRONTEND() { invoke<Void>(0x14621BB1DF14E2B2); }
	NATIVE_DECL BOOL CODE_WANTS_SCRIPT_TO_TAKE_CONTROL() { return invoke<BOOL>(0x66E7CB63C97B7D20); }
	NATIVE_DECL int GET_SCREEN_CODE_WANTS_SCRIPT_TO_CONTROL() { return invoke<int>(0x593FEAE1F73392D4); }
	NATIVE_DECL BOOL IS_NAVIGATING_MENU_CONTENT() { return invoke<BOOL>(0x4E3CD0EF8A489541); }
	NATIVE_DECL BOOL HAS_MENU_TRIGGER_EVENT_OCCURRED() { return invoke<BOOL>(0xF284AC67940C6812); }
	NATIVE_DECL BOOL HAS_MENU_LAYOUT_CHANGED_EVENT_OCCURRED() { return invoke<BOOL>(0x2E22FEFA0100275E); }
	NATIVE_DECL void SET_SAVEGAME_LIST_UNIQUE_ID(Any p0) { invoke<Void>(0x0CF54F20DE43879C, p0); }
	NATIVE_DECL void GET_MENU_TRIGGER_EVENT_DETAILS(int* lastItemMenuId, int* selectedItemUniqueId) { invoke<Void>(0x36C1451A88A09630, lastItemMenuId, selectedItemUniqueId); }
	NATIVE_DECL void GET_MENU_LAYOUT_CHANGED_EVENT_DETAILS(int* lastItemMenuId, int* selectedItemMenuId, int* selectedItemUniqueId) { invoke<Void>(0x7E17BE53E1AAABAF, lastItemMenuId, selectedItemMenuId, selectedItemUniqueId); }
	NATIVE_DECL BOOL GET_PM_PLAYER_CREW_COLOR(int* r, int* g, int* b) { return invoke<BOOL>(0xA238192F33110615, r, g, b); }
	NATIVE_DECL BOOL GET_MENU_PED_INT_STAT(Any p0, Any* p1) { return invoke<BOOL>(0xEF4CED81CEBEDC6D, p0, p1); }
	NATIVE_DECL BOOL GET_CHARACTER_MENU_PED_INT_STAT(Any p0, Any* p1, Any p2) { return invoke<BOOL>(0xCA6B2F7CE32AB653, p0, p1, p2); }
	NATIVE_DECL BOOL GET_MENU_PED_MASKED_INT_STAT(Hash statHash, int* outValue, int mask, BOOL p3) { return invoke<BOOL>(0x90A6526CF0381030, statHash, outValue, mask, p3); }
	NATIVE_DECL BOOL GET_CHARACTER_MENU_PED_MASKED_INT_STAT(Hash statHash, Any* outValue, int p2, int mask, BOOL p4) { return invoke<BOOL>(0x24A49BEAF468DC90, statHash, outValue, p2, mask, p4); }
	NATIVE_DECL BOOL GET_MENU_PED_FLOAT_STAT(Hash statHash, float* outValue) { return invoke<BOOL>(0x5FBD7095FE7AE57F, statHash, outValue); }
	NATIVE_DECL BOOL GET_CHARACTER_MENU_PED_FLOAT_STAT(float statHash, float* outValue, BOOL p2) { return invoke<BOOL>(0x8F08017F9D7C47BD, statHash, outValue, p2); }
	NATIVE_DECL BOOL GET_MENU_PED_BOOL_STAT(Hash statHash, BOOL* outValue) { return invoke<BOOL>(0x052991E59076E4E4, statHash, outValue); }
	NATIVE_DECL void CLEAR_PED_IN_PAUSE_MENU() { invoke<Void>(0x5E62BE5DC58E9E06); }
	NATIVE_DECL void GIVE_PED_TO_PAUSE_MENU(Ped ped, int p1) { invoke<Void>(0xAC0BFBDC3BE00E14, ped, p1); }
	NATIVE_DECL void SET_PAUSE_MENU_PED_LIGHTING(BOOL state) { invoke<Void>(0x3CA6050692BC61B0, state); }
	NATIVE_DECL void SET_PAUSE_MENU_PED_SLEEP_STATE(BOOL state) { invoke<Void>(0xECF128344E9FF9F1, state); }
	NATIVE_DECL void OPEN_ONLINE_POLICIES_MENU() { invoke<Void>(0x805D7CBB36FD6C4C); }
	NATIVE_DECL BOOL ARE_ONLINE_POLICIES_UP_TO_DATE() { return invoke<BOOL>(0xF13FE2A80C05C561); }
	NATIVE_DECL BOOL IS_ONLINE_POLICIES_MENU_ACTIVE() { return invoke<BOOL>(0x6F72CD94F7B5B68C); }
	NATIVE_DECL void OPEN_SOCIAL_CLUB_MENU(Hash menu) { invoke<Void>(0x75D3691713C3B05A, menu); }
	NATIVE_DECL void CLOSE_SOCIAL_CLUB_MENU() { invoke<Void>(0xD2B32BE3FC1626C6); }
	NATIVE_DECL void SET_SOCIAL_CLUB_TOUR(const char* name) { invoke<Void>(0x9E778248D6685FE0, name); }
	NATIVE_DECL BOOL IS_SOCIAL_CLUB_ACTIVE() { return invoke<BOOL>(0xC406BE343FC4B9AF); }
	NATIVE_DECL void SET_TEXT_INPUT_BOX_ENABLED(BOOL p0) { invoke<Void>(0x1185A8087587322C, p0); }
	NATIVE_DECL void FORCE_CLOSE_TEXT_INPUT_BOX() { invoke<Void>(0x8817605C2BA76200); }
	NATIVE_DECL void SET_ALLOW_COMMA_ON_TEXT_INPUT(Any p0) { invoke<Void>(0x577599CCED639CA2, p0); }
	NATIVE_DECL void OVERRIDE_MP_TEXT_CHAT_TEAM_STRING(Hash gxtEntryHash) { invoke<Void>(0x6A1738B4323FE2D9, gxtEntryHash); }
	NATIVE_DECL BOOL IS_MP_TEXT_CHAT_TYPING() { return invoke<BOOL>(0xB118AF58B5F332A1); }
	NATIVE_DECL void CLOSE_MP_TEXT_CHAT() { invoke<Void>(0x1AC8F4AD40E22127); }
	NATIVE_DECL void MP_TEXT_CHAT_IS_TEAM_JOB(Any p0) { invoke<Void>(0x7C226D5346D4D10A, p0); }
	NATIVE_DECL void OVERRIDE_MP_TEXT_CHAT_COLOR(int p0, int hudColor) { invoke<Void>(0xF47E567B3630DD12, p0, hudColor); }
	NATIVE_DECL void MP_TEXT_CHAT_DISABLE(BOOL toggle) { invoke<Void>(0x1DB21A44B09E8BA3, toggle); }
	NATIVE_DECL void FLAG_PLAYER_CONTEXT_IN_TOURNAMENT(BOOL toggle) { invoke<Void>(0xCEF214315D276FD1, toggle); }
	NATIVE_DECL void SET_PED_HAS_AI_BLIP(Ped ped, BOOL hasCone) { invoke<Void>(0xD30C50DF888D58B5, ped, hasCone); }
	NATIVE_DECL void SET_PED_HAS_AI_BLIP_WITH_COLOUR(Ped ped, BOOL hasCone, int color) { invoke<Void>(0xB13DCB4C6FAAD238, ped, hasCone, color); }
	NATIVE_DECL BOOL DOES_PED_HAVE_AI_BLIP(Ped ped) { return invoke<BOOL>(0x15B8ECF844EE67ED, ped); }
	NATIVE_DECL void SET_PED_AI_BLIP_GANG_ID(Ped ped, int gangId) { invoke<Void>(0xE52B8E7F85D39A08, ped, gangId); }
	NATIVE_DECL void SET_PED_AI_BLIP_HAS_CONE(Ped ped, BOOL toggle) { invoke<Void>(0x3EED80DFF7325CAA, ped, toggle); }
	NATIVE_DECL void SET_PED_AI_BLIP_FORCED_ON(Ped ped, BOOL toggle) { invoke<Void>(0x0C4BBF625CA98C4E, ped, toggle); }
	NATIVE_DECL void SET_PED_AI_BLIP_NOTICE_RANGE(Ped ped, float range) { invoke<Void>(0x97C65887D4B37FA9, ped, range); }
	NATIVE_DECL void SET_PED_AI_BLIP_SPRITE(Ped ped, int spriteId) { invoke<Void>(0xFCFACD0DB9D7A57D, ped, spriteId); }
	NATIVE_DECL Blip GET_AI_PED_PED_BLIP_INDEX(Ped ped) { return invoke<Blip>(0x7CD934010E115C2C, ped); }
	NATIVE_DECL Blip GET_AI_PED_VEHICLE_BLIP_INDEX(Ped ped) { return invoke<Blip>(0x56176892826A4FE8, ped); }
	NATIVE_DECL BOOL HAS_DIRECTOR_MODE_BEEN_LAUNCHED_BY_CODE() { return invoke<BOOL>(0xA277800A9EAE340E); }
	NATIVE_DECL void SET_DIRECTOR_MODE_LAUNCHED_BY_SCRIPT() { invoke<Void>(0x2632482FD6B9AB87); }
	NATIVE_DECL void SET_PLAYER_IS_IN_DIRECTOR_MODE(BOOL toggle) { invoke<Void>(0x808519373FD336A3, toggle); }
	NATIVE_DECL void SET_DIRECTOR_MODE_AVAILABLE(BOOL toggle) { invoke<Void>(0x04655F9D075D0AE5, toggle); }
	NATIVE_DECL void HIDE_HUDMARKERS_THIS_FRAME() { invoke<Void>(0x243296A510B562B6); }
}

namespace INTERIOR
{
	NATIVE_DECL float GET_INTERIOR_HEADING(Interior interior) { return invoke<float>(0xF49B58631D9E22D9, interior); }
	NATIVE_DECL void GET_INTERIOR_LOCATION_AND_NAMEHASH(Interior interior, Vector3* position, Hash* nameHash) { invoke<Void>(0x252BDC06B73FA6EA, interior, position, nameHash); }
	NATIVE_DECL int GET_INTERIOR_GROUP_ID(Interior interior) { return invoke<int>(0xE4A84ABF135EF91A, interior); }
	NATIVE_DECL Vector3 GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(Interior interior, float x, float y, float z) { return invoke<Vector3>(0x9E3B3E6D66F6E22F, interior, x, y, z); }
	NATIVE_DECL BOOL IS_INTERIOR_SCENE() { return invoke<BOOL>(0xBC72B5D7A1CBD54D); }
	NATIVE_DECL BOOL IS_VALID_INTERIOR(Interior interior) { return invoke<BOOL>(0x26B0E73D7EAAF4D3, interior); }
	NATIVE_DECL void CLEAR_ROOM_FOR_ENTITY(Entity entity) { invoke<Void>(0xB365FC0C4E27FFA7, entity); }
	NATIVE_DECL void FORCE_ROOM_FOR_ENTITY(Entity entity, Interior interior, Hash roomHashKey) { invoke<Void>(0x52923C4710DD9907, entity, interior, roomHashKey); }
	NATIVE_DECL Hash GET_ROOM_KEY_FROM_ENTITY(Entity entity) { return invoke<Hash>(0x47C2A06D4F5F424B, entity); }
	NATIVE_DECL Hash GET_KEY_FOR_ENTITY_IN_ROOM(Entity entity) { return invoke<Hash>(0x399685DB942336BC, entity); }
	NATIVE_DECL Interior GET_INTERIOR_FROM_ENTITY(Entity entity) { return invoke<Interior>(0x2107BA504071A6BB, entity); }
	NATIVE_DECL void RETAIN_ENTITY_IN_INTERIOR(Entity entity, Interior interior) { invoke<Void>(0x82EBB79E258FA2B7, entity, interior); }
	NATIVE_DECL void CLEAR_INTERIOR_STATE_OF_ENTITY(Entity entity) { invoke<Void>(0x85D5422B2039A70D, entity); }
	NATIVE_DECL void FORCE_ACTIVATING_TRACKING_ON_ENTITY(Any p0, Any p1) { invoke<Void>(0x38C1CB1CB119A016, p0, p1); }
	NATIVE_DECL void FORCE_ROOM_FOR_GAME_VIEWPORT(int interiorID, Hash roomHashKey) { invoke<Void>(0x920D853F3E17F1DA, interiorID, roomHashKey); }
	NATIVE_DECL void SET_ROOM_FOR_GAME_VIEWPORT_BY_NAME(const char* roomName) { invoke<Void>(0xAF348AFCB575A441, roomName); }
	NATIVE_DECL void SET_ROOM_FOR_GAME_VIEWPORT_BY_KEY(Hash roomHashKey) { invoke<Void>(0x405DC2AEF6AF95B9, roomHashKey); }
	NATIVE_DECL Hash GET_ROOM_KEY_FOR_GAME_VIEWPORT() { return invoke<Hash>(0xA6575914D2A0B450); }
	NATIVE_DECL void CLEAR_ROOM_FOR_GAME_VIEWPORT() { invoke<Void>(0x23B59D8912F94246); }
	NATIVE_DECL Interior GET_INTERIOR_FROM_PRIMARY_VIEW() { return invoke<Interior>(0xE7D267EC6CA966C3); }
	NATIVE_DECL Interior GET_INTERIOR_AT_COORDS(float x, float y, float z) { return invoke<Interior>(0xB0F7F8663821D9C3, x, y, z); }
	NATIVE_DECL void ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(Pickup pickup, const char* roomName) { invoke<Void>(0x3F6167F351168730, pickup, roomName); }
	NATIVE_DECL void PIN_INTERIOR_IN_MEMORY(Interior interior) { invoke<Void>(0x2CA429C029CCF247, interior); }
	NATIVE_DECL void UNPIN_INTERIOR(Interior interior) { invoke<Void>(0x261CCE7EED010641, interior); }
	NATIVE_DECL BOOL IS_INTERIOR_READY(Interior interior) { return invoke<BOOL>(0x6726BDCCC1932F0E, interior); }
	NATIVE_DECL BOOL SET_INTERIOR_IN_USE(Interior interior) { return invoke<BOOL>(0x4C2330E61D3DEB56, interior); }
	NATIVE_DECL Interior GET_INTERIOR_AT_COORDS_WITH_TYPE(float x, float y, float z, const char* interiorType) { return invoke<Interior>(0x05B7A89BD78797FC, x, y, z, interiorType); }
	NATIVE_DECL Interior GET_INTERIOR_AT_COORDS_WITH_TYPEHASH(float x, float y, float z, Hash typeHash) { return invoke<Interior>(0xF0F77ADB9F67E79D, x, y, z, typeHash); }
	NATIVE_DECL void ACTIVATE_INTERIOR_GROUPS_USING_CAMERA() { invoke<Void>(0x483ACA1176CA93F1); }
	NATIVE_DECL BOOL IS_COLLISION_MARKED_OUTSIDE(float x, float y, float z) { return invoke<BOOL>(0xEEA5AC2EDA7C33E8, x, y, z); }
	NATIVE_DECL Interior GET_INTERIOR_FROM_COLLISION(float x, float y, float z) { return invoke<Interior>(0xEC4CF9FCB29A4424, x, y, z); }
	NATIVE_DECL void ENABLE_STADIUM_PROBES_THIS_FRAME(BOOL toggle) { invoke<Void>(0x7ECDF98587E92DEC, toggle); }
	NATIVE_DECL void ACTIVATE_INTERIOR_ENTITY_SET(Interior interior, const char* entitySetName) { invoke<Void>(0x55E86AF2712B36A1, interior, entitySetName); }
	NATIVE_DECL void DEACTIVATE_INTERIOR_ENTITY_SET(Interior interior, const char* entitySetName) { invoke<Void>(0x420BD37289EEE162, interior, entitySetName); }
	NATIVE_DECL BOOL IS_INTERIOR_ENTITY_SET_ACTIVE(Interior interior, const char* entitySetName) { return invoke<BOOL>(0x35F7DD45E8C0A16D, interior, entitySetName); }
	NATIVE_DECL void SET_INTERIOR_ENTITY_SET_TINT_INDEX(Interior interior, const char* entitySetName, int color) { invoke<Void>(0xC1F1920BAF281317, interior, entitySetName, color); }
	NATIVE_DECL void REFRESH_INTERIOR(Interior interior) { invoke<Void>(0x41F37C3427C75AE0, interior); }
	NATIVE_DECL void ENABLE_EXTERIOR_CULL_MODEL_THIS_FRAME(Hash mapObjectHash) { invoke<Void>(0xA97F257D0151A6AB, mapObjectHash); }
	NATIVE_DECL void ENABLE_SHADOW_CULL_MODEL_THIS_FRAME(Hash mapObjectHash) { invoke<Void>(0x50C375537449F369, mapObjectHash); }
	NATIVE_DECL void DISABLE_INTERIOR(Interior interior, BOOL toggle) { invoke<Void>(0x6170941419D7D8EC, interior, toggle); }
	NATIVE_DECL BOOL IS_INTERIOR_DISABLED(Interior interior) { return invoke<BOOL>(0xBC5115A5A939DD15, interior); }
	NATIVE_DECL void CAP_INTERIOR(Interior interior, BOOL toggle) { invoke<Void>(0xD9175F941610DB54, interior, toggle); }
	NATIVE_DECL BOOL IS_INTERIOR_CAPPED(Interior interior) { return invoke<BOOL>(0x92BAC8ACF88CEC26, interior); }
	NATIVE_DECL void DISABLE_METRO_SYSTEM(BOOL toggle) { invoke<Void>(0x9E6542F0CE8E70A3, toggle); }
	NATIVE_DECL void SET_IS_EXTERIOR_ONLY(Entity entity, BOOL toggle) { invoke<Void>(0x7241CCB7D020DB69, entity, toggle); }
	static void _0XDD3D5F9CA0C715D0(BOOL toggle) { invoke<Void>(0XDD3D5F9CA0C715D0, toggle); } // 0XDD3D5F9CA0C715D0
}

namespace ITEMSETS
{
	NATIVE_DECL ScrHandle CREATE_ITEMSET(BOOL p0) { return invoke<ScrHandle>(0x35AD299F50D91B24, p0); }
	NATIVE_DECL void DESTROY_ITEMSET(ScrHandle itemset) { invoke<Void>(0xDE18220B1C183EDA, itemset); }
	NATIVE_DECL BOOL IS_ITEMSET_VALID(ScrHandle itemset) { return invoke<BOOL>(0xB1B1EA596344DFAB, itemset); }
	NATIVE_DECL BOOL ADD_TO_ITEMSET(ScrHandle item, ScrHandle itemset) { return invoke<BOOL>(0xE3945201F14637DD, item, itemset); }
	NATIVE_DECL void REMOVE_FROM_ITEMSET(ScrHandle item, ScrHandle itemset) { invoke<Void>(0x25E68244B0177686, item, itemset); }
	NATIVE_DECL int GET_ITEMSET_SIZE(ScrHandle itemset) { return invoke<int>(0xD9127E83ABF7C631, itemset); }
	NATIVE_DECL ScrHandle GET_INDEXED_ITEM_IN_ITEMSET(int index, ScrHandle itemset) { return invoke<ScrHandle>(0x7A197E2521EE2BAB, index, itemset); }
	NATIVE_DECL BOOL IS_IN_ITEMSET(ScrHandle item, ScrHandle itemset) { return invoke<BOOL>(0x2D0FC594D1E9C107, item, itemset); }
	NATIVE_DECL void CLEAN_ITEMSET(ScrHandle itemset) { invoke<Void>(0x41BC0D722FC04221, itemset); }
}

namespace LOBBY
{
	NATIVE_DECL BOOL LOBBY_AUTO_MULTIPLAYER_MENU() { return invoke<BOOL>(0xF2CA003F167E21D2); }
	NATIVE_DECL BOOL LOBBY_AUTO_MULTIPLAYER_FREEMODE() { return invoke<BOOL>(0xEF7D17BC6C85264C); }
	NATIVE_DECL void LOBBY_SET_AUTO_MULTIPLAYER(BOOL toggle) { invoke<Void>(0xB0C56BD3D808D863, toggle); }
	NATIVE_DECL BOOL LOBBY_AUTO_MULTIPLAYER_EVENT() { return invoke<BOOL>(0x8AA464D4E0F6ACCD); }
	NATIVE_DECL void LOBBY_SET_AUTO_MULTIPLAYER_EVENT(BOOL toggle) { invoke<Void>(0xFC309E94546FCDB5, toggle); }
	NATIVE_DECL BOOL LOBBY_AUTO_MULTIPLAYER_RANDOM_JOB() { return invoke<BOOL>(0xC6DC823253FBB366); }
	NATIVE_DECL void LOBBY_SET_AUTO_MP_RANDOM_JOB(BOOL toggle) { invoke<Void>(0xC7E7181C09F33B69, toggle); }
	NATIVE_DECL void SHUTDOWN_SESSION_CLEARS_AUTO_MULTIPLAYER(BOOL toggle) { invoke<Void>(0xFA1E0E893D915215, toggle); }
}

namespace LOCALIZATION
{
	NATIVE_DECL int LOCALIZATION_GET_SYSTEM_LANGUAGE() { return invoke<int>(0x497420E022796B3F); }
	NATIVE_DECL int GET_CURRENT_LANGUAGE() { return invoke<int>(0x2BDD44CC428A7EAE); }
	NATIVE_DECL int LOCALIZATION_GET_SYSTEM_DATE_TYPE() { return invoke<int>(0xA8AE43AEC1A61314); }
}

namespace MISC
{
	NATIVE_DECL int GET_ALLOCATED_STACK_SIZE() { return invoke<int>(0x8B3CA62B1EF19B62); }
	NATIVE_DECL int GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE(int stackSize) { return invoke<int>(0xFEAD16FC8F9DFC0F, stackSize); }
	NATIVE_DECL void SET_RANDOM_SEED(int seed) { invoke<Void>(0x444D98F98C11F3EC, seed); }
	NATIVE_DECL void SET_TIME_SCALE(float timeScale) { invoke<Void>(0x1D408577D440E81E, timeScale); }
	NATIVE_DECL void SET_MISSION_FLAG(BOOL toggle) { invoke<Void>(0xC4301E5121A0ED73, toggle); }
	NATIVE_DECL BOOL GET_MISSION_FLAG() { return invoke<BOOL>(0xA33CDCCDA663159E); }
	NATIVE_DECL void SET_RANDOM_EVENT_FLAG(BOOL toggle) { invoke<Void>(0x971927086CFD2158, toggle); }
	NATIVE_DECL BOOL GET_RANDOM_EVENT_FLAG() { return invoke<BOOL>(0xD2D57F1D764117B1); }
	NATIVE_DECL const char* GET_CONTENT_TO_LOAD() { return invoke<const char*>(0x24DA7D7667FD7B09); }
	NATIVE_DECL void ACTIVITY_FEED_CREATE(const char* p0, const char* p1) { invoke<Void>(0x4DCDF92BF64236CD, p0, p1); }
	NATIVE_DECL void ACTIVITY_FEED_ADD_SUBSTRING_TO_CAPTION(const char* p0) { invoke<Void>(0x31125FD509D9043F, p0); }
	NATIVE_DECL void ACTIVITY_FEED_ADD_LITERAL_SUBSTRING_TO_CAPTION(const char* p0) { invoke<Void>(0xEBD3205A207939ED, p0); }
	NATIVE_DECL void ACTIVITY_FEED_ADD_INT_TO_CAPTION(Any p0) { invoke<Void>(0x97E7E2C04245115B, p0); }
	NATIVE_DECL void ACTIVITY_FEED_LARGE_IMAGE_URL(const char* p0) { invoke<Void>(0x916CA67D26FD1E37, p0); }
	NATIVE_DECL void ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE(const char* p0, const char* p1) { invoke<Void>(0xEB078CA2B5E82ADD, p0, p1); }
	NATIVE_DECL void ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE_ADD(const char* p0) { invoke<Void>(0x703CC7F60CBB2B57, p0); }
	NATIVE_DECL void ACTIVITY_FEED_POST() { invoke<Void>(0x8951EB9C6906D3C8); }
	NATIVE_DECL void ACTIVITY_FEED_ONLINE_PLAYED_WITH_POST(const char* p0) { invoke<Void>(0xBA4B8D83BDC75551, p0); }
	NATIVE_DECL BOOL HAS_RESUMED_FROM_SUSPEND() { return invoke<BOOL>(0xE8B9C0EC9E183F35); }
	NATIVE_DECL void SET_SCRIPT_HIGH_PRIO(BOOL toggle) { invoke<Void>(0x65D2EBB47E1CEC21, toggle); }
	NATIVE_DECL void SET_THIS_IS_A_TRIGGER_SCRIPT(BOOL toggle) { invoke<Void>(0x6F2135B6129620C1, toggle); }
	NATIVE_DECL void INFORM_CODE_OF_CONTENT_ID_OF_CURRENT_UGC_MISSION(const char* p0) { invoke<Void>(0x8D74E26F54B4E5C3, p0); }
	NATIVE_DECL BOOL GET_BASE_ELEMENT_LOCATION_FROM_METADATA_BLOCK(Any* p0, Any* p1, Any p2, BOOL p3) { return invoke<BOOL>(0xB335F761606DB47C, p0, p1, p2, p3); }
	NATIVE_DECL Hash GET_PREV_WEATHER_TYPE_HASH_NAME() { return invoke<Hash>(0x564B884A05EC45A3); }
	NATIVE_DECL Hash GET_NEXT_WEATHER_TYPE_HASH_NAME() { return invoke<Hash>(0x711327CD09C8F162); }
	NATIVE_DECL BOOL IS_PREV_WEATHER_TYPE(const char* weatherType) { return invoke<BOOL>(0x44F28F86433B10A9, weatherType); }
	NATIVE_DECL BOOL IS_NEXT_WEATHER_TYPE(const char* weatherType) { return invoke<BOOL>(0x2FAA3A30BEC0F25D, weatherType); }
	NATIVE_DECL void SET_WEATHER_TYPE_PERSIST(const char* weatherType) { invoke<Void>(0x704983DF373B198F, weatherType); }
	NATIVE_DECL void SET_WEATHER_TYPE_NOW_PERSIST(const char* weatherType) { invoke<Void>(0xED712CA327900C8A, weatherType); }
	NATIVE_DECL void SET_WEATHER_TYPE_NOW(const char* weatherType) { invoke<Void>(0x29B487C359E19889, weatherType); }
	NATIVE_DECL void SET_WEATHER_TYPE_OVERTIME_PERSIST(const char* weatherType, float time) { invoke<Void>(0xFB5045B7C42B75BF, weatherType, time); }
	NATIVE_DECL void SET_RANDOM_WEATHER_TYPE() { invoke<Void>(0x8B05F884CF7E8020); }
	NATIVE_DECL void CLEAR_WEATHER_TYPE_PERSIST() { invoke<Void>(0xCCC39339BEF76CF5); }
	NATIVE_DECL void CLEAR_WEATHER_TYPE_NOW_PERSIST_NETWORK(int milliseconds) { invoke<Void>(0x0CF97F497FE7D048, milliseconds); }
	NATIVE_DECL void GET_CURR_WEATHER_STATE(Hash* weatherType1, Hash* weatherType2, float* percentWeather2) { invoke<Void>(0xF3BBE884A14BB413, weatherType1, weatherType2, percentWeather2); }
	NATIVE_DECL void SET_CURR_WEATHER_STATE(Hash weatherType1, Hash weatherType2, float percentWeather2) { invoke<Void>(0x578C752848ECFA0C, weatherType1, weatherType2, percentWeather2); }
	NATIVE_DECL void SET_OVERRIDE_WEATHER(const char* weatherType) { invoke<Void>(0xA43D5C6FE51ADBEF, weatherType); }
	NATIVE_DECL void SET_OVERRIDE_WEATHEREX(const char* weatherType, BOOL p1) { invoke<Void>(0x1178E104409FE58C, weatherType, p1); }
	NATIVE_DECL void CLEAR_OVERRIDE_WEATHER() { invoke<Void>(0x338D2E3477711050); }
	NATIVE_DECL void WATER_OVERRIDE_SET_SHOREWAVEAMPLITUDE(float amplitude) { invoke<Void>(0xB8F87EAD7533B176, amplitude); }
	NATIVE_DECL void WATER_OVERRIDE_SET_SHOREWAVEMINAMPLITUDE(float minAmplitude) { invoke<Void>(0xC3EAD29AB273ECE8, minAmplitude); }
	NATIVE_DECL void WATER_OVERRIDE_SET_SHOREWAVEMAXAMPLITUDE(float maxAmplitude) { invoke<Void>(0xA7A1127490312C36, maxAmplitude); }
	NATIVE_DECL void WATER_OVERRIDE_SET_OCEANNOISEMINAMPLITUDE(float minAmplitude) { invoke<Void>(0x31727907B2C43C55, minAmplitude); }
	NATIVE_DECL void WATER_OVERRIDE_SET_OCEANWAVEAMPLITUDE(float amplitude) { invoke<Void>(0x405591EC8FD9096D, amplitude); }
	NATIVE_DECL void WATER_OVERRIDE_SET_OCEANWAVEMINAMPLITUDE(float minAmplitude) { invoke<Void>(0xF751B16FB32ABC1D, minAmplitude); }
	NATIVE_DECL void WATER_OVERRIDE_SET_OCEANWAVEMAXAMPLITUDE(float maxAmplitude) { invoke<Void>(0xB3E6360DDE733E82, maxAmplitude); }
	NATIVE_DECL void WATER_OVERRIDE_SET_RIPPLEBUMPINESS(float bumpiness) { invoke<Void>(0x7C9C0B1EEB1F9072, bumpiness); }
	NATIVE_DECL void WATER_OVERRIDE_SET_RIPPLEMINBUMPINESS(float minBumpiness) { invoke<Void>(0x6216B116083A7CB4, minBumpiness); }
	NATIVE_DECL void WATER_OVERRIDE_SET_RIPPLEMAXBUMPINESS(float maxBumpiness) { invoke<Void>(0x9F5E6BB6B34540DA, maxBumpiness); }
	NATIVE_DECL void WATER_OVERRIDE_SET_RIPPLEDISTURB(float disturb) { invoke<Void>(0xB9854DFDE0D833D6, disturb); }
	NATIVE_DECL void WATER_OVERRIDE_SET_STRENGTH(float strength) { invoke<Void>(0xC54A08C85AE4D410, strength); }
	NATIVE_DECL void WATER_OVERRIDE_FADE_IN(float p0) { invoke<Void>(0xA8434F1DFF41D6E7, p0); }
	NATIVE_DECL void WATER_OVERRIDE_FADE_OUT(float p0) { invoke<Void>(0xC3C221ADDDE31A11, p0); }
	NATIVE_DECL void SET_WIND(float speed) { invoke<Void>(0xAC3A74E8384A9919, speed); }
	NATIVE_DECL void SET_WIND_SPEED(float speed) { invoke<Void>(0xEE09ECEDBABE47FC, speed); }
	NATIVE_DECL float GET_WIND_SPEED() { return invoke<float>(0xA8CF1CC0AFCD3F12); }
	NATIVE_DECL void SET_WIND_DIRECTION(float direction) { invoke<Void>(0xEB0F4468467B4528, direction); }
	NATIVE_DECL Vector3 GET_WIND_DIRECTION() { return invoke<Vector3>(0x1F400FEF721170DA); }
	NATIVE_DECL void SET_RAIN(float intensity) { invoke<Void>(0x643E26EA6E024D92, intensity); }
	NATIVE_DECL float GET_RAIN_LEVEL() { return invoke<float>(0x96695E368AD855F3); }
	NATIVE_DECL void SET_SNOW(float level) { invoke<Void>(0x7F06937B0CDCBC1A, level); }
	NATIVE_DECL float GET_SNOW_LEVEL() { return invoke<float>(0xC5868A966E5BE3AE); }
	NATIVE_DECL void FORCE_LIGHTNING_FLASH() { invoke<Void>(0xF6062E089251C898); }
	NATIVE_DECL void SET_CLOUD_SETTINGS_OVERRIDE(const char* p0) { invoke<Void>(0x02DEAAC8F8EA7FE7, p0); }
	NATIVE_DECL void PRELOAD_CLOUD_HAT(const char* name) { invoke<Void>(0x11B56FBBF7224868, name); }
	NATIVE_DECL void LOAD_CLOUD_HAT(const char* name, float transitionTime) { invoke<Void>(0xFC4842A34657BFCB, name, transitionTime); }
	NATIVE_DECL void UNLOAD_CLOUD_HAT(const char* name, float p1) { invoke<Void>(0xA74802FB8D0B7814, name, p1); }
	NATIVE_DECL void UNLOAD_ALL_CLOUD_HATS() { invoke<Void>(0x957E790EA1727B64); }
	NATIVE_DECL void SET_CLOUDS_ALPHA(float opacity) { invoke<Void>(0xF36199225D6D8C86, opacity); }
	NATIVE_DECL float GET_CLOUDS_ALPHA() { return invoke<float>(0x20AC25E781AE4A84); }
	NATIVE_DECL int GET_GAME_TIMER() { return invoke<int>(0x9CD27B0045628463); }
	NATIVE_DECL float GET_FRAME_TIME() { return invoke<float>(0x15C40837039FFAF7); }
	NATIVE_DECL float GET_SYSTEM_TIME_STEP() { return invoke<float>(0xE599A503B3837E1B); }
	NATIVE_DECL int GET_FRAME_COUNT() { return invoke<int>(0xFC8202EFC642E6F2); }
	NATIVE_DECL float GET_RANDOM_FLOAT_IN_RANGE(float startRange, float endRange) { return invoke<float>(0x313CE5879CEB6FCD, startRange, endRange); }
	NATIVE_DECL int GET_RANDOM_INT_IN_RANGE(int startRange, int endRange) { return invoke<int>(0xD53343AA4FB7DD28, startRange, endRange); }
	NATIVE_DECL int GET_RANDOM_MWC_INT_IN_RANGE(int startRange, int endRange) { return invoke<int>(0xF2D49816A804D134, startRange, endRange); }
	NATIVE_DECL BOOL GET_GROUND_Z_FOR_3D_COORD(float x, float y, float z, float* groundZ, BOOL ignoreWater, BOOL p5) { return invoke<BOOL>(0xC906A7DAB05C8D2B, x, y, z, groundZ, ignoreWater, p5); }
	NATIVE_DECL BOOL GET_GROUND_Z_AND_NORMAL_FOR_3D_COORD(float x, float y, float z, float* groundZ, Vector3* normal) { return invoke<BOOL>(0x8BDC7BFC57A81E76, x, y, z, groundZ, normal); }
	NATIVE_DECL BOOL GET_GROUND_Z_EXCLUDING_OBJECTS_FOR_3D_COORD(float x, float y, float z, float* groundZ, BOOL p4, BOOL p5) { return invoke<BOOL>(0x9E82F0F362881B29, x, y, z, groundZ, p4, p5); }
	NATIVE_DECL float ASIN(float p0) { return invoke<float>(0xC843060B5765DCE7, p0); }
	NATIVE_DECL float ACOS(float p0) { return invoke<float>(0x1D08B970013C34B6, p0); }
	NATIVE_DECL float TAN(float p0) { return invoke<float>(0x632106CC96E82E91, p0); }
	NATIVE_DECL float ATAN(float p0) { return invoke<float>(0xA9D1795CD5043663, p0); }
	NATIVE_DECL float ATAN2(float p0, float p1) { return invoke<float>(0x8927CBF9D22261A4, p0, p1); }
	NATIVE_DECL float GET_DISTANCE_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, BOOL useZ) { return invoke<float>(0xF1B760881820C952, x1, y1, z1, x2, y2, z2, useZ); }
	NATIVE_DECL float GET_ANGLE_BETWEEN_2D_VECTORS(float x1, float y1, float x2, float y2) { return invoke<float>(0x186FC4BE848E1C92, x1, y1, x2, y2); }
	NATIVE_DECL float GET_HEADING_FROM_VECTOR_2D(float dx, float dy) { return invoke<float>(0x2FFB6B224F4B2926, dx, dy); }
	NATIVE_DECL float GET_RATIO_OF_CLOSEST_POINT_ON_LINE(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, BOOL clamp) { return invoke<float>(0x7F8F6405F4777AF6, x1, y1, z1, x2, y2, z2, x3, y3, z3, clamp); }
	NATIVE_DECL Vector3 GET_CLOSEST_POINT_ON_LINE(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, BOOL clamp) { return invoke<Vector3>(0x21C235BC64831E5A, x1, y1, z1, x2, y2, z2, x3, y3, z3, clamp); }
	NATIVE_DECL BOOL GET_LINE_PLANE_INTERSECTION(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float* p12) { return invoke<BOOL>(0xF56DFB7B61BE7276, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	NATIVE_DECL BOOL GET_POINT_AREA_OVERLAP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { return invoke<BOOL>(0xA0AD167E4B39D9A2, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
	NATIVE_DECL void SET_BIT(int* address, int offset) { invoke<Void>(0x933D6A9EEC1BACD0, address, offset); }
	NATIVE_DECL void CLEAR_BIT(int* address, int offset) { invoke<Void>(0xE80492A9AC099A93, address, offset); }
	NATIVE_DECL Hash GET_HASH_KEY(const char* string) { return invoke<Hash>(0xD24D37CC275948CC, string); }
	NATIVE_DECL void SLERP_NEAR_QUATERNION(float t, float x, float y, float z, float w, float x1, float y1, float z1, float w1, float* outX, float* outY, float* outZ, float* outW) { invoke<Void>(0xF2F6A2FA49278625, t, x, y, z, w, x1, y1, z1, w1, outX, outY, outZ, outW); }
	NATIVE_DECL BOOL IS_AREA_OCCUPIED(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6, BOOL p7, BOOL p8, BOOL p9, BOOL p10, Any p11, BOOL p12) { return invoke<BOOL>(0xA61B4DF533DCB56E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	NATIVE_DECL BOOL IS_AREA_OCCUPIED_SLOW(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<BOOL>(0x39455BF4F4F55186, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	NATIVE_DECL BOOL IS_POSITION_OCCUPIED(float x, float y, float z, float range, BOOL p4, BOOL checkVehicles, BOOL checkPeds, BOOL p7, BOOL p8, Entity ignoreEntity, BOOL p10) { return invoke<BOOL>(0xADCDE75E1C60F32D, x, y, z, range, p4, checkVehicles, checkPeds, p7, p8, ignoreEntity, p10); }
	NATIVE_DECL BOOL IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(float p0, float p1, float p2, float p3, float p4, float p5, Any p6) { return invoke<BOOL>(0xE54E209C35FFA18D, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void CLEAR_AREA(float X, float Y, float Z, float radius, BOOL p4, BOOL ignoreCopCars, BOOL ignoreObjects, BOOL p7) { invoke<Void>(0xA56F01F3765B93A0, X, Y, Z, radius, p4, ignoreCopCars, ignoreObjects, p7); }
	NATIVE_DECL void CLEAR_AREA_LEAVE_VEHICLE_HEALTH(float x, float y, float z, float radius, BOOL p4, BOOL p5, BOOL p6, BOOL p7) { invoke<Void>(0x957838AAF91BD12D, x, y, z, radius, p4, p5, p6, p7); }
	NATIVE_DECL void CLEAR_AREA_OF_VEHICLES(float x, float y, float z, float radius, BOOL p4, BOOL p5, BOOL p6, BOOL p7, BOOL p8, BOOL p9, Any p10) { invoke<Void>(0x01C7B9B38428AEB6, x, y, z, radius, p4, p5, p6, p7, p8, p9, p10); }
	NATIVE_DECL void CLEAR_ANGLED_AREA_OF_VEHICLES(float x1, float y1, float z1, float x2, float y2, float z2, float width, BOOL p7, BOOL p8, BOOL p9, BOOL p10, BOOL p11, Any p12, Any p13) { invoke<Void>(0x11DB3500F042A8AA, x1, y1, z1, x2, y2, z2, width, p7, p8, p9, p10, p11, p12, p13); }
	NATIVE_DECL void CLEAR_AREA_OF_OBJECTS(float x, float y, float z, float radius, int flags) { invoke<Void>(0xDD9B9B385AAC7F5B, x, y, z, radius, flags); }
	NATIVE_DECL void CLEAR_AREA_OF_PEDS(float x, float y, float z, float radius, int flags) { invoke<Void>(0xBE31FD6CE464AC59, x, y, z, radius, flags); }
	NATIVE_DECL void CLEAR_AREA_OF_COPS(float x, float y, float z, float radius, int flags) { invoke<Void>(0x04F8FC8FCF58F88D, x, y, z, radius, flags); }
	NATIVE_DECL void CLEAR_AREA_OF_PROJECTILES(float x, float y, float z, float radius, int flags) { invoke<Void>(0x0A1CB9094635D1A6, x, y, z, radius, flags); }
	NATIVE_DECL void CLEAR_SCENARIO_SPAWN_HISTORY() { invoke<Void>(0x7EC6F9A478A6A512); }
	NATIVE_DECL void SET_SAVE_MENU_ACTIVE(BOOL ignoreVehicle) { invoke<Void>(0xC9BF75D28165FF77, ignoreVehicle); }
	NATIVE_DECL int GET_STATUS_OF_MANUAL_SAVE() { return invoke<int>(0x397BAA01068BAA96); }
	NATIVE_DECL void SET_CREDITS_ACTIVE(BOOL toggle) { invoke<Void>(0xB938B7E6D3C0620C, toggle); }
	NATIVE_DECL void SET_CREDITS_FADE_OUT_WITH_SCREEN(BOOL toggle) { invoke<Void>(0xB51B9AB9EF81868C, toggle); }
	NATIVE_DECL BOOL HAVE_CREDITS_REACHED_END() { return invoke<BOOL>(0x075F1D57402C93BA); }
	NATIVE_DECL BOOL ARE_CREDITS_RUNNING() { return invoke<BOOL>(0xD19C0826DC20CF1C); }
	NATIVE_DECL void TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(const char* scriptName) { invoke<Void>(0x9DC711BC69C548DF, scriptName); }
	NATIVE_DECL void NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME() { invoke<Void>(0x9243BAC96D64C050); }
	NATIVE_DECL int ADD_HOSPITAL_RESTART(float x, float y, float z, float heading, int whenToUse) { return invoke<int>(0x1F464EF988465A81, x, y, z, heading, whenToUse); }
	NATIVE_DECL void DISABLE_HOSPITAL_RESTART(int hospitalIndex, BOOL toggle) { invoke<Void>(0xC8535819C450EBA8, hospitalIndex, toggle); }
	NATIVE_DECL int ADD_POLICE_RESTART(float x, float y, float z, float heading, int whenToUse) { return invoke<int>(0x452736765B31FC4B, x, y, z, heading, whenToUse); }
	NATIVE_DECL void DISABLE_POLICE_RESTART(int policeIndex, BOOL toggle) { invoke<Void>(0x23285DED6EBD7EA3, policeIndex, toggle); }
	NATIVE_DECL void SET_RESTART_COORD_OVERRIDE(float x, float y, float z, float heading) { invoke<Void>(0x706B5EDCAA7FA663, x, y, z, heading); }
	NATIVE_DECL void CLEAR_RESTART_COORD_OVERRIDE() { invoke<Void>(0xA2716D40842EAF79); }
	NATIVE_DECL void PAUSE_DEATH_ARREST_RESTART(BOOL toggle) { invoke<Void>(0x2C2B3493FBF51C71, toggle); }
	NATIVE_DECL void IGNORE_NEXT_RESTART(BOOL toggle) { invoke<Void>(0x21FFB63D8C615361, toggle); }
	NATIVE_DECL void SET_FADE_OUT_AFTER_DEATH(BOOL toggle) { invoke<Void>(0x4A18E01DF2C87B86, toggle); }
	NATIVE_DECL void SET_FADE_OUT_AFTER_ARREST(BOOL toggle) { invoke<Void>(0x1E0B4DC0D990A4E7, toggle); }
	NATIVE_DECL void SET_FADE_IN_AFTER_DEATH_ARREST(BOOL toggle) { invoke<Void>(0xDA66D2796BA33F12, toggle); }
	NATIVE_DECL void SET_FADE_IN_AFTER_LOAD(BOOL toggle) { invoke<Void>(0xF3D78F59DFE18D79, toggle); }
	NATIVE_DECL int REGISTER_SAVE_HOUSE(float x, float y, float z, float p3, const char* p4, Any p5, Any p6) { return invoke<int>(0xC0714D0A7EEECA54, x, y, z, p3, p4, p5, p6); }
	NATIVE_DECL void SET_SAVE_HOUSE(int savehouseHandle, BOOL p1, BOOL p2) { invoke<Void>(0x4F548CABEAE553BC, savehouseHandle, p1, p2); }
	NATIVE_DECL BOOL OVERRIDE_SAVE_HOUSE(BOOL p0, float p1, float p2, float p3, float p4, BOOL p5, float p6, float p7) { return invoke<BOOL>(0x1162EA8AE9D24EEA, p0, p1, p2, p3, p4, p5, p6, p7); }
	NATIVE_DECL BOOL GET_SAVE_HOUSE_DETAILS_AFTER_SUCCESSFUL_LOAD(Vector3* p0, float* p1, BOOL* fadeInAfterLoad, BOOL* p3) { return invoke<BOOL>(0xA4A0065E39C9F25C, p0, p1, fadeInAfterLoad, p3); }
	NATIVE_DECL void DO_AUTO_SAVE() { invoke<Void>(0x50EEAAD86232EE55); }
	NATIVE_DECL BOOL GET_IS_AUTO_SAVE_OFF() { return invoke<BOOL>(0x6E04F06094C87047); }
	NATIVE_DECL BOOL IS_AUTO_SAVE_IN_PROGRESS() { return invoke<BOOL>(0x69240733738C19A0); }
	NATIVE_DECL BOOL HAS_CODE_REQUESTED_AUTOSAVE() { return invoke<BOOL>(0x2107A3773771186D); }
	NATIVE_DECL void CLEAR_CODE_REQUESTED_AUTOSAVE() { invoke<Void>(0x06462A961E94B67C); }
	NATIVE_DECL void BEGIN_REPLAY_STATS(Any p0, Any p1) { invoke<Void>(0xE0E500246FF73D66, p0, p1); }
	NATIVE_DECL void ADD_REPLAY_STAT_VALUE(Any value) { invoke<Void>(0x69FE6DC87BD2A5E9, value); }
	NATIVE_DECL void END_REPLAY_STATS() { invoke<Void>(0xA23E821FBDF8A5F2); }
	NATIVE_DECL BOOL HAVE_REPLAY_STATS_BEEN_STORED() { return invoke<BOOL>(0xD642319C54AADEB6); }
	NATIVE_DECL int GET_REPLAY_STAT_MISSION_ID() { return invoke<int>(0x5B1F2E327B6B6FE1); }
	NATIVE_DECL int GET_REPLAY_STAT_MISSION_TYPE() { return invoke<int>(0x2B626A0150E4D449); }
	NATIVE_DECL int GET_REPLAY_STAT_COUNT() { return invoke<int>(0xDC9274A7EF6B2867); }
	NATIVE_DECL int GET_REPLAY_STAT_AT_INDEX(int index) { return invoke<int>(0x8098C8D6597AAE18, index); }
	NATIVE_DECL void CLEAR_REPLAY_STATS() { invoke<Void>(0x1B1AB132A16FDA55); }
	NATIVE_DECL BOOL QUEUE_MISSION_REPEAT_LOAD() { return invoke<BOOL>(0x72DE52178C291CB5); }
	NATIVE_DECL BOOL QUEUE_MISSION_REPEAT_SAVE() { return invoke<BOOL>(0x44A0BDC559B35F6E); }
	NATIVE_DECL BOOL QUEUE_MISSION_REPEAT_SAVE_FOR_BENCHMARK_TEST() { return invoke<BOOL>(0xEB2104E905C6F2E9); }
	NATIVE_DECL int GET_STATUS_OF_MISSION_REPEAT_SAVE() { return invoke<int>(0x2B5E102E4A42F2BF); }
	NATIVE_DECL BOOL IS_MEMORY_CARD_IN_USE() { return invoke<BOOL>(0x8A75CE2956274ADD); }
	NATIVE_DECL void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, int damage, BOOL p7, Hash weaponHash, Ped ownerPed, BOOL isAudible, BOOL isInvisible, float speed) { invoke<Void>(0x867654CBC7606F2C, x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed); }
	NATIVE_DECL void SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(float x1, float y1, float z1, float x2, float y2, float z2, int damage, BOOL p7, Hash weaponHash, Ped ownerPed, BOOL isAudible, BOOL isInvisible, float speed, Entity entity, Any p14) { invoke<Void>(0xE3A7742E0B7A2F8B, x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed, entity, p14); }
	NATIVE_DECL void SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY_NEW(float x1, float y1, float z1, float x2, float y2, float z2, int damage, BOOL p7, Hash weaponHash, Ped ownerPed, BOOL isAudible, BOOL isInvisible, float speed, Entity entity, BOOL p14, BOOL p15, Entity targetEntity, BOOL p17, Any p18, Any p19, Any p20) { invoke<Void>(0xBFE5756E7407064A, x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed, entity, p14, p15, targetEntity, p17, p18, p19, p20); }
	NATIVE_DECL void GET_MODEL_DIMENSIONS(Hash modelHash, Vector3* minimum, Vector3* maximum) { invoke<Void>(0x03E8D3D5F549087A, modelHash, minimum, maximum); }
	NATIVE_DECL void SET_FAKE_WANTED_LEVEL(int fakeWantedLevel) { invoke<Void>(0x1454F2448DE30163, fakeWantedLevel); }
	NATIVE_DECL int GET_FAKE_WANTED_LEVEL() { return invoke<int>(0x4C9296CBCD1B971E); }
	NATIVE_DECL void USING_MISSION_CREATOR(BOOL toggle) { invoke<Void>(0xF14878FC50BEC6EE, toggle); }
	NATIVE_DECL void ALLOW_MISSION_CREATOR_WARP(BOOL toggle) { invoke<Void>(0xDEA36202FC3382DF, toggle); }
	NATIVE_DECL void SET_MINIGAME_IN_PROGRESS(BOOL toggle) { invoke<Void>(0x19E00D7322C6F85B, toggle); }
	NATIVE_DECL BOOL IS_MINIGAME_IN_PROGRESS() { return invoke<BOOL>(0x2B4A15E44DE0F478); }
	NATIVE_DECL BOOL IS_THIS_A_MINIGAME_SCRIPT() { return invoke<BOOL>(0x7B30F65D7B710098); }
	NATIVE_DECL BOOL IS_SNIPER_INVERTED() { return invoke<BOOL>(0x61A23B7EDA9BDA24); }
	NATIVE_DECL BOOL SHOULD_USE_METRIC_MEASUREMENTS() { return invoke<BOOL>(0xD3D15555431AB793); }
	NATIVE_DECL int GET_PROFILE_SETTING(int profileSetting) { return invoke<int>(0xC488FF2356EA7791, profileSetting); }
	NATIVE_DECL BOOL ARE_STRINGS_EQUAL(const char* string1, const char* string2) { return invoke<BOOL>(0x0C515FAB3FF9EA92, string1, string2); }
	NATIVE_DECL int COMPARE_STRINGS(const char* str1, const char* str2, BOOL matchCase, int maxLength) { return invoke<int>(0x1E34710ECD4AB0EB, str1, str2, matchCase, maxLength); }
	NATIVE_DECL int ABSI(int value) { return invoke<int>(0xF0D31AD191A74F87, value); }
	NATIVE_DECL float ABSF(float value) { return invoke<float>(0x73D57CFFDD12C355, value); }
	NATIVE_DECL BOOL IS_SNIPER_BULLET_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<BOOL>(0xFEFCF11B01287125, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL BOOL IS_PROJECTILE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, BOOL ownedByPlayer) { return invoke<BOOL>(0x5270A8FBC098C3F8, x1, y1, z1, x2, y2, z2, ownedByPlayer); }
	NATIVE_DECL BOOL IS_PROJECTILE_TYPE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, int type, BOOL ownedByPlayer) { return invoke<BOOL>(0x2E0DC353342C4A6D, x1, y1, z1, x2, y2, z2, type, ownedByPlayer); }
	NATIVE_DECL BOOL IS_PROJECTILE_TYPE_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, Any p7, BOOL ownedByPlayer) { return invoke<BOOL>(0xF0BC12401061DEA0, x1, y1, z1, x2, y2, z2, width, p7, ownedByPlayer); }
	NATIVE_DECL BOOL IS_PROJECTILE_TYPE_WITHIN_DISTANCE(float x, float y, float z, Hash projectileHash, float radius, BOOL ownedByPlayer) { return invoke<BOOL>(0x34318593248C8FB2, x, y, z, projectileHash, radius, ownedByPlayer); }
	NATIVE_DECL BOOL GET_COORDS_OF_PROJECTILE_TYPE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, Hash projectileHash, Vector3* projectilePos, BOOL ownedByPlayer) { return invoke<BOOL>(0x8D7A43EC6A5FEA45, x1, y1, z1, x2, y2, z2, projectileHash, projectilePos, ownedByPlayer); }
	NATIVE_DECL BOOL GET_COORDS_OF_PROJECTILE_TYPE_IN_ANGLED_AREA(float vecAngledAreaPoint1X, float vecAngledAreaPoint1Y, float vecAngledAreaPoint1Z, float vecAngledAreaPoint2X, float vecAngledAreaPoint2Y, float vecAngledAreaPoint2Z, float distanceOfOppositeFace, Hash weaponType, Vector3* positionOut, BOOL bIsPlayer) { return invoke<BOOL>(0x3DA8C28346B62CED, vecAngledAreaPoint1X, vecAngledAreaPoint1Y, vecAngledAreaPoint1Z, vecAngledAreaPoint2X, vecAngledAreaPoint2Y, vecAngledAreaPoint2Z, distanceOfOppositeFace, weaponType, positionOut, bIsPlayer); }
	NATIVE_DECL BOOL GET_COORDS_OF_PROJECTILE_TYPE_WITHIN_DISTANCE(Ped ped, Hash weaponHash, float distance, Vector3* outCoords, BOOL p4) { return invoke<BOOL>(0xDFB4138EEFED7B81, ped, weaponHash, distance, outCoords, p4); }
	NATIVE_DECL BOOL GET_PROJECTILE_OF_PROJECTILE_TYPE_WITHIN_DISTANCE(Ped ped, Hash weaponHash, float distance, Vector3* outCoords, Object* outProjectile, BOOL p5) { return invoke<BOOL>(0x82FDE6A57EE4EE44, ped, weaponHash, distance, outCoords, outProjectile, p5); }
	NATIVE_DECL BOOL IS_BULLET_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, BOOL ownedByPlayer) { return invoke<BOOL>(0x1A8B5F3C01E2B477, x1, y1, z1, x2, y2, z2, width, ownedByPlayer); }
	NATIVE_DECL BOOL IS_BULLET_IN_AREA(float x, float y, float z, float radius, BOOL ownedByPlayer) { return invoke<BOOL>(0x3F2023999AD51C1F, x, y, z, radius, ownedByPlayer); }
	NATIVE_DECL BOOL IS_BULLET_IN_BOX(float x1, float y1, float z1, float x2, float y2, float z2, BOOL ownedByPlayer) { return invoke<BOOL>(0xDE0F6D7450D37351, x1, y1, z1, x2, y2, z2, ownedByPlayer); }
	NATIVE_DECL BOOL HAS_BULLET_IMPACTED_IN_AREA(float x, float y, float z, float radius, BOOL bIsPlayer, BOOL bIsEntry) { return invoke<BOOL>(0x9870ACFB89A90995, x, y, z, radius, bIsPlayer, bIsEntry); }
	NATIVE_DECL BOOL HAS_BULLET_IMPACTED_IN_BOX(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6, BOOL p7) { return invoke<BOOL>(0xDC8C5D7CFEAB8394, p0, p1, p2, p3, p4, p5, p6, p7); }
	NATIVE_DECL BOOL IS_ORBIS_VERSION() { return invoke<BOOL>(0xA72BC0B675B1519E); }
	NATIVE_DECL BOOL IS_DURANGO_VERSION() { return invoke<BOOL>(0x4D982ADB1978442D); }
	NATIVE_DECL BOOL IS_XBOX360_VERSION() { return invoke<BOOL>(0xF6201B4DAF662A9D); }
	NATIVE_DECL BOOL IS_PS3_VERSION() { return invoke<BOOL>(0xCCA1072C29D096C2); }
	NATIVE_DECL BOOL IS_PC_VERSION() { return invoke<BOOL>(0x48AF36444B965238); }
	NATIVE_DECL BOOL IS_STEAM_VERSION() { return invoke<BOOL>(0x0A27B2B6282F7169); }
	NATIVE_DECL BOOL _IS_XBOXPC_VERSION() { return invoke<BOOL>(0xE2BCD0EFAE90D1F4); }
	NATIVE_DECL BOOL IS_AUSSIE_VERSION() { return invoke<BOOL>(0x9F1935CA1F724008); }
	NATIVE_DECL BOOL IS_JAPANESE_VERSION() { return invoke<BOOL>(0xB8C0BB75D8A77DB3); }
	NATIVE_DECL BOOL IS_XBOX_PLATFORM() { return invoke<BOOL>(0x138679CA01E21F53); }
	NATIVE_DECL BOOL IS_SCARLETT_VERSION() { return invoke<BOOL>(0xC545AB1CF97ABB34); }
	NATIVE_DECL BOOL IS_SCE_PLATFORM() { return invoke<BOOL>(0xF911E695C1EB8518); }
	NATIVE_DECL BOOL IS_PROSPERO_VERSION() { return invoke<BOOL>(0x807ABE1AB65C24D2); }
	NATIVE_DECL BOOL IS_STRING_NULL(const char* string) { return invoke<BOOL>(0xF22B6C47C6EAB066, string); }
	NATIVE_DECL BOOL IS_STRING_NULL_OR_EMPTY(const char* string) { return invoke<BOOL>(0xCA042B6957743895, string); }
	NATIVE_DECL BOOL STRING_TO_INT(const char* string, int* outInteger) { return invoke<BOOL>(0x5A5F40FE637EB584, string, outInteger); }
	NATIVE_DECL void SET_BITS_IN_RANGE(int* var, int rangeStart, int rangeEnd, int p3) { invoke<Void>(0x8EF07E15701D61ED, var, rangeStart, rangeEnd, p3); }
	NATIVE_DECL int GET_BITS_IN_RANGE(int var, int rangeStart, int rangeEnd) { return invoke<int>(0x53158863FCC0893A, var, rangeStart, rangeEnd); }
	NATIVE_DECL int ADD_STUNT_JUMP(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, float camX, float camY, float camZ, int p15, int p16, int p17) { return invoke<int>(0x1A992DA297A4630C, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, camX, camY, camZ, p15, p16, p17); }
	NATIVE_DECL int ADD_STUNT_JUMP_ANGLED(float x1, float y1, float z1, float x2, float y2, float z2, float radius1, float x3, float y3, float z3, float x4, float y4, float z4, float radius2, float camX, float camY, float camZ, int p17, int p18, int p19) { return invoke<int>(0xBBE5D803A5360CBF, x1, y1, z1, x2, y2, z2, radius1, x3, y3, z3, x4, y4, z4, radius2, camX, camY, camZ, p17, p18, p19); }
	NATIVE_DECL void TOGGLE_SHOW_OPTIONAL_STUNT_JUMP_CAMERA(BOOL toggle) { invoke<Void>(0xFB80AB299D2EE1BD, toggle); }
	NATIVE_DECL void DELETE_STUNT_JUMP(int p0) { invoke<Void>(0xDC518000E39DAE1F, p0); }
	NATIVE_DECL void ENABLE_STUNT_JUMP_SET(int p0) { invoke<Void>(0xE369A5783B866016, p0); }
	NATIVE_DECL void DISABLE_STUNT_JUMP_SET(int p0) { invoke<Void>(0xA5272EBEDD4747F6, p0); }
	NATIVE_DECL void SET_STUNT_JUMPS_CAN_TRIGGER(BOOL toggle) { invoke<Void>(0xD79185689F8FD5DF, toggle); }
	NATIVE_DECL BOOL IS_STUNT_JUMP_IN_PROGRESS() { return invoke<BOOL>(0x7A3F19700A4D0525); }
	NATIVE_DECL BOOL IS_STUNT_JUMP_MESSAGE_SHOWING() { return invoke<BOOL>(0x2272B0A1343129F4); }
	NATIVE_DECL int GET_NUM_SUCCESSFUL_STUNT_JUMPS() { return invoke<int>(0x996DD1E1E02F1008); }
	NATIVE_DECL int GET_TOTAL_SUCCESSFUL_STUNT_JUMPS() { return invoke<int>(0x6856EC3D35C81EA4); }
	NATIVE_DECL void CANCEL_STUNT_JUMP() { invoke<Void>(0xE6B7B0ACD4E4B75E); }
	NATIVE_DECL void SET_GAME_PAUSED(BOOL toggle) { invoke<Void>(0x577D1284D6873711, toggle); }
	NATIVE_DECL void SET_THIS_SCRIPT_CAN_BE_PAUSED(BOOL toggle) { invoke<Void>(0xAA391C728106F7AF, toggle); }
	NATIVE_DECL void SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(BOOL toggle) { invoke<Void>(0xB98236CAAECEF897, toggle); }
	NATIVE_DECL BOOL HAS_CHEAT_WITH_HASH_BEEN_ACTIVATED(Hash hash, int amount) { return invoke<BOOL>(0x071E2A839DE82D90, hash, amount); }
	NATIVE_DECL BOOL HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(Hash hash) { return invoke<BOOL>(0x557E43C447E700A8, hash); }
	NATIVE_DECL void OVERRIDE_FREEZE_FLAGS(BOOL p0) { invoke<Void>(0xFA3FFB0EEBC288A3, p0); }
	NATIVE_DECL void SET_INSTANCE_PRIORITY_MODE(int p0) { invoke<Void>(0x9BAE5AD2508DF078, p0); }
	NATIVE_DECL void SET_INSTANCE_PRIORITY_HINT(int flag) { invoke<Void>(0xC5F0A8EBD3F361CE, flag); }
	NATIVE_DECL BOOL IS_FRONTEND_FADING() { return invoke<BOOL>(0x7EA2B6AF97ECA6ED); }
	NATIVE_DECL void POPULATE_NOW() { invoke<Void>(0x7472BB270D7B4F3E); }
	NATIVE_DECL int GET_INDEX_OF_CURRENT_LEVEL() { return invoke<int>(0xCBAD6729F7B1F4FC); }
	NATIVE_DECL void SET_GRAVITY_LEVEL(int level) { invoke<Void>(0x740E14FAD5842351, level); }
	NATIVE_DECL void START_SAVE_DATA(Any* p0, Any p1, BOOL p2) { invoke<Void>(0xA9575F812C6A7997, p0, p1, p2); }
	NATIVE_DECL void STOP_SAVE_DATA() { invoke<Void>(0x74E20C9145FB66FD); }
	NATIVE_DECL int GET_SIZE_OF_SAVE_DATA(BOOL p0) { return invoke<int>(0xA09F896CE912481F, p0); }
	NATIVE_DECL void REGISTER_INT_TO_SAVE(Any* p0, const char* name) { invoke<Void>(0x34C9EE5986258415, p0, name); }
	NATIVE_DECL void REGISTER_INT64_TO_SAVE(Any* p0, const char* name) { invoke<Void>(0xA735353C77334EA0, p0, name); }
	NATIVE_DECL void REGISTER_ENUM_TO_SAVE(Any* p0, const char* name) { invoke<Void>(0x10C2FA78D0E128A1, p0, name); }
	NATIVE_DECL void REGISTER_FLOAT_TO_SAVE(Any* p0, const char* name) { invoke<Void>(0x7CAEC29ECB5DFEBB, p0, name); }
	NATIVE_DECL void REGISTER_BOOL_TO_SAVE(Any* p0, const char* name) { invoke<Void>(0xC8F4131414C835A1, p0, name); }
	NATIVE_DECL void REGISTER_TEXT_LABEL_TO_SAVE(Any* p0, const char* name) { invoke<Void>(0xEDB1232C5BEAE62F, p0, name); }
	NATIVE_DECL void REGISTER_TEXT_LABEL_15_TO_SAVE(Any* p0, const char* name) { invoke<Void>(0x6F7794F28C6B2535, p0, name); }
	NATIVE_DECL void REGISTER_TEXT_LABEL_23_TO_SAVE(Any* p0, const char* name) { invoke<Void>(0x48F069265A0E4BEC, p0, name); }
	NATIVE_DECL void REGISTER_TEXT_LABEL_31_TO_SAVE(Any* p0, const char* name) { invoke<Void>(0x8269816F6CFD40F8, p0, name); }
	NATIVE_DECL void REGISTER_TEXT_LABEL_63_TO_SAVE(Any* p0, const char* name) { invoke<Void>(0xFAA457EF263E8763, p0, name); }
	NATIVE_DECL void START_SAVE_STRUCT_WITH_SIZE(Any* p0, int size, const char* structName) { invoke<Void>(0xBF737600CDDBEADD, p0, size, structName); }
	NATIVE_DECL void STOP_SAVE_STRUCT() { invoke<Void>(0xEB1774DF12BB9F12); }
	NATIVE_DECL void START_SAVE_ARRAY_WITH_SIZE(Any* p0, int size, const char* arrayName) { invoke<Void>(0x60FE567DF1B1AF9D, p0, size, arrayName); }
	NATIVE_DECL void STOP_SAVE_ARRAY() { invoke<Void>(0x04456F95153C6BE4); }
	NATIVE_DECL void COPY_SCRIPT_STRUCT(Any* dst, Any* src, int size) { invoke<Void>(0x213AEB2B90CBA7AC, dst, src, size); }
	NATIVE_DECL void ENABLE_DISPATCH_SERVICE(int dispatchService, BOOL toggle) { invoke<Void>(0xDC0F817884CDD856, dispatchService, toggle); }
	NATIVE_DECL void BLOCK_DISPATCH_SERVICE_RESOURCE_CREATION(int dispatchService, BOOL toggle) { invoke<Void>(0x9B2BD3773123EA2F, dispatchService, toggle); }
	NATIVE_DECL int GET_NUMBER_RESOURCES_ALLOCATED_TO_WANTED_LEVEL(int dispatchService) { return invoke<int>(0xEB4A0C2D56441717, dispatchService); }
	NATIVE_DECL BOOL CREATE_INCIDENT(int dispatchService, float x, float y, float z, int numUnits, float radius, int* outIncidentID, Any p7, Any p8) { return invoke<BOOL>(0x3F892CAF67444AE7, dispatchService, x, y, z, numUnits, radius, outIncidentID, p7, p8); }
	NATIVE_DECL BOOL CREATE_INCIDENT_WITH_ENTITY(int dispatchService, Ped ped, int numUnits, float radius, int* outIncidentID, Any p5, Any p6) { return invoke<BOOL>(0x05983472F0494E60, dispatchService, ped, numUnits, radius, outIncidentID, p5, p6); }
	NATIVE_DECL void DELETE_INCIDENT(int incidentId) { invoke<Void>(0x556C1AA270D5A207, incidentId); }
	NATIVE_DECL BOOL IS_INCIDENT_VALID(int incidentId) { return invoke<BOOL>(0xC8BC6461E629BEAA, incidentId); }
	NATIVE_DECL void SET_INCIDENT_REQUESTED_UNITS(int incidentId, int dispatchService, int numUnits) { invoke<Void>(0xB08B85D860E7BA3C, incidentId, dispatchService, numUnits); }
	NATIVE_DECL void SET_IDEAL_SPAWN_DISTANCE_FOR_INCIDENT(int incidentId, float p1) { invoke<Void>(0xD261BA3E7E998072, incidentId, p1); }
	NATIVE_DECL BOOL FIND_SPAWN_POINT_IN_DIRECTION(float posX, float posY, float posZ, float fwdVecX, float fwdVecY, float fwdVecZ, float distance, Vector3* spawnPoint) { return invoke<BOOL>(0x6874E2190B0C1972, posX, posY, posZ, fwdVecX, fwdVecY, fwdVecZ, distance, spawnPoint); }
	NATIVE_DECL int ADD_POP_MULTIPLIER_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float p6, float p7, BOOL p8, BOOL p9) { return invoke<int>(0x67F6413D3220E18D, x1, y1, z1, x2, y2, z2, p6, p7, p8, p9); }
	NATIVE_DECL BOOL DOES_POP_MULTIPLIER_AREA_EXIST(int id) { return invoke<BOOL>(0x1327E2FE9746BAEE, id); }
	NATIVE_DECL void REMOVE_POP_MULTIPLIER_AREA(int id, BOOL p1) { invoke<Void>(0xB129E447A2EDA4BF, id, p1); }
	NATIVE_DECL BOOL IS_POP_MULTIPLIER_AREA_NETWORKED(int id) { return invoke<BOOL>(0x1312F4B242609CE3, id); }
	NATIVE_DECL int ADD_POP_MULTIPLIER_SPHERE(float x, float y, float z, float radius, float pedMultiplier, float vehicleMultiplier, BOOL p6, BOOL p7) { return invoke<int>(0x32C7A7E8C43A1F80, x, y, z, radius, pedMultiplier, vehicleMultiplier, p6, p7); }
	NATIVE_DECL BOOL DOES_POP_MULTIPLIER_SPHERE_EXIST(int id) { return invoke<BOOL>(0x171BAFB3C60389F4, id); }
	NATIVE_DECL void REMOVE_POP_MULTIPLIER_SPHERE(int id, BOOL p1) { invoke<Void>(0xE6869BECDD8F2403, id, p1); }
	NATIVE_DECL void ENABLE_TENNIS_MODE(Ped ped, BOOL toggle, BOOL p2) { invoke<Void>(0x28A04B411933F8A6, ped, toggle, p2); }
	NATIVE_DECL BOOL IS_TENNIS_MODE(Ped ped) { return invoke<BOOL>(0x5D5479D115290C3F, ped); }
	NATIVE_DECL void PLAY_TENNIS_SWING_ANIM(Ped ped, const char* animDict, const char* animName, float p3, float p4, BOOL p5) { invoke<Void>(0xE266ED23311F24D4, ped, animDict, animName, p3, p4, p5); }
	NATIVE_DECL BOOL GET_TENNIS_SWING_ANIM_COMPLETE(Ped ped) { return invoke<BOOL>(0x17DF68D720AA77F8, ped); }
	NATIVE_DECL BOOL GET_TENNIS_SWING_ANIM_CAN_BE_INTERRUPTED(Ped ped) { return invoke<BOOL>(0x19BFED045C647C49, ped); }
	NATIVE_DECL BOOL GET_TENNIS_SWING_ANIM_SWUNG(Ped ped) { return invoke<BOOL>(0xE95B0C7D5BA3B96B, ped); }
	NATIVE_DECL void PLAY_TENNIS_DIVE_ANIM(Ped ped, int p1, float p2, float p3, float p4, BOOL p5) { invoke<Void>(0x8FA9C42FC5D7C64B, ped, p1, p2, p3, p4, p5); }
	NATIVE_DECL void SET_TENNIS_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, const char* p1, float p2) { invoke<Void>(0x54F157E0336A3822, ped, p1, p2); }
	NATIVE_DECL void RESET_DISPATCH_SPAWN_LOCATION() { invoke<Void>(0x5896F2BD5683A4E1); }
	NATIVE_DECL void SET_DISPATCH_SPAWN_LOCATION(float x, float y, float z) { invoke<Void>(0xD10F442036302D50, x, y, z); }
	NATIVE_DECL void RESET_DISPATCH_IDEAL_SPAWN_DISTANCE() { invoke<Void>(0x77A84429DD9F0A15); }
	NATIVE_DECL void SET_DISPATCH_IDEAL_SPAWN_DISTANCE(float distance) { invoke<Void>(0x6FE601A64180D423, distance); }
	NATIVE_DECL void RESET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(Any p0) { invoke<Void>(0xEB2DB0CAD13154B3, p0); }
	NATIVE_DECL void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(Any p0, float p1) { invoke<Void>(0x44F7CBC1BEB3327D, p0, p1); }
	NATIVE_DECL void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(Any p0, float p1) { invoke<Void>(0x48838ED9937A15D1, p0, p1); }
	NATIVE_DECL int ADD_DISPATCH_SPAWN_ANGLED_BLOCKING_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width) { return invoke<int>(0x918C7B2D2FF3928B, x1, y1, z1, x2, y2, z2, width); }
	NATIVE_DECL int ADD_DISPATCH_SPAWN_SPHERE_BLOCKING_AREA(float x1, float y1, float x2, float y2) { return invoke<int>(0x2D4259F1FEB81DA9, x1, y1, x2, y2); }
	NATIVE_DECL void REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(int p0) { invoke<Void>(0x264AC28B01B353A5, p0); }
	NATIVE_DECL void RESET_DISPATCH_SPAWN_BLOCKING_AREAS() { invoke<Void>(0xAC7BFD5C1D83EA75); }
	NATIVE_DECL void RESET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN() { invoke<Void>(0xD9F692D349249528); }
	NATIVE_DECL void SET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN(int p0, int p1) { invoke<Void>(0xE532EC1A63231B4F, p0, p1); }
	NATIVE_DECL void ADD_TACTICAL_NAV_MESH_POINT(float x, float y, float z) { invoke<Void>(0xB8721407EE9C3FF6, x, y, z); }
	NATIVE_DECL void CLEAR_TACTICAL_NAV_MESH_POINTS() { invoke<Void>(0xB3CD58CCA6CDA852); }
	NATIVE_DECL void SET_RIOT_MODE_ENABLED(BOOL toggle) { invoke<Void>(0x2587A48BC88DFADF, toggle); }
	NATIVE_DECL void DISPLAY_ONSCREEN_KEYBOARD_WITH_LONGER_INITIAL_STRING(int p0, const char* windowTitle, Any* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, const char* defaultConcat4, const char* defaultConcat5, const char* defaultConcat6, const char* defaultConcat7, int maxInputLength) { invoke<Void>(0xCA78CFA0366592FE, p0, windowTitle, p2, defaultText, defaultConcat1, defaultConcat2, defaultConcat3, defaultConcat4, defaultConcat5, defaultConcat6, defaultConcat7, maxInputLength); }
	NATIVE_DECL void DISPLAY_ONSCREEN_KEYBOARD(int p0, const char* windowTitle, const char* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, int maxInputLength) { invoke<Void>(0x00DC833F2568DBF6, p0, windowTitle, p2, defaultText, defaultConcat1, defaultConcat2, defaultConcat3, maxInputLength); }
	NATIVE_DECL int UPDATE_ONSCREEN_KEYBOARD() { return invoke<int>(0x0CF2B696BBF945AE); }
	NATIVE_DECL const char* GET_ONSCREEN_KEYBOARD_RESULT() { return invoke<const char*>(0x8362B09B91893647); }
	NATIVE_DECL void CANCEL_ONSCREEN_KEYBOARD() { invoke<Void>(0x58A39BE597CE99CD); }
	NATIVE_DECL void NEXT_ONSCREEN_KEYBOARD_RESULT_WILL_DISPLAY_USING_THESE_FONTS(int p0) { invoke<Void>(0x3ED1438C1F5C6612, p0); }
	NATIVE_DECL void ACTION_MANAGER_ENABLE_ACTION(Hash hash, BOOL enable) { invoke<Void>(0xA6A12939F16D85BE, hash, enable); }
	NATIVE_DECL int GET_REAL_WORLD_TIME() { return invoke<int>(0x3F60413F5DF65748); }
	NATIVE_DECL void SUPRESS_RANDOM_EVENT_THIS_FRAME(int eventType, BOOL suppress) { invoke<Void>(0x1EAE0A6E978894A2, eventType, suppress); }
	NATIVE_DECL void SET_EXPLOSIVE_AMMO_THIS_FRAME(Player player) { invoke<Void>(0xA66C71C98D5F2CFB, player); }
	NATIVE_DECL void SET_FIRE_AMMO_THIS_FRAME(Player player) { invoke<Void>(0x11879CDD803D30F4, player); }
	NATIVE_DECL void SET_EXPLOSIVE_MELEE_THIS_FRAME(Player player) { invoke<Void>(0xFF1BED81BFDC0FE0, player); }
	NATIVE_DECL void SET_SUPER_JUMP_THIS_FRAME(Player player) { invoke<Void>(0x57FFF03E423A4C0B, player); }
	NATIVE_DECL void SET_BEAST_JUMP_THIS_FRAME(Player player) { invoke<Void>(0x438822C279B73B93, player); }
	NATIVE_DECL void SET_FORCED_JUMP_THIS_FRAME(Player player) { invoke<Void>(0xA1183BCFEE0F93D1, player); }
	NATIVE_DECL BOOL HAS_GAME_INSTALLED_THIS_SESSION() { return invoke<BOOL>(0x6FDDF453C0C756EC); }
	NATIVE_DECL void SET_TICKER_JOHNMARSTON_IS_DONE() { invoke<Void>(0xFB00CA71DA386228); }
	NATIVE_DECL BOOL ARE_PROFILE_SETTINGS_VALID() { return invoke<BOOL>(0x5AA3BEFA29F03AD4); }
	NATIVE_DECL void PREVENT_ARREST_STATE_THIS_FRAME() { invoke<Void>(0xE3D969D2785FFB5E); }
	NATIVE_DECL void FORCE_GAME_STATE_PLAYING() { invoke<Void>(0xC0AA53F866B3134D); }
	NATIVE_DECL void SCRIPT_RACE_INIT(int p0, int p1, Any p2, Any p3) { invoke<Void>(0x0A60017F841A54F2, p0, p1, p2, p3); }
	NATIVE_DECL void SCRIPT_RACE_SHUTDOWN() { invoke<Void>(0x1FF6BF9A63E5757F); }
	NATIVE_DECL void SCRIPT_RACE_PLAYER_HIT_CHECKPOINT(Player player, Any p1, Any p2, Any p3) { invoke<Void>(0x1BB299305C3E8C13, player, p1, p2, p3); }
	NATIVE_DECL BOOL SCRIPT_RACE_GET_PLAYER_SPLIT_TIME(Player player, int* p1, int* p2) { return invoke<BOOL>(0x8EF5573A1F801A5C, player, p1, p2); }
	NATIVE_DECL void START_END_USER_BENCHMARK() { invoke<Void>(0x92790862E36C2ADA); }
	NATIVE_DECL void STOP_END_USER_BENCHMARK() { invoke<Void>(0xC7DB36C24634F52B); }
	NATIVE_DECL void RESET_END_USER_BENCHMARK() { invoke<Void>(0x437138B6A830166A); }
	NATIVE_DECL void SAVE_END_USER_BENCHMARK() { invoke<Void>(0x37DEB0AA183FB6D8); }
	NATIVE_DECL BOOL UI_STARTED_END_USER_BENCHMARK() { return invoke<BOOL>(0xEA2F2061875EED90); }
	NATIVE_DECL BOOL LANDING_SCREEN_STARTED_END_USER_BENCHMARK() { return invoke<BOOL>(0x3BBBD13E5041A79E); }
	NATIVE_DECL BOOL IS_COMMANDLINE_END_USER_BENCHMARK() { return invoke<BOOL>(0xA049A5BE0F04F2F8); }
	NATIVE_DECL int GET_BENCHMARK_ITERATIONS() { return invoke<int>(0x4750FC27570311EC); }
	NATIVE_DECL int GET_BENCHMARK_PASS() { return invoke<int>(0x1B2366C3F2A5C8DF); }
	NATIVE_DECL void RESTART_GAME() { invoke<Void>(0xE574A662ACAEFBB1); }
	NATIVE_DECL void QUIT_GAME() { invoke<Void>(0xEB6891F03362FB12); }
	NATIVE_DECL BOOL HAS_ASYNC_INSTALL_FINISHED() { return invoke<BOOL>(0x14832BF2ABA53FC5); }
	NATIVE_DECL void CLEANUP_ASYNC_INSTALL() { invoke<Void>(0xC79AE21974B01FB2); }
	NATIVE_DECL BOOL PLM_IS_IN_CONSTRAINED_MODE() { return invoke<BOOL>(0x684A41975F077262); }
	NATIVE_DECL int PLM_GET_CONSTRAINED_DURATION_MS() { return invoke<int>(0xABB2FA71C83A1B72); }
	NATIVE_DECL void SET_PLAYER_IS_IN_ANIMAL_FORM(BOOL toggle) { invoke<Void>(0x4EBB7E87AA0DBED4, toggle); }
	NATIVE_DECL BOOL GET_IS_PLAYER_IN_ANIMAL_FORM() { return invoke<BOOL>(0x9689123E3F213AA5); }
	NATIVE_DECL void SET_PLAYER_IS_REPEATING_A_MISSION(BOOL toggle) { invoke<Void>(0x9D8D44ADBBA61EF2, toggle); }
	NATIVE_DECL void DISABLE_SCREEN_DIMMING_THIS_FRAME() { invoke<Void>(0x23227DF0B2115469); }
	NATIVE_DECL float GET_CITY_DENSITY() { return invoke<float>(0xD10282B6E3751BA0); }
	NATIVE_DECL void USE_ACTIVE_CAMERA_FOR_TIMESLICING_CENTRE() { invoke<Void>(0x693478ACBD7F18E7); }
	NATIVE_DECL void SET_CONTENT_ID_INDEX(Hash contentId, int index) { invoke<Void>(0x4B82FA6F2D624634, contentId, index); }
	NATIVE_DECL int GET_CONTENT_ID_INDEX(Hash contentId) { return invoke<int>(0xECF041186C5A94DC, contentId); }
	NATIVE_DECL void _SET_CONTENT_PROP_TYPE(Hash model, int type) { invoke<Void>(0xBA4583AF4C678A9B, model, type); }
	NATIVE_DECL int _GET_CONTENT_PROP_TYPE(Hash model) { return invoke<int>(0x8BAF8AD59F47AAFC, model); }
}

namespace MONEY
{
	NATIVE_DECL void NETWORK_INITIALIZE_CASH(int wallet, int bank) { invoke<Void>(0x3DA5ECD1A56CBA6D, wallet, bank); }
	NATIVE_DECL void NETWORK_DELETE_CHARACTER(int characterSlot, BOOL p1, BOOL p2) { invoke<Void>(0x05A50AF38947EB8D, characterSlot, p1, p2); }
	NATIVE_DECL void NETWORK_MANUAL_DELETE_CHARACTER(int characterSlot) { invoke<Void>(0x821418C727FCACD7, characterSlot); }
	NATIVE_DECL BOOL NETWORK_GET_PLAYER_IS_HIGH_EARNER() { return invoke<BOOL>(0xFB2456B2040A6A67); }
	NATIVE_DECL void NETWORK_CLEAR_CHARACTER_WALLET(int characterSlot) { invoke<Void>(0xA921DED15FDF28F5, characterSlot); }
	NATIVE_DECL void NETWORK_GIVE_PLAYER_JOBSHARE_CASH(int amount, Any* gamerHandle) { invoke<Void>(0xFB18DF9CB95E0105, amount, gamerHandle); }
	NATIVE_DECL void NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH(int value, Any* gamerHandle) { invoke<Void>(0x56A3B51944C50598, value, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CAN_SHARE_JOB_CASH() { return invoke<BOOL>(0x1C2473301B1C66BA); }
	NATIVE_DECL void NETWORK_REFUND_CASH(int index, const char* context, const char* reason, BOOL p3) { invoke<Void>(0xF9C812CD7C46E817, index, context, reason, p3); }
	NATIVE_DECL void NETWORK_DEDUCT_CASH(int amount, const char* p1, const char* p2, BOOL p3, BOOL p4, BOOL p5) { invoke<Void>(0x18B7AE224B087E26, amount, p1, p2, p3, p4, p5); }
	NATIVE_DECL BOOL NETWORK_MONEY_CAN_BET(int amount, BOOL p1, BOOL p2) { return invoke<BOOL>(0x81404F3DC124FE5B, amount, p1, p2); }
	NATIVE_DECL BOOL NETWORK_CAN_BET(int amount) { return invoke<BOOL>(0x3A54E33660DED67F, amount); }
	NATIVE_DECL BOOL NETWORK_CASINO_CAN_BET(Hash hash) { return invoke<BOOL>(0x158C16F5E4CF41F8, hash); }
	NATIVE_DECL BOOL NETWORK_CASINO_CAN_BET_PVC() { return invoke<BOOL>(0x394DCDB9E836B7A9); }
	NATIVE_DECL BOOL NETWORK_CASINO_CAN_BET_AMOUNT(Any p0) { return invoke<BOOL>(0xF62F6D9528358FE4, p0); }
	NATIVE_DECL BOOL NETWORK_CASINO_CAN_BUY_CHIPS_PVC() { return invoke<BOOL>(0x8968D4D8C6C40C11); }
	NATIVE_DECL BOOL NETWORK_CASINO_BUY_CHIPS(int p0, int p1) { return invoke<BOOL>(0x3BD101471C7F9EEC, p0, p1); }
	NATIVE_DECL BOOL NETWORK_CASINO_SELL_CHIPS(int p0, int p1) { return invoke<BOOL>(0xED44897CB336F480, p0, p1); }
	NATIVE_DECL void NETWORK_DEFER_CASH_TRANSACTIONS_UNTIL_SHOP_SAVE() { invoke<Void>(0xCD0F5B5D932AE473); }
	NATIVE_DECL BOOL CAN_PAY_AMOUNT_TO_BOSS(int p0, int p1, int amount, int* p3) { return invoke<BOOL>(0x9777734DAD16992F, p0, p1, amount, p3); }
	NATIVE_DECL void NETWORK_EARN_FROM_PICKUP(int amount) { invoke<Void>(0xED1517D3AF17C698, amount); }
	NATIVE_DECL void NETWORK_EARN_FROM_CASHING_OUT(int amount) { invoke<Void>(0x718FBBF67414FA36, amount); }
	NATIVE_DECL void NETWORK_EARN_FROM_GANGATTACK_PICKUP(int amount) { invoke<Void>(0xA03D4ACE0A3284CE, amount); }
	NATIVE_DECL void NETWORK_EARN_ASSASSINATE_TARGET_KILLED(int amount) { invoke<Void>(0xFA700D8A9905F78A, amount); }
	NATIVE_DECL void NETWORK_EARN_FROM_ROB_ARMORED_CARS(int amount) { invoke<Void>(0xF514621E8EA463D0, amount); }
	NATIVE_DECL void NETWORK_EARN_FROM_CRATE_DROP(int amount) { invoke<Void>(0xB1CC1B9EC3007A2A, amount); }
	NATIVE_DECL void NETWORK_EARN_FROM_BETTING(int amount, const char* p1) { invoke<Void>(0x827A5BA1A44ACA6D, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_FROM_JOB(int amount, const char* p1) { invoke<Void>(0xB2CC4836834E8A98, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_FROM_JOBX2(int amount, const char* p1) { invoke<Void>(0xDEBBF584665411D0, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_FROM_PREMIUM_JOB(int amount, const char* p1) { invoke<Void>(0xC8407624CEF2354B, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_FROM_BEND_JOB(int amount, const char* heistHash) { invoke<Void>(0x61326EE6DF15B0CA, amount, heistHash); }
	NATIVE_DECL void NETWORK_EARN_FROM_CHALLENGE_WIN(Any p0, Any* p1, BOOL p2) { invoke<Void>(0x2B171E6B2F64D8DF, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_FROM_BOUNTY(int amount, Any* gamerHandle, Any* p2, Any p3) { invoke<Void>(0x131BB5DA15453ACF, amount, gamerHandle, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_FROM_IMPORT_EXPORT(int amount, Hash modelHash) { invoke<Void>(0xF92A014A634442D6, amount, modelHash); }
	NATIVE_DECL void NETWORK_EARN_FROM_HOLDUPS(int amount) { invoke<Void>(0x45B8154E077D9E4D, amount); }
	NATIVE_DECL void NETWORK_EARN_FROM_PROPERTY(int amount, Hash propertyName) { invoke<Void>(0x849648349D77F5C5, amount, propertyName); }
	NATIVE_DECL void NETWORK_EARN_FROM_AI_TARGET_KILL(Any p0, Any p1) { invoke<Void>(0x515B4A22E4D3C6D7, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_FROM_NOT_BADSPORT(int amount) { invoke<Void>(0x4337511FA8221D36, amount); }
	NATIVE_DECL void NETWORK_EARN_FROM_VEHICLE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xB539BD8A4C1EECF8, p0, p1, p2, p3, p4, p5, p6, p7); }
	NATIVE_DECL void NETWORK_EARN_FROM_PERSONAL_VEHICLE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x3F4D00167E41E0AD, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL void NETWORK_EARN_FROM_DAILY_OBJECTIVES(int amount, const char* type, int characterSlot) { invoke<Void>(0x6EA318C91C1A8786, amount, type, characterSlot); }
	NATIVE_DECL void NETWORK_EARN_FROM_AMBIENT_JOB(int p0, const char* p1, Any* p2) { invoke<Void>(0xFB6DB092FBAE29E6, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_FROM_JOB_BONUS(Any p0, Any* p1, Any* p2) { invoke<Void>(0x6816FB4416760775, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_FROM_CRIMINAL_MASTERMIND(Any p0, Any p1, Any p2) { invoke<Void>(0xFA009A62990671D4, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_HEIST_AWARD(Any p0, Any p1, Any p2) { invoke<Void>(0x9D4FDBB035229669, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_FIRST_TIME_BONUS(Any p0, Any p1, Any p2) { invoke<Void>(0x11B0A20C493F7E36, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_GOON(Any p0, Any p1, Any p2) { invoke<Void>(0xCDA1C62BE2777802, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_BOSS(Any p0, Any p1, Any p2) { invoke<Void>(0x08B0CA7A6AB3AC32, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_AGENCY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0CB1BE0633C024A8, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_FROM_WAREHOUSE(int amount, int id) { invoke<Void>(0x3E4ADAFF1830F146, amount, id); }
	NATIVE_DECL void NETWORK_EARN_FROM_CONTRABAND(int amount, Any p1) { invoke<Void>(0xECA658CE2A4E5A72, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_FROM_DESTROYING_CONTRABAND(Any p0, Any p1, Any p2) { invoke<Void>(0x84C0116D012E8FC2, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_FROM_SMUGGLER_WORK(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x6B7E4FB50D5F3D65, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL void NETWORK_EARN_FROM_HANGAR_TRADE(Any p0, Any p1) { invoke<Void>(0x31BA138F6304FB9F, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_PURCHASE_CLUB_HOUSE(Any p0, Any p1) { invoke<Void>(0x55A1E095DB052FA5, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_FROM_BUSINESS_PRODUCT(int amount, Any p1, Any p2, Any p3) { invoke<Void>(0x8586789730B10CAF, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_FROM_VEHICLE_EXPORT(int amount, Any p1, Any p2) { invoke<Void>(0xEDEAD9A91EC768B3, amount, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_SMUGGLER_AGENCY(int amount, Any p1, Any p2, Any p3) { invoke<Void>(0xDEE612F2D71B0308, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_BOUNTY_HUNTER_REWARD(Any p0) { invoke<Void>(0xF6B170F9A02E9E87, p0); }
	NATIVE_DECL void NETWORK_EARN_FROM_BUSINESS_BATTLE(Any p0) { invoke<Void>(0x42FCE14F50F27291, p0); }
	NATIVE_DECL void NETWORK_EARN_FROM_CLUB_MANAGEMENT_PARTICIPATION(Any p0, int p1) { invoke<Void>(0xA75EAC69F59E96E7, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_FROM_FMBB_PHONECALL_MISSION(Any p0) { invoke<Void>(0xC5156361F26E2212, p0); }
	NATIVE_DECL void NETWORK_EARN_FROM_BUSINESS_HUB_SELL(Any p0, Any p1, Any p2) { invoke<Void>(0x0B39CF0D53F1C883, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_FROM_FMBB_BOSS_WORK(Any p0) { invoke<Void>(0x1FDA0AA679C9919B, p0); }
	NATIVE_DECL void NETWORK_EARN_FMBB_WAGE_BONUS(Any p0) { invoke<Void>(0xFFFBA1B1F7C0B6F4, p0); }
	NATIVE_DECL BOOL NETWORK_CAN_SPEND_MONEY(Any p0, BOOL p1, BOOL p2, BOOL p3, Any p4, Any p5) { return invoke<BOOL>(0xAB3CAA6B422164DA, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL BOOL NETWORK_CAN_SPEND_MONEY2(Any p0, BOOL p1, BOOL p2, BOOL p3, Any* p4, Any p5, Any p6) { return invoke<BOOL>(0x7303E27CC6532080, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void NETWORK_BUY_ITEM(int amount, Hash item, Any p2, Any p3, BOOL p4, const char* item_name, Any p6, Any p7, Any p8, BOOL p9) { invoke<Void>(0xF0077C797F66A355, amount, item, p2, p3, p4, item_name, p6, p7, p8, p9); }
	NATIVE_DECL void NETWORK_SPENT_TAXI(int amount, BOOL p1, BOOL p2, Any p3, Any p4) { invoke<Void>(0x17C3A7D31EAE39F9, amount, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_PAY_EMPLOYEE_WAGE(Any p0, BOOL p1, BOOL p2) { invoke<Void>(0x5FD5ED82CBBE9989, p0, p1, p2); }
	NATIVE_DECL void NETWORK_PAY_MATCH_ENTRY_FEE(int amount, const char* matchId, BOOL p2, BOOL p3) { invoke<Void>(0x9346E14F2AF74D46, amount, matchId, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_BETTING(int amount, int p1, const char* matchId, BOOL p3, BOOL p4) { invoke<Void>(0x1C436FD11FFA692F, amount, p1, matchId, p3, p4); }
	NATIVE_DECL void NETWORK_SPENT_WAGER(Any p0, Any p1, int amount) { invoke<Void>(0xD99DB210089617FE, p0, p1, amount); }
	NATIVE_DECL void NETWORK_SPENT_IN_STRIPCLUB(Any p0, BOOL p1, Any p2, BOOL p3) { invoke<Void>(0xEE99784E4467689C, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_BUY_HEALTHCARE(int cost, BOOL p1, BOOL p2) { invoke<Void>(0xD9B067E55253E3DD, cost, p1, p2); }
	NATIVE_DECL void NETWORK_BUY_AIRSTRIKE(int cost, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x763B4BD305338F19, cost, p1, p2, p3); }
	NATIVE_DECL void NETWORK_BUY_BACKUP_GANG(int p0, int p1, BOOL p2, BOOL p3, int npcProvider) { invoke<Void>(0xA3EDDAA42411D3B9, p0, p1, p2, p3, npcProvider); }
	NATIVE_DECL void NETWORK_BUY_HELI_STRIKE(int cost, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x81AA4610E3FD3A69, cost, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_AMMO_DROP(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0xB162DC95C0A3317B, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_BUY_BOUNTY(int amount, Player victim, BOOL p2, BOOL p3, Any p4) { invoke<Void>(0x7B718E197453F2D9, amount, victim, p2, p3, p4); }
	NATIVE_DECL void NETWORK_BUY_PROPERTY(int cost, Hash propertyName, BOOL p2, BOOL p3) { invoke<Void>(0x650A08A280870AF6, cost, propertyName, p2, p3); }
	NATIVE_DECL void NETWORK_BUY_SMOKES(int p0, BOOL p1, BOOL p2) { invoke<Void>(0x75AF80E61248EEBD, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_HELI_PICKUP(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x7BF1D73DB2ECA492, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_BOAT_PICKUP(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x524EE43A37232C00, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_BULL_SHARK(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0xA6DD8458CE24012C, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_CASH_DROP(int amount, BOOL p1, BOOL p2) { invoke<Void>(0x289016EC778D60E0, amount, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_HIRE_MUGGER(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0xE404BFB981665BF0, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_ROBBED_BY_MUGGER(int amount, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x995A65F15F581359, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_HIRE_MERCENARY(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0xE7B80E2BF9D80BD6, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_BUY_WANTEDLEVEL(Any p0, Any* p1, BOOL p2, BOOL p3, Any p4) { invoke<Void>(0xE1B13771A843C4F6, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPENT_BUY_OFFTHERADAR(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0xA628A745E2275C5D, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_BUY_REVEAL_PLAYERS(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x6E176F1B18BC0637, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_CARWASH(Any p0, Any p1, Any p2, BOOL p3, BOOL p4) { invoke<Void>(0xEC03C719DB2F4306, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPENT_CINEMA(Any p0, Any p1, BOOL p2, BOOL p3) { invoke<Void>(0x6B38ECB05A63A685, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_TELESCOPE(Any p0, BOOL p1, BOOL p2) { invoke<Void>(0x7FE61782AD94CC09, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_HOLDUPS(Any p0, BOOL p1, BOOL p2) { invoke<Void>(0xD9B86B9872039763, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_BUY_PASSIVE_MODE(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x6D3A430D1A809179, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_BANK_INTEREST(int p0, BOOL p1, BOOL p2) { invoke<Void>(0xCA230C9682556CF1, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_PROSTITUTES(Any p0, BOOL p1, BOOL p2) { invoke<Void>(0xB21B89501CFAC79E, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_ARREST_BAIL(Any p0, BOOL p1, BOOL p2) { invoke<Void>(0x812F5488B1B2A299, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM(int amount, Hash vehicleModel, Any* gamerHandle, BOOL notBankrupt, BOOL hasTheMoney) { invoke<Void>(0x9FF28D88C766E3E8, amount, vehicleModel, gamerHandle, notBankrupt, hasTheMoney); }
	NATIVE_DECL void NETWORK_SPENT_CALL_PLAYER(Any p0, Any* p1, BOOL p2, BOOL p3) { invoke<Void>(0xACDE7185B374177C, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_BOUNTY(Any p0, BOOL p1, BOOL p2) { invoke<Void>(0x29B260B84947DFCC, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_FROM_ROCKSTAR(int p0, BOOL p1, BOOL p2) { invoke<Void>(0x6A445B64ED7ABEB5, p0, p1, p2); }
	NATIVE_DECL int NETWORK_SPEND_EARNED_FROM_BANK_AND_WALLETS(int amount) { return invoke<int>(0x9B5016A6433A68C5, amount); }
	NATIVE_DECL const char* PROCESS_CASH_GIFT(int* p0, int* p1, const char* p2) { return invoke<const char*>(0x20194D48EAEC9A41, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_MOVE_SUBMARINE(Any p0, Any p1, Any p2) { invoke<Void>(0xCD4D66B43B1DD28D, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_PLAYER_HEALTHCARE(int p0, int p1, BOOL p2, BOOL p3) { invoke<Void>(0x7C99101F7FCE2EE5, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_NO_COPS(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0xD5BB406F4E04019F, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_CARGO_SOURCING(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x948705F6F9C50824, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void NETWORK_SPENT_REQUEST_JOB(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x8204DA7934DF3155, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_REQUEST_HEIST(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x9D26502BB97BFE62, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_BUY_FAIRGROUND_RIDE(int amount, Any p1, BOOL p2, BOOL p3, Any p4) { invoke<Void>(0x8A7B3952DD64D2B5, amount, p1, p2, p3, p4); }
	NATIVE_DECL BOOL NETWORK_ECONOMY_HAS_FIXED_CRAZY_NUMBERS() { return invoke<BOOL>(0x7C4FCCD2E4DEB394); }
	NATIVE_DECL void NETWORK_SPENT_JOB_SKIP(int amount, const char* matchId, BOOL p2, BOOL p3) { invoke<Void>(0x28F174A67B8D0C2F, amount, matchId, p2, p3); }
	NATIVE_DECL BOOL NETWORK_SPENT_BOSS_GOON(int amount, BOOL p1, BOOL p2) { return invoke<BOOL>(0xFFBE02CD385356BD, amount, p1, p2); }
	NATIVE_DECL void NETWORK_SPEND_GOON(int p0, int p1, int amount) { invoke<Void>(0x08A1B82B91900682, p0, p1, amount); }
	NATIVE_DECL void NETWORK_SPEND_BOSS(Any p0, Any p1, Any p2) { invoke<Void>(0xDBC966A01C02BCA7, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_MOVE_YACHT(int amount, BOOL p1, BOOL p2) { invoke<Void>(0xE7DF4E0545DFB56E, amount, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_RENAME_ORGANIZATION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xFC4EE00A7B3BFB76, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_BUY_CONTRABAND_MISSION(int p0, int p1, Hash p2, BOOL p3, BOOL p4) { invoke<Void>(0x30FD873ECE50E9F6, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPENT_PA_SERVICE_HELI(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x112209CE0290C03A, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_PA_SERVICE_VEHICLE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xED5FD7AF10F5E262, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_PA_SERVICE_SNACK(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0D30EB83668E63C5, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_PA_SERVICE_DANCER(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xB49ECA122467D05F, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_PA_SERVICE_IMPOUND(Any p0, Any p1, Any p2) { invoke<Void>(0xE23ADC6FCB1F29AE, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_PA_HELI_PICKUP(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0FE8E1FCD2B86B33, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_PURCHASE_OFFICE_PROPERTY(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x69EF772B192614C1, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_OFFICE_PROPERTY(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x8E243837643D9583, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPENT_PURCHASE_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xBD0EFB25CCA8F97A, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xA95F667A755725DA, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_PURCHASE_IMPEXP_WAREHOUSE_PROPERTY(int amount, Any* data, BOOL p2, BOOL p3) { invoke<Void>(0x33981D6804E62F49, amount, data, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_IMPEXP_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x4128464231E3CA0B, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_TRADE_IMPEXP_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x2FAB6614CE22E196, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_ORDER_WAREHOUSE_VEHICLE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x05F04155A226FBBF, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_ORDER_BODYGUARD_VEHICLE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xE8B0B270B6E7C76E, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_JUKEBOX(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x5BCDE0F640C773D2, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_PURCHASE_CLUB_HOUSE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x998E18CEB44487FC, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_CLUB_HOUSE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xFA07759E6FDDD7CF, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_PURCHASE_BUSINESS_PROPERTY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6FD97159FE3C971A, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_BUSINESS_PROPERTY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x675D19C6067CAE08, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_TRADE_BUSINESS_PROPERTY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xA51B086B0B2C0F7A, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_MC_ABILITY(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xD7CCCBA28C4ECAF0, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPENT_PAY_BUSINESS_SUPPLIES(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0035BB914316F1E3, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_CHANGE_APPEARANCE(Any p0, Any p1, Any p2) { invoke<Void>(0x5F456788B05FAEAC, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_VEHICLE_EXPORT_MODS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xA75CCF58A60A5FD1, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	NATIVE_DECL void NETWORK_SPENT_PURCHASE_OFFICE_GARAGE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xB4C2EC463672474E, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_OFFICE_GARAGE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x2AFC2D19B50797F2, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_IMPORT_EXPORT_REPAIR(Any p0, Any p1, Any p2) { invoke<Void>(0xC1952F3773BA18FE, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_PURCHASE_HANGAR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCCB339CC970452DA, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_HANGAR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x615EB504B0788DAF, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_HANGAR_UTILITY_CHARGES(int amount, BOOL p1, BOOL p2) { invoke<Void>(0xB18AC2ECBB15CB6A, amount, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_HANGAR_STAFF_CHARGES(int amount, BOOL p1, BOOL p2) { invoke<Void>(0xB1F1346FD57685D7, amount, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_BUY_TRUCK(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xAC272C0AE01B4BD8, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_TRUCK(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x365E877C61D6988B, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_BUY_BUNKER(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x12D148D26538D0F9, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPRADE_BUNKER(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0C82D21A77C22D49, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_FROM_SELL_BUNKER(int amount, Hash bunkerHash) { invoke<Void>(0x9251B6ABF2D0A5B4, amount, bunkerHash); }
	NATIVE_DECL void NETWORK_SPENT_BALLISTIC_EQUIPMENT(int amount, BOOL p1, BOOL p2) { invoke<Void>(0x5D97630A8A0EF123, amount, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_RDR_BONUS(int amount, Any p1) { invoke<Void>(0x7A5349B773584675, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_WAGE_PAYMENT(int amount, Any p1) { invoke<Void>(0x35F8DA0E8A31EF1B, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_WAGE_PAYMENT_BONUS(int amount) { invoke<Void>(0x005ACA7100BD101D, amount); }
	NATIVE_DECL void NETWORK_SPENT_BUY_BASE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x4EA3F425C7744D21, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_BASE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x3DD3F33A5D55EA6F, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_BUY_TILTROTOR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0CCE73BC7A11E885, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_TILTROTOR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x165E135D6DFA2907, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_EMPLOY_ASSASSINS(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x5BBBD92186E1F1C5, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_GANGOPS_CANNON(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x771ADB0E7635B7BF, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_GANGOPS_SKIP_MISSION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xDA947AE8880D5C18, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_CASINO_HEIST_SKIP_MISSION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x487009DD91D93429, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_SELL_BASE(int amount, Hash baseNameHash) { invoke<Void>(0x0E1E2FF3F4EC11AA, amount, baseNameHash); }
	NATIVE_DECL void NETWORK_EARN_TARGET_REFUND(int amount, int p1) { invoke<Void>(0x5B669CF2299A271F, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_GANGOPS_WAGES(int amount, int p1) { invoke<Void>(0x2DCB19ABAB0380A8, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_GANGOPS_WAGES_BONUS(int amount, int p1) { invoke<Void>(0x15BB2A5C757EB91F, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_DAR_CHALLENGE(int amount, Any p1) { invoke<Void>(0xCAC672087B4A24AB, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_DOOMSDAY_FINALE_BONUS(int amount, Hash vehicleHash) { invoke<Void>(0x128A747F4A230952, amount, vehicleHash); }
	NATIVE_DECL void NETWORK_EARN_GANGOPS_AWARD(int amount, const char* p1, Any p2) { invoke<Void>(0xA9A31475F530DFDA, amount, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_GANGOPS_ELITE(int amount, const char* p1, int actIndex) { invoke<Void>(0x2597A0D4A4FC2C77, amount, p1, actIndex); }
	NATIVE_DECL void NETWORK_SERVICE_EARN_GANGOPS_RIVAL_DELIVERY(int earnedMoney) { invoke<Void>(0x1B882107C23A9022, earnedMoney); }
	NATIVE_DECL void NETWORK_SPEND_GANGOPS_START_STRAND(int type, int amount, BOOL p2, BOOL p3) { invoke<Void>(0xA19EC0786E326E06, type, amount, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_GANGOPS_TRIP_SKIP(int amount, BOOL p1, BOOL p2) { invoke<Void>(0x5ECE6FD7B4EC8D6A, amount, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_GANGOPS_PREP_PARTICIPATION(int amount) { invoke<Void>(0xED26584F6BDCBBFD, amount); }
	NATIVE_DECL void NETWORK_EARN_GANGOPS_SETUP(int amount, const char* p1) { invoke<Void>(0xA9160796D47A2CF8, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_GANGOPS_FINALE(int amount, const char* p1) { invoke<Void>(0x1C121FC9545E0D52, amount, p1); }
	NATIVE_DECL void NETWORK_SPEND_GANGOPS_REPAIR_COST(Any p0, Any p1, Any p2) { invoke<Void>(0x2A7CEC72C3443BCC, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_NIGHTCLUB(Any p0, Any p1) { invoke<Void>(0xE0F82D68C7039158, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_NIGHTCLUB_DANCING(Any p0) { invoke<Void>(0xB4DEAE67F35E2ACD, p0); }
	NATIVE_DECL void NETWORK_EARN_BB_EVENT_BONUS(int amount) { invoke<Void>(0xFDD8D2440DAF1590, amount); }
	NATIVE_DECL void NETWORK_SPENT_PURCHASE_HACKER_TRUCK(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x2A93C46AAB1EACC9, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_HACKER_TRUCK(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x226C284C830D0CA8, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_HACKER_TRUCK(Any p0, int amount, Any p2, Any p3) { invoke<Void>(0xE8815FE993896AD3, p0, amount, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_PURCHASE_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xED76D195E6E3BF7F, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_UPGRADE_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x1DC9B749E7AE282B, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xC6E74CF8C884C880, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void NETWORK_SPEND_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x65482BFD0923C8A1, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_RDR_HATCHET_BONUS(int amount, BOOL p1, BOOL p2) { invoke<Void>(0xE284D46FFDB82E36, amount, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_NIGHTCLUB_ENTRY_FEE(Player player, int amount, Any p1, BOOL p2, BOOL p3) { invoke<Void>(0x876056684281655D, player, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_NIGHTCLUB_BAR_DRINK(int amount, Any p1, BOOL p2, BOOL p3) { invoke<Void>(0xDD21B016E4289465, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_BOUNTY_HUNTER_MISSION(int amount, BOOL p1, BOOL p2) { invoke<Void>(0x1BEA0CD93470BB1F, amount, p1, p2); }
	NATIVE_DECL void NETWORK_SPENT_REHIRE_DJ(int amount, Any p1, BOOL p2, BOOL p3) { invoke<Void>(0xF6C8A544E4CF14FC, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPENT_ARENA_JOIN_SPECTATOR(int amount, Any p1, BOOL p2, BOOL p3) { invoke<Void>(0x14EAEA58F93B55AF, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_ARENA_SKILL_LEVEL_PROGRESSION(int amount, Any p1) { invoke<Void>(0xE08256F972C7BB2C, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_ARENA_CAREER_PROGRESSION(int amount, Any p1) { invoke<Void>(0x0F99F70C61F14619, amount, p1); }
	NATIVE_DECL void NETWORK_SPEND_MAKE_IT_RAIN(int amount, BOOL p1, BOOL p2) { invoke<Void>(0xE5F5A060439C2F5D, amount, p1, p2); }
	NATIVE_DECL void NETWORK_SPEND_BUY_ARENA(int amount, BOOL p1, BOOL p2, const char* p3) { invoke<Void>(0x40D5DA9550B7CB46, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_UPGRADE_ARENA(int amount, BOOL p1, BOOL p2, const char* p3) { invoke<Void>(0x037ABB06825D7AB1, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_ARENA_SPECTATOR_BOX(int amount, int type, BOOL p2, BOOL p3) { invoke<Void>(0x7049BF858601DC0F, amount, type, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_SPIN_THE_WHEEL_PAYMENT(int amount, Any p1, BOOL p2) { invoke<Void>(0x9A5BD1D0000B339C, amount, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_SPIN_THE_WHEEL_CASH(int amount) { invoke<Void>(0x676C48776CACBB5A, amount); }
	NATIVE_DECL void NETWORK_SPEND_ARENA_PREMIUM(int amount, BOOL p1, BOOL p2) { invoke<Void>(0x619496D837EFD920, amount, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_ARENA_WAR(int amount, Any p1, Any p2, Any p3) { invoke<Void>(0x631F1CB8FB4130AA, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_ARENA_WAR_ASSASSINATE_TARGET(int amount) { invoke<Void>(0x5E7AE8AABE8B7C0D, amount); }
	NATIVE_DECL void NETWORK_EARN_ARENA_WAR_EVENT_CARGO(int amount) { invoke<Void>(0xA82959062361B259, amount); }
	NATIVE_DECL void NETWORK_EARN_RC_TIME_TRIAL(int amount) { invoke<Void>(0xDFF49EE984E7AAE8, amount); }
	NATIVE_DECL void NETWORK_EARN_DAILY_OBJECTIVE_EVENT(int amount) { invoke<Void>(0x5128DF14A5BB86FC, amount); }
	NATIVE_DECL void NETWORK_SPEND_CASINO_MEMBERSHIP(int amount, BOOL p1, BOOL p2, int p3) { invoke<Void>(0xFBBE0570EDF39D46, amount, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_BUY_CASINO(int amount, BOOL p1, BOOL p2, Any* data) { invoke<Void>(0x34A6FC4D06C4DA0F, amount, p1, p2, data); }
	NATIVE_DECL void NETWORK_SPEND_UPGRADE_CASINO(int amount, BOOL p1, BOOL p2, Any* data) { invoke<Void>(0x4740D62BC1B4EBEA, amount, p1, p2, data); }
	NATIVE_DECL void NETWORK_SPEND_CASINO_GENERIC(int amount, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x88BF9B612B84D3C3, amount, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_EARN_CASINO_TIME_TRIAL_WIN(int amount) { invoke<Void>(0x0819DB99FD2FBBD8, amount); }
	NATIVE_DECL void NETWORK_EARN_COLLECTABLES_ACTION_FIGURES(int amount) { invoke<Void>(0x5517F90043466049, amount); }
	NATIVE_DECL void NETWORK_EARN_CASINO_COLLECTABLE_COMPLETED_COLLECTION(int amount) { invoke<Void>(0x83AD64F53F4E9483, amount); }
	NATIVE_DECL void NETWORK_EARN_SELL_PRIZE_VEHICLE(int amount, Any p1, Any p2) { invoke<Void>(0x8BCB27A057DF7B7F, amount, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_CASINO_MISSION_REWARD(int amount) { invoke<Void>(0x566FD402B25787DE, amount); }
	NATIVE_DECL void NETWORK_EARN_CASINO_STORY_MISSION_REWARD(int amount) { invoke<Void>(0xAC95ED552157E092, amount); }
	NATIVE_DECL void NETWORK_EARN_CASINO_MISSION_PARTICIPATION(int amount) { invoke<Void>(0x09E8F18641BE2575, amount); }
	NATIVE_DECL void NETWORK_EARN_CASINO_AWARD(int amount, Hash hash) { invoke<Void>(0x973A9781A34F8DEB, amount, hash); }
	NATIVE_DECL void NETWORK_SPEND_BUY_ARCADE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x870289A558348378, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_UPGRADE_ARCADE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x5574637681911FDA, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_CASINO_HEIST(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0xD30E8392F407C328, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	NATIVE_DECL void NETWORK_SPEND_ARCADE_MGMT(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xB5B58E24868CB09E, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPEND_PLAY_ARCADE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xEAD3D81F2C3A1458, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPEND_ARCADE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x43AA7FAC4E6D6687, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_EARN_CASINO_HEIST(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x72E7C7B9615FA3C3, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void NETWORK_EARN_UPGRADE_ARCADE(Any p0, Any p1, Any p2) { invoke<Void>(0x4C3B75694F7E0D9C, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_ARCADE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xD29334ED1A256DBF, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL void NETWORK_EARN_COLLECTABLES(Any p0, Any p1, Any p2) { invoke<Void>(0xA95CFB4E02390842, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_CHALLENGE(int amount, Any p1, Any p2) { invoke<Void>(0x0DD362F14F18942A, amount, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_CASINO_HEIST_AWARDS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x3EC7471E6909798A, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_EARN_COLLECTABLE_ITEM(int amount, Any p1) { invoke<Void>(0x84FF63BD4966F33D, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_COLLECTABLE_COMPLETED_COLLECTION(int amount, Any p1) { invoke<Void>(0x5C9B198AF5A54FA6, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_YATCH_MISSION(int amount, Any p1) { invoke<Void>(0xDE68E30D89F97132, amount, p1); }
	NATIVE_DECL void NETWORK_EARN_DISPATCH_CALL(int amount, Any p1) { invoke<Void>(0xE2E244AB823B4483, amount, p1); }
	NATIVE_DECL void NETWORK_SPEND_BEACH_PARTY(Any p0) { invoke<Void>(0x54ABA22FA6371249, p0); }
	NATIVE_DECL void NETWORK_SPEND_SUBMARINE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x6C8BC1488527AAAB, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL void NETWORK_SPEND_CASINO_CLUB(int amount1, Any p1, BOOL p2, Any p3, int p4, int p5, int p6, int amount2, Any p8) { invoke<Void>(0xC991C255AA6D90B2, amount1, p1, p2, p3, p4, p5, p6, amount2, p8); }
	NATIVE_DECL void NETWORK_SPEND_BUY_SUB(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x90CD7C6871FBF1B4, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_UPGRADE_SUB(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x89049A84065CE68E, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_ISLAND_HEIST(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xE86689E5F82DE429, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_ISLAND_HEIST(int amount1, Any p1, Any p2, Any p3, int amount2, int p5) { invoke<Void>(0xD21D111C46BA9F15, amount1, p1, p2, p3, amount2, p5); }
	NATIVE_DECL void NETWORK_EARN_BEACH_PARTY_LOST_FOUND(Any p0, Any p1, Any p2) { invoke<Void>(0xA51338E0DCCD4065, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_FROM_ISLAND_HEIST_DJ_MISSION(Any p0, Any p1) { invoke<Void>(0xE2BB399D90942091, p0, p1); }
	NATIVE_DECL void NETWORK_SPEND_CAR_CLUB_MEMBERSHIP(int amount1, Any p1, Any p2, int amount2, Any p4) { invoke<Void>(0x1464E17207CD36E2, amount1, p1, p2, amount2, p4); }
	NATIVE_DECL void NETWORK_SPEND_CAR_CLUB_BAR(Any p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x925227803A0EAA1B, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_AUTOSHOP_MODIFY(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x9BEA350D7C48061B, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPEND_CAR_CLUB_TAKEOVER(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD1E46824E6FB92B5, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_BUY_AUTOSHOP(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xEEB7E5D1FEB20869, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_UPGRADE_AUTOSHOP(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xDD829AA198FDC46C, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_AUTOSHOP_BUSINESS(Any p0, Any p1, Any p2) { invoke<Void>(0x36A7FD5A7194B03E, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_AUTOSHOP_INCOME(Any p0, int p1) { invoke<Void>(0xC66D1CF99ED7FE25, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_CARCLUB_MEMBERSHIP(Any p0) { invoke<Void>(0xBC6227792A188E2E, p0); }
	NATIVE_DECL void NETWORK_EARN_DAILY_VEHICLE(Any p0, Any p1) { invoke<Void>(0x533073E8A596008C, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_DAILY_VEHICLE_BONUS(Any p0) { invoke<Void>(0xFE65AFE7308E32B2, p0); }
	NATIVE_DECL void NETWORK_EARN_TUNER_AWARD(Any p0, Any p1, Any p2) { invoke<Void>(0xB846F547D3792DF6, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_TUNER_ROBBERY(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xBCB266247193AC61, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_EARN_UPGRADE_AUTOSHOP(Any p0, Any p1) { invoke<Void>(0xC10322A8D3E061EE, p0, p1); }
	NATIVE_DECL void NETWORK_SPEND_INTERACTION_MENU_ABILITY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x93AA4165CB67E925, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_SET_COMMON_FIELDS(Any p0, Any p1, Any p2, BOOL p3) { invoke<Void>(0xB9F7A469460E7A4A, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_SET_DISCOUNT(BOOL p0) { invoke<Void>(0x7E2F4E8F44CAF4E0, p0); }
	NATIVE_DECL void NETWORK_SPEND_BUY_AGENCY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xEA8CD3C9B3C35884, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_UPGRADE_AGENCY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6CCA64840589A3B6, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_AGENCY(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x1B2120405080125C, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPEND_HIDDEN(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xBF8793B91EA094A7, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_SOURCE_BIKE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD9DF467CBE4398C8, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_COMP_SUV(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD86581F9E7CDA383, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_SUV_FST_TRVL(int p0, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x61A2DF64ED2D396E, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_SUPPLY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xEBD482B82ACB8BAD, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_BIKE_SHOP(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x923AEA8E78F8DF0B, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SPEND_VEHICLE_REQUESTED(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x02D24A35A9CC3503, p0, p1, p2, p3, p4); }
	NATIVE_DECL void NETWORK_SPEND_GUNRUNNING(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x2CEB0E0BC2A77C05, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_AGENCY_SAFE(Any p0, Any p1) { invoke<Void>(0x663B4B9D11742A12, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_AWARD_CONTRACT(Any p0, Any p1) { invoke<Void>(0x146D4EB6D22A403F, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_AGENCY_CONTRACT(Any p0, Any p1) { invoke<Void>(0x38482AD49CB905C7, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_AWARD_PHONE(Any p0, Any p1) { invoke<Void>(0x7397A115030F1BE3, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_AGENCY_PHONE(Any p0, Any p1, Any p2) { invoke<Void>(0xE29F3D5FA63B1B82, p0, p1, p2); }
	NATIVE_DECL void NETWORK_EARN_AWARD_FIXER_MISSION(Any p0, Any p1) { invoke<Void>(0x88D6C327D6C57C45, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_FIXER_PREP(Any p0, Any p1) { invoke<Void>(0x6283E5DE4C4460C6, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_FIXER_FINALE(Any p0, Any p1) { invoke<Void>(0xBA154373C5FE51E8, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_FIXER_AGENCY_SHORT_TRIP(Any p0, Any p1) { invoke<Void>(0xF4A8E57460BF2037, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_AWARD_SHORT_TRIP(Any p0, Any p1) { invoke<Void>(0x5B4DBDED84D6A420, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_FIXER_RIVAL_DELIVERY(Any p0, Any p1) { invoke<Void>(0x235D41210B3A1A5E, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_UPGRADE_AGENCY(Any p0, Any p1) { invoke<Void>(0xD07C7C3F1995108C, p0, p1); }
	NATIVE_DECL void NETWORK_SPEND_APARTMENT_UTILITIES(int amount, BOOL p1, BOOL p2, Any* data) { invoke<Void>(0x1254B5B3925EFD3D, amount, p1, p2, data); }
	NATIVE_DECL void NETWORK_SPEND_BUSINESS_PROPERTY_FEES(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x92D1CFDA1227FF1C, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_SIGHTSEEING_REWARD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x45087AE480B233AC, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_EARN_BIKER_SHOP(Any p0, Any p1) { invoke<Void>(0x2C5809EB9DF57257, p0, p1); }
	NATIVE_DECL void NETWORK_EARN_BIKER(Any p0) { invoke<Void>(0x71BEC32FA466E105, p0); }
	NATIVE_DECL void NETWORK_YOHAN_SOURCE_GOODS(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x59498BC8B1C8B15C, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_SPEND_BUY_MFGARAGE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xA2ED36DCF0FCA413, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_SPEND_UPGRADE_MFGARAGE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCF8F346DDDC66643, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_SPEND_BUY_SUPPLIES(int p0, BOOL p1, BOOL p2, int p3) { invoke<Void>(0xB48185C0CA67B16B, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_SPEND_BUY_ACID_LAB(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF1E26A7924327152, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_SPEND_UPGRADE_ACID_LAB_EQUIPMENT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x110EE9D486C23126, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_SPEND_UPGRADE_ACID_LAB_ARMOR(int p0, BOOL p1, BOOL p2, int p3) { invoke<Void>(0xA7D541C9ACD63133, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_SPEND_UPGRADE_ACID_LAB_SCOOP(int p0, BOOL p1, BOOL p2, int p3) { invoke<Void>(0x2940558E05BCC2EC, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_SPEND_UPGRADE_ACID_LAB_MINES(int p0, BOOL p1, BOOL p2, int p3) { invoke<Void>(0x4B99AB08C92C54E4, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_SPEND_RENAME_ACID_LAB(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x842B1C5AF61ACDE9, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_SPEND_RENAME_ACID_PRODUCT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x446798F7495DD7D8, p0, p1, p2, p3); }
	NATIVE_DECL void _NETWORK_EARN_AWARD_JUGGALO_MISSION(Any p0, Any p1) { invoke<Void>(0xDDF047577F1A02A7, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_AWARD_ACID_LAB(Any p0, Any p1) { invoke<Void>(0xD1A8165767AD2D23, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_AWARD_DAILY_STASH(Any p0, Any p1) { invoke<Void>(0xC30650FA74A19D02, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_AWARD_DEAD_DROP(Any p0, Any p1) { invoke<Void>(0xD01EBAEA1F905EF6, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_AWARD_RANDOM_EVENT(Any p0, Any p1) { invoke<Void>(0xBEAFBB1B98B7EF55, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_AWARD_TAXI(Any p0, Any p1) { invoke<Void>(0xA914768AD35CD3A5, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_STREET_DEALER(Any p0, Any p1) { invoke<Void>(0xA81017EE1324FDFE, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_SELL_ACID(Any p0, Any p1) { invoke<Void>(0x79B656937DF6DF5D, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_SETUP_PARTICIPATION_ACID_LAB(Any p0, Any p1) { invoke<Void>(0xE3942D59E8A7F70D, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_SOURCE_PARTICIPATION_ACID_LAB(Any p0, Any p1) { invoke<Void>(0x136F11B5DF1B304D, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_SELL_PARTICIPATION_ACID_LAB(Any p0, Any p1) { invoke<Void>(0xCA3EF9B09A8D76B4, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_JUGGALO_STORY_MISSION(Any p0, Any p1) { invoke<Void>(0xE01D10BA8CD53621, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_JUGGALO_STORY_MISSION_PARTICIPATION(Any p0, Any p1) { invoke<Void>(0x40FF6CCCC476185C, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_FOOLIGAN_JOB(Any p0, Any p1) { invoke<Void>(0xCE4452AE85F5E252, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_FOOLIGAN_JOB_PARTICIPATION(Any p0, Any p1) { invoke<Void>(0xC376B92D0E060970, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_TAXI_JOB(Any p0, Any p1) { invoke<Void>(0x991E1588FAD9019D, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_DAILY_STASH_HOUSE_COMPLETED(Any p0, Any p1) { invoke<Void>(0xCABC9874AFA70D6D, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_DAILY_STASH_HOUSE_PARTICIPATION(Any p0, Any p1) { invoke<Void>(0x9C0C6BD0F94CE391, p0, p1); }
	NATIVE_DECL void _NETWORK_EARN_AVENGER(int amount, int p1) { invoke<Void>(0x55F006B9D4A46C1D, amount, p1); }
	NATIVE_DECL void _NETWORK_EARN_SMUGGLER_OPS(Any p0, Any p1, Any p2) { invoke<Void>(0xDEA273D5F8A9661A, p0, p1, p2); }
	NATIVE_DECL void _NETWORK_EARN_BONUS_OBJECTIVE(int amount, Any p1, Any p2) { invoke<Void>(0xDCEF983C24191997, amount, p1, p2); }
	NATIVE_DECL void _NETWORK_EARN_PROGRESS_HUB(Any p0, Any p1) { invoke<Void>(0xF8332B06F0EECC9C, p0, p1); }
	NATIVE_DECL void _NETWORK_SPENT_AIR_FREIGHT(int hangarCargoSourcingPrice, BOOL fromBank, BOOL fromBankAndWallet, int cost, int warehouseId, int warehouseSlot, Any p6) { invoke<Void>(0x8C7E8D6F96C9E948, hangarCargoSourcingPrice, fromBank, fromBankAndWallet, cost, warehouseId, warehouseSlot, p6); }
	NATIVE_DECL void _NETWORK_SPENT_SKIP_CARGO_SOURCE_SETUP(int amount, BOOL fromBank, BOOL fromBankAndWallet, int cost) { invoke<Void>(0xED1B407BADA42CEC, amount, fromBank, fromBankAndWallet, cost); }
	NATIVE_DECL void _NETWORK_SPENT_STEALTH_MODULE(int amount, BOOL fromBank, BOOL fromBankAndWallet, Hash p3) { invoke<Void>(0x95CE79A6939C537A, amount, fromBank, fromBankAndWallet, p3); }
	NATIVE_DECL void _NETWORK_SPENT_MISSILE_JAMMER(int amount, BOOL fromBank, BOOL fromBankAndWallet, Hash p3) { invoke<Void>(0xD687100F616163F4, amount, fromBank, fromBankAndWallet, p3); }
	NATIVE_DECL void _NETWORK_SPENT_GENERIC(int price, BOOL p1, BOOL p2, Hash stat, Hash spent, const char* p5, const char* p6, Any* data) { invoke<Void>(0x2803B027479FB640, price, p1, p2, stat, spent, p5, p6, data); }
	NATIVE_DECL void _NETWORK_EARN_GENERIC(int amount, Hash earn, const char* p2, const char* p3, Any* data) { invoke<Void>(0xBF7B5BB7ED890380, amount, earn, p2, p3, data); }
	NATIVE_DECL void _NETWORK_CLEAR_TRANSACTION_TELEMETRY_NONCE() { invoke<Void>(0xE03B9F95556E48E9); }
	NATIVE_DECL int NETWORK_GET_VC_BANK_BALANCE() { return invoke<int>(0x76EF28DA05EA395A); }
	NATIVE_DECL int NETWORK_GET_VC_WALLET_BALANCE(int characterSlot) { return invoke<int>(0xA40F9C2623F6A8B5, characterSlot); }
	NATIVE_DECL int NETWORK_GET_VC_BALANCE() { return invoke<int>(0x5CBAD97E059E1B94); }
	NATIVE_DECL int NETWORK_GET_EVC_BALANCE() { return invoke<int>(0x5D1E75F91C07DEE5); }
	NATIVE_DECL int NETWORK_GET_PVC_BALANCE() { return invoke<int>(0x4F54F3B6C202FB4E); }
	NATIVE_DECL const char* NETWORK_GET_STRING_WALLET_BALANCE(int characterSlot) { return invoke<const char*>(0xF9B10B529DCFB33B, characterSlot); }
	NATIVE_DECL const char* NETWORK_GET_STRING_BANK_BALANCE() { return invoke<const char*>(0xA6FA3979BED01B81); }
	NATIVE_DECL const char* NETWORK_GET_STRING_BANK_WALLET_BALANCE(int character) { return invoke<const char*>(0x700AF71AE615E6DD, character); }
	NATIVE_DECL BOOL NETWORK_GET_CAN_SPEND_FROM_WALLET(int amount, int characterSlot) { return invoke<BOOL>(0xED5AB8860415BABA, amount, characterSlot); }
	NATIVE_DECL BOOL NETWORK_GET_CAN_SPEND_FROM_BANK(int amount) { return invoke<BOOL>(0xA31FD6A0865B6D14, amount); }
	NATIVE_DECL BOOL NETWORK_GET_CAN_SPEND_FROM_BANK_AND_WALLET(int amount, int characterSlot) { return invoke<BOOL>(0xDC18531D7019A535, amount, characterSlot); }
	NATIVE_DECL int NETWORK_GET_PVC_TRANSFER_BALANCE() { return invoke<int>(0x13A8DE2FD77D04F3); }
	NATIVE_DECL BOOL NETWORK_GET_CAN_TRANSFER_CASH(int amount) { return invoke<BOOL>(0x08E8EEADFD0DC4A0, amount); }
	NATIVE_DECL BOOL NETWORK_CAN_RECEIVE_PLAYER_CASH(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x5D17BE59D2123284, p0, p1, p2, p3); }
	NATIVE_DECL int NETWORK_GET_REMAINING_TRANSFER_BALANCE() { return invoke<int>(0xEA560AC9EEB1E19B); }
	NATIVE_DECL int WITHDRAW_VC(int amount) { return invoke<int>(0xF70EFA14FE091429, amount); }
	NATIVE_DECL BOOL DEPOSIT_VC(int amount) { return invoke<BOOL>(0xE260E0BB9CD995AC, amount); }
	NATIVE_DECL BOOL HAS_VC_WITHDRAWAL_COMPLETED(Any p0) { return invoke<BOOL>(0xE154B48B68EF72BC, p0); }
	NATIVE_DECL BOOL WAS_VC_WITHDRAWAL_SUCCESSFUL(Any p0) { return invoke<BOOL>(0x6FCF8DDEA146C45B, p0); }
	NATIVE_DECL BOOL _NETWORK_GET_TOTAL_EVC_BALANCE_IS_GREATER_THAN_100M() { return invoke<BOOL>(0xDBD91315C80E9483); }
	NATIVE_DECL BOOL _NETWORK_GET_TOTAL_EVC_BALANCE_IS_GREATER_THAN_500M() { return invoke<BOOL>(0xC44398D46FF6ADB9); }
	NATIVE_DECL BOOL _NETWORK_GET_TOTAL_EVC_BALANCE_IS_GREATER_THAN_1B() { return invoke<BOOL>(0xEEB1C310842A81E0); }
}

namespace NETSHOPPING
{
	NATIVE_DECL BOOL NET_GAMESERVER_USE_SERVER_TRANSACTIONS() { return invoke<BOOL>(0x7D2708796355B20B); }
	NATIVE_DECL BOOL NET_GAMESERVER_CATALOG_ITEM_IS_VALID(const char* name) { return invoke<BOOL>(0xBD4D7EAF8A30F637, name); }
	NATIVE_DECL BOOL NET_GAMESERVER_CATALOG_ITEM_KEY_IS_VALID(Hash hash) { return invoke<BOOL>(0x247F0F73A182EA0B, hash); }
	NATIVE_DECL int NET_GAMESERVER_GET_PRICE(Hash itemHash, Hash categoryHash, BOOL p2) { return invoke<int>(0xC27009422FCCA88D, itemHash, categoryHash, p2); }
	NATIVE_DECL BOOL NET_GAMESERVER_CATALOG_IS_VALID() { return invoke<BOOL>(0x3C4487461E9B0DCB); }
	NATIVE_DECL BOOL NET_GAMESERVER_IS_CATALOG_CURRENT() { return invoke<BOOL>(0x2B949A1E6AEC8F6A); }
	NATIVE_DECL Hash NET_GAMESERVER_GET_CATALOG_CLOUD_CRC() { return invoke<Hash>(0x85F6C9ABA1DE2BCF); }
	NATIVE_DECL BOOL NET_GAMESERVER_REFRESH_SERVER_CATALOG() { return invoke<BOOL>(0x357B152EF96C30B6); }
	NATIVE_DECL BOOL NET_GAMESERVER_RETRIEVE_CATALOG_REFRESH_STATUS(int* state) { return invoke<BOOL>(0xCF38DAFBB49EDE5E, state); }
	NATIVE_DECL BOOL NET_GAMESERVER_INIT_SESSION() { return invoke<BOOL>(0xE3E5A7C64CA2C6ED); }
	NATIVE_DECL BOOL NET_GAMESERVER_RETRIEVE_INIT_SESSION_STATUS(int* p0) { return invoke<BOOL>(0x0395CB47B022E62C, p0); }
	NATIVE_DECL BOOL NET_GAMESERVER_START_SESSION(int charSlot) { return invoke<BOOL>(0xA135AC892A58FC07, charSlot); }
	NATIVE_DECL BOOL NET_GAMESERVER_START_SESSION_PENDING() { return invoke<BOOL>(0x72EB7BA9B69BF6AB); }
	NATIVE_DECL BOOL NET_GAMESERVER_RETRIEVE_START_SESSION_STATUS(int* p0) { return invoke<BOOL>(0x170910093218C8B9, p0); }
	NATIVE_DECL BOOL NET_GAMESERVER_RETRIEVE_SESSION_ERROR_CODE(int* p0) { return invoke<BOOL>(0xC13C38E47EA5DF31, p0); }
	NATIVE_DECL BOOL NET_GAMESERVER_IS_SESSION_VALID(int charSlot) { return invoke<BOOL>(0xB24F0944DA203D9E, charSlot); }
	NATIVE_DECL BOOL NET_GAMESERVER_CLEAR_SESSION(int p0) { return invoke<BOOL>(0x74A0FD0688F1EE45, p0); }
	NATIVE_DECL BOOL NET_GAMESERVER_SESSION_APPLY_RECEIVED_DATA(int charSlot) { return invoke<BOOL>(0x2F41D51BA3BCD1F1, charSlot); }
	NATIVE_DECL BOOL NET_GAMESERVER_IS_SESSION_REFRESH_PENDING() { return invoke<BOOL>(0x810E8431C0614BF9); }
	NATIVE_DECL BOOL NET_GAMESERVER_START_SESSION_RESTART(BOOL inventory, BOOL playerbalance) { return invoke<BOOL>(0x35A1B3E1D1315CFA, inventory, playerbalance); }
	NATIVE_DECL BOOL NET_GAMESERVER_TRANSACTION_IN_PROGRESS() { return invoke<BOOL>(0x613F125BA3BD2EB9); }
	NATIVE_DECL BOOL NET_GAMESERVER_GET_SESSION_STATE_AND_STATUS(int* p0, BOOL* p1) { return invoke<BOOL>(0x897433D292B44130, p0, p1); }
	NATIVE_DECL BOOL NET_GAMESERVER_BASKET_START(int* transactionId, Hash categoryHash, Hash actionHash, int flags) { return invoke<BOOL>(0x279F08B1A4B29B7E, transactionId, categoryHash, actionHash, flags); }
	NATIVE_DECL BOOL NET_GAMESERVER_BASKET_END() { return invoke<BOOL>(0xFA336E7F40C0A0D0); }
	NATIVE_DECL BOOL NET_GAMESERVER_BASKET_IS_ACTIVE() { return invoke<BOOL>(0xA65568121DF2EA26); }
	NATIVE_DECL BOOL NET_GAMESERVER_BASKET_ADD_ITEM(Any* itemData, int quantity) { return invoke<BOOL>(0xF30980718C8ED876, itemData, quantity); }
	NATIVE_DECL BOOL NET_GAMESERVER_BASKET_IS_FULL() { return invoke<BOOL>(0x27F76CC6C55AD30E); }
	NATIVE_DECL BOOL NET_GAMESERVER_BASKET_APPLY_SERVER_DATA(Any p0, Any* p1) { return invoke<BOOL>(0xE1A0450ED46A7812, p0, p1); }
	NATIVE_DECL BOOL NET_GAMESERVER_CHECKOUT_START(int transactionId) { return invoke<BOOL>(0x39BE7CEA8D9CC8E6, transactionId); }
	NATIVE_DECL BOOL NET_GAMESERVER_CHECKOUT_PENDING(int transactionId) { return invoke<BOOL>(0x4B64CD6D18474126, transactionId); }
	NATIVE_DECL BOOL NET_GAMESERVER_BEGIN_SERVICE(int* transactionId, Hash categoryHash, Hash itemHash, Hash actionTypeHash, int value, int flags) { return invoke<BOOL>(0x3C5FD37B5499582E, transactionId, categoryHash, itemHash, actionTypeHash, value, flags); }
	NATIVE_DECL BOOL NET_GAMESERVER_END_SERVICE(int transactionId) { return invoke<BOOL>(0xE2A99A9B524BEFFF, transactionId); }
	NATIVE_DECL BOOL NET_GAMESERVER_DELETE_CHARACTER(int slot, BOOL transfer, Hash reason) { return invoke<BOOL>(0x51F1A8E48C3D2F6D, slot, transfer, reason); }
	NATIVE_DECL int NET_GAMESERVER_DELETE_CHARACTER_GET_STATUS() { return invoke<int>(0x0A6D923DFFC9BD89); }
	NATIVE_DECL BOOL NET_GAMESERVER_DELETE_SET_TELEMETRY_NONCE_SEED() { return invoke<BOOL>(0x112CEF1615A1139F); }
	NATIVE_DECL BOOL NET_GAMESERVER_TRANSFER_BANK_TO_WALLET(int charSlot, int amount) { return invoke<BOOL>(0xD47A2C1BA117471D, charSlot, amount); }
	NATIVE_DECL BOOL NET_GAMESERVER_TRANSFER_WALLET_TO_BANK(int charSlot, int amount) { return invoke<BOOL>(0xC2F7FE5309181C7D, charSlot, amount); }
	NATIVE_DECL int NET_GAMESERVER_TRANSFER_BANK_TO_WALLET_GET_STATUS() { return invoke<int>(0x23789E777D14CE44); }
	NATIVE_DECL int NET_GAMESERVER_TRANSFER_WALLET_TO_BANK_GET_STATUS() { return invoke<int>(0x350AA5EBC03D3BD2); }
	NATIVE_DECL BOOL NET_GAMESERVER_TRANSFER_CASH_SET_TELEMETRY_NONCE_SEED() { return invoke<BOOL>(0x498C1E05CE5F7877); }
	NATIVE_DECL BOOL NET_GAMESERVER_SET_TELEMETRY_NONCE_SEED(int p0) { return invoke<BOOL>(0x9507D4271988E1AE, p0); }
}

namespace NETWORK
{
	NATIVE_DECL const char* GET_ONLINE_VERSION() { return invoke<const char*>(0xFCA9373EF340AC0A); }
	NATIVE_DECL BOOL NETWORK_IS_SIGNED_IN() { return invoke<BOOL>(0x054354A99211EB96); }
	NATIVE_DECL BOOL NETWORK_IS_SIGNED_ONLINE() { return invoke<BOOL>(0x1077788E268557C2); }
	NATIVE_DECL BOOL NETWORK_IS_NP_AVAILABLE() { return invoke<BOOL>(0xBD545D44CCE70597); }
	NATIVE_DECL BOOL NETWORK_IS_NP_PENDING() { return invoke<BOOL>(0xEBCAB9E5048434F4); }
	NATIVE_DECL int NETWORK_GET_NP_UNAVAILABLE_REASON() { return invoke<int>(0x74FB3E29E6D10FA9); }
	NATIVE_DECL BOOL NETWORK_IS_CONNETED_TO_NP_PRESENCE() { return invoke<BOOL>(0x7808619F31FF22DB); }
	NATIVE_DECL BOOL NETWORK_IS_LOGGED_IN_TO_PSN() { return invoke<BOOL>(0xA0FA4EC6A05DA44E); }
	NATIVE_DECL BOOL NETWORK_HAS_VALID_ROS_CREDENTIALS() { return invoke<BOOL>(0x85443FF4C328F53B); }
	NATIVE_DECL BOOL NETWORK_IS_REFRESHING_ROS_CREDENTIALS() { return invoke<BOOL>(0x8D11E61A4ABF49CC); }
	NATIVE_DECL BOOL NETWORK_IS_CLOUD_AVAILABLE() { return invoke<BOOL>(0x9A4CF4F48AD77302); }
	NATIVE_DECL BOOL NETWORK_HAS_SOCIAL_CLUB_ACCOUNT() { return invoke<BOOL>(0x67A5589628E0CFF6); }
	NATIVE_DECL BOOL NETWORK_ARE_SOCIAL_CLUB_POLICIES_CURRENT() { return invoke<BOOL>(0xBA9775570DB788CF); }
	NATIVE_DECL BOOL NETWORK_IS_HOST() { return invoke<BOOL>(0x8DB296B814EDDA07); }
	NATIVE_DECL Player NETWORK_GET_HOST_PLAYER_INDEX() { return invoke<Player>(0x8251FB94DC4FDFC8); }
	NATIVE_DECL BOOL NETWORK_WAS_GAME_SUSPENDED() { return invoke<BOOL>(0x4237E822315D8BA9); }
	NATIVE_DECL BOOL NETWORK_HAVE_ONLINE_PRIVILEGES() { return invoke<BOOL>(0x25CB5A9F37BFD063); }
	NATIVE_DECL BOOL _NETWORK_MULTIPLAYER_CROSSPLAY_NOT_ALLOWED() { return invoke<BOOL>(0xA6BC0D9BCF9662FA); }
	NATIVE_DECL BOOL NETWORK_HAS_AGE_RESTRICTIONS() { return invoke<BOOL>(0x1353F87E89946207); }
	NATIVE_DECL BOOL NETWORK_HAVE_USER_CONTENT_PRIVILEGES(int p0) { return invoke<BOOL>(0x72D918C99BCACC54, p0); }
	NATIVE_DECL BOOL NETWORK_HAVE_COMMUNICATION_PRIVILEGES(int p0, Player player) { return invoke<BOOL>(0xAEEF48CDF5B6CE7C, p0, player); }
	NATIVE_DECL BOOL _NETWORK_HAVE_PLATFORM_COMMUNICATION_PRIVILEGES() { return invoke<BOOL>(0xE1E02509169C124E); }
	NATIVE_DECL BOOL NETWORK_CHECK_ONLINE_PRIVILEGES(Any p0, BOOL p1) { return invoke<BOOL>(0x78321BEA235FD8CD, p0, p1); }
	NATIVE_DECL BOOL NETWORK_CHECK_USER_CONTENT_PRIVILEGES(int p0, int p1, BOOL p2) { return invoke<BOOL>(0x595F028698072DD9, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_CHECK_COMMUNICATION_PRIVILEGES(int p0, int p1, BOOL p2) { return invoke<BOOL>(0x83F28CE49FBBFFBA, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_CHECK_TEXT_COMMUNICATION_PRIVILEGES(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x07EAB372C8841D99, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_IS_USING_ONLINE_PROMOTION() { return invoke<BOOL>(0x906CA41A4B74ECA4); }
	NATIVE_DECL BOOL NETWORK_SHOULD_SHOW_PROMOTION_ALERT_SCREEN() { return invoke<BOOL>(0x023ACAB2DC9DC4A4); }
	NATIVE_DECL BOOL NETWORK_HAS_SOCIAL_NETWORKING_SHARING_PRIV() { return invoke<BOOL>(0x76BF03FADBF154F5); }
	NATIVE_DECL int NETWORK_GET_AGE_GROUP() { return invoke<int>(0x9614B71F8ADB982B); }
	NATIVE_DECL BOOL NETWORK_CHECK_PRIVILEGES(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x0CF6CC51AA18F0F8, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_IS_PRIVILEGE_CHECK_IN_PROGRESS() { return invoke<BOOL>(0x64E5C4CC82847B73); }
	NATIVE_DECL void NETWORK_SET_PRIVILEGE_CHECK_RESULT_NOT_NEEDED() { invoke<Void>(0x1F7BC3539F9E0224); }
	NATIVE_DECL BOOL NETWORK_RESOLVE_PRIVILEGE_USER_CONTENT() { return invoke<BOOL>(0xDE9225854F37BF72); }
	NATIVE_DECL BOOL NETWORK_HAVE_PLATFORM_SUBSCRIPTION() { return invoke<BOOL>(0x5EA784D197556507); }
	NATIVE_DECL BOOL NETWORK_IS_PLATFORM_SUBSCRIPTION_CHECK_PENDING() { return invoke<BOOL>(0xA8ACB6459542A8C8); }
	NATIVE_DECL void NETWORK_SHOW_ACCOUNT_UPGRADE_UI() { invoke<Void>(0x83FE8D7229593017); }
	NATIVE_DECL BOOL NETWORK_IS_SHOWING_SYSTEM_UI_OR_RECENTLY_REQUESTED_UPSELL() { return invoke<BOOL>(0x7788DFE15016A182); }
	NATIVE_DECL BOOL NETWORK_NEED_TO_START_NEW_GAME_BUT_BLOCKED() { return invoke<BOOL>(0x53C10C8BD774F2C9); }
	NATIVE_DECL BOOL NETWORK_CAN_BAIL() { return invoke<BOOL>(0x580CE4438479CC61); }
	NATIVE_DECL void NETWORK_BAIL(int p0, int p1, int p2) { invoke<Void>(0x95914459A87EBA28, p0, p1, p2); }
	NATIVE_DECL void NETWORK_ON_RETURN_TO_SINGLE_PLAYER() { invoke<Void>(0x283B6062A2C01E9B); }
	NATIVE_DECL BOOL NETWORK_TRANSITION_START(int p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x8B4FFC790CA131EF, p0, p1, p2, p3); }
	NATIVE_DECL BOOL NETWORK_TRANSITION_ADD_STAGE(Hash hash, int p1, int p2, int state, int p4) { return invoke<BOOL>(0xC3BFED92026A2AAD, hash, p1, p2, state, p4); }
	NATIVE_DECL BOOL NETWORK_TRANSITION_FINISH(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x04918A41BC9B8157, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_CAN_ACCESS_MULTIPLAYER(int* loadingState) { return invoke<BOOL>(0xAF50DA1A3F8B1BA4, loadingState); }
	NATIVE_DECL BOOL NETWORK_CHECK_CAN_ACCESS_AND_ALERT() { return invoke<BOOL>(0x6FA9825D0B5A721B); }
	NATIVE_DECL const char* _NETWORK_GET_ACCESS_CODE_LABEL_HEADING(int accessCode) { return invoke<const char*>(0x967E6FB554E1B6DE, accessCode); }
	NATIVE_DECL const char* _NETWORK_GET_ACCESS_CODE_LABEL_BODY(int accessCode) { return invoke<const char*>(0x214CA1730793EBA8, accessCode); }
	NATIVE_DECL BOOL NETWORK_IS_MULTIPLAYER_DISABLED() { return invoke<BOOL>(0x9747292807126EDA); }
	NATIVE_DECL BOOL NETWORK_CAN_ENTER_MULTIPLAYER() { return invoke<BOOL>(0x7E782A910C362C25); }
	NATIVE_DECL BOOL NETWORK_SESSION_DO_FREEROAM_QUICKMATCH(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x330ED4D05491934F, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_SESSION_DO_FRIEND_MATCHMAKING(int p0, int p1, int p2) { return invoke<BOOL>(0x2CFC76E0D087C994, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_SESSION_DO_CREW_MATCHMAKING(int crewId, int p1, int p2, int maxPlayers) { return invoke<BOOL>(0x94BC51E9449D917F, crewId, p1, p2, maxPlayers); }
	NATIVE_DECL BOOL NETWORK_SESSION_DO_ACTIVITY_QUICKMATCH(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0xBE3E347A87ACEB82, p0, p1, p2, p3, p4); }
	NATIVE_DECL BOOL NETWORK_SESSION_HOST(int p0, int maxPlayers, BOOL p2) { return invoke<BOOL>(0x6F3D4ED9BEE4E61D, p0, maxPlayers, p2); }
	NATIVE_DECL BOOL NETWORK_SESSION_HOST_CLOSED(int p0, int maxPlayers) { return invoke<BOOL>(0xED34C0C02C098BB7, p0, maxPlayers); }
	NATIVE_DECL BOOL NETWORK_SESSION_HOST_FRIENDS_ONLY(int p0, int maxPlayers) { return invoke<BOOL>(0xB9CFD27A5D578D83, p0, maxPlayers); }
	NATIVE_DECL BOOL NETWORK_SESSION_IS_CLOSED_FRIENDS() { return invoke<BOOL>(0xFBCFA2EA2E206890); }
	NATIVE_DECL BOOL NETWORK_SESSION_IS_CLOSED_CREW() { return invoke<BOOL>(0x74732C6CA90DA2B4); }
	NATIVE_DECL BOOL NETWORK_SESSION_IS_SOLO() { return invoke<BOOL>(0xF3929C2379B60CCE); }
	NATIVE_DECL BOOL NETWORK_SESSION_IS_PRIVATE() { return invoke<BOOL>(0xCEF70AA5B3F89BA1); }
	NATIVE_DECL BOOL _NETWORK_SESSION_LEAVE_INCLUDING_REASON(int leaveFlags, int leaveReason) { return invoke<BOOL>(0xE0128328CF1FD9F4, leaveFlags, leaveReason); }
	NATIVE_DECL BOOL NETWORK_SESSION_LEAVE(Any p0) { return invoke<BOOL>(0xB9351A07A0D458B1, p0); }
	NATIVE_DECL void NETWORK_SESSION_KICK_PLAYER(Player player) { invoke<Void>(0xFA8904DC5F304220, player); }
	NATIVE_DECL BOOL NETWORK_SESSION_GET_KICK_VOTE(Player player) { return invoke<BOOL>(0xD6D09A6F32F49EF1, player); }
	NATIVE_DECL BOOL NETWORK_SESSION_RESERVE_SLOTS_TRANSITION(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x041C7F2A6C9894E6, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_JOIN_PREVIOUSLY_FAILED_SESSION() { return invoke<BOOL>(0x59DF79317F85A7E0); }
	NATIVE_DECL BOOL NETWORK_JOIN_PREVIOUSLY_FAILED_TRANSITION() { return invoke<BOOL>(0xFFE1E5B792D92B34); }
	NATIVE_DECL void NETWORK_SESSION_SET_MATCHMAKING_GROUP(int matchmakingGroup) { invoke<Void>(0x49EC8030F5015F8B, matchmakingGroup); }
	NATIVE_DECL void NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX(int playerType, int playerCount) { invoke<Void>(0x8B6A4DD0AF9CE215, playerType, playerCount); }
	NATIVE_DECL int NETWORK_SESSION_GET_MATCHMAKING_GROUP_FREE(int p0) { return invoke<int>(0x56CE820830EF040B, p0); }
	NATIVE_DECL void NETWORK_SESSION_ADD_ACTIVE_MATCHMAKING_GROUP(int groupId) { invoke<Void>(0xCAE55F48D3D7875C, groupId); }
	NATIVE_DECL void NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT(Any p0) { invoke<Void>(0xF49ABC20D8552257, p0); }
	NATIVE_DECL int NETWORK_SESSION_GET_UNIQUE_CREW_LIMIT() { return invoke<int>(0xCDC936BF35EDCB73); }
	NATIVE_DECL void NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT_TRANSITION(Any p0) { invoke<Void>(0x4811BBAC21C5FCD5, p0); }
	NATIVE_DECL void NETWORK_SESSION_SET_UNIQUE_CREW_ONLY_CREWS_TRANSITION(BOOL p0) { invoke<Void>(0x5539C3EBF104A53A, p0); }
	NATIVE_DECL void NETWORK_SESSION_SET_CREW_LIMIT_MAX_MEMBERS_TRANSITION(Any p0) { invoke<Void>(0x702BC4D605522539, p0); }
	NATIVE_DECL void NETWORK_SESSION_SET_MATCHMAKING_PROPERTY_ID(BOOL p0) { invoke<Void>(0x3F52E880AAF6C8CA, p0); }
	NATIVE_DECL void NETWORK_SESSION_SET_MATCHMAKING_MENTAL_STATE(int p0) { invoke<Void>(0xF1EEA2DDA9FFA69D, p0); }
	NATIVE_DECL void NETWORK_SESSION_SET_NUM_BOSSES(int num) { invoke<Void>(0x59D421683D31835A, num); }
	NATIVE_DECL void NETWORK_SESSION_SET_SCRIPT_VALIDATE_JOIN() { invoke<Void>(0x1153FA02A659051C); }
	NATIVE_DECL void NETWORK_SESSION_VALIDATE_JOIN(BOOL p0) { invoke<Void>(0xC19F6C8E7865A6FF, p0); }
	NATIVE_DECL void NETWORK_ADD_FOLLOWERS(int* p0, int p1) { invoke<Void>(0x236406F60CF216D6, p0, p1); }
	NATIVE_DECL void NETWORK_CLEAR_FOLLOWERS() { invoke<Void>(0x058F43EC59A8631A); }
	NATIVE_DECL void NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK(int* hours, int* minutes, int* seconds) { invoke<Void>(0x6D03BFBD643B2A02, hours, minutes, seconds); }
	NATIVE_DECL void NETWORK_SESSION_SET_GAMEMODE(Any p0) { invoke<Void>(0x600F8CB31C7AAB6E, p0); }
	NATIVE_DECL int NETWORK_SESSION_GET_HOST_AIM_PREFERENCE() { return invoke<int>(0xDFFA5BE8381C3314); }
	NATIVE_DECL BOOL NETWORK_FIND_GAMERS_IN_CREW(int crewId) { return invoke<BOOL>(0xE532D6811B3A4D2A, crewId); }
	NATIVE_DECL BOOL NETWORK_FIND_MATCHED_GAMERS(int attribute, float fallbackLimit, float lowerLimit, float upperLimit) { return invoke<BOOL>(0xF7B2CFDE5C9F700D, attribute, fallbackLimit, lowerLimit, upperLimit); }
	NATIVE_DECL BOOL NETWORK_IS_FINDING_GAMERS() { return invoke<BOOL>(0xDDDF64C91BFCF0AA); }
	NATIVE_DECL BOOL NETWORK_DID_FIND_GAMERS_SUCCEED() { return invoke<BOOL>(0xF9B83B77929D8863); }
	NATIVE_DECL int NETWORK_GET_NUM_FOUND_GAMERS() { return invoke<int>(0xA1B043EE79A916FB); }
	NATIVE_DECL BOOL NETWORK_GET_FOUND_GAMER(Any* p0, Any p1) { return invoke<BOOL>(0x9DCFF2AFB68B3476, p0, p1); }
	NATIVE_DECL void NETWORK_CLEAR_FOUND_GAMERS() { invoke<Void>(0x6D14CCEE1B40381A); }
	NATIVE_DECL BOOL NETWORK_QUEUE_GAMER_FOR_STATUS(Any* p0) { return invoke<BOOL>(0x85A0EF54A500882C, p0); }
	NATIVE_DECL BOOL NETWORK_GET_GAMER_STATUS_FROM_QUEUE() { return invoke<BOOL>(0x2CC848A861D01493); }
	NATIVE_DECL BOOL NETWORK_IS_GETTING_GAMER_STATUS() { return invoke<BOOL>(0x94A8394D150B013A); }
	NATIVE_DECL BOOL NETWORK_DID_GET_GAMER_STATUS_SUCCEED() { return invoke<BOOL>(0x5AE17C6B0134B7F1); }
	NATIVE_DECL BOOL NETWORK_GET_GAMER_STATUS_RESULT(Any* p0, Any p1) { return invoke<BOOL>(0x02A8BEC6FD9AF660, p0, p1); }
	NATIVE_DECL void NETWORK_CLEAR_GET_GAMER_STATUS() { invoke<Void>(0x86E0660E4F5C956D); }
	NATIVE_DECL void NETWORK_SESSION_JOIN_INVITE() { invoke<Void>(0xC6F8AB8A4189CF3A); }
	NATIVE_DECL void NETWORK_SESSION_CANCEL_INVITE() { invoke<Void>(0x2FBF47B1B36D36F9); }
	NATIVE_DECL void NETWORK_SESSION_FORCE_CANCEL_INVITE() { invoke<Void>(0xA29177F7703B5644); }
	NATIVE_DECL BOOL NETWORK_HAS_PENDING_INVITE() { return invoke<BOOL>(0xAC8C7B9B88C4A668); }
	NATIVE_DECL BOOL NETWORK_HAS_CONFIRMED_INVITE() { return invoke<BOOL>(0xC42DD763159F3461); }
	NATIVE_DECL BOOL NETWORK_REQUEST_INVITE_CONFIRMED_EVENT() { return invoke<BOOL>(0x62A0296C1BB1CEB3); }
	NATIVE_DECL BOOL NETWORK_SESSION_WAS_INVITED() { return invoke<BOOL>(0x23DFB504655D0CE4); }
	NATIVE_DECL void NETWORK_SESSION_GET_INVITER(Any* gamerHandle) { invoke<Void>(0xE57397B4A3429DD0, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_SESSION_IS_AWAITING_INVITE_RESPONSE() { return invoke<BOOL>(0xD313DE83394AF134); }
	NATIVE_DECL BOOL NETWORK_SESSION_IS_DISPLAYING_INVITE_CONFIRMATION() { return invoke<BOOL>(0xBDB6F89C729CF388); }
	NATIVE_DECL void NETWORK_SUPPRESS_INVITE(BOOL toggle) { invoke<Void>(0xA0682D67EF1FBA3D, toggle); }
	NATIVE_DECL void NETWORK_BLOCK_INVITES(BOOL toggle) { invoke<Void>(0x34F9E9049454A7A0, toggle); }
	NATIVE_DECL void NETWORK_BLOCK_JOIN_QUEUE_INVITES(BOOL toggle) { invoke<Void>(0xCFEB8AF24FC1D0BB, toggle); }
	NATIVE_DECL void NETWORK_SET_CAN_RECEIVE_RS_INVITES(BOOL p0) { invoke<Void>(0x68980414688F7F9D, p0); }
	NATIVE_DECL void NETWORK_STORE_INVITE_THROUGH_RESTART() { invoke<Void>(0xF814FEC6A19FD6E0); }
	NATIVE_DECL void NETWORK_ALLOW_INVITE_PROCESS_IN_PLAYER_SWITCH(BOOL p0) { invoke<Void>(0x6B07B9CE4D390375, p0); }
	NATIVE_DECL void NETWORK_SET_SCRIPT_READY_FOR_EVENTS(BOOL toggle) { invoke<Void>(0x7AC752103856FB20, toggle); }
	NATIVE_DECL BOOL NETWORK_IS_OFFLINE_INVITE_PENDING() { return invoke<BOOL>(0x74698374C45701D2); }
	NATIVE_DECL void NETWORK_CLEAR_OFFLINE_INVITE_PENDING() { invoke<Void>(0x140E6A44870A11CE); }
	NATIVE_DECL const char* _NETWORK_INVITE_GET_JOIN_FAIL_REASON() { return invoke<const char*>(0x7B335F84501145BB); }
	NATIVE_DECL void _NETWORK_INVITE_CLEAR_JOIN_FAIL_REASON() { invoke<Void>(0x8EF5F5811A940F82); }
	NATIVE_DECL void NETWORK_SESSION_HOST_SINGLE_PLAYER(int p0) { invoke<Void>(0xC74C33FCA52856D5, p0); }
	NATIVE_DECL void NETWORK_SESSION_LEAVE_SINGLE_PLAYER() { invoke<Void>(0x3442775428FD2DAA); }
	NATIVE_DECL BOOL NETWORK_IS_GAME_IN_PROGRESS() { return invoke<BOOL>(0x10FAB35428CCC9D7); }
	NATIVE_DECL BOOL NETWORK_IS_SESSION_ACTIVE() { return invoke<BOOL>(0xD83C2B94E7508980); }
	NATIVE_DECL BOOL NETWORK_IS_IN_SESSION() { return invoke<BOOL>(0xCA97246103B63917); }
	NATIVE_DECL BOOL _NETWORK_IS_AMERICAS_VERSION() { return invoke<BOOL>(0x0292BD7F3766CEBC); }
	NATIVE_DECL BOOL NETWORK_IS_SESSION_STARTED() { return invoke<BOOL>(0x9DE624D2FC4B603F); }
	NATIVE_DECL BOOL NETWORK_IS_SESSION_BUSY() { return invoke<BOOL>(0xF4435D66A8E2905E); }
	NATIVE_DECL BOOL NETWORK_CAN_SESSION_END() { return invoke<BOOL>(0x4EEBC3694E49C572); }
	NATIVE_DECL int NETWORK_GET_GAME_MODE() { return invoke<int>(0x4C9034162368E206); }
	NATIVE_DECL void NETWORK_SESSION_MARK_VISIBLE(BOOL toggle) { invoke<Void>(0x271CC6AB59EBF9A5, toggle); }
	NATIVE_DECL BOOL NETWORK_SESSION_IS_VISIBLE() { return invoke<BOOL>(0xBA416D68C631496A); }
	NATIVE_DECL void NETWORK_SESSION_BLOCK_JOIN_REQUESTS(BOOL toggle) { invoke<Void>(0xA73667484D7037C3, toggle); }
	NATIVE_DECL void NETWORK_SESSION_CHANGE_SLOTS(int slots, BOOL p1) { invoke<Void>(0xB4AB419E0D86ACAE, slots, p1); }
	NATIVE_DECL int NETWORK_SESSION_GET_PRIVATE_SLOTS() { return invoke<int>(0x53AFD64C6758F2F9); }
	NATIVE_DECL BOOL NETWORK_SESSION_VOICE_HOST() { return invoke<BOOL>(0x9C1556705F864230); }
	NATIVE_DECL BOOL NETWORK_SESSION_VOICE_LEAVE() { return invoke<BOOL>(0x6793E42BE02B575D); }
	NATIVE_DECL void NETWORK_SESSION_VOICE_CONNECT_TO_PLAYER(Any* gamerHandle) { invoke<Void>(0xABD5E88B8A2D3DB2, gamerHandle); }
	NATIVE_DECL void NETWORK_SESSION_VOICE_RESPOND_TO_REQUEST(BOOL p0, int p1) { invoke<Void>(0x7F8413B7FC2AA6B9, p0, p1); }
	NATIVE_DECL void NETWORK_SESSION_VOICE_SET_TIMEOUT(int timeout) { invoke<Void>(0x5B8ED3DB018927B1, timeout); }
	NATIVE_DECL BOOL NETWORK_SESSION_IS_IN_VOICE_SESSION() { return invoke<BOOL>(0x855BC38818F6F684); }
	NATIVE_DECL BOOL NETWORK_SESSION_IS_VOICE_SESSION_ACTIVE() { return invoke<BOOL>(0xB5D3453C98456528); }
	NATIVE_DECL BOOL NETWORK_SESSION_IS_VOICE_SESSION_BUSY() { return invoke<BOOL>(0xEF0912DDF7C4CB4B); }
	NATIVE_DECL BOOL NETWORK_SEND_TEXT_MESSAGE(const char* message, Any* gamerHandle) { return invoke<BOOL>(0x3A214F2EC889B100, message, gamerHandle); }
	NATIVE_DECL void NETWORK_SET_ACTIVITY_SPECTATOR(BOOL toggle) { invoke<Void>(0x75138790B4359A74, toggle); }
	NATIVE_DECL BOOL NETWORK_IS_ACTIVITY_SPECTATOR() { return invoke<BOOL>(0x12103B9E0C9F92FB); }
	NATIVE_DECL void NETWORK_SET_ACTIVITY_PLAYER_MAX(Any p0) { invoke<Void>(0x0E4F77F7B9D74D84, p0); }
	NATIVE_DECL void NETWORK_SET_ACTIVITY_SPECTATOR_MAX(int maxSpectators) { invoke<Void>(0x9D277B76D1D12222, maxSpectators); }
	NATIVE_DECL int NETWORK_GET_ACTIVITY_PLAYER_NUM(BOOL p0) { return invoke<int>(0x73E2B500410DA5A2, p0); }
	NATIVE_DECL BOOL NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(Any* gamerHandle) { return invoke<BOOL>(0x2763BBAA72A7BCB9, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_HOST_TRANSITION(int p0, int p1, int p2, int p3, Any p4, BOOL p5, BOOL p6, int p7, Any p8, int p9) { return invoke<BOOL>(0xA60BB5CE242BB254, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	NATIVE_DECL BOOL NETWORK_DO_TRANSITION_QUICKMATCH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x71FB0EBCD4915D56, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL BOOL NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0xA091A5E44F0072E5, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL BOOL NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP(Any p0, Any p1, Any p2, Any p3, Any* p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0x9C4AB58491FDC98A, p0, p1, p2, p3, p4, p5, p6, p7); }
	NATIVE_DECL BOOL NETWORK_JOIN_GROUP_ACTIVITY() { return invoke<BOOL>(0xA06509A691D12BE4); }
	NATIVE_DECL void NETWORK_CLEAR_GROUP_ACTIVITY() { invoke<Void>(0x1888694923EF4591); }
	NATIVE_DECL void NETWORK_RETAIN_ACTIVITY_GROUP() { invoke<Void>(0xB13E88E655E5A3BC); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_CLOSED_FRIENDS() { return invoke<BOOL>(0x6512765E3BE78C50); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_CLOSED_CREW() { return invoke<BOOL>(0x0DBD5D7E3C5BEC3B); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_SOLO() { return invoke<BOOL>(0x5DC577201723960A); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_PRIVATE() { return invoke<BOOL>(0x5A6AA44FF8E931E6); }
	NATIVE_DECL int NETWORK_GET_NUM_TRANSITION_NON_ASYNC_GAMERS() { return invoke<int>(0x617F49C2668E6155); }
	NATIVE_DECL void NETWORK_MARK_AS_PREFERRED_ACTIVITY(BOOL p0) { invoke<Void>(0x261E97AD7BCF3D40, p0); }
	NATIVE_DECL void NETWORK_MARK_AS_WAITING_ASYNC(BOOL p0) { invoke<Void>(0x39917E1B4CB0F911, p0); }
	NATIVE_DECL void NETWORK_SET_IN_PROGRESS_FINISH_TIME(Any p0) { invoke<Void>(0x2CE9D95E4051AECD, p0); }
	NATIVE_DECL void NETWORK_SET_TRANSITION_CREATOR_HANDLE(Any* p0) { invoke<Void>(0xEF26739BCD9907D5, p0); }
	NATIVE_DECL void NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE() { invoke<Void>(0xFB3272229A82C759); }
	NATIVE_DECL BOOL NETWORK_INVITE_GAMERS_TO_TRANSITION(Any* p0, Any p1) { return invoke<BOOL>(0x4A595C32F77DFF76, p0, p1); }
	NATIVE_DECL void NETWORK_SET_GAMER_INVITED_TO_TRANSITION(Any* gamerHandle) { invoke<Void>(0xCA2C8073411ECDB6, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_LEAVE_TRANSITION() { return invoke<BOOL>(0xD23A1A815D21DB19); }
	NATIVE_DECL BOOL NETWORK_LAUNCH_TRANSITION() { return invoke<BOOL>(0x2DCF46CB1A4F0884); }
	NATIVE_DECL void NETWORK_SET_DO_NOT_LAUNCH_FROM_JOIN_AS_MIGRATED_HOST(BOOL toggle) { invoke<Void>(0xA2E9C1AB8A92E8CD, toggle); }
	NATIVE_DECL void NETWORK_CANCEL_TRANSITION_MATCHMAKING() { invoke<Void>(0x023782EFC70585EE); }
	NATIVE_DECL void NETWORK_BAIL_TRANSITION(int p0, int p1, int p2) { invoke<Void>(0xEAA572036990CD1B, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_DO_TRANSITION_TO_GAME(BOOL p0, int maxPlayers) { return invoke<BOOL>(0x3E9BB38102A589B0, p0, maxPlayers); }
	NATIVE_DECL BOOL NETWORK_DO_TRANSITION_TO_NEW_GAME(BOOL p0, int maxPlayers, BOOL p2) { return invoke<BOOL>(0x4665F51EFED00034, p0, maxPlayers, p2); }
	NATIVE_DECL BOOL NETWORK_DO_TRANSITION_TO_FREEMODE(Any* p0, Any p1, BOOL p2, int players, BOOL p4) { return invoke<BOOL>(0x3AAD8B2FCA1E289F, p0, p1, p2, players, p4); }
	NATIVE_DECL BOOL NETWORK_DO_TRANSITION_TO_NEW_FREEMODE(Any* p0, Any p1, int players, BOOL p3, BOOL p4, BOOL p5) { return invoke<BOOL>(0x9E80A5BA8109F974, p0, p1, players, p3, p4, p5); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_TO_GAME() { return invoke<BOOL>(0x9D7696D8F4FA6CB7); }
	NATIVE_DECL int NETWORK_GET_TRANSITION_MEMBERS(Any* data, int dataCount) { return invoke<int>(0x73B000F7FBC55829, data, dataCount); }
	NATIVE_DECL void NETWORK_APPLY_TRANSITION_PARAMETER(int p0, int p1) { invoke<Void>(0x521638ADA1BA0D18, p0, p1); }
	NATIVE_DECL void NETWORK_APPLY_TRANSITION_PARAMETER_STRING(int p0, const char* string, BOOL p2) { invoke<Void>(0xEBEFC2E77084F599, p0, string, p2); }
	NATIVE_DECL BOOL NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION(Any* gamerHandle, const char* p1, int p2, int p3, BOOL p4) { return invoke<BOOL>(0x31D1D2B858D25E6B, gamerHandle, p1, p2, p3, p4); }
	NATIVE_DECL BOOL NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED(Any* p0) { return invoke<BOOL>(0x5728BB6D63E3FF1D, p0); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_HOST() { return invoke<BOOL>(0x0B824797C9BF2159); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_HOST_FROM_HANDLE(Any* gamerHandle) { return invoke<BOOL>(0x6B5C83BA3EFE6A10, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_GET_TRANSITION_HOST(Any* gamerHandle) { return invoke<BOOL>(0x65042B9774C4435E, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_IS_IN_TRANSITION() { return invoke<BOOL>(0x68049AEFF83D8F0A); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_STARTED() { return invoke<BOOL>(0x53FA83401D9C07FE); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_BUSY() { return invoke<BOOL>(0x520F3282A53D26B7); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_MATCHMAKING() { return invoke<BOOL>(0x292564C735375EDF); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_LEAVE_POSTPONED() { return invoke<BOOL>(0xC571D0E77D8BBC29); }
	NATIVE_DECL void NETWORK_TRANSITION_SET_IN_PROGRESS(Any p0) { invoke<Void>(0x1398582B7F72B3ED, p0); }
	NATIVE_DECL void NETWORK_TRANSITION_SET_CONTENT_CREATOR(Any p0) { invoke<Void>(0x1F8E00FB18239600, p0); }
	NATIVE_DECL void NETWORK_TRANSITION_SET_ACTIVITY_ISLAND(Any p0) { invoke<Void>(0xF6F4383B7C92F11A, p0); }
	NATIVE_DECL void NETWORK_OPEN_TRANSITION_MATCHMAKING() { invoke<Void>(0x2B3A8F7CA3A38FDE); }
	NATIVE_DECL void NETWORK_CLOSE_TRANSITION_MATCHMAKING() { invoke<Void>(0x43F4DBA69710E01E); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_OPEN_TO_MATCHMAKING() { return invoke<BOOL>(0x37A4494483B9F5C9); }
	NATIVE_DECL void NETWORK_SET_TRANSITION_VISIBILITY_LOCK(BOOL p0, BOOL p1) { invoke<Void>(0x0C978FDA19692C2C, p0, p1); }
	NATIVE_DECL BOOL NETWORK_IS_TRANSITION_VISIBILITY_LOCKED() { return invoke<BOOL>(0xD0A484CB2F829FBE); }
	NATIVE_DECL void NETWORK_SET_TRANSITION_ACTIVITY_ID(Any p0) { invoke<Void>(0x30DE938B516F0AD2, p0); }
	NATIVE_DECL void NETWORK_CHANGE_TRANSITION_SLOTS(Any p0, BOOL p1) { invoke<Void>(0xEEEDA5E6D7080987, p0, p1); }
	NATIVE_DECL void NETWORK_TRANSITION_BLOCK_JOIN_REQUESTS(BOOL p0) { invoke<Void>(0x973D76AA760A6CB6, p0); }
	NATIVE_DECL BOOL NETWORK_HAS_PLAYER_STARTED_TRANSITION(Player player) { return invoke<BOOL>(0x9AC9CCBFA8C29795, player); }
	NATIVE_DECL BOOL NETWORK_ARE_TRANSITION_DETAILS_VALID(Any p0) { return invoke<BOOL>(0x2615AA2A695930C1, p0); }
	NATIVE_DECL BOOL NETWORK_JOIN_TRANSITION(Player player) { return invoke<BOOL>(0x9D060B08CD63321A, player); }
	NATIVE_DECL BOOL NETWORK_HAS_INVITED_GAMER_TO_TRANSITION(Any* p0) { return invoke<BOOL>(0x7284A47B3540E6CF, p0); }
	NATIVE_DECL BOOL NETWORK_HAS_TRANSITION_INVITE_BEEN_ACKED(Any* p0) { return invoke<BOOL>(0x3F9990BF5F22759C, p0); }
	NATIVE_DECL BOOL NETWORK_IS_ACTIVITY_SESSION() { return invoke<BOOL>(0x05095437424397FA); }
	NATIVE_DECL void NETWORK_DISABLE_REALTIME_MULTIPLAYER() { invoke<Void>(0x236905C700FDB54D); }
	NATIVE_DECL void NETWORK_SET_PRESENCE_SESSION_INVITES_BLOCKED(BOOL toggle) { invoke<Void>(0x4A9FDE3A5A6D0437, toggle); }
	NATIVE_DECL BOOL NETWORK_SEND_INVITE_VIA_PRESENCE(Any* gamerHandle, const char* p1, int dataCount, int p3) { return invoke<BOOL>(0xC3C7A6AFDB244624, gamerHandle, p1, dataCount, p3); }
	NATIVE_DECL BOOL NETWORK_SEND_TRANSITION_INVITE_VIA_PRESENCE(Any* gamerHandle, const char* p1, int dataCount, int p3) { return invoke<BOOL>(0xC116FF9B4D488291, gamerHandle, p1, dataCount, p3); }
	NATIVE_DECL BOOL NETWORK_SEND_IMPORTANT_TRANSITION_INVITE_VIA_PRESENCE(Any* gamerHandle, const char* p1, int dataCount, int p3) { return invoke<BOOL>(0x1171A97A3D3981B6, gamerHandle, p1, dataCount, p3); }
	NATIVE_DECL int NETWORK_GET_PRESENCE_INVITE_INDEX_BY_ID(int p0) { return invoke<int>(0x742B58F723233ED9, p0); }
	NATIVE_DECL int NETWORK_GET_NUM_PRESENCE_INVITES() { return invoke<int>(0xCEFA968912D0F78D); }
	NATIVE_DECL BOOL NETWORK_ACCEPT_PRESENCE_INVITE(int p0) { return invoke<BOOL>(0xFA91550DF9318B22, p0); }
	NATIVE_DECL BOOL NETWORK_REMOVE_PRESENCE_INVITE(int p0) { return invoke<BOOL>(0xF0210268DB0974B1, p0); }
	NATIVE_DECL int NETWORK_GET_PRESENCE_INVITE_ID(int p0) { return invoke<int>(0xDFF09646E12EC386, p0); }
	NATIVE_DECL const char* NETWORK_GET_PRESENCE_INVITE_INVITER(int p0) { return invoke<const char*>(0x4962CC4AA2F345B7, p0); }
	NATIVE_DECL BOOL NETWORK_GET_PRESENCE_INVITE_HANDLE(Any p0, Any* p1) { return invoke<BOOL>(0x38D5B0FEBB086F75, p0, p1); }
	NATIVE_DECL int NETWORK_GET_PRESENCE_INVITE_SESSION_ID(Any p0) { return invoke<int>(0x26E1CD96B0903D60, p0); }
	NATIVE_DECL const char* NETWORK_GET_PRESENCE_INVITE_CONTENT_ID(int p0) { return invoke<const char*>(0x24409FC4C55CB22D, p0); }
	NATIVE_DECL int NETWORK_GET_PRESENCE_INVITE_PLAYLIST_LENGTH(int p0) { return invoke<int>(0xD39B3FFF8FFDD5BF, p0); }
	NATIVE_DECL int NETWORK_GET_PRESENCE_INVITE_PLAYLIST_CURRENT(int p0) { return invoke<int>(0x728C4CC7920CD102, p0); }
	NATIVE_DECL BOOL NETWORK_GET_PRESENCE_INVITE_FROM_ADMIN(int p0) { return invoke<BOOL>(0x3DBF2DF0AEB7D289, p0); }
	NATIVE_DECL BOOL NETWORK_GET_PRESENCE_INVITE_IS_TOURNAMENT(Any p0) { return invoke<BOOL>(0x8806CEBFABD3CE05, p0); }
	NATIVE_DECL BOOL NETWORK_HAS_FOLLOW_INVITE() { return invoke<BOOL>(0x76D9B976C4C09FDE); }
	NATIVE_DECL BOOL NETWORK_ACTION_FOLLOW_INVITE() { return invoke<BOOL>(0xC88156EBB786F8D5); }
	NATIVE_DECL BOOL NETWORK_CLEAR_FOLLOW_INVITE() { return invoke<BOOL>(0x439BFDE3CD0610F6); }
	NATIVE_DECL void NETWORK_REMOVE_AND_CANCEL_ALL_INVITES() { invoke<Void>(0xEBF8284D8CADEB53); }
	NATIVE_DECL void NETWORK_REMOVE_TRANSITION_INVITE(Any* p0) { invoke<Void>(0x7524B431B2E6F7EE, p0); }
	NATIVE_DECL void NETWORK_REMOVE_ALL_TRANSITION_INVITE() { invoke<Void>(0x726E0375C7A26368); }
	NATIVE_DECL void NETWORK_REMOVE_AND_CANCEL_ALL_TRANSITION_INVITES() { invoke<Void>(0xF083835B70BA9BFE); }
	NATIVE_DECL BOOL NETWORK_INVITE_GAMERS(Any* p0, Any p1, Any* p2, Any p3) { return invoke<BOOL>(0x9D80CD1D0E6327DE, p0, p1, p2, p3); }
	NATIVE_DECL BOOL NETWORK_HAS_INVITED_GAMER(Any* p0) { return invoke<BOOL>(0x4D86CD31E8976ECE, p0); }
	NATIVE_DECL BOOL NETWORK_HAS_MADE_INVITE_DECISION(Any* gamerHandle) { return invoke<BOOL>(0x71DC455F5CD1C2B1, gamerHandle); }
	NATIVE_DECL int NETWORK_GET_INVITE_REPLY_STATUS(Any p0) { return invoke<int>(0x3855FB5EB2C5E8B2, p0); }
	NATIVE_DECL BOOL NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(Any* p0) { return invoke<BOOL>(0x74881E6BCAE2327C, p0); }
	NATIVE_DECL BOOL NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(Any* p0) { return invoke<BOOL>(0x7206F674F2A3B1BB, p0); }
	NATIVE_DECL void NETWORK_SET_INVITE_ON_CALL_FOR_INVITE_MENU(Any* p0) { invoke<Void>(0x66F010A4B031A331, p0); }
	NATIVE_DECL BOOL NETWORK_CHECK_DATA_MANAGER_SUCCEEDED_FOR_HANDLE(int p0, Any* gamerHandle) { return invoke<BOOL>(0x44B37CDCAE765AAE, p0, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CHECK_DATA_MANAGER_FOR_HANDLE(Any p0, Any* gamerHandle) { return invoke<BOOL>(0x4AD490AE1536933B, p0, gamerHandle); }
	NATIVE_DECL void NETWORK_SET_INVITE_FAILED_MESSAGE_FOR_INVITE_MENU(Any* p0, Any* p1) { invoke<Void>(0x0D77A82DC2D0DA59, p0, p1); }
	NATIVE_DECL BOOL FILLOUT_PM_PLAYER_LIST(Any* gamerHandle, Any p1, Any p2) { return invoke<BOOL>(0xCBBD7C4991B64809, gamerHandle, p1, p2); }
	NATIVE_DECL BOOL FILLOUT_PM_PLAYER_LIST_WITH_NAMES(Any* p0, Any* p1, Any p2, Any p3) { return invoke<BOOL>(0x716B6DB9D1886106, p0, p1, p2, p3); }
	NATIVE_DECL BOOL REFRESH_PLAYER_LIST_STATS(int p0) { return invoke<BOOL>(0xE26CCFF8094D8C74, p0); }
	NATIVE_DECL BOOL NETWORK_SET_CURRENT_DATA_MANAGER_HANDLE(Any* p0) { return invoke<BOOL>(0x796A87B3B68D1F3D, p0); }
	NATIVE_DECL BOOL NETWORK_IS_IN_PLATFORM_PARTY() { return invoke<BOOL>(0x2FC5650B0271CB57); }
	NATIVE_DECL int NETWORK_GET_PLATFORM_PARTY_MEMBER_COUNT() { return invoke<int>(0x01ABCE5E7CBDA196); }
	NATIVE_DECL int NETWORK_GET_PLATFORM_PARTY_MEMBERS(Any* data, int dataSize) { return invoke<int>(0x120364DE2845DAF8, data, dataSize); }
	NATIVE_DECL BOOL NETWORK_IS_IN_PLATFORM_PARTY_CHAT() { return invoke<BOOL>(0xFD8B834A8BA05048); }
	NATIVE_DECL BOOL NETWORK_IS_CHATTING_IN_PLATFORM_PARTY(Any* gamerHandle) { return invoke<BOOL>(0x8DE9945BCC9AEC52, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CAN_QUEUE_FOR_PREVIOUS_SESSION_JOIN() { return invoke<BOOL>(0x2BF66D2E7414F686); }
	NATIVE_DECL BOOL NETWORK_IS_QUEUING_FOR_SESSION_JOIN() { return invoke<BOOL>(0x14922ED3E38761F0); }
	NATIVE_DECL void NETWORK_CLEAR_QUEUED_JOIN_REQUEST() { invoke<Void>(0x6CE50E47F5543D0C); }
	NATIVE_DECL void NETWORK_SEND_QUEUED_JOIN_REQUEST() { invoke<Void>(0xFA2888E3833C8E96); }
	NATIVE_DECL void NETWORK_REMOVE_ALL_QUEUED_JOIN_REQUESTS() { invoke<Void>(0x25D990F8E0E3F13C); }
	NATIVE_DECL void NETWORK_SEED_RANDOM_NUMBER_GENERATOR(int seed) { invoke<Void>(0xF1B84178F8674195, seed); }
	NATIVE_DECL int NETWORK_GET_RANDOM_INT() { return invoke<int>(0x599E4FA1F87EB5FF); }
	NATIVE_DECL int NETWORK_GET_RANDOM_INT_RANGED(int rangeStart, int rangeEnd) { return invoke<int>(0xE30CF56F1EFA5F43, rangeStart, rangeEnd); }
	NATIVE_DECL float _NETWORK_GET_RANDOM_FLOAT_RANGED(float rangeStart, float rangeEnd) { return invoke<float>(0x04BD27B5ACB67067, rangeStart, rangeEnd); }
	NATIVE_DECL BOOL NETWORK_PLAYER_IS_CHEATER() { return invoke<BOOL>(0x655B91F1495A9090); }
	NATIVE_DECL int NETWORK_PLAYER_GET_CHEATER_REASON() { return invoke<int>(0x172F75B6EE2233BA); }
	NATIVE_DECL BOOL NETWORK_PLAYER_IS_BADSPORT() { return invoke<BOOL>(0x19D8DA0E5A68045A); }
	NATIVE_DECL BOOL REMOTE_CHEATER_PLAYER_DETECTED(Player player, int a, int b) { return invoke<BOOL>(0x472841A026D26D8B, player, a, b); }
	NATIVE_DECL BOOL BAD_SPORT_PLAYER_LEFT_DETECTED(Any* gamerHandle, int event, int amountReceived) { return invoke<BOOL>(0xEC5E3AF5289DCA81, gamerHandle, event, amountReceived); }
	NATIVE_DECL void NETWORK_ADD_INVALID_OBJECT_MODEL(Hash modelHash, Any p1) { invoke<Void>(0x7F562DBC212E81F9, modelHash, p1); }
	NATIVE_DECL void NETWORK_REMOVE_INVALID_OBJECT_MODEL(Hash modelHash) { invoke<Void>(0x791EDB5803B2F468, modelHash); }
	NATIVE_DECL void NETWORK_CLEAR_INVALID_OBJECT_MODELS() { invoke<Void>(0x03B2F03A53D85E41); }
	NATIVE_DECL void NETWORK_APPLY_PED_SCAR_DATA(Ped ped, int p1) { invoke<Void>(0xE66C690248F11150, ped, p1); }
	NATIVE_DECL void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(int maxNumMissionParticipants, BOOL p1, int instanceId) { invoke<Void>(0x1CA59E306ECB80A5, maxNumMissionParticipants, p1, instanceId); }
	NATIVE_DECL BOOL NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(Any p0, BOOL p1, Any p2) { return invoke<BOOL>(0xD1110739EEADB592, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT() { return invoke<BOOL>(0x2910669969E9535E); }
	NATIVE_DECL int NETWORK_GET_MAX_NUM_PARTICIPANTS() { return invoke<int>(0xA6C90FBC38E395EE); }
	NATIVE_DECL int NETWORK_GET_NUM_PARTICIPANTS() { return invoke<int>(0x18D0456E86604654); }
	NATIVE_DECL int NETWORK_GET_SCRIPT_STATUS() { return invoke<int>(0x57D158647A6BFABF); }
	NATIVE_DECL void NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(int* vars, int numVars, const char* debugName) { invoke<Void>(0x3E9B2F01C50DF595, vars, numVars, debugName); }
	NATIVE_DECL void NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(int* vars, int numVars, const char* debugName) { invoke<Void>(0x3364AA97340CA215, vars, numVars, debugName); }
	NATIVE_DECL void NETWORK_REGISTER_HIGH_FREQUENCY_HOST_BROADCAST_VARIABLES(Any p0, Any p1, Any p2) { invoke<Void>(0xEA8C0DDB10E2822A, p0, p1, p2); }
	NATIVE_DECL void NETWORK_REGISTER_HIGH_FREQUENCY_PLAYER_BROADCAST_VARIABLES(Any p0, Any p1, Any p2) { invoke<Void>(0xD6D7478CA62B8D41, p0, p1, p2); }
	NATIVE_DECL void NETWORK_FINISH_BROADCASTING_DATA() { invoke<Void>(0x64F62AFB081E260D); }
	NATIVE_DECL int _NETWORK_GET_HOST_BROADCAST_DATA_SIZE_UNSYNCED(Hash scriptNameHash, int instance, Hash positionHash, int handlerNum) { return invoke<int>(0x72C8588ABE22C972, scriptNameHash, instance, positionHash, handlerNum); }
	NATIVE_DECL int _NETWORK_GET_PLAYER_BROADCAST_DATA_SIZE_UNSYNCED(Hash scriptNameHash, int instance, Hash positionHash, int handlerNum) { return invoke<int>(0xB99CD664FD4720A1, scriptNameHash, instance, positionHash, handlerNum); }
	NATIVE_DECL int _NETWORK_GET_BROADCAST_DATA_HOST_UPDATE_SIZE(Hash scriptNameHash, int instance, Hash positionHash, int handlerNum) { return invoke<int>(0xE448693B3EA3B92C, scriptNameHash, instance, positionHash, handlerNum); }
	NATIVE_DECL int _NETWORK_GET_BROADCAST_DATA_PLAYER_UPDATE_SIZE(Hash scriptNameHash, int instance, Hash positionHash, int handlerNum) { return invoke<int>(0xAC3F722321800755, scriptNameHash, instance, positionHash, handlerNum); }
	NATIVE_DECL BOOL NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA() { return invoke<BOOL>(0x5D10B3795F3FC886); }
	NATIVE_DECL Player NETWORK_GET_PLAYER_INDEX(Player player) { return invoke<Player>(0x24FB80D107371267, player); }
	NATIVE_DECL int NETWORK_GET_PARTICIPANT_INDEX(int index) { return invoke<int>(0x1B84DF6AF2A46938, index); }
	NATIVE_DECL Player NETWORK_GET_PLAYER_INDEX_FROM_PED(Ped ped) { return invoke<Player>(0x6C0E2E0125610278, ped); }
	NATIVE_DECL int NETWORK_GET_NUM_CONNECTED_PLAYERS() { return invoke<int>(0xA4A79DD2D9600654); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_CONNECTED(Player player) { return invoke<BOOL>(0x93DC1BE4E1ABE9D1, player); }
	NATIVE_DECL int NETWORK_GET_TOTAL_NUM_PLAYERS() { return invoke<int>(0xCF61D4B4702EE9EB); }
	NATIVE_DECL BOOL NETWORK_IS_PARTICIPANT_ACTIVE(int p0) { return invoke<BOOL>(0x6FF8FF40B6357D45, p0); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_ACTIVE(Player player) { return invoke<BOOL>(0xB8DFD30D6973E135, player); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_A_PARTICIPANT(Player player) { return invoke<BOOL>(0x3CA58F6CB7CBD784, player); }
	NATIVE_DECL BOOL NETWORK_IS_HOST_OF_THIS_SCRIPT() { return invoke<BOOL>(0x83CD99A1E6061AB5); }
	NATIVE_DECL Player NETWORK_GET_HOST_OF_THIS_SCRIPT() { return invoke<Player>(0xC7B4D79B01FA7A5C); }
	NATIVE_DECL Player NETWORK_GET_HOST_OF_SCRIPT(const char* scriptName, int instance_id, int position_hash) { return invoke<Player>(0x1D6A14F1F9A736FC, scriptName, instance_id, position_hash); }
	NATIVE_DECL Player NETWORK_GET_HOST_OF_THREAD(int threadId) { return invoke<Player>(0xD3DEBE2991FE8098, threadId); }
	NATIVE_DECL void NETWORK_SET_MISSION_FINISHED() { invoke<Void>(0x3B3D11CD9FFCDFC9); }
	NATIVE_DECL BOOL NETWORK_IS_SCRIPT_ACTIVE(const char* scriptName, int instance_id, BOOL p2, int position_hash) { return invoke<BOOL>(0x9D40DF90FAD26098, scriptName, instance_id, p2, position_hash); }
	NATIVE_DECL BOOL NETWORK_IS_SCRIPT_ACTIVE_BY_HASH(Hash scriptHash, int p1, BOOL p2, int p3) { return invoke<BOOL>(0xDA7DE67F5FE5EE13, scriptHash, p1, p2, p3); }
	NATIVE_DECL BOOL NETWORK_IS_THREAD_A_NETWORK_SCRIPT(int threadId) { return invoke<BOOL>(0x560B423D73015E77, threadId); }
	NATIVE_DECL int NETWORK_GET_NUM_SCRIPT_PARTICIPANTS(const char* scriptName, int instance_id, int position_hash) { return invoke<int>(0x3658E8CD94FC121A, scriptName, instance_id, position_hash); }
	NATIVE_DECL int NETWORK_GET_INSTANCE_ID_OF_THIS_SCRIPT() { return invoke<int>(0x638A3A81733086DB); }
	NATIVE_DECL Hash NETWORK_GET_POSITION_HASH_OF_THIS_SCRIPT() { return invoke<Hash>(0x257ED0FADF750BCF); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(Player player, const char* script, int instance_id) { return invoke<BOOL>(0x1AD5B71586B94820, player, script, instance_id); }
	NATIVE_DECL void NETWORK_PREVENT_SCRIPT_HOST_MIGRATION() { invoke<Void>(0x2302C0264EA58D31); }
	NATIVE_DECL void NETWORK_REQUEST_TO_BE_HOST_OF_THIS_SCRIPT() { invoke<Void>(0x741A3D8380319A81); }
	NATIVE_DECL Player PARTICIPANT_ID() { return invoke<Player>(0x90986E8876CE0A83); }
	NATIVE_DECL int PARTICIPANT_ID_TO_INT() { return invoke<int>(0x57A3BDDAD8E5AA0A); }
	NATIVE_DECL Player NETWORK_GET_KILLER_OF_PLAYER(Player player, Hash* weaponHash) { return invoke<Player>(0x2DA41ED6E1FCD7A5, player, weaponHash); }
	NATIVE_DECL Player NETWORK_GET_DESTROYER_OF_NETWORK_ID(int netId, Hash* weaponHash) { return invoke<Player>(0x7A1ADEEF01740A24, netId, weaponHash); }
	NATIVE_DECL Player NETWORK_GET_DESTROYER_OF_ENTITY(Entity entity, Hash* weaponHash) { return invoke<Player>(0xC434133D9BA52777, entity, weaponHash); }
	NATIVE_DECL BOOL NETWORK_GET_ASSISTED_KILL_OF_ENTITY(Player player, Entity entity, int* p2) { return invoke<BOOL>(0x83660B734994124D, player, entity, p2); }
	NATIVE_DECL BOOL NETWORK_GET_ASSISTED_DAMAGE_OF_ENTITY(Player player, Entity entity, int* p2) { return invoke<BOOL>(0x4CACA84440FA26F6, player, entity, p2); }
	NATIVE_DECL Entity NETWORK_GET_ENTITY_KILLER_OF_PLAYER(Player player, Hash* weaponHash) { return invoke<Entity>(0x42B2DAA6B596F5F8, player, weaponHash); }
	NATIVE_DECL void NETWORK_SET_CURRENT_PUBLIC_CONTENT_ID(const char* missionId) { invoke<Void>(0x2C863ACDCD12B3DB, missionId); }
	NATIVE_DECL void NETWORK_SET_CURRENT_CHAT_OPTION(int newChatOption) { invoke<Void>(0x3DAD00265FBF356B, newChatOption); }
	NATIVE_DECL void NETWORK_SET_CURRENT_SPAWN_LOCATION_OPTION(Hash mpSettingSpawn) { invoke<Void>(0xAA6D5451DC3448B6, mpSettingSpawn); }
	NATIVE_DECL void NETWORK_SET_VEHICLE_DRIVEN_IN_TEST_DRIVE(BOOL toggle) { invoke<Void>(0x8C70252FC40F320B, toggle); }
	NATIVE_DECL void NETWORK_SET_VEHICLE_DRIVEN_LOCATION(Hash location) { invoke<Void>(0xA0CE91E47531D3BB, location); }
	NATIVE_DECL void NETWORK_RESURRECT_LOCAL_PLAYER(float x, float y, float z, float heading, BOOL p4, BOOL changetime, BOOL p6, int p7, int p8) { invoke<Void>(0xEA23C49EAA83ACFB, x, y, z, heading, p4, changetime, p6, p7, p8); }
	NATIVE_DECL void NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME(int time) { invoke<Void>(0x2D95C7E2D7E07307, time); }
	NATIVE_DECL BOOL NETWORK_IS_LOCAL_PLAYER_INVINCIBLE() { return invoke<BOOL>(0x8A8694B48715B000); }
	NATIVE_DECL void NETWORK_DISABLE_INVINCIBLE_FLASHING(Player player, BOOL toggle) { invoke<Void>(0x9DD368BF06983221, player, toggle); }
	NATIVE_DECL void NETWORK_PATCH_POST_CUTSCENE_HS4F_TUN_ENT(Ped ped) { invoke<Void>(0xF0BC9BCD24A511D5, ped); }
	NATIVE_DECL void NETWORK_SET_LOCAL_PLAYER_SYNC_LOOK_AT(BOOL toggle) { invoke<Void>(0x524FF0AEFF9C3973, toggle); }
	NATIVE_DECL BOOL NETWORK_HAS_ENTITY_BEEN_REGISTERED_WITH_THIS_THREAD(Entity entity) { return invoke<BOOL>(0xB07D3185E11657A5, entity); }
	NATIVE_DECL int NETWORK_GET_NETWORK_ID_FROM_ENTITY(Entity entity) { return invoke<int>(0xA11700682F3AD45C, entity); }
	NATIVE_DECL Entity NETWORK_GET_ENTITY_FROM_NETWORK_ID(int netId) { return invoke<Entity>(0xCE4E5D9B0A4FF560, netId); }
	NATIVE_DECL BOOL NETWORK_GET_ENTITY_IS_NETWORKED(Entity entity) { return invoke<BOOL>(0xC7827959479DCC78, entity); }
	NATIVE_DECL BOOL NETWORK_GET_ENTITY_IS_LOCAL(Entity entity) { return invoke<BOOL>(0x0991549DE4D64762, entity); }
	NATIVE_DECL void NETWORK_REGISTER_ENTITY_AS_NETWORKED(Entity entity) { invoke<Void>(0x06FAACD625D80CAA, entity); }
	NATIVE_DECL void NETWORK_UNREGISTER_NETWORKED_ENTITY(Entity entity) { invoke<Void>(0x7368E683BB9038D6, entity); }
	NATIVE_DECL BOOL NETWORK_DOES_NETWORK_ID_EXIST(int netId) { return invoke<BOOL>(0x38CE16C96BD11344, netId); }
	NATIVE_DECL BOOL NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(int netId) { return invoke<BOOL>(0x18A47D074708FD68, netId); }
	NATIVE_DECL BOOL NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(int netId) { return invoke<BOOL>(0xA670B3662FAFFBD0, netId); }
	NATIVE_DECL BOOL NETWORK_HAS_CONTROL_OF_NETWORK_ID(int netId) { return invoke<BOOL>(0x4D36070FE0215186, netId); }
	NATIVE_DECL BOOL NETWORK_IS_NETWORK_ID_REMOTELY_CONTROLLED(int netId) { return invoke<BOOL>(0x7242F8B741CE1086, netId); }
	NATIVE_DECL BOOL NETWORK_REQUEST_CONTROL_OF_ENTITY(Entity entity) { return invoke<BOOL>(0xB69317BF5E782347, entity); }
	NATIVE_DECL BOOL NETWORK_REQUEST_CONTROL_OF_DOOR(int doorID) { return invoke<BOOL>(0x870DDFD5A4A796E4, doorID); }
	NATIVE_DECL BOOL NETWORK_HAS_CONTROL_OF_ENTITY(Entity entity) { return invoke<BOOL>(0x01BF60A500E28887, entity); }
	NATIVE_DECL BOOL NETWORK_HAS_CONTROL_OF_PICKUP(Pickup pickup) { return invoke<BOOL>(0x5BC9495F0B3B6FA6, pickup); }
	NATIVE_DECL BOOL NETWORK_HAS_CONTROL_OF_DOOR(Hash doorHash) { return invoke<BOOL>(0xCB3C68ADB06195DF, doorHash); }
	NATIVE_DECL BOOL NETWORK_IS_DOOR_NETWORKED(Hash doorHash) { return invoke<BOOL>(0xC01E93FAC20C3346, doorHash); }
	NATIVE_DECL int VEH_TO_NET(Vehicle vehicle) { return invoke<int>(0xB4C94523F023419C, vehicle); }
	NATIVE_DECL int PED_TO_NET(Ped ped) { return invoke<int>(0x0EDEC3C276198689, ped); }
	NATIVE_DECL int OBJ_TO_NET(Object object) { return invoke<int>(0x99BFDC94A603E541, object); }
	NATIVE_DECL Vehicle NET_TO_VEH(int netHandle) { return invoke<Vehicle>(0x367B936610BA360C, netHandle); }
	NATIVE_DECL Ped NET_TO_PED(int netHandle) { return invoke<Ped>(0xBDCD95FC216A8B3E, netHandle); }
	NATIVE_DECL Object NET_TO_OBJ(int netHandle) { return invoke<Object>(0xD8515F5FEA14CB3F, netHandle); }
	NATIVE_DECL Entity NET_TO_ENT(int netHandle) { return invoke<Entity>(0xBFFEAB45A9A9094A, netHandle); }
	NATIVE_DECL void NETWORK_GET_LOCAL_HANDLE(Any* gamerHandle, int gamerHandleSize) { invoke<Void>(0xE86051786B66CD8E, gamerHandle, gamerHandleSize); }
	NATIVE_DECL void NETWORK_HANDLE_FROM_USER_ID(const char* userId, Any* gamerHandle, int gamerHandleSize) { invoke<Void>(0xDCD51DD8F87AEC5C, userId, gamerHandle, gamerHandleSize); }
	NATIVE_DECL void NETWORK_HANDLE_FROM_MEMBER_ID(const char* memberId, Any* gamerHandle, int gamerHandleSize) { invoke<Void>(0xA0FD21BED61E5C4C, memberId, gamerHandle, gamerHandleSize); }
	NATIVE_DECL void NETWORK_HANDLE_FROM_PLAYER(Player player, Any* gamerHandle, int gamerHandleSize) { invoke<Void>(0x388EB2B86C73B6B3, player, gamerHandle, gamerHandleSize); }
	NATIVE_DECL Hash NETWORK_HASH_FROM_PLAYER_HANDLE(Player player) { return invoke<Hash>(0xBC1D768F2F5D6C05, player); }
	NATIVE_DECL Hash NETWORK_HASH_FROM_GAMER_HANDLE(Any* gamerHandle) { return invoke<Hash>(0x58575AC3CF2CA8EC, gamerHandle); }
	NATIVE_DECL void NETWORK_HANDLE_FROM_FRIEND(int friendIndex, Any* gamerHandle, int gamerHandleSize) { invoke<Void>(0xD45CB817D7E177D2, friendIndex, gamerHandle, gamerHandleSize); }
	NATIVE_DECL BOOL NETWORK_GAMERTAG_FROM_HANDLE_START(Any* gamerHandle) { return invoke<BOOL>(0x9F0C0A981D73FA56, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_GAMERTAG_FROM_HANDLE_PENDING() { return invoke<BOOL>(0xB071E27958EF4CF0); }
	NATIVE_DECL BOOL NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED() { return invoke<BOOL>(0xFD00798DBA7523DD); }
	NATIVE_DECL const char* NETWORK_GET_GAMERTAG_FROM_HANDLE(Any* gamerHandle) { return invoke<const char*>(0x426141162EBE5CDB, gamerHandle); }
	NATIVE_DECL int NETWORK_DISPLAYNAMES_FROM_HANDLES_START(Any* p0, Any p1) { return invoke<int>(0xD66C9E72B3CC4982, p0, p1); }
	NATIVE_DECL int NETWORK_GET_DISPLAYNAMES_FROM_HANDLES(Any p0, Any p1, Any p2) { return invoke<int>(0x58CC181719256197, p0, p1, p2); }
	NATIVE_DECL BOOL NETWORK_ARE_HANDLES_THE_SAME(Any* gamerHandle1, Any* gamerHandle2) { return invoke<BOOL>(0x57DBA049E110F217, gamerHandle1, gamerHandle2); }
	NATIVE_DECL BOOL NETWORK_IS_HANDLE_VALID(Any* gamerHandle, int gamerHandleSize) { return invoke<BOOL>(0x6F79B93B0A8E4133, gamerHandle, gamerHandleSize); }
	NATIVE_DECL Player NETWORK_GET_PLAYER_FROM_GAMER_HANDLE(Any* gamerHandle) { return invoke<Player>(0xCE5F689CF5A0A49D, gamerHandle); }
	NATIVE_DECL const char* NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(Any* gamerHandle) { return invoke<const char*>(0xC82630132081BB6F, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_IS_GAMER_IN_MY_SESSION(Any* gamerHandle) { return invoke<BOOL>(0x0F10B05DDF8D16E9, gamerHandle); }
	NATIVE_DECL void NETWORK_SHOW_PROFILE_UI(Any* gamerHandle) { invoke<Void>(0x859ED1CEA343FCA8, gamerHandle); }
	NATIVE_DECL const char* NETWORK_PLAYER_GET_NAME(Player player) { return invoke<const char*>(0x7718D2E2060837D2, player); }
	NATIVE_DECL const char* NETWORK_PLAYER_GET_USERID(Player player, int* userID) { return invoke<const char*>(0x4927FC39CD0869A0, player, userID); }
	NATIVE_DECL BOOL NETWORK_PLAYER_IS_ROCKSTAR_DEV(Player player) { return invoke<BOOL>(0x544ABDDA3B409B6D, player); }
	NATIVE_DECL BOOL NETWORK_PLAYER_INDEX_IS_CHEATER(Player player) { return invoke<BOOL>(0x565E430DB3B05BEC, player); }
	NATIVE_DECL int NETWORK_ENTITY_GET_OBJECT_ID(Entity entity) { return invoke<int>(0x815F18AD865F057F, entity); }
	NATIVE_DECL Entity NETWORK_GET_ENTITY_FROM_OBJECT_ID(Any p0) { return invoke<Entity>(0x37D5F739FD494675, p0); }
	NATIVE_DECL BOOL NETWORK_IS_INACTIVE_PROFILE(Any* p0) { return invoke<BOOL>(0x7E58745504313A2E, p0); }
	NATIVE_DECL const char* _NETWORK_LOAD_GAMER_DISPLAY_NAME(Any* gamerHandle) { return invoke<const char*>(0x338ECE3637937BC2, gamerHandle); }
	NATIVE_DECL int NETWORK_GET_MAX_FRIENDS() { return invoke<int>(0xAFEBB0D5D8F687D2); }
	NATIVE_DECL int NETWORK_GET_FRIEND_COUNT() { return invoke<int>(0x203F1CFD823B27A4); }
	NATIVE_DECL const char* NETWORK_GET_FRIEND_NAME(int friendIndex) { return invoke<const char*>(0xE11EBBB2A783FE8B, friendIndex); }
	NATIVE_DECL const char* NETWORK_GET_FRIEND_DISPLAY_NAME(int friendIndex) { return invoke<const char*>(0x4164F227D052E293, friendIndex); }
	NATIVE_DECL BOOL NETWORK_IS_FRIEND_ONLINE(const char* name) { return invoke<BOOL>(0x425A44533437B64D, name); }
	NATIVE_DECL BOOL NETWORK_IS_FRIEND_HANDLE_ONLINE(Any* gamerHandle) { return invoke<BOOL>(0x87EB7A3FFCB314DB, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_IS_FRIEND_IN_SAME_TITLE(const char* friendName) { return invoke<BOOL>(0x2EA9A3BEDF3F17B8, friendName); }
	NATIVE_DECL BOOL NETWORK_IS_FRIEND_IN_MULTIPLAYER(const char* friendName) { return invoke<BOOL>(0x57005C18827F3A28, friendName); }
	NATIVE_DECL BOOL NETWORK_IS_FRIEND(Any* gamerHandle) { return invoke<BOOL>(0x1A24A179F9B31654, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_IS_PENDING_FRIEND(Any p0) { return invoke<BOOL>(0x0BE73DA6984A6E33, p0); }
	NATIVE_DECL BOOL NETWORK_IS_ADDING_FRIEND() { return invoke<BOOL>(0x6EA101606F6E4D81); }
	NATIVE_DECL BOOL NETWORK_ADD_FRIEND(Any* gamerHandle, const char* message) { return invoke<BOOL>(0x8E02D73914064223, gamerHandle, message); }
	NATIVE_DECL BOOL NETWORK_IS_FRIEND_INDEX_ONLINE(int friendIndex) { return invoke<BOOL>(0xBAD8F2A42B844821, friendIndex); }
	NATIVE_DECL void NETWORK_SET_PLAYER_IS_PASSIVE(BOOL toggle) { invoke<Void>(0x1B857666604B1A74, toggle); }
	NATIVE_DECL BOOL NETWORK_GET_PLAYER_OWNS_WAYPOINT(Player player) { return invoke<BOOL>(0x82377B65E943F72D, player); }
	NATIVE_DECL BOOL NETWORK_CAN_SET_WAYPOINT() { return invoke<BOOL>(0xC927EC229934AF60); }
	NATIVE_DECL void NETWORK_IGNORE_REMOTE_WAYPOINTS() { invoke<Void>(0x4C2A9FDC22377075); }
	NATIVE_DECL BOOL _NETWORK_DOES_COMMUNICATION_GROUP_HAVE_PERMISSION(int communicationType) { return invoke<BOOL>(0xDBDF80673BBA3D65, communicationType); }
	NATIVE_DECL BOOL _NETWORK_DOES_COMMUNICATION_GROUP_HAVE_SETTINGS_ENABLED(int communicationType) { return invoke<BOOL>(0x20C12650830A64EC, communicationType); }
	NATIVE_DECL int _NETWORK_GET_COMMUNICATION_GROUP_FLAGS(int communicationType) { return invoke<int>(0x40DF02F371F40883, communicationType); }
	NATIVE_DECL int _NETWORK_GET_COMMUNICATION_GROUP_DEFAULT_FLAGS(int communicationType) { return invoke<int>(0x97F35B898D2D067F, communicationType); }
	NATIVE_DECL int _NETWORK_GET_COMMUNICATION_GROUP_VALUE(int communicationType) { return invoke<int>(0xBF66ACD9AE81A99F, communicationType); }
	NATIVE_DECL void _NETWORK_SET_COMMUNICATION_GROUP_FLAGS(int communicationType, int communicationGroupFlag) { invoke<Void>(0xE549F846DE7D32D5, communicationType, communicationGroupFlag); }
	NATIVE_DECL BOOL _NETWORK_HAS_PLAYER_PASSED_CHECK_TYPE(int checkType, Any* gamerHandle) { return invoke<BOOL>(0x62E29CDA11F9C230, checkType, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_ON_BLOCKLIST(Any* gamerHandle) { return invoke<BOOL>(0xAD4326FCA30D62F8, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_SET_SCRIPT_AUTOMUTED(Any p0) { return invoke<BOOL>(0xB309EBEA797E001F, p0); }
	NATIVE_DECL BOOL NETWORK_HAS_AUTOMUTE_OVERRIDE() { return invoke<BOOL>(0x26F07DD83A5F7F98); }
	NATIVE_DECL BOOL NETWORK_HAS_HEADSET() { return invoke<BOOL>(0xE870F9F1F7B4F1FA); }
	NATIVE_DECL void NETWORK_SET_LOOK_AT_TALKERS(BOOL p0) { invoke<Void>(0x7D395EA61622E116, p0); }
	NATIVE_DECL BOOL NETWORK_IS_PUSH_TO_TALK_ACTIVE() { return invoke<BOOL>(0xC0D2AF00BCC234CA); }
	NATIVE_DECL BOOL NETWORK_GAMER_HAS_HEADSET(Any* gamerHandle) { return invoke<BOOL>(0xF2FD55CB574BCC55, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_IS_GAMER_TALKING(Any* gamerHandle) { return invoke<BOOL>(0x71C33B22606CD88A, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_PERMISSIONS_HAS_GAMER_RECORD(Any* gamerHandle) { return invoke<BOOL>(0x559EBF901A8C68E0, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CAN_COMMUNICATE_WITH_GAMER(Any* gamerHandle) { return invoke<BOOL>(0xA150A4F065806B1F, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CAN_TEXT_CHAT_WITH_GAMER(Any* gamerHandle) { return invoke<BOOL>(0xEEC02C7C0666D990, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_IS_GAMER_MUTED_BY_ME(Any* gamerHandle) { return invoke<BOOL>(0xCE60DE011B6C7978, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_AM_I_MUTED_BY_GAMER(Any* gamerHandle) { return invoke<BOOL>(0xDF02A2C93F1F26DA, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_IS_GAMER_BLOCKED_BY_ME(Any* gamerHandle) { return invoke<BOOL>(0xE944C4F5AF1B5883, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_AM_I_BLOCKED_BY_GAMER(Any* gamerHandle) { return invoke<BOOL>(0x15337C7C268A27B2, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CAN_VIEW_GAMER_USER_CONTENT(Any* gamerHandle) { return invoke<BOOL>(0xB57A49545BA53CE7, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_HAS_VIEW_GAMER_USER_CONTENT_RESULT(Any* gamerHandle) { return invoke<BOOL>(0xCCA4318E1AB03F1F, gamerHandle); }
	NATIVE_DECL BOOL _NETWORK_CAN_TEXT_FROM_GAMER_BE_VIEWED(Any* gamerHandle) { return invoke<BOOL>(0x9F633448E4C73207, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CAN_PLAY_MULTIPLAYER_WITH_GAMER(Any* gamerHandle) { return invoke<BOOL>(0x07DD29D5E22763F1, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CAN_GAMER_PLAY_MULTIPLAYER_WITH_ME(Any* gamerHandle) { return invoke<BOOL>(0x135F9B7B7ADD2185, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CAN_SEND_LOCAL_INVITE(Any* gamerHandle) { return invoke<BOOL>(0x021ABCBD98EC4320, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CAN_RECEIVE_LOCAL_INVITE(Any* gamerHandle) { return invoke<BOOL>(0x421E34C55F125964, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_TALKING(Player player) { return invoke<BOOL>(0x031E11F3D447647E, player); }
	NATIVE_DECL BOOL NETWORK_PLAYER_HAS_HEADSET(Player player) { return invoke<BOOL>(0x3FB99A8B08D18FD6, player); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_MUTED_BY_ME(Player player) { return invoke<BOOL>(0x8C71288AE68EDE39, player); }
	NATIVE_DECL BOOL NETWORK_AM_I_MUTED_BY_PLAYER(Player player) { return invoke<BOOL>(0x9D6981DFC91A8604, player); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_BLOCKED_BY_ME(Player player) { return invoke<BOOL>(0x57AF1F8E27483721, player); }
	NATIVE_DECL BOOL NETWORK_AM_I_BLOCKED_BY_PLAYER(Player player) { return invoke<BOOL>(0x87F395D957D4353D, player); }
	NATIVE_DECL float NETWORK_GET_PLAYER_LOUDNESS(Player player) { return invoke<float>(0x21A1684A25C2867F, player); }
	NATIVE_DECL void NETWORK_SET_TALKER_PROXIMITY(float value) { invoke<Void>(0xCBF12D65F95AD686, value); }
	NATIVE_DECL float NETWORK_GET_TALKER_PROXIMITY() { return invoke<float>(0x84F0F13120B4E098); }
	NATIVE_DECL void NETWORK_SET_VOICE_ACTIVE(BOOL toggle) { invoke<Void>(0xBABEC9E69A91C57B, toggle); }
	NATIVE_DECL void NETWORK_REMAIN_IN_GAME_CHAT(BOOL p0) { invoke<Void>(0xCFEB46DCD7D8D5EB, p0); }
	NATIVE_DECL void NETWORK_OVERRIDE_TRANSITION_CHAT(BOOL p0) { invoke<Void>(0xAF66059A131AA269, p0); }
	NATIVE_DECL void NETWORK_SET_TEAM_ONLY_CHAT(BOOL toggle) { invoke<Void>(0xD5B4883AC32F24C3, toggle); }
	NATIVE_DECL void NETWORK_SET_SCRIPT_CONTROLLING_TEAMS(Any p0) { invoke<Void>(0x265559DA40B3F327, p0); }
	NATIVE_DECL BOOL NETWORK_SET_SAME_TEAM_AS_LOCAL_PLAYER(Any p0, Any p1) { return invoke<BOOL>(0x4348BFDA56023A2F, p0, p1); }
	NATIVE_DECL void NETWORK_OVERRIDE_TEAM_RESTRICTIONS(int team, BOOL toggle) { invoke<Void>(0x6F697A66CE78674E, team, toggle); }
	NATIVE_DECL void NETWORK_SET_OVERRIDE_SPECTATOR_MODE(BOOL toggle) { invoke<Void>(0x70DA3BF8DACD3210, toggle); }
	NATIVE_DECL void NETWORK_SET_OVERRIDE_TUTORIAL_SESSION_CHAT(BOOL toggle) { invoke<Void>(0x3C5C1E2C2FF814B1, toggle); }
	NATIVE_DECL void NETWORK_SET_PROXIMITY_AFFECTS_TEAM(BOOL toggle) { invoke<Void>(0x9D7AFCBF21C51712, toggle); }
	NATIVE_DECL void NETWORK_SET_NO_SPECTATOR_CHAT(BOOL toggle) { invoke<Void>(0xF46A1E03E8755980, toggle); }
	NATIVE_DECL void NETWORK_SET_IGNORE_SPECTATOR_CHAT_LIMITS_SAME_TEAM(BOOL toggle) { invoke<Void>(0x6A5D89D7769A40D8, toggle); }
	NATIVE_DECL void NETWORK_OVERRIDE_CHAT_RESTRICTIONS(Player player, BOOL toggle) { invoke<Void>(0x3039AE5AD2C9C0C4, player, toggle); }
	NATIVE_DECL void NETWORK_OVERRIDE_SEND_RESTRICTIONS(Player player, BOOL toggle) { invoke<Void>(0x97DD4C5944CC2E6A, player, toggle); }
	NATIVE_DECL void NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL(BOOL toggle) { invoke<Void>(0x57B192B4D4AD23D5, toggle); }
	NATIVE_DECL void NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(Player player, BOOL toggle) { invoke<Void>(0xDDF73E2B1FEC5AB4, player, toggle); }
	NATIVE_DECL void NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL(BOOL toggle) { invoke<Void>(0x0FF2862B61A58AF9, toggle); }
	NATIVE_DECL void NETWORK_SET_VOICE_CHANNEL(int channel) { invoke<Void>(0xEF6212C2EFEF1A23, channel); }
	NATIVE_DECL void NETWORK_CLEAR_VOICE_CHANNEL() { invoke<Void>(0xE036A705F989E049); }
	NATIVE_DECL void NETWORK_APPLY_VOICE_PROXIMITY_OVERRIDE(float x, float y, float z) { invoke<Void>(0xDBD2056652689917, x, y, z); }
	NATIVE_DECL void NETWORK_CLEAR_VOICE_PROXIMITY_OVERRIDE() { invoke<Void>(0xF03755696450470C); }
	NATIVE_DECL void NETWORK_ENABLE_VOICE_BANDWIDTH_RESTRICTION(Player player) { invoke<Void>(0x5E3AA4CA2B6FB0EE, player); }
	NATIVE_DECL void NETWORK_DISABLE_VOICE_BANDWIDTH_RESTRICTION(Player player) { invoke<Void>(0xCA575C391FEA25CC, player); }
	NATIVE_DECL void NETWORK_GET_MUTE_COUNT_FOR_PLAYER(Player p0, float* p1, float* p2) { invoke<Void>(0xADB57E5B663CCA8B, p0, p1, p2); }
	NATIVE_DECL void NETWORK_SET_SPECTATOR_TO_NON_SPECTATOR_TEXT_CHAT(BOOL toggle) { invoke<Void>(0x8EF52ACAECC51D9C, toggle); }
	NATIVE_DECL BOOL NETWORK_TEXT_CHAT_IS_TYPING() { return invoke<BOOL>(0x5FCF4D7069B09026); }
	NATIVE_DECL void SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME() { invoke<Void>(0x593850C16A36B692); }
	NATIVE_DECL BOOL SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE() { return invoke<BOOL>(0x9ECA15ADFE141431); }
	NATIVE_DECL void NETWORK_SET_FRIENDLY_FIRE_OPTION(BOOL toggle) { invoke<Void>(0xF808475FA571D823, toggle); }
	NATIVE_DECL void NETWORK_SET_RICH_PRESENCE(int p0, int p1, Any p2, Any p3) { invoke<Void>(0x1DCCACDCFC569362, p0, p1, p2, p3); }
	NATIVE_DECL void NETWORK_SET_RICH_PRESENCE_STRING(int p0, const char* textLabel) { invoke<Void>(0x3E200C2BCF4164EB, p0, textLabel); }
	NATIVE_DECL int NETWORK_GET_TIMEOUT_TIME() { return invoke<int>(0x5ED0356A0CE3A34F); }
	NATIVE_DECL void NETWORK_LEAVE_PED_BEHIND_BEFORE_WARP(Player player, float x, float y, float z, BOOL p4, BOOL p5) { invoke<Void>(0x9769F811D1785B03, player, x, y, z, p4, p5); }
	NATIVE_DECL void NETWORK_LEAVE_PED_BEHIND_BEFORE_CUTSCENE(Player player, BOOL p1) { invoke<Void>(0xBF22E0F32968E967, player, p1); }
	NATIVE_DECL void REMOVE_ALL_STICKY_BOMBS_FROM_ENTITY(Entity entity, Ped ped) { invoke<Void>(0x715135F4B82AC90D, entity, ped); }
	NATIVE_DECL void NETWORK_KEEP_ENTITY_COLLISION_DISABLED_AFTER_ANIM_SCENE(Any p0, Any p1) { invoke<Void>(0x17C9E241111A674D, p0, p1); }
	NATIVE_DECL BOOL NETWORK_IS_ANY_PLAYER_NEAR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<BOOL>(0x2E4C123D1C8A710E, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL BOOL NETWORK_CLAN_SERVICE_IS_VALID() { return invoke<BOOL>(0x579CCED0265D4896); }
	NATIVE_DECL BOOL NETWORK_CLAN_PLAYER_IS_ACTIVE(Any* gamerHandle) { return invoke<BOOL>(0xB124B57F571D8F18, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CLAN_PLAYER_GET_DESC(Any* clanDesc, int bufferSize, Any* gamerHandle) { return invoke<BOOL>(0xEEE6EACBE8874FBA, clanDesc, bufferSize, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CLAN_IS_ROCKSTAR_CLAN(Any* clanDesc, int bufferSize) { return invoke<BOOL>(0x7543BB439F63792B, clanDesc, bufferSize); }
	NATIVE_DECL void NETWORK_CLAN_GET_UI_FORMATTED_TAG(Any* clanDesc, int bufferSize, char* formattedTag) { invoke<Void>(0xF45352426FF3A4F0, clanDesc, bufferSize, formattedTag); }
	NATIVE_DECL int NETWORK_CLAN_GET_LOCAL_MEMBERSHIPS_COUNT() { return invoke<int>(0x1F471B79ACC90BEF); }
	NATIVE_DECL BOOL NETWORK_CLAN_GET_MEMBERSHIP_DESC(Any* memberDesc, int p1) { return invoke<BOOL>(0x48DE78AF2C8885B8, memberDesc, p1); }
	NATIVE_DECL BOOL NETWORK_CLAN_DOWNLOAD_MEMBERSHIP(Any* gamerHandle) { return invoke<BOOL>(0xA989044E70010ABE, gamerHandle); }
	NATIVE_DECL BOOL NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING(Any* p0) { return invoke<BOOL>(0x5B9E023DC6EBEDC0, p0); }
	NATIVE_DECL BOOL NETWORK_CLAN_ANY_DOWNLOAD_MEMBERSHIP_PENDING() { return invoke<BOOL>(0xB3F64A6A91432477); }
	NATIVE_DECL BOOL NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE(int* p0) { return invoke<BOOL>(0xBB6E6FEE99D866B2, p0); }
	NATIVE_DECL int NETWORK_CLAN_GET_MEMBERSHIP_COUNT(int* p0) { return invoke<int>(0xAAB11F6C4ADBC2C1, p0); }
	NATIVE_DECL BOOL NETWORK_CLAN_GET_MEMBERSHIP_VALID(int* p0, Any p1) { return invoke<BOOL>(0x48A59CF88D43DF0E, p0, p1); }
	NATIVE_DECL BOOL NETWORK_CLAN_GET_MEMBERSHIP(int* p0, Any* clanMembership, int p2) { return invoke<BOOL>(0xC8BC2011F67B3411, p0, clanMembership, p2); }
	NATIVE_DECL BOOL NETWORK_CLAN_JOIN(int clanDesc) { return invoke<BOOL>(0x9FAAA4F4FC71F87F, clanDesc); }
	NATIVE_DECL BOOL NETWORK_CLAN_CREWINFO_GET_STRING_VALUE(const char* animDict, const char* animName) { return invoke<BOOL>(0x729E3401F0430686, animDict, animName); }
	NATIVE_DECL BOOL NETWORK_CLAN_CREWINFO_GET_CREWRANKTITLE(int p0, const char* p1) { return invoke<BOOL>(0x2B51EDBEFC301339, p0, p1); }
	NATIVE_DECL BOOL NETWORK_CLAN_HAS_CREWINFO_METADATA_BEEN_RECEIVED() { return invoke<BOOL>(0xC32EA7A2F6CA7557); }
	NATIVE_DECL BOOL NETWORK_CLAN_GET_EMBLEM_TXD_NAME(Any* netHandle, char* txdName) { return invoke<BOOL>(0x5835D9CD92E83184, netHandle, txdName); }
	NATIVE_DECL BOOL NETWORK_CLAN_REQUEST_EMBLEM(Any p0) { return invoke<BOOL>(0x13518FF1C6B28938, p0); }
	NATIVE_DECL BOOL NETWORK_CLAN_IS_EMBLEM_READY(Any p0, Any* p1) { return invoke<BOOL>(0xA134777FF7F33331, p0, p1); }
	NATIVE_DECL void NETWORK_CLAN_RELEASE_EMBLEM(Any p0) { invoke<Void>(0x113E6E3E50E286B0, p0); }
	NATIVE_DECL BOOL NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR() { return invoke<BOOL>(0x9AA46BADAD0E27ED); }
	NATIVE_DECL void NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL() { invoke<Void>(0x042E4B70B93E6054); }
	NATIVE_DECL BOOL NETWORK_GET_PRIMARY_CLAN_DATA_START(Any* p0, Any p1) { return invoke<BOOL>(0xCE86D8191B762107, p0, p1); }
	NATIVE_DECL BOOL NETWORK_GET_PRIMARY_CLAN_DATA_PENDING() { return invoke<BOOL>(0xB5074DB804E28CE7); }
	NATIVE_DECL BOOL NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS() { return invoke<BOOL>(0x5B4F04F19376A0BA); }
	NATIVE_DECL BOOL NETWORK_GET_PRIMARY_CLAN_DATA_NEW(Any* p0, Any* p1) { return invoke<BOOL>(0xC080FF658B2E41DA, p0, p1); }
	NATIVE_DECL void SET_NETWORK_ID_CAN_MIGRATE(int netId, BOOL toggle) { invoke<Void>(0x299EEB23175895FC, netId, toggle); }
	NATIVE_DECL void SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(int netId, BOOL toggle) { invoke<Void>(0xE05E81A888FA63C8, netId, toggle); }
	NATIVE_DECL void SET_NETWORK_ID_ALWAYS_EXISTS_FOR_PLAYER(int netId, Player player, BOOL toggle) { invoke<Void>(0xA8A024587329F36A, netId, player, toggle); }
	NATIVE_DECL void SET_NETWORK_ID_CAN_BE_REASSIGNED(int netId, BOOL toggle) { invoke<Void>(0x9D724B400A7E8FFC, netId, toggle); }
	NATIVE_DECL void NETWORK_SET_ENTITY_CAN_BLEND(Entity entity, BOOL toggle) { invoke<Void>(0xD830567D88A1E873, entity, toggle); }
	NATIVE_DECL void NETWORK_SET_OBJECT_CAN_BLEND_WHEN_FIXED(Object object, BOOL toggle) { invoke<Void>(0x0379DAF89BA09AA5, object, toggle); }
	NATIVE_DECL void NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(Entity entity, BOOL toggle) { invoke<Void>(0xF1CA12B18AEF5298, entity, toggle); }
	NATIVE_DECL void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE(int netId, BOOL p1, BOOL p2) { invoke<Void>(0xA6928482543022B4, netId, p1, p2); }
	NATIVE_DECL void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_HACK(int netId, BOOL p1, BOOL p2) { invoke<Void>(0x32EBD154CB6B8B99, netId, p1, p2); }
	NATIVE_DECL void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_REMAIN_HACK(Any p0, Any p1, Any p2) { invoke<Void>(0x76B3F29D3F967692, p0, p1, p2); }
	NATIVE_DECL void SET_NETWORK_CUTSCENE_ENTITIES(BOOL toggle) { invoke<Void>(0xAAA553E7DD28A457, toggle); }
	NATIVE_DECL BOOL ARE_CUTSCENE_ENTITIES_NETWORKED() { return invoke<BOOL>(0x66D6A5E9C511214A); }
	NATIVE_DECL void SET_NETWORK_ID_PASS_CONTROL_IN_TUTORIAL(int netId, BOOL state) { invoke<Void>(0x3FA36981311FA4FF, netId, state); }
	NATIVE_DECL void _NETWORK_SET_TUTORIAL_SPECIAL_SESSION(BOOL toggle) { invoke<Void>(0x35AEB4AC7C73C6E1, toggle); }
	NATIVE_DECL BOOL _NETWORK_IS_SPECIAL_TUTORIAL_SESSION() { return invoke<BOOL>(0x4666CD7431DE98E2); }
	NATIVE_DECL BOOL IS_NETWORK_ID_OWNED_BY_PARTICIPANT(int netId) { return invoke<BOOL>(0xA1607996431332DF, netId); }
	NATIVE_DECL void SET_REMOTE_PLAYER_VISIBLE_IN_CUTSCENE(Player player, BOOL locallyVisible) { invoke<Void>(0x96320E6549DAE7B4, player, locallyVisible); }
	NATIVE_DECL void SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE(BOOL p0, BOOL p1) { invoke<Void>(0xD1065D68947E7B6E, p0, p1); }
	NATIVE_DECL void SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(BOOL bIncludePlayersVehicle) { invoke<Void>(0xE5F773C1A1D9D168, bIncludePlayersVehicle); }
	NATIVE_DECL void SET_LOCAL_PLAYER_VISIBLE_LOCALLY(BOOL bIncludePlayersVehicle) { invoke<Void>(0x7619364C82D3BF14, bIncludePlayersVehicle); }
	NATIVE_DECL void SET_PLAYER_INVISIBLE_LOCALLY(Player player, BOOL bIncludePlayersVehicle) { invoke<Void>(0x12B37D54667DB0B8, player, bIncludePlayersVehicle); }
	NATIVE_DECL void SET_PLAYER_VISIBLE_LOCALLY(Player player, BOOL bIncludePlayersVehicle) { invoke<Void>(0xFAA10F1FAFB11AF2, player, bIncludePlayersVehicle); }
	NATIVE_DECL void FADE_OUT_LOCAL_PLAYER(BOOL p0) { invoke<Void>(0x416DBD4CD6ED8DD2, p0); }
	NATIVE_DECL void NETWORK_FADE_OUT_ENTITY(Entity entity, BOOL normal, BOOL slow) { invoke<Void>(0xDE564951F95E09ED, entity, normal, slow); }
	NATIVE_DECL void NETWORK_FADE_IN_ENTITY(Entity entity, BOOL state, Any p2) { invoke<Void>(0x1F4ED342ACEFE62D, entity, state, p2); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_FADING(Player player) { return invoke<BOOL>(0x631DC5DFF4B110E3, player); }
	NATIVE_DECL BOOL NETWORK_IS_ENTITY_FADING(Entity entity) { return invoke<BOOL>(0x422F32CC7E56ABAD, entity); }
	NATIVE_DECL BOOL IS_PLAYER_IN_CUTSCENE(Player player) { return invoke<BOOL>(0xE73092F4157CD126, player); }
	NATIVE_DECL void SET_ENTITY_VISIBLE_IN_CUTSCENE(Any p0, BOOL p1, BOOL p2) { invoke<Void>(0xE0031D3C8F36AB82, p0, p1, p2); }
	NATIVE_DECL void SET_ENTITY_LOCALLY_INVISIBLE(Entity entity) { invoke<Void>(0xE135A9FF3F5D05D8, entity); }
	NATIVE_DECL void SET_ENTITY_LOCALLY_VISIBLE(Entity entity) { invoke<Void>(0x241E289B5C059EDC, entity); }
	NATIVE_DECL BOOL IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(int netID) { return invoke<BOOL>(0x6E192E33AD436366, netID); }
	NATIVE_DECL void ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(int netID, BOOL toggle) { invoke<Void>(0xD45B1FFCCD52FF19, netID, toggle); }
	NATIVE_DECL BOOL IS_DAMAGE_TRACKER_ACTIVE_ON_PLAYER(Player player) { return invoke<BOOL>(0xB2092A1EAA7FD45F, player); }
	NATIVE_DECL void ACTIVATE_DAMAGE_TRACKER_ON_PLAYER(Player player, BOOL toggle) { invoke<Void>(0xBEC0816FF5ACBCDA, player, toggle); }
	NATIVE_DECL BOOL IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(float p0, float p1, float p2, float p3) { return invoke<BOOL>(0xD82CF8E64C8729D8, p0, p1, p2, p3); }
	NATIVE_DECL BOOL IS_SPHERE_VISIBLE_TO_PLAYER(Any p0, float p1, float p2, float p3, float p4) { return invoke<BOOL>(0xDC3A310219E5DA62, p0, p1, p2, p3, p4); }
	NATIVE_DECL void RESERVE_NETWORK_MISSION_OBJECTS(int amount) { invoke<Void>(0x4E5C93BD0C32FBF8, amount); }
	NATIVE_DECL void RESERVE_NETWORK_MISSION_PEDS(int amount) { invoke<Void>(0xB60FEBA45333D36F, amount); }
	NATIVE_DECL void RESERVE_NETWORK_MISSION_VEHICLES(int amount) { invoke<Void>(0x76B02E21ED27A469, amount); }
	NATIVE_DECL void RESERVE_LOCAL_NETWORK_MISSION_OBJECTS(int amount) { invoke<Void>(0x797F9C5E661D920E, amount); }
	NATIVE_DECL void RESERVE_LOCAL_NETWORK_MISSION_PEDS(int amount) { invoke<Void>(0x2C8DF5D129595281, amount); }
	NATIVE_DECL void RESERVE_LOCAL_NETWORK_MISSION_VEHICLES(int amount) { invoke<Void>(0x42613035157E4208, amount); }
	NATIVE_DECL BOOL CAN_REGISTER_MISSION_OBJECTS(int amount) { return invoke<BOOL>(0x800DD4721A8B008B, amount); }
	NATIVE_DECL BOOL CAN_REGISTER_MISSION_PEDS(int amount) { return invoke<BOOL>(0xBCBF4FEF9FA5D781, amount); }
	NATIVE_DECL BOOL CAN_REGISTER_MISSION_VEHICLES(int amount) { return invoke<BOOL>(0x7277F1F2E085EE74, amount); }
	NATIVE_DECL BOOL CAN_REGISTER_MISSION_PICKUPS(int amount) { return invoke<BOOL>(0x0A49D1CB6E34AF72, amount); }
	NATIVE_DECL BOOL CAN_REGISTER_MISSION_DOORS(Any p0) { return invoke<BOOL>(0xE16AA70CE9BEEDC3, p0); }
	NATIVE_DECL BOOL CAN_REGISTER_MISSION_ENTITIES(int ped_amt, int vehicle_amt, int object_amt, int pickup_amt) { return invoke<BOOL>(0x69778E7564BADE6D, ped_amt, vehicle_amt, object_amt, pickup_amt); }
	NATIVE_DECL int GET_NUM_RESERVED_MISSION_OBJECTS(BOOL p0, Any p1) { return invoke<int>(0xAA81B5F10BC43AC2, p0, p1); }
	NATIVE_DECL int GET_NUM_RESERVED_MISSION_PEDS(BOOL p0, Any p1) { return invoke<int>(0x1F13D5AE5CB17E17, p0, p1); }
	NATIVE_DECL int GET_NUM_RESERVED_MISSION_VEHICLES(BOOL p0, Any p1) { return invoke<int>(0xCF3A965906452031, p0, p1); }
	NATIVE_DECL int GET_NUM_CREATED_MISSION_OBJECTS(BOOL p0) { return invoke<int>(0x12B6281B6C6706C0, p0); }
	NATIVE_DECL int GET_NUM_CREATED_MISSION_PEDS(BOOL p0) { return invoke<int>(0xCB215C4B56A7FAE7, p0); }
	NATIVE_DECL int GET_NUM_CREATED_MISSION_VEHICLES(BOOL p0) { return invoke<int>(0x0CD9AB83489430EA, p0); }
	NATIVE_DECL void GET_RESERVED_MISSION_ENTITIES_IN_AREA(float x, float y, float z, Any p3, Any* out1, Any* out2, Any* out3) { invoke<Void>(0xE42D626EEC94E5D9, x, y, z, p3, out1, out2, out3); }
	NATIVE_DECL int GET_MAX_NUM_NETWORK_OBJECTS() { return invoke<int>(0xC7BE335216B5EC7C); }
	NATIVE_DECL int GET_MAX_NUM_NETWORK_PEDS() { return invoke<int>(0x0C1F7D49C39D2289); }
	NATIVE_DECL int GET_MAX_NUM_NETWORK_VEHICLES() { return invoke<int>(0x0AFCE529F69B21FF); }
	NATIVE_DECL int GET_MAX_NUM_NETWORK_PICKUPS() { return invoke<int>(0xA72835064DD63E4C); }
	NATIVE_DECL void NETWORK_SET_OBJECT_SCOPE_DISTANCE(Object object, float range) { invoke<Void>(0xBA7F0B77D80A4EB7, object, range); }
	NATIVE_DECL void NETWORK_ALLOW_CLONING_WHILE_IN_TUTORIAL(Any p0, Any p1) { invoke<Void>(0x0F1A4B45B7693B95, p0, p1); }
	NATIVE_DECL void NETWORK_SET_TASK_CUTSCENE_INSCOPE_MULTIPLER(float multiplier) { invoke<Void>(0xC6FCEE21C6FCEE21, multiplier); }
	NATIVE_DECL void _NETWORK_HIDE_ENTITY_IN_TUTORIAL_SESSION(int netHandle, BOOL hide) { invoke<Void>(0xCFE359CCCFE359CC, netHandle, hide); }
	NATIVE_DECL int GET_NETWORK_TIME() { return invoke<int>(0x7A5487FE9FAA6B48); }
	NATIVE_DECL int GET_NETWORK_TIME_ACCURATE() { return invoke<int>(0x89023FBBF9200E9F); }
	NATIVE_DECL BOOL HAS_NETWORK_TIME_STARTED() { return invoke<BOOL>(0x46718ACEEDEAFC84); }
	NATIVE_DECL int GET_TIME_OFFSET(int timeA, int timeB) { return invoke<int>(0x017008CCDAD48503, timeA, timeB); }
	NATIVE_DECL BOOL IS_TIME_LESS_THAN(int timeA, int timeB) { return invoke<BOOL>(0xCB2CF5148012C8D0, timeA, timeB); }
	NATIVE_DECL BOOL IS_TIME_MORE_THAN(int timeA, int timeB) { return invoke<BOOL>(0xDE350F8651E4346C, timeA, timeB); }
	NATIVE_DECL BOOL IS_TIME_EQUAL_TO(int timeA, int timeB) { return invoke<BOOL>(0xF5BC95857BD6D512, timeA, timeB); }
	NATIVE_DECL int GET_TIME_DIFFERENCE(int timeA, int timeB) { return invoke<int>(0xA2C6FC031D46FFF0, timeA, timeB); }
	NATIVE_DECL const char* GET_TIME_AS_STRING(int time) { return invoke<const char*>(0x9E23B1777A927DAD, time); }
	NATIVE_DECL const char* GET_CLOUD_TIME_AS_STRING() { return invoke<const char*>(0xF12E6CD06C73D69E); }
	NATIVE_DECL int GET_CLOUD_TIME_AS_INT() { return invoke<int>(0x9A73240B49945C76); }
	NATIVE_DECL void CONVERT_POSIX_TIME(int posixTime, Any* timeStructure) { invoke<Void>(0xAC97AF97FA68E5D5, posixTime, timeStructure); }
	NATIVE_DECL void NETWORK_SET_IN_SPECTATOR_MODE(BOOL toggle, Ped playerPed) { invoke<Void>(0x423DE3854BB50894, toggle, playerPed); }
	NATIVE_DECL void NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED(BOOL toggle, Ped playerPed, BOOL p2) { invoke<Void>(0x419594E137637120, toggle, playerPed, p2); }
	NATIVE_DECL void NETWORK_SET_IN_FREE_CAM_MODE(BOOL toggle) { invoke<Void>(0xFC18DB55AE19E046, toggle); }
	NATIVE_DECL void NETWORK_SET_ANTAGONISTIC_TO_PLAYER(BOOL toggle, Player player) { invoke<Void>(0x5C707A667DF8B9FA, toggle, player); }
	NATIVE_DECL BOOL NETWORK_IS_IN_SPECTATOR_MODE() { return invoke<BOOL>(0x048746E388762E11); }
	NATIVE_DECL void NETWORK_SET_IN_MP_CUTSCENE(BOOL p0, BOOL p1) { invoke<Void>(0x9CA5DE655269FEC4, p0, p1); }
	NATIVE_DECL BOOL NETWORK_IS_IN_MP_CUTSCENE() { return invoke<BOOL>(0x6CC27C9FA2040220); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_IN_MP_CUTSCENE(Player player) { return invoke<BOOL>(0x63F9EE203C3619F2, player); }
	NATIVE_DECL void NETWORK_HIDE_PROJECTILE_IN_CUTSCENE() { invoke<Void>(0xFAC18E7356BD3210); }
	NATIVE_DECL void SET_NETWORK_VEHICLE_RESPOT_TIMER(int netId, int time, Any p2, Any p3) { invoke<Void>(0xEC51713AB6EC36E8, netId, time, p2, p3); }
	NATIVE_DECL BOOL IS_NETWORK_VEHICLE_RUNNING_RESPOT_TIMER(int networkID) { return invoke<BOOL>(0xDD7CEF5B3A4DA8A6, networkID); }
	NATIVE_DECL void SET_NETWORK_VEHICLE_AS_GHOST(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x6274C4712850841E, vehicle, toggle); }
	NATIVE_DECL void SET_NETWORK_VEHICLE_MAX_POSITION_DELTA_MULTIPLIER(Vehicle vehicle, float multiplier) { invoke<Void>(0xA2A707979FE754DC, vehicle, multiplier); }
	NATIVE_DECL void SET_NETWORK_ENABLE_HIGH_SPEED_EDGE_FALL_DETECTION(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x838DA0936A24ED4D, vehicle, toggle); }
	NATIVE_DECL void SET_LOCAL_PLAYER_AS_GHOST(BOOL toggle, BOOL p1) { invoke<Void>(0x5FFE9B4144F9712F, toggle, p1); }
	NATIVE_DECL BOOL IS_ENTITY_A_GHOST(Entity entity) { return invoke<BOOL>(0x21D04D7BC538C146, entity); }
	NATIVE_DECL void SET_NON_PARTICIPANTS_OF_THIS_SCRIPT_AS_GHOSTS(BOOL p0) { invoke<Void>(0x13F1FCB111B820B0, p0); }
	NATIVE_DECL void SET_REMOTE_PLAYER_AS_GHOST(Player player, BOOL p1) { invoke<Void>(0xA7C511FA1C5BDA38, player, p1); }
	NATIVE_DECL void SET_GHOST_ALPHA(int alpha) { invoke<Void>(0x658500AE6D723A7E, alpha); }
	NATIVE_DECL void RESET_GHOST_ALPHA() { invoke<Void>(0x17330EBF2F2124A8); }
	NATIVE_DECL void SET_ENTITY_GHOSTED_FOR_GHOST_PLAYERS(Entity entity, BOOL toggle) { invoke<Void>(0x4BA166079D658ED4, entity, toggle); }
	NATIVE_DECL void SET_INVERT_GHOSTING(BOOL p0) { invoke<Void>(0xD7B6C73CAD419BCF, p0); }
	NATIVE_DECL BOOL IS_ENTITY_IN_GHOST_COLLISION(Entity entity) { return invoke<BOOL>(0x7EF7649B64D7FF10, entity); }
	NATIVE_DECL void _SET_FREEMODE_REPORT_DATA(Any* gamerHandle, Any* reportData) { invoke<Void>(0x527803286A8B6C81, gamerHandle, reportData); }
	NATIVE_DECL BOOL IS_OBJECT_REASSIGNMENT_IN_PROGRESS() { return invoke<BOOL>(0x28123C8B056CC8AA); }
	NATIVE_DECL void USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(BOOL toggle) { invoke<Void>(0x77758139EC9B66C7, toggle); }
	NATIVE_DECL int NETWORK_CREATE_SYNCHRONISED_SCENE(float x, float y, float z, float xRot, float yRot, float zRot, int rotationOrder, BOOL useOcclusionPortal, BOOL looped, float p9, float animTime, float p11) { return invoke<int>(0x7CD6BC4C2BBDD526, x, y, z, xRot, yRot, zRot, rotationOrder, useOcclusionPortal, looped, p9, animTime, p11); }
	NATIVE_DECL void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(Ped ped, int netScene, const char* animDict, const char* animnName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, Any p9) { invoke<Void>(0x742A637471BCECD9, ped, netScene, animDict, animnName, speed, speedMultiplier, duration, flag, playbackRate, p9); }
	NATIVE_DECL void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_WITH_IK(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xA5EAFE473E45C442, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	NATIVE_DECL void NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(Entity entity, int netScene, const char* animDict, const char* animName, float speed, float speedMulitiplier, int flag) { invoke<Void>(0xF2404D68CBC855FA, entity, netScene, animDict, animName, speed, speedMulitiplier, flag); }
	NATIVE_DECL void NETWORK_ADD_MAP_ENTITY_TO_SYNCHRONISED_SCENE(int netScene, Hash modelHash, float x, float y, float z, float p5, const char* p6, float p7, float p8, int flags) { invoke<Void>(0x45F35C0EDC33B03B, netScene, modelHash, x, y, z, p5, p6, p7, p8, flags); }
	NATIVE_DECL void NETWORK_ADD_SYNCHRONISED_SCENE_CAMERA(int netScene, const char* animDict, const char* animName) { invoke<Void>(0xCF8BD3B0BD6D42D7, netScene, animDict, animName); }
	NATIVE_DECL void NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(int netScene, Entity entity, int bone) { invoke<Void>(0x478DCBD2A98B705A, netScene, entity, bone); }
	NATIVE_DECL void NETWORK_START_SYNCHRONISED_SCENE(int netScene) { invoke<Void>(0x9A1B3FCDB36C8697, netScene); }
	NATIVE_DECL void NETWORK_STOP_SYNCHRONISED_SCENE(int netScene) { invoke<Void>(0xC254481A4574CB2F, netScene); }
	NATIVE_DECL int NETWORK_GET_LOCAL_SCENE_FROM_NETWORK_ID(int netId) { return invoke<int>(0x02C40BF885C567B6, netId); }
	NATIVE_DECL void NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA(int netScene) { invoke<Void>(0xC9B43A33D09CADA7, netScene); }
	NATIVE_DECL void NETWORK_ALLOW_REMOTE_SYNCED_SCENE_LOCAL_PLAYER_REQUESTS(Any p0) { invoke<Void>(0x144DA052257AE7D8, p0); }
	NATIVE_DECL BOOL NETWORK_FIND_LARGEST_BUNCH_OF_PLAYERS(int p0, Any p1) { return invoke<BOOL>(0xFB1F9381E80FA13F, p0, p1); }
	NATIVE_DECL BOOL NETWORK_START_RESPAWN_SEARCH_FOR_PLAYER(Player player, float x, float y, float z, float radius, float p5, float p6, float p7, int flags) { return invoke<BOOL>(0x5A6FFA2433E2F14C, player, x, y, z, radius, p5, p6, p7, flags); }
	NATIVE_DECL BOOL NETWORK_START_RESPAWN_SEARCH_IN_ANGLED_AREA_FOR_PLAYER(Player player, float x1, float y1, float z1, float x2, float y2, float z2, float width, float p8, float p9, float p10, int flags) { return invoke<BOOL>(0x4BA92A18502BCA61, player, x1, y1, z1, x2, y2, z2, width, p8, p9, p10, flags); }
	NATIVE_DECL int NETWORK_QUERY_RESPAWN_RESULTS(Any* p0) { return invoke<int>(0x3C891A251567DFCE, p0); }
	NATIVE_DECL void NETWORK_CANCEL_RESPAWN_SEARCH() { invoke<Void>(0xFB8F2A6F3DF08CBE); }
	NATIVE_DECL void NETWORK_GET_RESPAWN_RESULT(int randomInt, Vector3* coordinates, float* heading) { invoke<Void>(0x371EA43692861CF1, randomInt, coordinates, heading); }
	NATIVE_DECL int NETWORK_GET_RESPAWN_RESULT_FLAGS(int p0) { return invoke<int>(0x6C34F1208B8923FD, p0); }
	NATIVE_DECL void NETWORK_START_SOLO_TUTORIAL_SESSION() { invoke<Void>(0x17E0198B3882C2CB); }
	NATIVE_DECL void NETWORK_ALLOW_GANG_TO_JOIN_TUTORIAL_SESSION(int teamId, int instanceId) { invoke<Void>(0xFB680D403909DC70, teamId, instanceId); }
	NATIVE_DECL void NETWORK_END_TUTORIAL_SESSION() { invoke<Void>(0xD0AFAFF5A51D72F7); }
	NATIVE_DECL BOOL NETWORK_IS_IN_TUTORIAL_SESSION() { return invoke<BOOL>(0xADA24309FE08DACF); }
	NATIVE_DECL BOOL NETWORK_WAITING_POP_CLEAR_TUTORIAL_SESSION() { return invoke<BOOL>(0xB37E4E6A2388CA7B); }
	NATIVE_DECL BOOL NETWORK_IS_TUTORIAL_SESSION_CHANGE_PENDING() { return invoke<BOOL>(0x35F0B98A8387274D); }
	NATIVE_DECL int NETWORK_GET_PLAYER_TUTORIAL_SESSION_INSTANCE(Player player) { return invoke<int>(0x3B39236746714134, player); }
	NATIVE_DECL BOOL NETWORK_ARE_PLAYERS_IN_SAME_TUTORIAL_SESSION(Player player, int index) { return invoke<BOOL>(0x9DE986FC9A87C474, player, index); }
	NATIVE_DECL void NETWORK_BLOCK_PROXY_MIGRATION_BETWEEN_TUTORIAL_SESSIONS(Any p0) { invoke<Void>(0xFEA7A352DDB34D52, p0); }
	NATIVE_DECL void NETWORK_CONCEAL_PLAYER(Player player, BOOL toggle, BOOL p2) { invoke<Void>(0xBBDF066252829606, player, toggle, p2); }
	NATIVE_DECL BOOL NETWORK_IS_PLAYER_CONCEALED(Player player) { return invoke<BOOL>(0x919B3C98ED8292F9, player); }
	NATIVE_DECL void NETWORK_CONCEAL_ENTITY(Entity entity, BOOL toggle) { invoke<Void>(0x1632BE0AC1E62876, entity, toggle); }
	NATIVE_DECL BOOL NETWORK_IS_ENTITY_CONCEALED(Entity entity) { return invoke<BOOL>(0x71302EC70689052A, entity); }
	NATIVE_DECL void NETWORK_OVERRIDE_CLOCK_TIME(int hours, int minutes, int seconds) { invoke<Void>(0xE679E3E06E363892, hours, minutes, seconds); }
	NATIVE_DECL void NETWORK_OVERRIDE_CLOCK_RATE(int ms) { invoke<Void>(0x42BF1D2E723B6D7E, ms); }
	NATIVE_DECL void NETWORK_CLEAR_CLOCK_TIME_OVERRIDE() { invoke<Void>(0xD972DF67326F966E); }
	NATIVE_DECL void _NETWORK_CLEAR_CLOCK_SYNC_TIME_OVERRIDE(BOOL startGlobalTransition, int transitionTime) { invoke<Void>(0x0C1BF187985B15C8, startGlobalTransition, transitionTime); }
	NATIVE_DECL void NETWORK_SYNC_CLOCK_TIME_OVERRIDE() { invoke<Void>(0xCBD02360C5E16871); }
	NATIVE_DECL BOOL NETWORK_IS_CLOCK_TIME_OVERRIDDEN() { return invoke<BOOL>(0xD7C95D322FF57522); }
	NATIVE_DECL int NETWORK_ADD_ENTITY_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<int>(0x494C8FB299290269, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL int NETWORK_ADD_ENTITY_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width) { return invoke<int>(0x376C6375BA60293A, x1, y1, z1, x2, y2, z2, width); }
	NATIVE_DECL int NETWORK_ADD_CLIENT_ENTITY_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<int>(0x25B99872D588A101, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL int NETWORK_ADD_CLIENT_ENTITY_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float radius) { return invoke<int>(0x2B1C623823DB0D9D, x1, y1, z1, x2, y2, z2, radius); }
	NATIVE_DECL BOOL NETWORK_REMOVE_ENTITY_AREA(int areaHandle) { return invoke<BOOL>(0x93CF869BAA0C4874, areaHandle); }
	NATIVE_DECL BOOL NETWORK_ENTITY_AREA_DOES_EXIST(int areaHandle) { return invoke<BOOL>(0xE64A3CA08DFA37A9, areaHandle); }
	NATIVE_DECL BOOL NETWORK_ENTITY_AREA_HAVE_ALL_REPLIED(int areaHandle) { return invoke<BOOL>(0x4DF7CFFF471A7FB1, areaHandle); }
	NATIVE_DECL BOOL NETWORK_ENTITY_AREA_IS_OCCUPIED(int areaHandle) { return invoke<BOOL>(0x4A2D4E8BF4265B0F, areaHandle); }
	NATIVE_DECL void NETWORK_USE_HIGH_PRECISION_BLENDING(int netID, BOOL toggle) { invoke<Void>(0x2B1813ABA29016C5, netID, toggle); }
	NATIVE_DECL void NETWORK_SET_CUSTOM_ARENA_BALL_PARAMS(int netId) { invoke<Void>(0xA6FCECCF4721D679, netId); }
	NATIVE_DECL void NETWORK_ENTITY_USE_HIGH_PRECISION_ROTATION(int netId, BOOL toggle) { invoke<Void>(0x95BAF97C82464629, netId, toggle); }
	NATIVE_DECL BOOL NETWORK_REQUEST_CLOUD_BACKGROUND_SCRIPTS() { return invoke<BOOL>(0x924426BFFD82E915); }
	NATIVE_DECL BOOL NETWORK_IS_CLOUD_BACKGROUND_SCRIPT_REQUEST_PENDING() { return invoke<BOOL>(0x8132C0EB8B2B3293); }
	NATIVE_DECL void NETWORK_REQUEST_CLOUD_TUNABLES() { invoke<Void>(0x42FB3B532D526E6C); }
	NATIVE_DECL BOOL NETWORK_IS_TUNABLE_CLOUD_REQUEST_PENDING() { return invoke<BOOL>(0x0467C11ED88B7D28); }
	NATIVE_DECL int NETWORK_GET_TUNABLE_CLOUD_CRC() { return invoke<int>(0x10BD227A753B0D84); }
	NATIVE_DECL void _NETWORK_SET_TUNABLES_REGISTRATION_CONTEXTS(Any* tunableContextData) { invoke<Void>(0x014A73449675121D, tunableContextData); }
	NATIVE_DECL void _NETWORK_CLEAR_TUNABLES_REGISTRATION_CONTEXTS() { invoke<Void>(0x0C87C83C8950432B); }
	NATIVE_DECL BOOL _NETWORK_GET_TUNABLES_REGISTRATION_BOOL(Hash tunableName, BOOL defaultValue) { return invoke<BOOL>(0xB327CF1B8C2C0EA3, tunableName, defaultValue); }
	NATIVE_DECL int _NETWORK_GET_TUNABLES_REGISTRATION_INT(Hash tunableName, int defaultValue) { return invoke<int>(0x0D94071E55F4C9CE, tunableName, defaultValue); }
	NATIVE_DECL float _NETWORK_GET_TUNABLES_REGISTRATION_FLOAT(Hash tunableName, float defaultValue) { return invoke<float>(0x367E5E33E7F0DD1A, tunableName, defaultValue); }
	NATIVE_DECL BOOL NETWORK_DOES_TUNABLE_EXIST(const char* tunableContext, const char* tunableName) { return invoke<BOOL>(0x85E5F8B9B898B20A, tunableContext, tunableName); }
	NATIVE_DECL BOOL NETWORK_ACCESS_TUNABLE_INT(const char* tunableContext, const char* tunableName, int* value) { return invoke<BOOL>(0x8BE1146DFD5D4468, tunableContext, tunableName, value); }
	NATIVE_DECL BOOL NETWORK_ACCESS_TUNABLE_FLOAT(const char* tunableContext, const char* tunableName, float* value) { return invoke<BOOL>(0xE5608CA7BC163A5F, tunableContext, tunableName, value); }
	NATIVE_DECL BOOL NETWORK_ACCESS_TUNABLE_BOOL(const char* tunableContext, const char* tunableName) { return invoke<BOOL>(0xAA6A47A573ABB75A, tunableContext, tunableName); }
	NATIVE_DECL BOOL NETWORK_DOES_TUNABLE_EXIST_HASH(Hash tunableContext, Hash tunableName) { return invoke<BOOL>(0xE4E53E1419D81127, tunableContext, tunableName); }
	NATIVE_DECL BOOL NETWORK_ACCESS_TUNABLE_MODIFICATION_DETECTION_CLEAR() { return invoke<BOOL>(0xFAFC23AEE23868DB); }
	NATIVE_DECL BOOL NETWORK_ACCESS_TUNABLE_INT_HASH(Hash tunableContext, Hash tunableName, int* value) { return invoke<BOOL>(0x40FCE03E50E8DBE8, tunableContext, tunableName, value); }
	NATIVE_DECL BOOL NETWORK_ACCESS_TUNABLE_INT_MODIFICATION_DETECTION_REGISTRATION_HASH(Hash contextHash, Hash nameHash, int* value) { return invoke<BOOL>(0x3A8B55FDA4C8DDEF, contextHash, nameHash, value); }
	NATIVE_DECL BOOL NETWORK_ACCESS_TUNABLE_FLOAT_HASH(Hash tunableContext, Hash tunableName, float* value) { return invoke<BOOL>(0x972BC203BBC4C4D5, tunableContext, tunableName, value); }
	NATIVE_DECL BOOL NETWORK_ACCESS_TUNABLE_FLOAT_MODIFICATION_DETECTION_REGISTRATION_HASH(Hash contextHash, Hash nameHash, float* value) { return invoke<BOOL>(0x1950DAE9848A4739, contextHash, nameHash, value); }
	NATIVE_DECL BOOL NETWORK_ACCESS_TUNABLE_BOOL_HASH(Hash tunableContext, Hash tunableName) { return invoke<BOOL>(0xEA16B69D93D71A45, tunableContext, tunableName); }
	NATIVE_DECL BOOL NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH(Hash contextHash, Hash nameHash, BOOL* value) { return invoke<BOOL>(0x697F508861875B42, contextHash, nameHash, value); }
	NATIVE_DECL BOOL NETWORK_TRY_ACCESS_TUNABLE_BOOL_HASH(Hash tunableContext, Hash tunableName, BOOL defaultValue) { return invoke<BOOL>(0xC7420099936CE286, tunableContext, tunableName, defaultValue); }
	NATIVE_DECL int NETWORK_GET_CONTENT_MODIFIER_LIST_ID(Hash contentHash) { return invoke<int>(0x187382F8A3E0A6C3, contentHash); }
	NATIVE_DECL int NETWORK_GET_BONE_ID_OF_FATAL_HIT() { return invoke<int>(0x7DB53B37A2F211A0); }
	NATIVE_DECL void NETWORK_RESET_BODY_TRACKER() { invoke<Void>(0x72433699B4E6DD64); }
	NATIVE_DECL int NETWORK_GET_NUMBER_BODY_TRACKER_HITS() { return invoke<int>(0xD38C4A6D047C019D); }
	NATIVE_DECL BOOL NETWORK_HAS_BONE_BEEN_HIT_BY_KILLER(int boneIndex) { return invoke<BOOL>(0x2E0BF682CC778D49, boneIndex); }
	NATIVE_DECL BOOL NETWORK_SET_ATTRIBUTE_DAMAGE_TO_PLAYER(Ped ped, Player player) { return invoke<BOOL>(0x0EDE326D47CD0F3E, ped, player); }
	NATIVE_DECL void NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_DAMAGE(Entity entity, BOOL toggle) { invoke<Void>(0x890E2C5ABED7236D, entity, toggle); }
	NATIVE_DECL void _NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_PED_DAMAGE(Entity entity, BOOL trigger) { invoke<Void>(0xE9D0244ACBEE1BC4, entity, trigger); }
	NATIVE_DECL void NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_WEAPON_HASH(Entity entity, BOOL toggle) { invoke<Void>(0x38B7C51AB1EDC7D8, entity, toggle); }
	NATIVE_DECL void NETWORK_SET_NO_LONGER_NEEDED(Entity entity, BOOL toggle) { invoke<Void>(0x3FC795691834481D, entity, toggle); }
	NATIVE_DECL BOOL NETWORK_EXPLODE_VEHICLE(Vehicle vehicle, BOOL isAudible, BOOL isInvisible, int netId) { return invoke<BOOL>(0x301A42153C9AD707, vehicle, isAudible, isInvisible, netId); }
	NATIVE_DECL void NETWORK_EXPLODE_HELI(Vehicle vehicle, BOOL isAudible, BOOL isInvisible, int netId) { invoke<Void>(0x2A5E0621DD815A9A, vehicle, isAudible, isInvisible, netId); }
	NATIVE_DECL void NETWORK_USE_LOGARITHMIC_BLENDING_THIS_FRAME(Entity entity) { invoke<Void>(0xCD71A4ECAB22709E, entity); }
	NATIVE_DECL void NETWORK_OVERRIDE_COORDS_AND_HEADING(Entity entity, float x, float y, float z, float heading) { invoke<Void>(0xA7E30DE9272B6D49, entity, x, y, z, heading); }
	NATIVE_DECL void _NETWORK_ALLOW_DEAD_PED_NETWORK_BLENDING(int netId, BOOL allow) { invoke<Void>(0xE8BA82390622BA13, netId, allow); }
	NATIVE_DECL void NETWORK_ENABLE_EXTRA_VEHICLE_ORIENTATION_BLEND_CHECKS(int netId, BOOL toggle) { invoke<Void>(0xE6717E652B8C8D8A, netId, toggle); }
	NATIVE_DECL void NETWORK_DISABLE_PROXIMITY_MIGRATION(int netID) { invoke<Void>(0x407091CF6037118E, netID); }
	NATIVE_DECL void NETWORK_SET_PLAYER_MENTAL_STATE(int p0) { invoke<Void>(0x367EF5E2F439B4C6, p0); }
	NATIVE_DECL void NETWORK_SET_MINIMUM_RANK_FOR_MISSION(BOOL p0) { invoke<Void>(0x94538037EE44F5CF, p0); }
	NATIVE_DECL void NETWORK_CACHE_LOCAL_PLAYER_HEAD_BLEND_DATA() { invoke<Void>(0xBD0BE0BFC927EAC1); }
	NATIVE_DECL BOOL NETWORK_HAS_CACHED_PLAYER_HEAD_BLEND_DATA(Player player) { return invoke<BOOL>(0x237D5336A9A54108, player); }
	NATIVE_DECL BOOL NETWORK_APPLY_CACHED_PLAYER_HEAD_BLEND_DATA(Ped ped, Player player) { return invoke<BOOL>(0x99B72C7ABDE5C910, ped, player); }
	NATIVE_DECL void _NETWORK_SET_IGNORE_VEHICLE_RAMMED_BY_NON_VEHICLE(BOOL toggle) { invoke<Void>(0x67F7C81C1395672A, toggle); }
	NATIVE_DECL int GET_NUM_COMMERCE_ITEMS() { return invoke<int>(0xF2EAC213D5EA0623); }
	NATIVE_DECL BOOL IS_COMMERCE_DATA_VALID() { return invoke<BOOL>(0xEA14EEF5B7CD2C30); }
	NATIVE_DECL void TRIGGER_COMMERCE_DATA_FETCH(Any p0) { invoke<Void>(0xB606E6CC59664972, p0); }
	NATIVE_DECL BOOL IS_COMMERCE_DATA_FETCH_IN_PROGRESS() { return invoke<BOOL>(0x1D4DC17C38FEAFF0); }
	NATIVE_DECL const char* GET_COMMERCE_ITEM_ID(int index) { return invoke<const char*>(0x662635855957C411, index); }
	NATIVE_DECL const char* GET_COMMERCE_ITEM_NAME(int index) { return invoke<const char*>(0xB4271092CA7EDF48, index); }
	NATIVE_DECL const char* GET_COMMERCE_PRODUCT_PRICE(int index) { return invoke<const char*>(0xCA94551B50B4932C, index); }
	NATIVE_DECL int GET_COMMERCE_ITEM_NUM_CATS(int index) { return invoke<int>(0x2A7776C709904AB0, index); }
	NATIVE_DECL const char* GET_COMMERCE_ITEM_CAT(int index, int index2) { return invoke<const char*>(0x6F44CBF56D79FAC0, index, index2); }
	NATIVE_DECL void OPEN_COMMERCE_STORE(const char* p0, const char* p1, int p2) { invoke<Void>(0x58C21165F6545892, p0, p1, p2); }
	NATIVE_DECL BOOL IS_COMMERCE_STORE_OPEN() { return invoke<BOOL>(0x2EAC52B4019E2782); }
	NATIVE_DECL void SET_STORE_ENABLED(BOOL toggle) { invoke<Void>(0x9641A9FF718E9C5E, toggle); }
	NATIVE_DECL BOOL REQUEST_COMMERCE_ITEM_IMAGE(int index) { return invoke<BOOL>(0xA2F952104FC6DD4B, index); }
	NATIVE_DECL void RELEASE_ALL_COMMERCE_ITEM_IMAGES() { invoke<Void>(0x72D0706CD6CCDB58); }
	NATIVE_DECL const char* GET_COMMERCE_ITEM_TEXTURENAME(int index) { return invoke<const char*>(0x722F5D28B61C5EA8, index); }
	NATIVE_DECL BOOL IS_STORE_AVAILABLE_TO_USER() { return invoke<BOOL>(0x883D79C4071E18B3); }
	NATIVE_DECL void DELAY_MP_STORE_OPEN() { invoke<Void>(0x265635150FB0D82E); }
	NATIVE_DECL void RESET_STORE_NETWORK_GAME_TRACKING() { invoke<Void>(0x444C4525ECE0A4B9); }
	NATIVE_DECL BOOL IS_USER_OLD_ENOUGH_TO_ACCESS_STORE() { return invoke<BOOL>(0x59328EB08C5CEB2B); }
	NATIVE_DECL void SET_LAST_VIEWED_SHOP_ITEM(Hash p0, int p1, Hash p2) { invoke<Void>(0xFAE628F1E9ADB239, p0, p1, p2); }
	NATIVE_DECL int GET_USER_PREMIUM_ACCESS() { return invoke<int>(0x754615490A029508); }
	NATIVE_DECL int GET_USER_STARTER_ACCESS() { return invoke<int>(0x155467ACA0F55705); }
	NATIVE_DECL int CLOUD_DELETE_MEMBER_FILE(const char* p0) { return invoke<int>(0xC64DED7EF0D2FE37, p0); }
	NATIVE_DECL BOOL CLOUD_HAS_REQUEST_COMPLETED(int requestId) { return invoke<BOOL>(0x4C61B39930D045DA, requestId); }
	NATIVE_DECL BOOL CLOUD_DID_REQUEST_SUCCEED(int requestId) { return invoke<BOOL>(0x3A3D5568AF297CD5, requestId); }
	NATIVE_DECL void CLOUD_CHECK_AVAILABILITY() { invoke<Void>(0x4F18196C8D38768D); }
	NATIVE_DECL BOOL CLOUD_IS_CHECKING_AVAILABILITY() { return invoke<BOOL>(0xC7ABAC5DE675EE3B); }
	NATIVE_DECL BOOL CLOUD_GET_AVAILABILITY_CHECK_RESULT() { return invoke<BOOL>(0x0B0CC10720653F3B); }
	NATIVE_DECL int GET_CONTENT_TO_LOAD_TYPE() { return invoke<int>(0x8B0C2964BA471961); }
	NATIVE_DECL BOOL GET_IS_LAUNCH_FROM_LIVE_AREA() { return invoke<BOOL>(0x88B588B41FF7868E); }
	NATIVE_DECL BOOL GET_IS_LIVE_AREA_LAUNCH_WITH_CONTENT() { return invoke<BOOL>(0x67FC09BC554A75E5); }
	NATIVE_DECL void CLEAR_SERVICE_EVENT_ARGUMENTS() { invoke<Void>(0x966DD84FB6A46017); }
	NATIVE_DECL BOOL UGC_COPY_CONTENT(Any* p0, Any* p1) { return invoke<BOOL>(0x152D90E4C1B4738A, p0, p1); }
	NATIVE_DECL BOOL UGC_IS_CREATING() { return invoke<BOOL>(0x9FEDF86898F100E9); }
	NATIVE_DECL BOOL UGC_HAS_CREATE_FINISHED() { return invoke<BOOL>(0x5E24341A7F92A74B); }
	NATIVE_DECL BOOL UGC_DID_CREATE_SUCCEED() { return invoke<BOOL>(0x24E4E51FC16305F9); }
	NATIVE_DECL int UGC_GET_CREATE_RESULT() { return invoke<int>(0xFBC5E768C7A77A6A); }
	NATIVE_DECL const char* UGC_GET_CREATE_CONTENT_ID() { return invoke<const char*>(0xC55A0B40FFB1ED23); }
	NATIVE_DECL void UGC_CLEAR_CREATE_RESULT() { invoke<Void>(0x17440AA15D1D3739); }
	NATIVE_DECL BOOL UGC_QUERY_MY_CONTENT(Any p0, Any p1, Any* p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x9BF438815F5D96EA, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL BOOL UGC_QUERY_BY_CATEGORY(Any p0, Any p1, Any p2, const char* p3, Any p4, BOOL p5) { return invoke<BOOL>(0x692D58DF40657E8C, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL BOOL UGC_QUERY_BY_CONTENT_ID(const char* contentId, BOOL latestVersion, const char* contentTypeName) { return invoke<BOOL>(0x158EC424F35EC469, contentId, latestVersion, contentTypeName); }
	NATIVE_DECL BOOL UGC_QUERY_BY_CONTENT_IDS(Any* data, int count, BOOL latestVersion, const char* contentTypeName) { return invoke<BOOL>(0xC7397A83F7A2A462, data, count, latestVersion, contentTypeName); }
	NATIVE_DECL BOOL UGC_QUERY_MOST_RECENTLY_CREATED_CONTENT(int offset, int count, const char* contentTypeName, int p3) { return invoke<BOOL>(0x6D4CB481FAC835E8, offset, count, contentTypeName, p3); }
	NATIVE_DECL BOOL UGC_GET_BOOKMARKED_CONTENT(Any p0, Any p1, const char* p2, Any* p3) { return invoke<BOOL>(0xD5A4B59980401588, p0, p1, p2, p3); }
	NATIVE_DECL BOOL UGC_GET_MY_CONTENT(Any p0, Any p1, const char* p2, Any* p3) { return invoke<BOOL>(0x3195F8DD0D531052, p0, p1, p2, p3); }
	NATIVE_DECL BOOL UGC_GET_FRIEND_CONTENT(Any p0, Any p1, const char* p2, Any* p3) { return invoke<BOOL>(0xF9E1CCAE8BA4C281, p0, p1, p2, p3); }
	NATIVE_DECL BOOL UGC_GET_CREW_CONTENT(Any p0, Any p1, Any p2, const char* p3, Any* p4) { return invoke<BOOL>(0x9F6E2821885CAEE2, p0, p1, p2, p3, p4); }
	NATIVE_DECL BOOL UGC_GET_GET_BY_CATEGORY(Any p0, Any p1, Any p2, const char* p3, Any* p4) { return invoke<BOOL>(0x678BB03C1A3BD51E, p0, p1, p2, p3, p4); }
	NATIVE_DECL BOOL UGC_GET_GET_BY_CONTENT_ID(const char* contentId, const char* contentTypeName) { return invoke<BOOL>(0x815E5E3073DA1D67, contentId, contentTypeName); }
	NATIVE_DECL BOOL UGC_GET_GET_BY_CONTENT_IDS(Any* data, int dataCount, const char* contentTypeName) { return invoke<BOOL>(0xB8322EEB38BE7C26, data, dataCount, contentTypeName); }
	NATIVE_DECL BOOL UGC_GET_MOST_RECENTLY_CREATED_CONTENT(Any p0, Any p1, Any* p2, Any* p3) { return invoke<BOOL>(0xA7862BC5ED1DFD7E, p0, p1, p2, p3); }
	NATIVE_DECL BOOL UGC_GET_MOST_RECENTLY_PLAYED_CONTENT(Any p0, Any p1, Any* p2, Any* p3) { return invoke<BOOL>(0x97A770BEEF227E2B, p0, p1, p2, p3); }
	NATIVE_DECL BOOL UGC_GET_TOP_RATED_CONTENT(Any p0, Any p1, Any* p2, Any* p3) { return invoke<BOOL>(0x5324A0E3E4CE3570, p0, p1, p2, p3); }
	NATIVE_DECL BOOL _UGC_GET_NOMINATED_CONTENT(int offset, int maxCount, const char* contentTypeName, Any* p3) { return invoke<BOOL>(0xB1556B9C1425B727, offset, maxCount, contentTypeName, p3); }
	NATIVE_DECL void UGC_CANCEL_QUERY() { invoke<Void>(0xE9B99B6853181409); }
	NATIVE_DECL BOOL UGC_IS_GETTING() { return invoke<BOOL>(0xD53ACDBEF24A46E8); }
	NATIVE_DECL BOOL UGC_HAS_GET_FINISHED() { return invoke<BOOL>(0x02ADA21EA2F6918F); }
	NATIVE_DECL BOOL UGC_DID_GET_SUCCEED() { return invoke<BOOL>(0x941E5306BCD7C2C7); }
	NATIVE_DECL BOOL UGC_WAS_QUERY_FORCE_CANCELLED() { return invoke<BOOL>(0xC87E740D9F3872CC); }
	NATIVE_DECL int UGC_GET_QUERY_RESULT() { return invoke<int>(0xEDF7F927136C224B); }
	NATIVE_DECL int UGC_GET_CONTENT_NUM() { return invoke<int>(0xE0A6138401BCB837); }
	NATIVE_DECL int UGC_GET_CONTENT_TOTAL() { return invoke<int>(0x769951E2455E2EB5); }
	NATIVE_DECL Hash UGC_GET_CONTENT_HASH() { return invoke<Hash>(0x3A17A27D75C74887); }
	NATIVE_DECL void UGC_CLEAR_QUERY_RESULTS() { invoke<Void>(0xBA96394A0EECFA65); }
	NATIVE_DECL const char* UGC_GET_CONTENT_USER_ID(int p0) { return invoke<const char*>(0xCD67AD041A394C9C, p0); }
	NATIVE_DECL BOOL UGC_GET_CONTENT_CREATOR_GAMER_HANDLE(int p0, Any* p1) { return invoke<BOOL>(0x584770794D758C18, p0, p1); }
	NATIVE_DECL BOOL UGC_GET_CONTENT_CREATED_BY_LOCAL_PLAYER(Any p0) { return invoke<BOOL>(0x8C8D2739BA44AF0F, p0); }
	NATIVE_DECL const char* UGC_GET_CONTENT_USER_NAME(Any p0) { return invoke<const char*>(0x703F12425ECA8BF5, p0); }
	NATIVE_DECL BOOL UGC_GET_CONTENT_IS_USING_SC_NICKNAME(Any p0) { return invoke<BOOL>(0xAEAB987727C5A8A4, p0); }
	NATIVE_DECL int UGC_GET_CONTENT_CATEGORY(int p0) { return invoke<int>(0xA7BAB11E7C9C6C5A, p0); }
	NATIVE_DECL const char* UGC_GET_CONTENT_ID(int p0) { return invoke<const char*>(0x55AA95F481D694D2, p0); }
	NATIVE_DECL const char* UGC_GET_ROOT_CONTENT_ID(int p0) { return invoke<const char*>(0xC0173D6BFF4E0348, p0); }
	NATIVE_DECL const char* UGC_GET_CONTENT_NAME(Any p0) { return invoke<const char*>(0xBF09786A7FCAB582, p0); }
	NATIVE_DECL const char* UGC_GET_CONTENT_DESCRIPTION(int index) { return invoke<const char*>(0x4A56710BAB5C4DB4, index); }
	NATIVE_DECL int UGC_GET_CONTENT_DESCRIPTION_HASH(Any p0) { return invoke<int>(0x7CF0448787B23758, p0); }
	NATIVE_DECL const char* UGC_GET_CONTENT_PATH(int p0, int p1) { return invoke<const char*>(0xBAF6BABF9E7CCC13, p0, p1); }
	NATIVE_DECL void UGC_GET_CONTENT_UPDATED_DATE(Any p0, Any* p1) { invoke<Void>(0xCFD115B373C0DF63, p0, p1); }
	NATIVE_DECL int UGC_GET_CONTENT_FILE_VERSION(Any p0, Any p1) { return invoke<int>(0x37025B27D9B658B1, p0, p1); }
	NATIVE_DECL BOOL UGC_GET_CONTENT_HAS_LO_RES_PHOTO(int p0) { return invoke<BOOL>(0x1D610EB0FEA716D9, p0); }
	NATIVE_DECL BOOL UGC_GET_CONTENT_HAS_HI_RES_PHOTO(int p0) { return invoke<BOOL>(0x7FCC39C46C3C03BD, p0); }
	NATIVE_DECL int UGC_GET_CONTENT_LANGUAGE(Any p0) { return invoke<int>(0x32DD916F3F7C9672, p0); }
	NATIVE_DECL BOOL UGC_GET_CONTENT_IS_PUBLISHED(Any p0) { return invoke<BOOL>(0x3054F114121C21EA, p0); }
	NATIVE_DECL BOOL UGC_GET_CONTENT_IS_VERIFIED(Any p0) { return invoke<BOOL>(0xA9240A96C74CCA13, p0); }
	NATIVE_DECL float UGC_GET_CONTENT_RATING(Any p0, Any p1) { return invoke<float>(0x1ACCFBA3D8DAB2EE, p0, p1); }
	NATIVE_DECL int UGC_GET_CONTENT_RATING_COUNT(Any p0, Any p1) { return invoke<int>(0x759299C5BB31D2A9, p0, p1); }
	NATIVE_DECL int UGC_GET_CONTENT_RATING_POSITIVE_COUNT(Any p0, Any p1) { return invoke<int>(0x87E5C46C187FE0AE, p0, p1); }
	NATIVE_DECL int UGC_GET_CONTENT_RATING_NEGATIVE_COUNT(Any p0, Any p1) { return invoke<int>(0x4E548C0D7AE39FF9, p0, p1); }
	NATIVE_DECL BOOL UGC_GET_CONTENT_HAS_PLAYER_RECORD(Any p0) { return invoke<BOOL>(0x70EA8DA57840F9BE, p0); }
	NATIVE_DECL BOOL UGC_GET_CONTENT_HAS_PLAYER_BOOKMARKED(Any p0) { return invoke<BOOL>(0x993CBE59D350D225, p0); }
	NATIVE_DECL int UGC_REQUEST_CONTENT_DATA_FROM_INDEX(int p0, int p1) { return invoke<int>(0x171DF6A0C07FB3DC, p0, p1); }
	NATIVE_DECL int UGC_REQUEST_CONTENT_DATA_FROM_PARAMS(const char* contentTypeName, const char* contentId, int p2, int p3, int p4) { return invoke<int>(0x7FD2990AF016795E, contentTypeName, contentId, p2, p3, p4); }
	NATIVE_DECL int UGC_REQUEST_CACHED_DESCRIPTION(int p0) { return invoke<int>(0x5E0165278F6339EE, p0); }
	NATIVE_DECL BOOL UGC_IS_DESCRIPTION_REQUEST_IN_PROGRESS(Any p0) { return invoke<BOOL>(0x2D5DC831176D0114, p0); }
	NATIVE_DECL BOOL UGC_HAS_DESCRIPTION_REQUEST_FINISHED(Any p0) { return invoke<BOOL>(0xEBFA8D50ADDC54C4, p0); }
	NATIVE_DECL BOOL UGC_DID_DESCRIPTION_REQUEST_SUCCEED(Any p0) { return invoke<BOOL>(0x162C23CA83ED0A62, p0); }
	NATIVE_DECL const char* UGC_GET_CACHED_DESCRIPTION(Any p0, Any p1) { return invoke<const char*>(0x40F7E66472DF3E5C, p0, p1); }
	NATIVE_DECL BOOL UGC_RELEASE_CACHED_DESCRIPTION(Any p0) { return invoke<BOOL>(0x5A34CD9C3C5BEC44, p0); }
	NATIVE_DECL void UGC_RELEASE_ALL_CACHED_DESCRIPTIONS() { invoke<Void>(0x68103E2247887242); }
	NATIVE_DECL BOOL UGC_HAS_PERMISSION_TO_WRITE() { return invoke<BOOL>(0xC33E7CBC06EC1A8D); }
	NATIVE_DECL BOOL UGC_PUBLISH(const char* contentId, const char* baseContentId, const char* contentTypeName) { return invoke<BOOL>(0x1DE0F5F50D723CAA, contentId, baseContentId, contentTypeName); }
	NATIVE_DECL BOOL UGC_SET_BOOKMARKED(const char* contentId, BOOL bookmarked, const char* contentTypeName) { return invoke<BOOL>(0x274A1519DFC1094F, contentId, bookmarked, contentTypeName); }
	NATIVE_DECL BOOL _UGC_SET_NOMINATED_JOB(const char* contentId, BOOL nominated, const char* contentTypeName) { return invoke<BOOL>(0xEA92F1225A53BE3F, contentId, nominated, contentTypeName); }
	NATIVE_DECL BOOL _UGC_CLEAR_NOMINATED_JOB(const char* contentTypeName) { return invoke<BOOL>(0x24B3A7EB827EEDCF, contentTypeName); }
	NATIVE_DECL BOOL UGC_SET_DELETED(Any* p0, BOOL p1, const char* p2) { return invoke<BOOL>(0xD05D1A6C74DA3498, p0, p1, p2); }
	NATIVE_DECL BOOL UGC_IS_MODIFYING() { return invoke<BOOL>(0x45E816772E93A9DB); }
	NATIVE_DECL BOOL UGC_HAS_MODIFY_FINISHED() { return invoke<BOOL>(0x299EF3C576773506); }
	NATIVE_DECL BOOL UGC_DID_MODIFY_SUCCEED() { return invoke<BOOL>(0x793FF272D5B365F4); }
	NATIVE_DECL int UGC_GET_MODIFY_RESULT() { return invoke<int>(0x5A0A3D1A186A5508); }
	NATIVE_DECL void UGC_CLEAR_MODIFY_RESULT() { invoke<Void>(0xA1E5E0204A6FCC70); }
	NATIVE_DECL BOOL UGC_GET_CREATORS_BY_USER_ID(Any* p0, Any* p1) { return invoke<BOOL>(0xB746D20B17F2A229, p0, p1); }
	NATIVE_DECL BOOL UGC_HAS_QUERY_CREATORS_FINISHED() { return invoke<BOOL>(0x63B406D7884BFA95); }
	NATIVE_DECL BOOL UGC_DID_QUERY_CREATORS_SUCCEED() { return invoke<BOOL>(0x4D02279C83BE69FE); }
	NATIVE_DECL int UGC_GET_CREATOR_NUM() { return invoke<int>(0x597F8DBA9B206FC7); }
	NATIVE_DECL BOOL UGC_LOAD_OFFLINE_QUERY(Any p0) { return invoke<BOOL>(0x5CAE833B0EE0C500, p0); }
	NATIVE_DECL void UGC_CLEAR_OFFLINE_QUERY() { invoke<Void>(0x61A885D3F7CFEE9A); }
	NATIVE_DECL void UGC_SET_QUERY_DATA_FROM_OFFLINE(BOOL p0) { invoke<Void>(0xF98DDE0A8ED09323, p0); }
	NATIVE_DECL void UGC_SET_USING_OFFLINE_CONTENT(BOOL p0) { invoke<Void>(0xFD75DABC0957BF33, p0); }
	NATIVE_DECL BOOL UGC_IS_LANGUAGE_SUPPORTED(Any p0) { return invoke<BOOL>(0xF53E48461B71EECB, p0); }
	NATIVE_DECL BOOL FACEBOOK_POST_COMPLETED_HEIST(const char* heistName, int cashEarned, int xpEarned) { return invoke<BOOL>(0x098AB65B9ED9A9EC, heistName, cashEarned, xpEarned); }
	NATIVE_DECL BOOL FACEBOOK_POST_CREATE_CHARACTER() { return invoke<BOOL>(0xDC48473142545431); }
	NATIVE_DECL BOOL FACEBOOK_POST_COMPLETED_MILESTONE(int milestoneId) { return invoke<BOOL>(0x0AE1F1653B554AB9, milestoneId); }
	NATIVE_DECL BOOL FACEBOOK_HAS_POST_COMPLETED() { return invoke<BOOL>(0x62B9FEC9A11F10EF); }
	NATIVE_DECL BOOL FACEBOOK_DID_POST_SUCCEED() { return invoke<BOOL>(0xA75E2B6733DA5142); }
	NATIVE_DECL BOOL FACEBOOK_CAN_POST_TO_FACEBOOK() { return invoke<BOOL>(0x43865688AE10F0D7); }
	NATIVE_DECL int TEXTURE_DOWNLOAD_REQUEST(Any* gamerHandle, const char* filePath, const char* name, BOOL p3) { return invoke<int>(0x16160DA74A8E74A2, gamerHandle, filePath, name, p3); }
	NATIVE_DECL int TITLE_TEXTURE_DOWNLOAD_REQUEST(const char* filePath, const char* name, BOOL p2) { return invoke<int>(0x0B203B4AFDE53A4F, filePath, name, p2); }
	NATIVE_DECL int UGC_TEXTURE_DOWNLOAD_REQUEST(const char* p0, int p1, int p2, int p3, const char* p4, BOOL p5) { return invoke<int>(0x308F96458B7087CC, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL void TEXTURE_DOWNLOAD_RELEASE(int p0) { invoke<Void>(0x487EB90B98E9FB19, p0); }
	NATIVE_DECL BOOL TEXTURE_DOWNLOAD_HAS_FAILED(int p0) { return invoke<BOOL>(0x5776ED562C134687, p0); }
	NATIVE_DECL const char* TEXTURE_DOWNLOAD_GET_NAME(int p0) { return invoke<const char*>(0x3448505B6E35262D, p0); }
	NATIVE_DECL int GET_STATUS_OF_TEXTURE_DOWNLOAD(int p0) { return invoke<int>(0x8BD6C6DEA20E82C6, p0); }
	NATIVE_DECL BOOL NETWORK_CHECK_ROS_LINK_WENTDOWN_NOT_NET() { return invoke<BOOL>(0x60EDD13EB3AC1FF3); }
	NATIVE_DECL BOOL NETWORK_SHOULD_SHOW_STRICT_NAT_WARNING() { return invoke<BOOL>(0x82A2B386716608F1); }
	NATIVE_DECL BOOL NETWORK_IS_CABLE_CONNECTED() { return invoke<BOOL>(0xEFFB25453D8600F9); }
	NATIVE_DECL BOOL NETWORK_HAVE_SCS_PRIVATE_MSG_PRIV() { return invoke<BOOL>(0x66B59CFFD78467AF); }
	NATIVE_DECL BOOL NETWORK_HAVE_ROS_SOCIAL_CLUB_PRIV() { return invoke<BOOL>(0x606E4D3E3CCCF3EB); }
	NATIVE_DECL BOOL NETWORK_HAVE_ROS_BANNED_PRIV() { return invoke<BOOL>(0x8020A73847E0CA7D); }
	NATIVE_DECL BOOL NETWORK_HAVE_ROS_CREATE_TICKET_PRIV() { return invoke<BOOL>(0xA0AD7E2AF5349F61); }
	NATIVE_DECL BOOL NETWORK_HAVE_ROS_MULTIPLAYER_PRIV() { return invoke<BOOL>(0x5F91D5D0B36AA310); }
	NATIVE_DECL BOOL NETWORK_HAVE_ROS_LEADERBOARD_WRITE_PRIV() { return invoke<BOOL>(0x422D396F80A96547); }
	NATIVE_DECL BOOL NETWORK_HAS_ROS_PRIVILEGE(int index) { return invoke<BOOL>(0xA699957E60D80214, index); }
	NATIVE_DECL BOOL NETWORK_HAS_ROS_PRIVILEGE_END_DATE(int privilege, int* banType, Any* timeData) { return invoke<BOOL>(0xC22912B1D85F26B1, privilege, banType, timeData); }
	NATIVE_DECL BOOL NETWORK_HAS_ROS_PRIVILEGE_PLAYED_LAST_GEN() { return invoke<BOOL>(0x593570C289A77688); }
	NATIVE_DECL BOOL NETWORK_HAS_ROS_PRIVILEGE_SPECIAL_EDITION_CONTENT() { return invoke<BOOL>(0x91B87C55093DE351); }
	NATIVE_DECL BOOL _NETWORK_HAS_ROS_PRIVILEGE_MP_TEXT_COMMUNICATION() { return invoke<BOOL>(0xD9719341663C385F); }
	NATIVE_DECL BOOL _NETWORK_HAS_ROS_PRIVILEGE_MP_VOICE_COMMUNICATION() { return invoke<BOOL>(0x8956A309BE90057C); }
	NATIVE_DECL BOOL _NETWORK_HAS_ROS_PRIVILEGE_REPORTING() { return invoke<BOOL>(0x9BA54B3CFB82ADDD); }
	NATIVE_DECL int NETWORK_START_USER_CONTENT_PERMISSIONS_CHECK(Any* netHandle) { return invoke<int>(0xDEB2B99A1AF1A2A6, netHandle); }
	NATIVE_DECL void NETWORK_SKIP_RADIO_RESET_NEXT_CLOSE() { invoke<Void>(0x9465E683B12D3F6B); }
	NATIVE_DECL void NETWORK_SKIP_RADIO_RESET_NEXT_OPEN() { invoke<Void>(0xCA59CCAE5D01E4CE); }
	NATIVE_DECL BOOL NETWORK_SKIP_RADIO_WARNING() { return invoke<BOOL>(0x659CF2EF7F550C4F); }
	NATIVE_DECL void NETWORK_FORCE_LOCAL_PLAYER_SCAR_SYNC() { invoke<Void>(0xB7C7F6AD6424304B); }
	NATIVE_DECL void NETWORK_DISABLE_LEAVE_REMOTE_PED_BEHIND(BOOL toggle) { invoke<Void>(0xC505036A35AFD01B, toggle); }
	NATIVE_DECL void NETWORK_ALLOW_REMOTE_ATTACHMENT_MODIFICATION(Entity entity, BOOL toggle) { invoke<Void>(0x267C78C60E806B9A, entity, toggle); }
	NATIVE_DECL void NETWORK_SHOW_CHAT_RESTRICTION_MSC(Player player) { invoke<Void>(0x6BFF5F84102DF80A, player); }
	NATIVE_DECL void NETWORK_SHOW_PSN_UGC_RESTRICTION() { invoke<Void>(0x5C497525F803486B); }
	NATIVE_DECL BOOL NETWORK_IS_TITLE_UPDATE_REQUIRED() { return invoke<BOOL>(0x6FB7BB3607D27FA2); }
	NATIVE_DECL void NETWORK_QUIT_MP_TO_DESKTOP() { invoke<Void>(0x45A83257ED02D9BC); }
	NATIVE_DECL BOOL NETWORK_IS_CONNECTED_VIA_RELAY(Player player) { return invoke<BOOL>(0x16D3D49902F697BB, player); }
	NATIVE_DECL float NETWORK_GET_AVERAGE_LATENCY(Player player) { return invoke<float>(0xD414BE129BB81B32, player); }
	NATIVE_DECL float NETWORK_GET_AVERAGE_PING(Player player) { return invoke<float>(0x0E3A041ED6AC2B45, player); }
	NATIVE_DECL float NETWORK_GET_AVERAGE_PACKET_LOSS(Player player) { return invoke<float>(0x350C23949E43686C, player); }
	NATIVE_DECL int NETWORK_GET_NUM_UNACKED_RELIABLES(Player player) { return invoke<int>(0xFF8FCF9FFC458A1C, player); }
	NATIVE_DECL int NETWORK_GET_UNRELIABLE_RESEND_COUNT(Player player) { return invoke<int>(0x3765C3A3E8192E10, player); }
	NATIVE_DECL int NETWORK_GET_HIGHEST_RELIABLE_RESEND_COUNT(Player player) { return invoke<int>(0x52C1EADAF7B10302, player); }
	NATIVE_DECL void NETWORK_REPORT_CODE_TAMPER() { invoke<Void>(0x5626D9D6810730D5); }
	NATIVE_DECL void _NETWORK_GET_DUMP_OF_ASSET_VERIFIER(Any* p0) { invoke<Void>(0x69D05E1EAD74B9DD, p0); }
	NATIVE_DECL Vector3 NETWORK_GET_LAST_ENTITY_POS_RECEIVED_OVER_NETWORK(Entity entity) { return invoke<Vector3>(0x64D779659BC37B19, entity); }
	NATIVE_DECL Vector3 NETWORK_GET_LAST_PLAYER_POS_RECEIVED_OVER_NETWORK(Player player) { return invoke<Vector3>(0x125E6D638B8605D4, player); }
	NATIVE_DECL Vector3 NETWORK_GET_LAST_VEL_RECEIVED_OVER_NETWORK(Entity entity) { return invoke<Vector3>(0x33DE49EDF4DDE77A, entity); }
	NATIVE_DECL Vector3 NETWORK_GET_PREDICTED_VELOCITY(Entity entity, float maxSpeedToPredict) { return invoke<Vector3>(0xAA5FAFCD2C5F5E47, entity, maxSpeedToPredict); }
	NATIVE_DECL void NETWORK_DUMP_NET_IF_CONFIG() { invoke<Void>(0xAEDF1BC1C133D6E3); }
	NATIVE_DECL void NETWORK_GET_SIGNALLING_INFO(Any* p0) { invoke<Void>(0x2555CF7DA5473794, p0); }
	NATIVE_DECL void NETWORK_GET_NET_STATISTICS_INFO(Any* p0) { invoke<Void>(0x6FD992C4A1C1B986, p0); }
	NATIVE_DECL int NETWORK_GET_PLAYER_ACCOUNT_ID(Player player) { return invoke<int>(0xDB663CC9FF3407A9, player); }
	NATIVE_DECL BOOL NETWORK_HAS_SC_MEMBERSHIP() { return invoke<BOOL>(0xAB286B2192A71E32); }
	NATIVE_DECL void NETWORK_UGC_NAV(Any p0, Any p1) { invoke<Void>(0xC1447451DDB512F0, p0, p1); }
	NATIVE_DECL int _NETWORK_GET_GAME_RESTART_REASON() { return invoke<int>(0x7F7E8401F81CB65B); }
	NATIVE_DECL void _NETWORK_CONFIRM_GAME_RESTART() { invoke<Void>(0x0A141818CA2311AD); }
	NATIVE_DECL const char* _NETWORK_GET_GAME_RESTART_REASON_MESSAGE_LABEL() { return invoke<const char*>(0x47B11D51FC50A259); }
	NATIVE_DECL const char* _NETWORK_GET_BATTLEYE_ERROR_MESSAGE_LABEL(int errorCode) { return invoke<const char*>(0xCBA50F371E45B90D, errorCode); }
}

namespace OBJECT
{
	NATIVE_DECL Object CREATE_OBJECT(Hash modelHash, float x, float y, float z, BOOL isNetwork, BOOL bScriptHostObj, BOOL dynamic) { return invoke<Object>(0x509D5878EB39E842, modelHash, x, y, z, isNetwork, bScriptHostObj, dynamic); }
	NATIVE_DECL Object CREATE_OBJECT_NO_OFFSET(Hash modelHash, float x, float y, float z, BOOL isNetwork, BOOL bScriptHostObj, BOOL dynamic, Any p7) { return invoke<Object>(0x9A294B2138ABB884, modelHash, x, y, z, isNetwork, bScriptHostObj, dynamic, p7); }
	NATIVE_DECL void DELETE_OBJECT(Object* object) { invoke<Void>(0x539E0AE3E6634B9F, object); }
	NATIVE_DECL BOOL PLACE_OBJECT_ON_GROUND_PROPERLY(Object object) { return invoke<BOOL>(0x58A850EAEE20FAA3, object); }
	NATIVE_DECL BOOL PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY(Object object) { return invoke<BOOL>(0xD76EEEF746057FD6, object); }
	NATIVE_DECL BOOL ROTATE_OBJECT(Object object, float p1, float p2, BOOL p3) { return invoke<BOOL>(0xAFE24E4D29249E4A, object, p1, p2, p3); }
	NATIVE_DECL BOOL SLIDE_OBJECT(Object object, float toX, float toY, float toZ, float speedX, float speedY, float speedZ, BOOL collision) { return invoke<BOOL>(0x2FDFF4107B8C1147, object, toX, toY, toZ, speedX, speedY, speedZ, collision); }
	NATIVE_DECL void SET_OBJECT_TARGETTABLE(Object object, BOOL targettable, Any p2) { invoke<Void>(0x8A7391690F5AFD81, object, targettable, p2); }
	NATIVE_DECL void _SET_OBJECT_TARGETTABLE_BY_PLAYER(Object object, BOOL setFlag34, BOOL setFlag35) { invoke<Void>(0xB39F03368DB0CAA2, object, setFlag34, setFlag35); }
	NATIVE_DECL void SET_OBJECT_FORCE_VEHICLES_TO_AVOID(Object object, BOOL toggle) { invoke<Void>(0x77F33F2CCF64B3AA, object, toggle); }
	NATIVE_DECL Object GET_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, BOOL isMission, BOOL p6, BOOL p7) { return invoke<Object>(0xE143FA2249364369, x, y, z, radius, modelHash, isMission, p6, p7); }
	NATIVE_DECL BOOL HAS_OBJECT_BEEN_BROKEN(Object object, Any p1) { return invoke<BOOL>(0x8ABFB70C49CC43E2, object, p1); }
	NATIVE_DECL BOOL HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(float p0, float p1, float p2, float p3, Hash modelHash, Any p5) { return invoke<BOOL>(0x761B0E69AC4D007E, p0, p1, p2, p3, modelHash, p5); }
	NATIVE_DECL BOOL HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_COMPLETELY_DESTROYED(float x, float y, float z, float radius, Hash modelHash, BOOL p5) { return invoke<BOOL>(0x46494A2475701343, x, y, z, radius, modelHash, p5); }
	NATIVE_DECL BOOL GET_HAS_OBJECT_BEEN_COMPLETELY_DESTROYED(Any p0) { return invoke<BOOL>(0x2542269291C6AC84, p0); }
	NATIVE_DECL Vector3 GET_OFFSET_FROM_COORD_AND_HEADING_IN_WORLD_COORDS(float xPos, float yPos, float zPos, float heading, float xOffset, float yOffset, float zOffset) { return invoke<Vector3>(0x163E252DE035A133, xPos, yPos, zPos, heading, xOffset, yOffset, zOffset); }
	NATIVE_DECL BOOL GET_COORDS_AND_ROTATION_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, Vector3* outPosition, Vector3* outRotation, int rotationOrder) { return invoke<BOOL>(0x163F8B586BC95F2A, x, y, z, radius, modelHash, outPosition, outRotation, rotationOrder); }
	NATIVE_DECL void SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, float x, float y, float z, BOOL locked, float heading, BOOL p6) { invoke<Void>(0xF82D8F1926A02C3D, type, x, y, z, locked, heading, p6); }
	NATIVE_DECL void GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, float x, float y, float z, BOOL* locked, float* heading) { invoke<Void>(0xEDC1A5B84AEF33FF, type, x, y, z, locked, heading); }
	NATIVE_DECL void SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(Hash modelHash, float x, float y, float z, BOOL locked, float xRotMult, float yRotMult, float zRotMult) { invoke<Void>(0x9B12F9A24FABEDB0, modelHash, x, y, z, locked, xRotMult, yRotMult, zRotMult); }
	NATIVE_DECL void PLAY_OBJECT_AUTO_START_ANIM(Any p0) { invoke<Void>(0x006E4B040ED37EC3, p0); }
	NATIVE_DECL void ADD_DOOR_TO_SYSTEM(Hash doorHash, Hash modelHash, float x, float y, float z, BOOL p5, BOOL scriptDoor, BOOL isLocal, Any p8) { invoke<Void>(0x6F8838D03D1DC226, doorHash, modelHash, x, y, z, p5, scriptDoor, isLocal, p8); }
	NATIVE_DECL void REMOVE_DOOR_FROM_SYSTEM(Hash doorHash, Any p1) { invoke<Void>(0x464D8E1427156FE4, doorHash, p1); }
	NATIVE_DECL void DOOR_SYSTEM_SET_DOOR_STATE(Hash doorHash, int state, BOOL requestDoor, BOOL forceUpdate) { invoke<Void>(0x6BAB9442830C7F53, doorHash, state, requestDoor, forceUpdate); }
	NATIVE_DECL int DOOR_SYSTEM_GET_DOOR_STATE(Hash doorHash) { return invoke<int>(0x160AA1B32F6139B8, doorHash); }
	NATIVE_DECL int DOOR_SYSTEM_GET_DOOR_PENDING_STATE(Hash doorHash) { return invoke<int>(0x4BC2854478F3A749, doorHash); }
	NATIVE_DECL void DOOR_SYSTEM_SET_AUTOMATIC_RATE(Hash doorHash, float rate, BOOL requestDoor, BOOL forceUpdate) { invoke<Void>(0x03C27E13B42A0E82, doorHash, rate, requestDoor, forceUpdate); }
	NATIVE_DECL void DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(Hash doorHash, float distance, BOOL requestDoor, BOOL forceUpdate) { invoke<Void>(0x9BA001CB45CBF627, doorHash, distance, requestDoor, forceUpdate); }
	NATIVE_DECL void DOOR_SYSTEM_SET_OPEN_RATIO(Hash doorHash, float ajar, BOOL requestDoor, BOOL forceUpdate) { invoke<Void>(0xB6E6FBA95C7324AC, doorHash, ajar, requestDoor, forceUpdate); }
	NATIVE_DECL float DOOR_SYSTEM_GET_AUTOMATIC_DISTANCE(Hash doorHash) { return invoke<float>(0xE851471AEFC3374F, doorHash); }
	NATIVE_DECL float DOOR_SYSTEM_GET_OPEN_RATIO(Hash doorHash) { return invoke<float>(0x65499865FCA6E5EC, doorHash); }
	NATIVE_DECL BOOL DOOR_SYSTEM_GET_IS_SPRING_REMOVED(Hash doorHash) { return invoke<BOOL>(0x8562FD8AB1E94D39, doorHash); }
	NATIVE_DECL void DOOR_SYSTEM_SET_SPRING_REMOVED(Hash doorHash, BOOL removed, BOOL requestDoor, BOOL forceUpdate) { invoke<Void>(0xC485E07E4F0B7958, doorHash, removed, requestDoor, forceUpdate); }
	NATIVE_DECL void DOOR_SYSTEM_SET_HOLD_OPEN(Hash doorHash, BOOL toggle) { invoke<Void>(0xD9B71952F78A2640, doorHash, toggle); }
	NATIVE_DECL void DOOR_SYSTEM_SET_DOOR_OPEN_FOR_RACES(Hash doorHash, BOOL p1) { invoke<Void>(0xA85A21582451E951, doorHash, p1); }
	NATIVE_DECL BOOL IS_DOOR_REGISTERED_WITH_SYSTEM(Hash doorHash) { return invoke<BOOL>(0xC153C43EA202C8C1, doorHash); }
	NATIVE_DECL BOOL IS_DOOR_CLOSED(Hash doorHash) { return invoke<BOOL>(0xC531EE8A1145A149, doorHash); }
	NATIVE_DECL void OPEN_ALL_BARRIERS_FOR_RACE(BOOL p0) { invoke<Void>(0xC7F29CA00F46350E, p0); }
	NATIVE_DECL void CLOSE_ALL_BARRIERS_FOR_RACE() { invoke<Void>(0x701FDA1E82076BA4); }
	NATIVE_DECL BOOL DOOR_SYSTEM_GET_IS_PHYSICS_LOADED(Any p0) { return invoke<BOOL>(0xDF97CDD4FC08FD34, p0); }
	NATIVE_DECL BOOL DOOR_SYSTEM_FIND_EXISTING_DOOR(float x, float y, float z, Hash modelHash, Hash* outDoorHash) { return invoke<BOOL>(0x589F80B325CC82C5, x, y, z, modelHash, outDoorHash); }
	NATIVE_DECL BOOL IS_GARAGE_EMPTY(Hash garageHash, BOOL p1, int p2) { return invoke<BOOL>(0x90E47239EA1980B8, garageHash, p1, p2); }
	NATIVE_DECL BOOL IS_PLAYER_ENTIRELY_INSIDE_GARAGE(Hash garageHash, Player player, float p2, int p3) { return invoke<BOOL>(0x024A60DEB0EA69F0, garageHash, player, p2, p3); }
	NATIVE_DECL BOOL IS_PLAYER_PARTIALLY_INSIDE_GARAGE(Hash garageHash, Player player, int p2) { return invoke<BOOL>(0x1761DC5D8471CBAA, garageHash, player, p2); }
	NATIVE_DECL BOOL ARE_ENTITIES_ENTIRELY_INSIDE_GARAGE(Hash garageHash, BOOL p1, BOOL p2, BOOL p3, Any p4) { return invoke<BOOL>(0x85B6C850546FDDE2, garageHash, p1, p2, p3, p4); }
	NATIVE_DECL BOOL IS_ANY_ENTITY_ENTIRELY_INSIDE_GARAGE(Hash garageHash, BOOL p1, BOOL p2, BOOL p3, Any p4) { return invoke<BOOL>(0x673ED815D6E323B7, garageHash, p1, p2, p3, p4); }
	NATIVE_DECL BOOL IS_OBJECT_ENTIRELY_INSIDE_GARAGE(Hash garageHash, Entity entity, float p2, int p3) { return invoke<BOOL>(0x372EF6699146A1E4, garageHash, entity, p2, p3); }
	NATIVE_DECL BOOL IS_OBJECT_PARTIALLY_INSIDE_GARAGE(Hash garageHash, Entity entity, int p2) { return invoke<BOOL>(0xF0EED5A6BC7B237A, garageHash, entity, p2); }
	NATIVE_DECL void CLEAR_GARAGE(Hash garageHash, BOOL isNetwork) { invoke<Void>(0xDA05194260CDCDF9, garageHash, isNetwork); }
	NATIVE_DECL void CLEAR_OBJECTS_INSIDE_GARAGE(Hash garageHash, BOOL vehicles, BOOL peds, BOOL objects, BOOL isNetwork) { invoke<Void>(0x190428512B240692, garageHash, vehicles, peds, objects, isNetwork); }
	NATIVE_DECL void DISABLE_TIDYING_UP_IN_GARAGE(int id, BOOL toggle) { invoke<Void>(0x659F9D71F52843F8, id, toggle); }
	NATIVE_DECL void ENABLE_SAVING_IN_GARAGE(Hash garageHash, BOOL toggle) { invoke<Void>(0xF2E1A7133DD356A6, garageHash, toggle); }
	NATIVE_DECL void CLOSE_SAFEHOUSE_GARAGES() { invoke<Void>(0x66A49D021870FE88); }
	NATIVE_DECL BOOL DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(float x, float y, float z, float radius, Hash hash, BOOL p5) { return invoke<BOOL>(0xBFA48E2FF417213F, x, y, z, radius, hash, p5); }
	NATIVE_DECL BOOL IS_POINT_IN_ANGLED_AREA(float xPos, float yPos, float zPos, float x1, float y1, float z1, float x2, float y2, float z2, float width, BOOL debug, BOOL includeZ) { return invoke<BOOL>(0x2A70BAE8883E4C81, xPos, yPos, zPos, x1, y1, z1, x2, y2, z2, width, debug, includeZ); }
	NATIVE_DECL void SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY(Object object, BOOL toggle) { invoke<Void>(0x4D89D607CB3DD1D2, object, toggle); }
	NATIVE_DECL void SET_OBJECT_PHYSICS_PARAMS(Object object, float weight, float p2, float p3, float p4, float p5, float gravity, float p7, float p8, float p9, float p10, float buoyancy) { invoke<Void>(0xF6DF6E90DE7DF90F, object, weight, p2, p3, p4, p5, gravity, p7, p8, p9, p10, buoyancy); }
	NATIVE_DECL float GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(Any p0, BOOL p1) { return invoke<float>(0xB6FBFD079B8D0596, p0, p1); }
	NATIVE_DECL void SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(Object object, BOOL toggle) { invoke<Void>(0x406137F8EF90EAF5, object, toggle); }
	NATIVE_DECL BOOL IS_ANY_OBJECT_NEAR_POINT(float x, float y, float z, float range, BOOL p4) { return invoke<BOOL>(0x397DC58FF00298D1, x, y, z, range, p4); }
	NATIVE_DECL BOOL IS_OBJECT_NEAR_POINT(Hash objectHash, float x, float y, float z, float range) { return invoke<BOOL>(0x8C90FE4B381BA60A, objectHash, x, y, z, range); }
	NATIVE_DECL void REMOVE_OBJECT_HIGH_DETAIL_MODEL(Object object) { invoke<Void>(0x4A39DB43E47CF3AA, object); }
	NATIVE_DECL void BREAK_OBJECT_FRAGMENT_CHILD(Object p0, Any p1, BOOL p2) { invoke<Void>(0xE7E4C198B0185900, p0, p1, p2); }
	NATIVE_DECL void DAMAGE_OBJECT_FRAGMENT_CHILD(Any p0, Any p1, Any p2) { invoke<Void>(0xE05F6AEEFEB0BB02, p0, p1, p2); }
	NATIVE_DECL void FIX_OBJECT_FRAGMENT(Object object) { invoke<Void>(0xF9C1681347C8BD15, object); }
	NATIVE_DECL void TRACK_OBJECT_VISIBILITY(Object object) { invoke<Void>(0xB252BC036B525623, object); }
	NATIVE_DECL BOOL IS_OBJECT_VISIBLE(Object object) { return invoke<BOOL>(0x8B32ACE6326A7546, object); }
	NATIVE_DECL void SET_OBJECT_IS_SPECIAL_GOLFBALL(Object object, BOOL toggle) { invoke<Void>(0xC6033D32241F6FB5, object, toggle); }
	NATIVE_DECL void SET_OBJECT_TAKES_DAMAGE_FROM_COLLIDING_WITH_BUILDINGS(Any p0, BOOL p1) { invoke<Void>(0xEB6F1A9B5510A5D2, p0, p1); }
	NATIVE_DECL void ALLOW_DAMAGE_EVENTS_FOR_NON_NETWORKED_OBJECTS(BOOL value) { invoke<Void>(0xABDABF4E1EDECBFA, value); }
	NATIVE_DECL void SET_CUTSCENES_WEAPON_FLASHLIGHT_ON_THIS_FRAME(Object object, BOOL toggle) { invoke<Void>(0xBCE595371A5FBAAF, object, toggle); }
	NATIVE_DECL Object GET_RAYFIRE_MAP_OBJECT(float x, float y, float z, float radius, const char* name) { return invoke<Object>(0xB48FCED898292E52, x, y, z, radius, name); }
	NATIVE_DECL void SET_STATE_OF_RAYFIRE_MAP_OBJECT(Object object, int state) { invoke<Void>(0x5C29F698D404C5E1, object, state); }
	NATIVE_DECL int GET_STATE_OF_RAYFIRE_MAP_OBJECT(Object object) { return invoke<int>(0x899BA936634A322E, object); }
	NATIVE_DECL BOOL DOES_RAYFIRE_MAP_OBJECT_EXIST(Object object) { return invoke<BOOL>(0x52AF537A0C5B8AAD, object); }
	NATIVE_DECL float GET_RAYFIRE_MAP_OBJECT_ANIM_PHASE(Object object) { return invoke<float>(0x260EE4FDBDF4DB01, object); }
	NATIVE_DECL Pickup CREATE_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int p4, int value, BOOL p6, Hash modelHash) { return invoke<Pickup>(0xFBA08C503DD5FA58, pickupHash, posX, posY, posZ, p4, value, p6, modelHash); }
	NATIVE_DECL Pickup CREATE_PICKUP_ROTATE(Hash pickupHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, int flag, int amount, Any p9, BOOL p10, Hash modelHash) { return invoke<Pickup>(0x891804727E0A98B7, pickupHash, posX, posY, posZ, rotX, rotY, rotZ, flag, amount, p9, p10, modelHash); }
	NATIVE_DECL void FORCE_PICKUP_ROTATE_FACE_UP() { invoke<Void>(0x394CD08E31313C28); }
	NATIVE_DECL void SET_CUSTOM_PICKUP_WEAPON_HASH(Hash pickupHash, Pickup pickup) { invoke<Void>(0x826D1EE4D1CAFC78, pickupHash, pickup); }
	NATIVE_DECL Object CREATE_AMBIENT_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int flags, int value, Hash modelHash, BOOL p7, BOOL p8) { return invoke<Object>(0x673966A0C0FD7171, pickupHash, posX, posY, posZ, flags, value, modelHash, p7, p8); }
	NATIVE_DECL Object CREATE_NON_NETWORKED_AMBIENT_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int flags, int value, Hash modelHash, BOOL p7, BOOL p8) { return invoke<Object>(0x9C93764223E29C50, pickupHash, posX, posY, posZ, flags, value, modelHash, p7, p8); }
	NATIVE_DECL void BLOCK_PLAYERS_FOR_AMBIENT_PICKUP(Any p0, Any p1) { invoke<Void>(0x1E3F1B1B891A2AAA, p0, p1); }
	NATIVE_DECL Object CREATE_PORTABLE_PICKUP(Hash pickupHash, float x, float y, float z, BOOL placeOnGround, Hash modelHash) { return invoke<Object>(0x2EAF1FDB2FB55698, pickupHash, x, y, z, placeOnGround, modelHash); }
	NATIVE_DECL Object CREATE_NON_NETWORKED_PORTABLE_PICKUP(Hash pickupHash, float x, float y, float z, BOOL placeOnGround, Hash modelHash) { return invoke<Object>(0x125494B98A21AAF7, pickupHash, x, y, z, placeOnGround, modelHash); }
	NATIVE_DECL void ATTACH_PORTABLE_PICKUP_TO_PED(Object pickupObject, Ped ped) { invoke<Void>(0x8DC39368BDD57755, pickupObject, ped); }
	NATIVE_DECL void DETACH_PORTABLE_PICKUP_FROM_PED(Object pickupObject) { invoke<Void>(0xCF463D1E9A0AECB1, pickupObject); }
	NATIVE_DECL void FORCE_PORTABLE_PICKUP_LAST_ACCESSIBLE_POSITION_SETTING(Object object) { invoke<Void>(0x5CE2E45A5CE2E45A, object); }
	NATIVE_DECL void HIDE_PORTABLE_PICKUP_WHEN_DETACHED(Object pickupObject, BOOL toggle) { invoke<Void>(0x867458251D47CCB2, pickupObject, toggle); }
	NATIVE_DECL void SET_MAX_NUM_PORTABLE_PICKUPS_CARRIED_BY_PLAYER(Hash modelHash, int number) { invoke<Void>(0x0BF3B3BD47D79C08, modelHash, number); }
	NATIVE_DECL void SET_LOCAL_PLAYER_CAN_COLLECT_PORTABLE_PICKUPS(BOOL toggle) { invoke<Void>(0x78857FC65CADB909, toggle); }
	NATIVE_DECL Vector3 GET_SAFE_PICKUP_COORDS(float x, float y, float z, float p3, float p4) { return invoke<Vector3>(0x6E16BC2503FF1FF0, x, y, z, p3, p4); }
	NATIVE_DECL void ADD_EXTENDED_PICKUP_PROBE_AREA(float x, float y, float z, float radius) { invoke<Void>(0xD4A7A435B3710D05, x, y, z, radius); }
	NATIVE_DECL void CLEAR_EXTENDED_PICKUP_PROBE_AREAS() { invoke<Void>(0xB7C6D80FB371659A); }
	NATIVE_DECL Vector3 GET_PICKUP_COORDS(Pickup pickup) { return invoke<Vector3>(0x225B8B35C88029B3, pickup); }
	NATIVE_DECL void SUPPRESS_PICKUP_SOUND_FOR_PICKUP(Any p0, Any p1) { invoke<Void>(0x8DCA505A5C196F05, p0, p1); }
	NATIVE_DECL void REMOVE_ALL_PICKUPS_OF_TYPE(Hash pickupHash) { invoke<Void>(0x27F9D613092159CF, pickupHash); }
	NATIVE_DECL BOOL HAS_PICKUP_BEEN_COLLECTED(Pickup pickup) { return invoke<BOOL>(0x80EC48E6679313F9, pickup); }
	NATIVE_DECL void REMOVE_PICKUP(Pickup pickup) { invoke<Void>(0x3288D8ACAECD2AB2, pickup); }
	NATIVE_DECL void CREATE_MONEY_PICKUPS(float x, float y, float z, int value, int amount, Hash model) { invoke<Void>(0x0589B5E791CE9B2B, x, y, z, value, amount, model); }
	NATIVE_DECL BOOL DOES_PICKUP_EXIST(Pickup pickup) { return invoke<BOOL>(0xAFC1CA75AD4074D1, pickup); }
	NATIVE_DECL BOOL DOES_PICKUP_OBJECT_EXIST(Object pickupObject) { return invoke<BOOL>(0xD9EFB6DBF7DAAEA3, pickupObject); }
	NATIVE_DECL Object GET_PICKUP_OBJECT(Pickup pickup) { return invoke<Object>(0x5099BC55630B25AE, pickup); }
	NATIVE_DECL BOOL IS_OBJECT_A_PICKUP(Object object) { return invoke<BOOL>(0xFC481C641EBBD27D, object); }
	NATIVE_DECL BOOL IS_OBJECT_A_PORTABLE_PICKUP(Object object) { return invoke<BOOL>(0x0378C08504160D0D, object); }
	NATIVE_DECL BOOL DOES_PICKUP_OF_TYPE_EXIST_IN_AREA(Hash pickupHash, float x, float y, float z, float radius) { return invoke<BOOL>(0xF9C36251F6E48E33, pickupHash, x, y, z, radius); }
	NATIVE_DECL void SET_PICKUP_REGENERATION_TIME(Pickup pickup, int duration) { invoke<Void>(0x78015C9B4B3ECC9D, pickup, duration); }
	NATIVE_DECL void FORCE_PICKUP_REGENERATE(Any p0) { invoke<Void>(0x758A5C1B3B1E1990, p0); }
	NATIVE_DECL void SET_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_OF_TYPE(Player player, Hash pickupHash, BOOL toggle) { invoke<Void>(0x616093EC6B139DD9, player, pickupHash, toggle); }
	NATIVE_DECL void SET_LOCAL_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_WITH_MODEL(Hash modelHash, BOOL toggle) { invoke<Void>(0x88EAEC617CD26926, modelHash, toggle); }
	NATIVE_DECL void ALLOW_ALL_PLAYERS_TO_COLLECT_PICKUPS_OF_TYPE(Hash pickupHash) { invoke<Void>(0xFDC07C58E8AAB715, pickupHash); }
	NATIVE_DECL void SET_TEAM_PICKUP_OBJECT(Object object, Any p1, BOOL p2) { invoke<Void>(0x53E0DF1A2A3CF0CA, object, p1, p2); }
	NATIVE_DECL void PREVENT_COLLECTION_OF_PORTABLE_PICKUP(Object object, BOOL p1, BOOL p2) { invoke<Void>(0x92AEFB5F6E294023, object, p1, p2); }
	NATIVE_DECL void SET_PICKUP_OBJECT_GLOW_WHEN_UNCOLLECTABLE(Pickup pickup, BOOL toggle) { invoke<Void>(0x27F248C3FEBFAAD3, pickup, toggle); }
	NATIVE_DECL void _SET_PICKUP_GLOW_DISABLED(Pickup pickup, BOOL toggle) { invoke<Void>(0x08BD8BA5BDE2C2FA, pickup, toggle); }
	NATIVE_DECL void SET_PICKUP_GLOW_OFFSET(Pickup pickup, float p1) { invoke<Void>(0x0596843B34B95CE5, pickup, p1); }
	NATIVE_DECL void SET_PICKUP_OBJECT_GLOW_OFFSET(Pickup pickup, float p1, BOOL p2) { invoke<Void>(0xA08FE5E49BDC39DD, pickup, p1, p2); }
	NATIVE_DECL void SET_OBJECT_GLOW_IN_SAME_TEAM(Pickup pickup) { invoke<Void>(0x62454A641B41F3C5, pickup); }
	NATIVE_DECL void SET_PICKUP_OBJECT_ARROW_MARKER(Pickup pickup, BOOL toggle) { invoke<Void>(0x39A5FB7EAF150840, pickup, toggle); }
	NATIVE_DECL void ALLOW_PICKUP_ARROW_MARKER_WHEN_UNCOLLECTABLE(Pickup pickup, BOOL toggle) { invoke<Void>(0x834344A414C7C85D, pickup, toggle); }
	NATIVE_DECL int GET_DEFAULT_AMMO_FOR_WEAPON_PICKUP(Hash pickupHash) { return invoke<int>(0xDB41D07A45A6D4B7, pickupHash); }
	NATIVE_DECL void SET_PICKUP_GENERATION_RANGE_MULTIPLIER(float multiplier) { invoke<Void>(0x318516E02DE3ECE2, multiplier); }
	NATIVE_DECL float GET_PICKUP_GENERATION_RANGE_MULTIPLIER() { return invoke<float>(0xB3ECA65C7317F174); }
	NATIVE_DECL void SET_ONLY_ALLOW_AMMO_COLLECTION_WHEN_LOW(BOOL p0) { invoke<Void>(0x31F924B53EADDF65, p0); }
	NATIVE_DECL void SET_PICKUP_UNCOLLECTABLE(Pickup pickup, BOOL toggle) { invoke<Void>(0x1C1B69FAE509BA97, pickup, toggle); }
	NATIVE_DECL void SET_PICKUP_TRANSPARENT_WHEN_UNCOLLECTABLE(Pickup pickup, BOOL toggle) { invoke<Void>(0x858EC9FD25DE04AA, pickup, toggle); }
	NATIVE_DECL void SET_PICKUP_HIDDEN_WHEN_UNCOLLECTABLE(Pickup pickup, BOOL toggle) { invoke<Void>(0x3ED2B83AB2E82799, pickup, toggle); }
	NATIVE_DECL void SET_PICKUP_OBJECT_TRANSPARENT_WHEN_UNCOLLECTABLE(Pickup pickup, BOOL toggle) { invoke<Void>(0x8881C98A31117998, pickup, toggle); }
	NATIVE_DECL void SET_PICKUP_OBJECT_ALPHA_WHEN_TRANSPARENT(int p0) { invoke<Void>(0x8CFF648FBD7330F1, p0); }
	NATIVE_DECL void SET_PORTABLE_PICKUP_PERSIST(Pickup pickup, BOOL toggle) { invoke<Void>(0x46F3ADD1E2D5BAF2, pickup, toggle); }
	NATIVE_DECL void ALLOW_PORTABLE_PICKUP_TO_MIGRATE_TO_NON_PARTICIPANTS(Pickup pickup, BOOL toggle) { invoke<Void>(0x641F272B52E2F0F8, pickup, toggle); }
	NATIVE_DECL void FORCE_ACTIVATE_PHYSICS_ON_UNFIXED_PICKUP(Pickup pickup, BOOL toggle) { invoke<Void>(0x4C134B4DF76025D0, pickup, toggle); }
	NATIVE_DECL void ALLOW_PICKUP_BY_NONE_PARTICIPANT(Pickup pickup, BOOL toggle) { invoke<Void>(0xAA059C615DE9DD03, pickup, toggle); }
	NATIVE_DECL void SUPPRESS_PICKUP_REWARD_TYPE(int rewardType, BOOL suppress) { invoke<Void>(0xF92099527DB8E2A7, rewardType, suppress); }
	NATIVE_DECL void CLEAR_ALL_PICKUP_REWARD_TYPE_SUPPRESSION() { invoke<Void>(0xA2C1F5E92AFE49ED); }
	NATIVE_DECL void CLEAR_PICKUP_REWARD_TYPE_SUPPRESSION(int rewardType) { invoke<Void>(0x762DB2D380B48D04, rewardType); }
	NATIVE_DECL void RENDER_FAKE_PICKUP_GLOW(float x, float y, float z, int colorIndex) { invoke<Void>(0x3430676B11CDF21D, x, y, z, colorIndex); }
	NATIVE_DECL void SET_PICKUP_OBJECT_COLLECTABLE_IN_VEHICLE(Pickup pickup) { invoke<Void>(0x7813E8B8C4AE4799, pickup); }
	NATIVE_DECL void SET_PICKUP_TRACK_DAMAGE_EVENTS(Pickup pickup, BOOL toggle) { invoke<Void>(0xBFFE53AE7E67FCDC, pickup, toggle); }
	NATIVE_DECL void SET_ENTITY_FLAG_SUPPRESS_SHADOW(Entity entity, BOOL toggle) { invoke<Void>(0xD05A3241B9A86F19, entity, toggle); }
	NATIVE_DECL void SET_ENTITY_FLAG_RENDER_SMALL_SHADOW(Object object, BOOL toggle) { invoke<Void>(0xB2D0BDE54F0E8E5A, object, toggle); }
	NATIVE_DECL Hash GET_WEAPON_TYPE_FROM_PICKUP_TYPE(Hash pickupHash) { return invoke<Hash>(0x08F96CA6C551AD51, pickupHash); }
	NATIVE_DECL Hash GET_PICKUP_TYPE_FROM_WEAPON_HASH(Hash weaponHash) { return invoke<Hash>(0xD6429A016084F1A5, weaponHash); }
	NATIVE_DECL BOOL IS_PICKUP_WEAPON_OBJECT_VALID(Object object) { return invoke<BOOL>(0x11D1E53A726891FE, object); }
	NATIVE_DECL int GET_OBJECT_TINT_INDEX(Object object) { return invoke<int>(0xE84EB93729C5F36A, object); }
	NATIVE_DECL void SET_OBJECT_TINT_INDEX(Object object, int textureVariation) { invoke<Void>(0x971DA0055324D033, object, textureVariation); }
	NATIVE_DECL BOOL SET_TINT_INDEX_CLOSEST_BUILDING_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, int textureVariation) { return invoke<BOOL>(0xF12E33034D887F66, x, y, z, radius, modelHash, textureVariation); }
	NATIVE_DECL void SET_PROP_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0x31574B1B41268673, p0, p1); }
	NATIVE_DECL BOOL SET_PROP_LIGHT_COLOR(Object object, BOOL p1, int r, int g, int b) { return invoke<BOOL>(0x5F048334B4A4E774, object, p1, r, g, b); }
	NATIVE_DECL BOOL IS_PROP_LIGHT_OVERRIDEN(Object object) { return invoke<BOOL>(0xADF084FB8F075D06, object); }
	NATIVE_DECL void SET_OBJECT_IS_VISIBLE_IN_MIRRORS(Object object, BOOL toggle) { invoke<Void>(0x3B2FD68DB5F8331C, object, toggle); }
	NATIVE_DECL void SET_OBJECT_SPEED_BOOST_AMOUNT(Object object, Any p1) { invoke<Void>(0x96EE0EBA0163DF80, object, p1); }
	NATIVE_DECL void SET_OBJECT_SPEED_BOOST_DURATION(Object object, float duration) { invoke<Void>(0xDF6CA0330F2E737B, object, duration); }
	NATIVE_DECL Hash CONVERT_OLD_PICKUP_TYPE_TO_NEW(Hash pickupHash) { return invoke<Hash>(0x5EAAD83F8CFB4575, pickupHash); }
	NATIVE_DECL void SET_FORCE_OBJECT_THIS_FRAME(float x, float y, float z, float p3) { invoke<Void>(0xF538081986E49E9D, x, y, z, p3); }
	NATIVE_DECL void ONLY_CLEAN_UP_OBJECT_WHEN_OUT_OF_RANGE(Object object) { invoke<Void>(0xADBE4809F19F927A, object); }
	NATIVE_DECL void SET_DISABLE_COLLISIONS_BETWEEN_CARS_AND_CAR_PARACHUTE(Any p0) { invoke<Void>(0x8CAAB2BD3EA58BD4, p0); }
	NATIVE_DECL void SET_PROJECTILES_SHOULD_EXPLODE_ON_CONTACT(Entity entity, Any p1) { invoke<Void>(0x63ECF581BC70E363, entity, p1); }
	NATIVE_DECL void SET_DRIVE_ARTICULATED_JOINT(Object object, BOOL toggle, int p2) { invoke<Void>(0x911024442F4898F0, object, toggle, p2); }
	NATIVE_DECL void SET_DRIVE_ARTICULATED_JOINT_WITH_INFLICTOR(Object object, BOOL toggle, int p2, Ped ped) { invoke<Void>(0xB20834A7DD3D8896, object, toggle, p2, ped); }
	NATIVE_DECL void SET_OBJECT_IS_A_PRESSURE_PLATE(Object object, BOOL toggle) { invoke<Void>(0x734E1714D077DA9A, object, toggle); }
	NATIVE_DECL void SET_WEAPON_IMPACTS_APPLY_GREATER_FORCE(Object object, BOOL p1) { invoke<Void>(0x1A6CBB06E2D0D79D, object, p1); }
	NATIVE_DECL BOOL GET_IS_ARTICULATED_JOINT_AT_MIN_ANGLE(Object object, Any p1) { return invoke<BOOL>(0x43C677F1E1158005, object, p1); }
	NATIVE_DECL BOOL GET_IS_ARTICULATED_JOINT_AT_MAX_ANGLE(Any p0, Any p1) { return invoke<BOOL>(0x3BD770D281982DB5, p0, p1); }
	NATIVE_DECL void SET_IS_OBJECT_ARTICULATED(Object object, BOOL toggle) { invoke<Void>(0x1C57C94A6446492A, object, toggle); }
	NATIVE_DECL void SET_IS_OBJECT_BALL(Object object, BOOL toggle) { invoke<Void>(0xB5B7742424BD4445, object, toggle); }
}

namespace PAD
{
	NATIVE_DECL BOOL IS_CONTROL_ENABLED(int control, int action) { return invoke<BOOL>(0x1CEA6BFDF248E5D9, control, action); }
	NATIVE_DECL BOOL IS_CONTROL_PRESSED(int control, int action) { return invoke<BOOL>(0xF3A21BCD95725A4A, control, action); }
	NATIVE_DECL BOOL IS_CONTROL_RELEASED(int control, int action) { return invoke<BOOL>(0x648EE3E7F38877DD, control, action); }
	NATIVE_DECL BOOL IS_CONTROL_JUST_PRESSED(int control, int action) { return invoke<BOOL>(0x580417101DDB492F, control, action); }
	NATIVE_DECL BOOL IS_CONTROL_JUST_RELEASED(int control, int action) { return invoke<BOOL>(0x50F940259D3841E6, control, action); }
	NATIVE_DECL BOOL _IS_CONTROL_HELD_DOWN(int control, int action, int duration) { return invoke<BOOL>(0xE9CB8C56E90D5079, control, action, duration); }
	NATIVE_DECL int GET_CONTROL_VALUE(int control, int action) { return invoke<int>(0xD95E79E8686D2C27, control, action); }
	NATIVE_DECL float GET_CONTROL_NORMAL(int control, int action) { return invoke<float>(0xEC3C9B8D5327B563, control, action); }
	NATIVE_DECL void SET_USE_ADJUSTED_MOUSE_COORDS(BOOL toggle) { invoke<Void>(0x5B73C77D9EB66E24, toggle); }
	NATIVE_DECL float GET_CONTROL_UNBOUND_NORMAL(int control, int action) { return invoke<float>(0x5B84D09CEC5209C5, control, action); }
	NATIVE_DECL BOOL SET_CONTROL_VALUE_NEXT_FRAME(int control, int action, float value) { return invoke<BOOL>(0xE8A25867FBA3B05E, control, action, value); }
	NATIVE_DECL BOOL IS_DISABLED_CONTROL_PRESSED(int control, int action) { return invoke<BOOL>(0xE2587F8CBBD87B1D, control, action); }
	NATIVE_DECL BOOL IS_DISABLED_CONTROL_RELEASED(int control, int action) { return invoke<BOOL>(0xFB6C4072E9A32E92, control, action); }
	NATIVE_DECL BOOL IS_DISABLED_CONTROL_JUST_PRESSED(int control, int action) { return invoke<BOOL>(0x91AEF906BCA88877, control, action); }
	NATIVE_DECL BOOL IS_DISABLED_CONTROL_JUST_RELEASED(int control, int action) { return invoke<BOOL>(0x305C8DCD79DA8B0F, control, action); }
	NATIVE_DECL float GET_DISABLED_CONTROL_NORMAL(int control, int action) { return invoke<float>(0x11E65974A982637C, control, action); }
	NATIVE_DECL float GET_DISABLED_CONTROL_UNBOUND_NORMAL(int control, int action) { return invoke<float>(0x4F8A26A890FD62FB, control, action); }
	NATIVE_DECL int GET_CONTROL_HOW_LONG_AGO(int control) { return invoke<int>(0xD7D22F5592AED8BA, control); }
	NATIVE_DECL BOOL IS_USING_KEYBOARD_AND_MOUSE(int control) { return invoke<BOOL>(0xA571D46727E2B718, control); }
	NATIVE_DECL BOOL IS_USING_CURSOR(int control) { return invoke<BOOL>(0x13337B38DB572509, control); }
	NATIVE_DECL BOOL SET_CURSOR_POSITION(float x, float y) { return invoke<BOOL>(0xFC695459D4D0E219, x, y); }
	NATIVE_DECL BOOL IS_USING_REMOTE_PLAY(int control) { return invoke<BOOL>(0x23F09EADC01449D6, control); }
	NATIVE_DECL BOOL HAVE_CONTROLS_CHANGED(int control) { return invoke<BOOL>(0x6CD79468A1E595C6, control); }
	NATIVE_DECL const char* GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING(int control, int action, BOOL allowXOSwap) { return invoke<const char*>(0x0499D7B09FC9B407, control, action, allowXOSwap); }
	NATIVE_DECL const char* GET_CONTROL_GROUP_INSTRUCTIONAL_BUTTONS_STRING(int control, int controlGroup, BOOL allowXOSwap) { return invoke<const char*>(0x80C2FD58D720C801, control, controlGroup, allowXOSwap); }
	NATIVE_DECL void SET_CONTROL_LIGHT_EFFECT_COLOR(int control, int red, int green, int blue) { invoke<Void>(0x8290252FFF36ACB5, control, red, green, blue); }
	NATIVE_DECL void CLEAR_CONTROL_LIGHT_EFFECT(int control) { invoke<Void>(0xCB0360EFEFB2580D, control); }
	NATIVE_DECL void SET_CONTROL_SHAKE(int control, int duration, int frequency) { invoke<Void>(0x48B3886C1358D0D5, control, duration, frequency); }
	NATIVE_DECL void SET_CONTROL_TRIGGER_SHAKE(int control, int leftDuration, int leftFrequency, int rightDuration, int rightFrequency) { invoke<Void>(0x14D29BB12D47F68C, control, leftDuration, leftFrequency, rightDuration, rightFrequency); }
	NATIVE_DECL void STOP_CONTROL_SHAKE(int control) { invoke<Void>(0x38C16A305E8CDC8D, control); }
	NATIVE_DECL void SET_CONTROL_SHAKE_SUPPRESSED_ID(int control, int uniqueId) { invoke<Void>(0xF239400E16C23E08, control, uniqueId); }
	NATIVE_DECL void CLEAR_CONTROL_SHAKE_SUPPRESSED_ID(int control) { invoke<Void>(0xA0CEFCEA390AAB9B, control); }
	NATIVE_DECL BOOL IS_LOOK_INVERTED() { return invoke<BOOL>(0x77B612531280010D); }
	NATIVE_DECL BOOL IS_MOUSE_LOOK_INVERTED() { return invoke<BOOL>(0xE1615EC03B3BB4FD); }
	NATIVE_DECL int GET_LOCAL_PLAYER_AIM_STATE() { return invoke<int>(0xBB41AFBBBC0A0287); }
	NATIVE_DECL int GET_LOCAL_PLAYER_GAMEPAD_AIM_STATE() { return invoke<int>(0x59B9A7AF4C95133C); }
	NATIVE_DECL BOOL GET_IS_USING_ALTERNATE_HANDBRAKE() { return invoke<BOOL>(0x25AAA32BDC98F2A3); }
	NATIVE_DECL BOOL GET_IS_USING_ALTERNATE_DRIVEBY() { return invoke<BOOL>(0x0F70731BACCFBB96); }
	NATIVE_DECL BOOL GET_ALLOW_MOVEMENT_WHILE_ZOOMED() { return invoke<BOOL>(0xFC859E2374407556); }
	NATIVE_DECL void SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(BOOL toggle) { invoke<Void>(0x798FDEB5B1575088, toggle); }
	NATIVE_DECL void SET_INPUT_EXCLUSIVE(int control, int action) { invoke<Void>(0xEDE476E5EE29EDB1, control, action); }
	NATIVE_DECL void DISABLE_CONTROL_ACTION(int control, int action, BOOL disableRelatedActions) { invoke<Void>(0xFE99B66D079CF6BC, control, action, disableRelatedActions); }
	NATIVE_DECL void ENABLE_CONTROL_ACTION(int control, int action, BOOL enableRelatedActions) { invoke<Void>(0x351220255D64C155, control, action, enableRelatedActions); }
	NATIVE_DECL void DISABLE_ALL_CONTROL_ACTIONS(int control) { invoke<Void>(0x5F4B6931816E599B, control); }
	NATIVE_DECL void ENABLE_ALL_CONTROL_ACTIONS(int control) { invoke<Void>(0xA5FFE9B05F199DE7, control); }
	NATIVE_DECL BOOL INIT_PC_SCRIPTED_CONTROLS(const char* schemeName) { return invoke<BOOL>(0x3D42B92563939375, schemeName); }
	NATIVE_DECL BOOL SWITCH_PC_SCRIPTED_CONTROLS(const char* schemeName) { return invoke<BOOL>(0x4683149ED1DDE7A1, schemeName); }
	NATIVE_DECL void SHUTDOWN_PC_SCRIPTED_CONTROLS() { invoke<Void>(0x643ED62D5EA3BEBD); }
	NATIVE_DECL void ALLOW_ALTERNATIVE_SCRIPT_CONTROLS_LAYOUT(int control) { invoke<Void>(0x7F4724035FDCA1DD, control); }
	NATIVE_DECL int _GET_GAMEPAD_TYPE() { return invoke<int>(0x18E474F40EF05F10); }
}

namespace PATH
{
	NATIVE_DECL void SET_ROADS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, BOOL nodeEnabled, BOOL unknown2) { invoke<Void>(0xBF1A602B5BA52FEE, x1, y1, z1, x2, y2, z2, nodeEnabled, unknown2); }
	NATIVE_DECL void SET_ROADS_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, BOOL unknown1, BOOL unknown2, BOOL unknown3) { invoke<Void>(0x1A5AA1208AF5DB59, x1, y1, z1, x2, y2, z2, width, unknown1, unknown2, unknown3); }
	NATIVE_DECL void SET_PED_PATHS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, BOOL p6, Any p7) { invoke<Void>(0x34F060F4BF92E018, x1, y1, z1, x2, y2, z2, p6, p7); }
	NATIVE_DECL BOOL GET_SAFE_COORD_FOR_PED(float x, float y, float z, BOOL onGround, Vector3* outPosition, int flags) { return invoke<BOOL>(0xB61C8E878A4199CA, x, y, z, onGround, outPosition, flags); }
	NATIVE_DECL BOOL GET_CLOSEST_VEHICLE_NODE(float x, float y, float z, Vector3* outPosition, int nodeFlags, float p5, float p6) { return invoke<BOOL>(0x240A18690AE96513, x, y, z, outPosition, nodeFlags, p5, p6); }
	NATIVE_DECL BOOL GET_CLOSEST_MAJOR_VEHICLE_NODE(float x, float y, float z, Vector3* outPosition, float unknown1, float unknown2) { return invoke<BOOL>(0x2EABE3B06F58C1BE, x, y, z, outPosition, unknown1, unknown2); }
	NATIVE_DECL BOOL GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(float x, float y, float z, Vector3* outPosition, float* outHeading, int nodeType, float p6, float p7) { return invoke<BOOL>(0xFF071FB798B803B0, x, y, z, outPosition, outHeading, nodeType, p6, p7); }
	NATIVE_DECL BOOL GET_NTH_CLOSEST_VEHICLE_NODE(float x, float y, float z, int nthClosest, Vector3* outPosition, int nodeFlags, float unknown1, float unknown2) { return invoke<BOOL>(0xE50E52416CCF948B, x, y, z, nthClosest, outPosition, nodeFlags, unknown1, unknown2); }
	NATIVE_DECL int GET_NTH_CLOSEST_VEHICLE_NODE_ID(float x, float y, float z, int nth, int nodeFlags, float p5, float p6) { return invoke<int>(0x22D7275A79FE8215, x, y, z, nth, nodeFlags, p5, p6); }
	NATIVE_DECL BOOL GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(float x, float y, float z, int nthClosest, Vector3* outPosition, float* outHeading, int* outNumLanes, int nodeFlags, float unknown3, float unknown4) { return invoke<BOOL>(0x80CA6A8B6C094CC4, x, y, z, nthClosest, outPosition, outHeading, outNumLanes, nodeFlags, unknown3, unknown4); }
	NATIVE_DECL int GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING(float x, float y, float z, int nthClosest, float* outHeading, int* outNumLanes, int nodeFlags, float zMeasureMult, float zTolerance) { return invoke<int>(0x6448050E9C2A7207, x, y, z, nthClosest, outHeading, outNumLanes, nodeFlags, zMeasureMult, zTolerance); }
	NATIVE_DECL BOOL GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(float x, float y, float z, float desiredX, float desiredY, float desiredZ, int nthClosest, Vector3* outPosition, float* outHeading, int nodeFlags, float p10, float p11) { return invoke<BOOL>(0x45905BE8654AE067, x, y, z, desiredX, desiredY, desiredZ, nthClosest, outPosition, outHeading, nodeFlags, p10, p11); }
	NATIVE_DECL BOOL GET_VEHICLE_NODE_PROPERTIES(float x, float y, float z, int* density, int* flags) { return invoke<BOOL>(0x0568566ACBB5DEDC, x, y, z, density, flags); }
	NATIVE_DECL BOOL IS_VEHICLE_NODE_ID_VALID(int vehicleNodeId) { return invoke<BOOL>(0x1EAF30FCFBF5AF74, vehicleNodeId); }
	NATIVE_DECL void GET_VEHICLE_NODE_POSITION(int nodeId, Vector3* outPosition) { invoke<Void>(0x703123E5E7D429C2, nodeId, outPosition); }
	NATIVE_DECL BOOL GET_VEHICLE_NODE_IS_GPS_ALLOWED(int nodeID) { return invoke<BOOL>(0xA2AE5C478B96E3B6, nodeID); }
	NATIVE_DECL BOOL GET_VEHICLE_NODE_IS_SWITCHED_OFF(int nodeID) { return invoke<BOOL>(0x4F5070AA58F69279, nodeID); }
	NATIVE_DECL BOOL GET_CLOSEST_ROAD(float x, float y, float z, float p3, int p4, Vector3* p5, Vector3* p6, Any* p7, Any* p8, float* p9, BOOL p10) { return invoke<BOOL>(0x132F52BBA570FE92, x, y, z, p3, p4, p5, p6, p7, p8, p9, p10); }
	NATIVE_DECL BOOL LOAD_ALL_PATH_NODES(BOOL bLoadAll) { return invoke<BOOL>(0xC2AB6BFE34E92F8B, bLoadAll); }
	NATIVE_DECL void SET_ALLOW_STREAM_PROLOGUE_NODES(BOOL toggle) { invoke<Void>(0x228E5C6AD4D74BFD, toggle); }
	NATIVE_DECL void SET_ALLOW_STREAM_HEIST_ISLAND_NODES(int type) { invoke<Void>(0xF74B1FFA4A15FBEA, type); }
	NATIVE_DECL BOOL ARE_NODES_LOADED_FOR_AREA(float x1, float y1, float x2, float y2) { return invoke<BOOL>(0xF7B79A50B905A30D, x1, y1, x2, y2); }
	NATIVE_DECL BOOL REQUEST_PATH_NODES_IN_AREA_THIS_FRAME(float x1, float y1, float x2, float y2) { return invoke<BOOL>(0x07FB139B592FA687, x1, y1, x2, y2); }
	NATIVE_DECL void SET_ROADS_BACK_TO_ORIGINAL(float p0, float p1, float p2, float p3, float p4, float p5, Any p6) { invoke<Void>(0x1EE7063B80FFC77C, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, Any p7) { invoke<Void>(0x0027501B9F3B407E, x1, y1, z1, x2, y2, z2, width, p7); }
	NATIVE_DECL void SET_AMBIENT_PED_RANGE_MULTIPLIER_THIS_FRAME(float multiplier) { invoke<Void>(0x0B919E1FB47CC4E0, multiplier); }
	NATIVE_DECL void ADJUST_AMBIENT_PED_SPAWN_DENSITIES_THIS_FRAME(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xAA76052DDA9BFC3E, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void SET_PED_PATHS_BACK_TO_ORIGINAL(float x1, float y1, float z1, float x2, float y2, float z2, Any p6) { invoke<Void>(0xE04B48F2CC926253, x1, y1, z1, x2, y2, z2, p6); }
	NATIVE_DECL BOOL GET_RANDOM_VEHICLE_NODE(float x, float y, float z, float radius, BOOL p4, BOOL p5, BOOL p6, Vector3* outPosition, int* nodeId) { return invoke<BOOL>(0x93E0DB8440B73A7D, x, y, z, radius, p4, p5, p6, outPosition, nodeId); }
	NATIVE_DECL void GET_SPAWN_COORDS_FOR_VEHICLE_NODE(int nodeAddress, float towardsCoorsX, float towardsCoorsY, float towardsCoorsZ, Vector3* centrePoint, float* heading) { invoke<Void>(0x809549AFC7AEC597, nodeAddress, towardsCoorsX, towardsCoorsY, towardsCoorsZ, centrePoint, heading); }
	NATIVE_DECL void GET_STREET_NAME_AT_COORD(float x, float y, float z, Hash* streetName, Hash* crossingRoad) { invoke<Void>(0x2EB41072B4C1E4C0, x, y, z, streetName, crossingRoad); }
	NATIVE_DECL int GENERATE_DIRECTIONS_TO_COORD(float x, float y, float z, BOOL p3, int* direction, float* p5, float* distToNxJunction) { return invoke<int>(0xF90125F1F79ECDF8, x, y, z, p3, direction, p5, distToNxJunction); }
	NATIVE_DECL void SET_IGNORE_NO_GPS_FLAG(BOOL toggle) { invoke<Void>(0x72751156E7678833, toggle); }
	NATIVE_DECL void SET_IGNORE_NO_GPS_FLAG_UNTIL_FIRST_NORMAL_NODE(BOOL toggle) { invoke<Void>(0x1FC289A0C3FF470F, toggle); }
	NATIVE_DECL void SET_GPS_DISABLED_ZONE(float x1, float y1, float z1, float x2, float y2, float z3) { invoke<Void>(0xDC20483CD3DD5201, x1, y1, z1, x2, y2, z3); }
	NATIVE_DECL int GET_GPS_BLIP_ROUTE_LENGTH() { return invoke<int>(0xBBB45C3CF5C8AA85); }
	NATIVE_DECL BOOL GET_POS_ALONG_GPS_TYPE_ROUTE(Vector3* result, BOOL p1, float p2, int p3) { return invoke<BOOL>(0xF3162836C28F9DA5, result, p1, p2, p3); }
	NATIVE_DECL BOOL GET_GPS_BLIP_ROUTE_FOUND() { return invoke<BOOL>(0x869DAACBBE9FA006); }
	NATIVE_DECL BOOL GET_ROAD_BOUNDARY_USING_HEADING(float x, float y, float z, float heading, Vector3* outPosition) { return invoke<BOOL>(0xA0F8A7517A273C05, x, y, z, heading, outPosition); }
	NATIVE_DECL BOOL GET_POSITION_BY_SIDE_OF_ROAD(float x, float y, float z, int p3, Vector3* outPosition) { return invoke<BOOL>(0x16F46FB18C8009E4, x, y, z, p3, outPosition); }
	NATIVE_DECL BOOL IS_POINT_ON_ROAD(float x, float y, float z, Vehicle vehicle) { return invoke<BOOL>(0x125BF4ABFC536B09, x, y, z, vehicle); }
	NATIVE_DECL int GET_NEXT_GPS_DISABLED_ZONE_INDEX() { return invoke<int>(0xD3A6A0EF48823A8C); }
	NATIVE_DECL void SET_GPS_DISABLED_ZONE_AT_INDEX(float x1, float y1, float z1, float x2, float y2, float z2, int index) { invoke<Void>(0xD0BC1C6FB18EE154, x1, y1, z1, x2, y2, z2, index); }
	NATIVE_DECL void CLEAR_GPS_DISABLED_ZONE_AT_INDEX(int index) { invoke<Void>(0x2801D0012266DF07, index); }
	NATIVE_DECL void ADD_NAVMESH_REQUIRED_REGION(float x, float y, float radius) { invoke<Void>(0x387EAD7EE42F6685, x, y, radius); }
	NATIVE_DECL void REMOVE_NAVMESH_REQUIRED_REGIONS() { invoke<Void>(0x916F0A3CDEC3445E); }
	NATIVE_DECL BOOL IS_NAVMESH_REQUIRED_REGION_IN_USE() { return invoke<BOOL>(0x705A844002B39DC0); }
	NATIVE_DECL void DISABLE_NAVMESH_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, BOOL toggle) { invoke<Void>(0x4C8872D8CDBE1B8B, x1, y1, z1, x2, y2, z2, toggle); }
	NATIVE_DECL BOOL ARE_ALL_NAVMESH_REGIONS_LOADED() { return invoke<BOOL>(0x8415D95B194A3AEA); }
	NATIVE_DECL BOOL IS_NAVMESH_LOADED_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<BOOL>(0xF813C7E63F9062A5, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL int GET_NUM_NAVMESHES_EXISTING_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<int>(0x01708E8DD3FF8C65, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL int ADD_NAVMESH_BLOCKING_OBJECT(float p0, float p1, float p2, float p3, float p4, float p5, float p6, BOOL p7, Any p8) { return invoke<int>(0xFCD5C8E06E502F5A, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL void UPDATE_NAVMESH_BLOCKING_OBJECT(Any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, Any p8) { invoke<Void>(0x109E99373F290687, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL void REMOVE_NAVMESH_BLOCKING_OBJECT(Any p0) { invoke<Void>(0x46399A7895957C0E, p0); }
	NATIVE_DECL BOOL DOES_NAVMESH_BLOCKING_OBJECT_EXIST(Any p0) { return invoke<BOOL>(0x0EAEB0DB4B132399, p0); }
	NATIVE_DECL float GET_APPROX_HEIGHT_FOR_POINT(float x, float y) { return invoke<float>(0x29C24BFBED8AB8FB, x, y); }
	NATIVE_DECL float GET_APPROX_HEIGHT_FOR_AREA(float x1, float y1, float x2, float y2) { return invoke<float>(0x8ABE8608576D9CE3, x1, y1, x2, y2); }
	NATIVE_DECL float GET_APPROX_FLOOR_FOR_POINT(float x, float y) { return invoke<float>(0x336511A34F2E5185, x, y); }
	NATIVE_DECL float GET_APPROX_FLOOR_FOR_AREA(float x1, float y1, float x2, float y2) { return invoke<float>(0x3599D741C9AC6310, x1, y1, x2, y2); }
	NATIVE_DECL float CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<float>(0xADD95C7005C4A197, x1, y1, z1, x2, y2, z2); }
}

namespace PED
{
	NATIVE_DECL Ped CREATE_PED(int pedType, Hash modelHash, float x, float y, float z, float heading, BOOL isNetwork, BOOL bScriptHostPed) { return invoke<Ped>(0xD49F9B0955C367DE, pedType, modelHash, x, y, z, heading, isNetwork, bScriptHostPed); }
	NATIVE_DECL void DELETE_PED(Ped* ped) { invoke<Void>(0x9614299DCB53E54B, ped); }
	NATIVE_DECL Ped CLONE_PED(Ped ped, BOOL isNetwork, BOOL bScriptHostPed, BOOL copyHeadBlendFlag) { return invoke<Ped>(0xEF29A16337FACADB, ped, isNetwork, bScriptHostPed, copyHeadBlendFlag); }
	NATIVE_DECL Ped CLONE_PED_ALT(Ped ped, BOOL isNetwork, BOOL bScriptHostPed, BOOL copyHeadBlendFlag, BOOL p4) { return invoke<Ped>(0x668FD40BCBA5DE48, ped, isNetwork, bScriptHostPed, copyHeadBlendFlag, p4); }
	NATIVE_DECL void CLONE_PED_TO_TARGET(Ped ped, Ped targetPed) { invoke<Void>(0xE952D6431689AD9A, ped, targetPed); }
	NATIVE_DECL void CLONE_PED_TO_TARGET_ALT(Ped ped, Ped targetPed, BOOL p2) { invoke<Void>(0x148B08C2D2ACB884, ped, targetPed, p2); }
	NATIVE_DECL BOOL IS_PED_IN_VEHICLE(Ped ped, Vehicle vehicle, BOOL atGetIn) { return invoke<BOOL>(0xA3EE4A07279BB9DB, ped, vehicle, atGetIn); }
	NATIVE_DECL BOOL IS_PED_IN_MODEL(Ped ped, Hash modelHash) { return invoke<BOOL>(0x796D90EFB19AA332, ped, modelHash); }
	NATIVE_DECL BOOL IS_PED_IN_ANY_VEHICLE(Ped ped, BOOL atGetIn) { return invoke<BOOL>(0x997ABD671D25CA0B, ped, atGetIn); }
	NATIVE_DECL BOOL IS_COP_PED_IN_AREA_3D(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<BOOL>(0x16EC4839969F9F5E, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL BOOL IS_PED_INJURED(Ped ped) { return invoke<BOOL>(0x84A2DD9AC37C35C1, ped); }
	NATIVE_DECL BOOL IS_PED_HURT(Ped ped) { return invoke<BOOL>(0x5983BB449D7FDB12, ped); }
	NATIVE_DECL BOOL IS_PED_FATALLY_INJURED(Ped ped) { return invoke<BOOL>(0xD839450756ED5A80, ped); }
	NATIVE_DECL BOOL IS_PED_DEAD_OR_DYING(Ped ped, BOOL checkMeleeDeathFlags) { return invoke<BOOL>(0x3317DEDB88C95038, ped, checkMeleeDeathFlags); }
	NATIVE_DECL BOOL IS_CONVERSATION_PED_DEAD(Ped ped) { return invoke<BOOL>(0xE0A0AEC214B1FABA, ped); }
	NATIVE_DECL BOOL IS_PED_AIMING_FROM_COVER(Ped ped) { return invoke<BOOL>(0x3998B1276A3300E5, ped); }
	NATIVE_DECL BOOL IS_PED_RELOADING(Ped ped) { return invoke<BOOL>(0x24B100C68C645951, ped); }
	NATIVE_DECL BOOL IS_PED_A_PLAYER(Ped ped) { return invoke<BOOL>(0x12534C348C6CB68B, ped); }
	NATIVE_DECL Ped CREATE_PED_INSIDE_VEHICLE(Vehicle vehicle, int pedType, Hash modelHash, int seat, BOOL isNetwork, BOOL bScriptHostPed) { return invoke<Ped>(0x7DD959874C1FD534, vehicle, pedType, modelHash, seat, isNetwork, bScriptHostPed); }
	NATIVE_DECL void SET_PED_DESIRED_HEADING(Ped ped, float heading) { invoke<Void>(0xAA5A7ECE2AA8FE70, ped, heading); }
	NATIVE_DECL void FORCE_ALL_HEADING_VALUES_TO_ALIGN(Ped ped) { invoke<Void>(0xFF287323B0E2C69A, ped); }
	NATIVE_DECL BOOL IS_PED_FACING_PED(Ped ped, Ped otherPed, float angle) { return invoke<BOOL>(0xD71649DB0A545AA3, ped, otherPed, angle); }
	NATIVE_DECL BOOL IS_PED_IN_MELEE_COMBAT(Ped ped) { return invoke<BOOL>(0x4E209B2C1EAD5159, ped); }
	NATIVE_DECL BOOL IS_PED_STOPPED(Ped ped) { return invoke<BOOL>(0x530944F6F4B8A214, ped); }
	NATIVE_DECL BOOL IS_PED_SHOOTING_IN_AREA(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, BOOL p7, BOOL p8) { return invoke<BOOL>(0x7E9DFE24AC1E58EF, ped, x1, y1, z1, x2, y2, z2, p7, p8); }
	NATIVE_DECL BOOL IS_ANY_PED_SHOOTING_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, BOOL p6, BOOL p7) { return invoke<BOOL>(0xA0D3D71EA1086C55, x1, y1, z1, x2, y2, z2, p6, p7); }
	NATIVE_DECL BOOL IS_PED_SHOOTING(Ped ped) { return invoke<BOOL>(0x34616828CD07F1A1, ped); }
	NATIVE_DECL void SET_PED_ACCURACY(Ped ped, int accuracy) { invoke<Void>(0x7AEFB85C1D49DEB6, ped, accuracy); }
	NATIVE_DECL int GET_PED_ACCURACY(Ped ped) { return invoke<int>(0x37F4AD56ECBC0CD6, ped); }
	NATIVE_DECL void SET_AMBIENT_LAW_PED_ACCURACY_MODIFIER(float multiplier) { invoke<Void>(0x87DDEB611B329A9C, multiplier); }
	NATIVE_DECL BOOL IS_PED_MODEL(Ped ped, Hash modelHash) { return invoke<BOOL>(0xC9D55B1A358A5BF7, ped, modelHash); }
	NATIVE_DECL void EXPLODE_PED_HEAD(Ped ped, Hash weaponHash) { invoke<Void>(0x2D05CED3A38D0F3A, ped, weaponHash); }
	NATIVE_DECL void REMOVE_PED_ELEGANTLY(Ped* ped) { invoke<Void>(0xAC6D445B994DF95E, ped); }
	NATIVE_DECL void ADD_ARMOUR_TO_PED(Ped ped, int amount) { invoke<Void>(0x5BA652A0CD14DF2F, ped, amount); }
	NATIVE_DECL void SET_PED_ARMOUR(Ped ped, int amount) { invoke<Void>(0xCEA04D83135264CC, ped, amount); }
	NATIVE_DECL void SET_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seatIndex) { invoke<Void>(0xF75B0D629E1C063D, ped, vehicle, seatIndex); }
	NATIVE_DECL void SET_PED_ALLOW_VEHICLES_OVERRIDE(Ped ped, BOOL toggle) { invoke<Void>(0x3C028C636A414ED9, ped, toggle); }
	NATIVE_DECL BOOL CAN_CREATE_RANDOM_PED(BOOL p0) { return invoke<BOOL>(0x3E8349C08E4B82E4, p0); }
	NATIVE_DECL Ped CREATE_RANDOM_PED(float posX, float posY, float posZ) { return invoke<Ped>(0xB4AC7D0CF06BFE8F, posX, posY, posZ); }
	NATIVE_DECL Ped CREATE_RANDOM_PED_AS_DRIVER(Vehicle vehicle, BOOL returnHandle) { return invoke<Ped>(0x9B62392B474F44A0, vehicle, returnHandle); }
	NATIVE_DECL BOOL CAN_CREATE_RANDOM_DRIVER() { return invoke<BOOL>(0xB8EB95E5B4E56978); }
	NATIVE_DECL BOOL CAN_CREATE_RANDOM_BIKE_RIDER() { return invoke<BOOL>(0xEACEEDA81751915C); }
	NATIVE_DECL void SET_PED_MOVE_ANIMS_BLEND_OUT(Ped ped) { invoke<Void>(0x9E8C908F41584ECD, ped); }
	NATIVE_DECL void SET_PED_CAN_BE_DRAGGED_OUT(Ped ped, BOOL toggle) { invoke<Void>(0xC1670E958EEE24E5, ped, toggle); }
	NATIVE_DECL void SET_PED_ALLOW_HURT_COMBAT_FOR_ALL_MISSION_PEDS(BOOL toggle) { invoke<Void>(0xF2BEBCDFAFDAA19E, toggle); }
	NATIVE_DECL BOOL IS_PED_MALE(Ped ped) { return invoke<BOOL>(0x6D9F5FAA7488BA46, ped); }
	NATIVE_DECL BOOL IS_PED_HUMAN(Ped ped) { return invoke<BOOL>(0xB980061DA992779D, ped); }
	NATIVE_DECL Vehicle GET_VEHICLE_PED_IS_IN(Ped ped, BOOL includeEntering) { return invoke<Vehicle>(0x9A9112A0FE9A4713, ped, includeEntering); }
	NATIVE_DECL void RESET_PED_LAST_VEHICLE(Ped ped) { invoke<Void>(0xBB8DE8CF6A8DD8BB, ped); }
	NATIVE_DECL void SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier) { invoke<Void>(0x95E3D6257B166CF2, multiplier); }
	NATIVE_DECL void SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(float p0, float p1) { invoke<Void>(0x7A556143A1C03898, p0, p1); }
	NATIVE_DECL void SUPPRESS_AMBIENT_PED_AGGRESSIVE_CLEANUP_THIS_FRAME() { invoke<Void>(0x5A7F62FDA59759BD); }
	NATIVE_DECL void SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME(float x, float y, float z) { invoke<Void>(0x5086C7843552CF85, x, y, z); }
	NATIVE_DECL void SET_PED_NON_CREATION_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { invoke<Void>(0xEE01041D559983EA, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL void CLEAR_PED_NON_CREATION_AREA() { invoke<Void>(0x2E05208086BA0651); }
	NATIVE_DECL void INSTANTLY_FILL_PED_POPULATION() { invoke<Void>(0x4759CC730F947C81); }
	NATIVE_DECL BOOL IS_PED_ON_MOUNT(Ped ped) { return invoke<BOOL>(0x460BC76A0E10655E, ped); }
	NATIVE_DECL Ped GET_MOUNT(Ped ped) { return invoke<Ped>(0xE7E11B8DCBED1058, ped); }
	NATIVE_DECL BOOL IS_PED_ON_VEHICLE(Ped ped) { return invoke<BOOL>(0x67722AEB798E5FAB, ped); }
	NATIVE_DECL BOOL IS_PED_ON_SPECIFIC_VEHICLE(Ped ped, Vehicle vehicle) { return invoke<BOOL>(0xEC5F66E459AF3BB2, ped, vehicle); }
	NATIVE_DECL void SET_PED_MONEY(Ped ped, int amount) { invoke<Void>(0xA9C8960E8684C1B5, ped, amount); }
	NATIVE_DECL int GET_PED_MONEY(Ped ped) { return invoke<int>(0x3F69145BBA87BAE7, ped); }
	NATIVE_DECL void SET_HEALTH_SNACKS_CARRIED_BY_ALL_NEW_PEDS(float p0, Any p1) { invoke<Void>(0xFF4803BC019852D9, p0, p1); }
	NATIVE_DECL void SET_AMBIENT_PEDS_DROP_MONEY(BOOL p0) { invoke<Void>(0x6B0E6172C9A4D902, p0); }
	NATIVE_DECL void _SET_BLOCK_AMBIENT_PEDS_FROM_DROPPING_WEAPONS_THIS_FRAME() { invoke<Void>(0xC73EFFC5E043A8BA); }
	NATIVE_DECL void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS_FOR_AMBIENT_PEDS_THIS_FRAME(BOOL p0) { invoke<Void>(0x9911F4A24485F653, p0); }
	NATIVE_DECL void SET_PED_SUFFERS_CRITICAL_HITS(Ped ped, BOOL toggle) { invoke<Void>(0xEBD76F2359F190AC, ped, toggle); }
	NATIVE_DECL void SET_PED_UPPER_BODY_DAMAGE_ONLY(Ped ped, BOOL toggle) { invoke<Void>(0xAFC976FD0580C7B3, ped, toggle); }
	NATIVE_DECL BOOL IS_PED_SITTING_IN_VEHICLE(Ped ped, Vehicle vehicle) { return invoke<BOOL>(0xA808AA1D79230FC2, ped, vehicle); }
	NATIVE_DECL BOOL IS_PED_SITTING_IN_ANY_VEHICLE(Ped ped) { return invoke<BOOL>(0x826AA586EDB9FEF8, ped); }
	NATIVE_DECL BOOL IS_PED_ON_FOOT(Ped ped) { return invoke<BOOL>(0x01FEE67DB37F59B2, ped); }
	NATIVE_DECL BOOL IS_PED_ON_ANY_BIKE(Ped ped) { return invoke<BOOL>(0x94495889E22C6479, ped); }
	NATIVE_DECL BOOL IS_PED_PLANTING_BOMB(Ped ped) { return invoke<BOOL>(0xC70B5FAE151982D8, ped); }
	NATIVE_DECL Vector3 GET_DEAD_PED_PICKUP_COORDS(Ped ped, float p1, float p2) { return invoke<Vector3>(0xCD5003B097200F36, ped, p1, p2); }
	NATIVE_DECL BOOL IS_PED_IN_ANY_BOAT(Ped ped) { return invoke<BOOL>(0x2E0E1C2B4F6CB339, ped); }
	NATIVE_DECL BOOL IS_PED_IN_ANY_SUB(Ped ped) { return invoke<BOOL>(0xFBFC01CCFB35D99E, ped); }
	NATIVE_DECL BOOL IS_PED_IN_ANY_HELI(Ped ped) { return invoke<BOOL>(0x298B91AE825E5705, ped); }
	NATIVE_DECL BOOL IS_PED_IN_ANY_PLANE(Ped ped) { return invoke<BOOL>(0x5FFF4CFC74D8FB80, ped); }
	NATIVE_DECL BOOL IS_PED_IN_FLYING_VEHICLE(Ped ped) { return invoke<BOOL>(0x9134873537FA419C, ped); }
	NATIVE_DECL void SET_PED_DIES_IN_WATER(Ped ped, BOOL toggle) { invoke<Void>(0x56CEF0AC79073BDE, ped, toggle); }
	NATIVE_DECL BOOL GET_PED_DIES_IN_WATER(Ped ped) { return invoke<BOOL>(0x65671A4FB8218930, ped); }
	NATIVE_DECL void SET_PED_DIES_IN_SINKING_VEHICLE(Ped ped, BOOL toggle) { invoke<Void>(0xD718A22995E2B4BC, ped, toggle); }
	NATIVE_DECL int GET_PED_ARMOUR(Ped ped) { return invoke<int>(0x9483AF821605B1D8, ped); }
	NATIVE_DECL void SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(Ped ped, BOOL toggle) { invoke<Void>(0xEDF4079F9D54C9A1, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_BE_SHOT_IN_VEHICLE(Ped ped, BOOL toggle) { invoke<Void>(0xC7EF1BA83230BA07, ped, toggle); }
	NATIVE_DECL BOOL GET_PED_LAST_DAMAGE_BONE(Ped ped, int* outBone) { return invoke<BOOL>(0xD75960F6BD9EA49C, ped, outBone); }
	NATIVE_DECL void CLEAR_PED_LAST_DAMAGE_BONE(Ped ped) { invoke<Void>(0x8EF6B7AC68E2F01B, ped); }
	NATIVE_DECL void SET_AI_WEAPON_DAMAGE_MODIFIER(float value) { invoke<Void>(0x1B1E2A40A65B8521, value); }
	NATIVE_DECL void RESET_AI_WEAPON_DAMAGE_MODIFIER() { invoke<Void>(0xEA16670E7BA4743C); }
	NATIVE_DECL void SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER(float modifier) { invoke<Void>(0x66460DEDDD417254, modifier); }
	NATIVE_DECL void RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER() { invoke<Void>(0x46E56A7CD1D63C3F); }
	NATIVE_DECL void SET_TREAT_AS_AMBIENT_PED_FOR_DRIVER_LOCKON(Ped ped, BOOL p1) { invoke<Void>(0x2F3C3D9F50681DE4, ped, p1); }
	NATIVE_DECL void SET_PED_CAN_BE_TARGETTED(Ped ped, BOOL toggle) { invoke<Void>(0x63F58F7C80513AAD, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_BE_TARGETTED_BY_TEAM(Ped ped, int team, BOOL toggle) { invoke<Void>(0xBF1CA77833E58F2C, ped, team, toggle); }
	NATIVE_DECL void SET_PED_CAN_BE_TARGETTED_BY_PLAYER(Ped ped, Player player, BOOL toggle) { invoke<Void>(0x66B57B72E0836A76, ped, player, toggle); }
	NATIVE_DECL void SET_ALLOW_LOCKON_TO_PED_IF_FRIENDLY(Ped ped, BOOL toggle) { invoke<Void>(0x061CB768363D6424, ped, toggle); }
	NATIVE_DECL void SET_USE_CAMERA_HEADING_FOR_DESIRED_DIRECTION_LOCK_ON_TEST(Ped ped, BOOL toggle) { invoke<Void>(0xFD325494792302D7, ped, toggle); }
	NATIVE_DECL BOOL IS_PED_IN_ANY_POLICE_VEHICLE(Ped ped) { return invoke<BOOL>(0x0BD04E29640C9C12, ped); }
	NATIVE_DECL void FORCE_PED_TO_OPEN_PARACHUTE(Ped ped) { invoke<Void>(0x16E42E800B472221, ped); }
	NATIVE_DECL BOOL IS_PED_IN_PARACHUTE_FREE_FALL(Ped ped) { return invoke<BOOL>(0x7DCE8BDA0F1C1200, ped); }
	NATIVE_DECL BOOL IS_PED_FALLING(Ped ped) { return invoke<BOOL>(0xFB92A102F1C4DFA3, ped); }
	NATIVE_DECL BOOL IS_PED_JUMPING(Ped ped) { return invoke<BOOL>(0xCEDABC5900A0BF97, ped); }
	NATIVE_DECL BOOL IS_PED_LANDING(Any p0) { return invoke<BOOL>(0x412F1364FA066CFB, p0); }
	NATIVE_DECL BOOL IS_PED_DOING_A_BEAST_JUMP(Any p0) { return invoke<BOOL>(0x451D05012CCEC234, p0); }
	NATIVE_DECL BOOL IS_PED_CLIMBING(Ped ped) { return invoke<BOOL>(0x53E8CB4F48BFE623, ped); }
	NATIVE_DECL BOOL IS_PED_VAULTING(Ped ped) { return invoke<BOOL>(0x117C70D1F5730B5E, ped); }
	NATIVE_DECL BOOL IS_PED_DIVING(Ped ped) { return invoke<BOOL>(0x5527B8246FEF9B11, ped); }
	NATIVE_DECL BOOL IS_PED_JUMPING_OUT_OF_VEHICLE(Ped ped) { return invoke<BOOL>(0x433DDFFE2044B636, ped); }
	NATIVE_DECL BOOL IS_PED_OPENING_DOOR(Ped ped) { return invoke<BOOL>(0x26AF0E8E30BD2A2C, ped); }
	NATIVE_DECL int GET_PED_PARACHUTE_STATE(Ped ped) { return invoke<int>(0x79CFD9827CC979B6, ped); }
	NATIVE_DECL int GET_PED_PARACHUTE_LANDING_TYPE(Ped ped) { return invoke<int>(0x8B9F1FC6AE8166C0, ped); }
	NATIVE_DECL void SET_PED_PARACHUTE_TINT_INDEX(Ped ped, int tintIndex) { invoke<Void>(0x333FC8DB079B7186, ped, tintIndex); }
	NATIVE_DECL void GET_PED_PARACHUTE_TINT_INDEX(Ped ped, int* outTintIndex) { invoke<Void>(0xEAF5F7E5AE7C6C9D, ped, outTintIndex); }
	NATIVE_DECL void SET_PED_RESERVE_PARACHUTE_TINT_INDEX(Ped ped, Any p1) { invoke<Void>(0xE88DA0751C22A2AD, ped, p1); }
	NATIVE_DECL Object CREATE_PARACHUTE_BAG_OBJECT(Ped ped, BOOL p1, BOOL p2) { return invoke<Object>(0x8C4F3BF23B6237DB, ped, p1, p2); }
	NATIVE_DECL void SET_PED_DUCKING(Ped ped, BOOL toggle) { invoke<Void>(0x030983CA930B692D, ped, toggle); }
	NATIVE_DECL BOOL IS_PED_DUCKING(Ped ped) { return invoke<BOOL>(0xD125AE748725C6BC, ped); }
	NATIVE_DECL BOOL IS_PED_IN_ANY_TAXI(Ped ped) { return invoke<BOOL>(0x6E575D6A898AB852, ped); }
	NATIVE_DECL void SET_PED_ID_RANGE(Ped ped, float value) { invoke<Void>(0xF107E836A70DCE05, ped, value); }
	NATIVE_DECL void SET_PED_HIGHLY_PERCEPTIVE(Ped ped, BOOL toggle) { invoke<Void>(0x52D59AB61DDC05DD, ped, toggle); }
	NATIVE_DECL void SET_COP_PERCEPTION_OVERRIDES(float seeingRange, float seeingRangePeripheral, float hearingRange, float visualFieldMinAzimuthAngle, float visualFieldMaxAzimuthAngle, float fieldOfGazeMaxAngle, float p6) { invoke<Void>(0x2F074C904D85129E, seeingRange, seeingRangePeripheral, hearingRange, visualFieldMinAzimuthAngle, visualFieldMaxAzimuthAngle, fieldOfGazeMaxAngle, p6); }
	NATIVE_DECL void SET_PED_INJURED_ON_GROUND_BEHAVIOUR(Ped ped, float p1) { invoke<Void>(0xEC4B4B3B9908052A, ped, p1); }
	NATIVE_DECL void DISABLE_PED_INJURED_ON_GROUND_BEHAVIOUR(Ped ped) { invoke<Void>(0x733C87D4CE22BEA2, ped); }
	NATIVE_DECL void SET_PED_SEEING_RANGE(Ped ped, float value) { invoke<Void>(0xF29CF591C4BF6CEE, ped, value); }
	NATIVE_DECL void SET_PED_HEARING_RANGE(Ped ped, float value) { invoke<Void>(0x33A8F7F7D5F7F33C, ped, value); }
	NATIVE_DECL void SET_PED_VISUAL_FIELD_MIN_ANGLE(Ped ped, float value) { invoke<Void>(0x2DB492222FB21E26, ped, value); }
	NATIVE_DECL void SET_PED_VISUAL_FIELD_MAX_ANGLE(Ped ped, float value) { invoke<Void>(0x70793BDCA1E854D4, ped, value); }
	NATIVE_DECL void SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(Ped ped, float angle) { invoke<Void>(0x7A276EB2C224D70F, ped, angle); }
	NATIVE_DECL void SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(Ped ped, float angle) { invoke<Void>(0x78D0B67629D75856, ped, angle); }
	NATIVE_DECL void SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(Ped ped, float range) { invoke<Void>(0x9C74B0BC831B753A, ped, range); }
	NATIVE_DECL void SET_PED_VISUAL_FIELD_CENTER_ANGLE(Ped ped, float angle) { invoke<Void>(0x3B6405E8AB34A907, ped, angle); }
	NATIVE_DECL float GET_PED_VISUAL_FIELD_CENTER_ANGLE(Ped ped) { return invoke<float>(0xEF2C71A32CAD5FBD, ped); }
	NATIVE_DECL void SET_PED_STEALTH_MOVEMENT(Ped ped, BOOL p1, const char* action) { invoke<Void>(0x88CBB5CEB96B7BD2, ped, p1, action); }
	NATIVE_DECL BOOL GET_PED_STEALTH_MOVEMENT(Ped ped) { return invoke<BOOL>(0x7C2AC9CA66575FBF, ped); }
	NATIVE_DECL int CREATE_GROUP(int unused) { return invoke<int>(0x90370EBE0FEE1A3D, unused); }
	NATIVE_DECL void SET_PED_AS_GROUP_LEADER(Ped ped, int groupId) { invoke<Void>(0x2A7819605465FBCE, ped, groupId); }
	NATIVE_DECL void SET_PED_AS_GROUP_MEMBER(Ped ped, int groupId) { invoke<Void>(0x9F3480FE65DB31B5, ped, groupId); }
	NATIVE_DECL void SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(Ped pedHandle, int groupHandle, BOOL toggle) { invoke<Void>(0x2E2F4240B3F24647, pedHandle, groupHandle, toggle); }
	NATIVE_DECL void REMOVE_GROUP(int groupId) { invoke<Void>(0x8EB2F69076AF7053, groupId); }
	NATIVE_DECL void REMOVE_PED_FROM_GROUP(Ped ped) { invoke<Void>(0xED74007FFB146BC2, ped); }
	NATIVE_DECL BOOL IS_PED_GROUP_MEMBER(Ped ped, int groupId) { return invoke<BOOL>(0x9BB01E3834671191, ped, groupId); }
	NATIVE_DECL BOOL IS_PED_HANGING_ON_TO_VEHICLE(Ped ped) { return invoke<BOOL>(0x1C86D8AEF8254B78, ped); }
	NATIVE_DECL void SET_GROUP_SEPARATION_RANGE(int groupHandle, float separationRange) { invoke<Void>(0x4102C7858CFEE4E4, groupHandle, separationRange); }
	NATIVE_DECL void SET_PED_MIN_GROUND_TIME_FOR_STUNGUN(Ped ped, int ms) { invoke<Void>(0xFA0675AB151073FA, ped, ms); }
	NATIVE_DECL BOOL IS_PED_PRONE(Ped ped) { return invoke<BOOL>(0xD6A86331A537A7B9, ped); }
	NATIVE_DECL BOOL IS_PED_IN_COMBAT(Ped ped, Ped target) { return invoke<BOOL>(0x4859F1FC66A6278E, ped, target); }
	NATIVE_DECL Entity GET_PED_TARGET_FROM_COMBAT_PED(Ped ped, Any p1) { return invoke<Entity>(0x32C27A11307B01CC, ped, p1); }
	NATIVE_DECL BOOL CAN_PED_IN_COMBAT_SEE_TARGET(Ped ped, Ped target) { return invoke<BOOL>(0xEAD42DE3610D0721, ped, target); }
	NATIVE_DECL BOOL IS_PED_DOING_DRIVEBY(Ped ped) { return invoke<BOOL>(0xB2C086CC1BF8F2BF, ped); }
	NATIVE_DECL BOOL IS_PED_JACKING(Ped ped) { return invoke<BOOL>(0x4AE4FF911DFB61DA, ped); }
	NATIVE_DECL BOOL IS_PED_BEING_JACKED(Ped ped) { return invoke<BOOL>(0x9A497FE2DF198913, ped); }
	NATIVE_DECL BOOL IS_PED_BEING_STUNNED(Ped ped, int p1) { return invoke<BOOL>(0x4FBACCE3B4138EE8, ped, p1); }
	NATIVE_DECL Ped GET_PEDS_JACKER(Ped ped) { return invoke<Ped>(0x9B128DC36C1E04CF, ped); }
	NATIVE_DECL Ped GET_JACK_TARGET(Ped ped) { return invoke<Ped>(0x5486A79D9FBD342D, ped); }
	NATIVE_DECL BOOL IS_PED_FLEEING(Ped ped) { return invoke<BOOL>(0xBBCCE00B381F8482, ped); }
	NATIVE_DECL BOOL IS_PED_IN_COVER(Ped ped, BOOL exceptUseWeapon) { return invoke<BOOL>(0x60DFD0691A170B88, ped, exceptUseWeapon); }
	NATIVE_DECL BOOL IS_PED_IN_COVER_FACING_LEFT(Ped ped) { return invoke<BOOL>(0x845333B3150583AB, ped); }
	NATIVE_DECL BOOL IS_PED_IN_HIGH_COVER(Ped ped) { return invoke<BOOL>(0x6A03BF943D767C93, ped); }
	NATIVE_DECL BOOL IS_PED_GOING_INTO_COVER(Ped ped) { return invoke<BOOL>(0x9F65DBC537E59AD5, ped); }
	NATIVE_DECL BOOL SET_PED_PINNED_DOWN(Ped ped, BOOL pinned, int i) { return invoke<BOOL>(0xAAD6D1ACF08F4612, ped, pinned, i); }
	NATIVE_DECL BOOL _HAS_PED_CLEAR_LOS_TO_ENTITY(Ped ped, Entity entity, float x, float y, float z, int p5, BOOL p6, BOOL p7) { return invoke<BOOL>(0xA32ABFEB2A03B306, ped, entity, x, y, z, p5, p6, p7); }
	NATIVE_DECL int GET_SEAT_PED_IS_TRYING_TO_ENTER(Ped ped) { return invoke<int>(0x6F4C85ACD641BCD2, ped); }
	NATIVE_DECL Vehicle GET_VEHICLE_PED_IS_TRYING_TO_ENTER(Ped ped) { return invoke<Vehicle>(0x814FA8BE5449445D, ped); }
	NATIVE_DECL Entity GET_PED_SOURCE_OF_DEATH(Ped ped) { return invoke<Entity>(0x93C8B64DEB84728C, ped); }
	NATIVE_DECL Hash GET_PED_CAUSE_OF_DEATH(Ped ped) { return invoke<Hash>(0x16FFE42AB2D2DC59, ped); }
	NATIVE_DECL int GET_PED_TIME_OF_DEATH(Ped ped) { return invoke<int>(0x1E98817B311AE98A, ped); }
	NATIVE_DECL int COUNT_PEDS_IN_COMBAT_WITH_TARGET(Ped ped) { return invoke<int>(0x5407B7288D0478B7, ped); }
	NATIVE_DECL int COUNT_PEDS_IN_COMBAT_WITH_TARGET_WITHIN_RADIUS(Ped ped, float x, float y, float z, float radius) { return invoke<int>(0x336B3D200AB007CB, ped, x, y, z, radius); }
	NATIVE_DECL void SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped, Hash hash) { invoke<Void>(0xADB3F206518799E8, ped, hash); }
	NATIVE_DECL void SET_PED_RELATIONSHIP_GROUP_HASH(Ped ped, Hash hash) { invoke<Void>(0xC80A74AC829DDD92, ped, hash); }
	NATIVE_DECL void SET_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2) { invoke<Void>(0xBF25EB89375A37AD, relationship, group1, group2); }
	NATIVE_DECL void CLEAR_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2) { invoke<Void>(0x5E29243FB56FC6D4, relationship, group1, group2); }
	NATIVE_DECL BOOL ADD_RELATIONSHIP_GROUP(const char* name, Hash* groupHash) { return invoke<BOOL>(0xF372BC22FCB88606, name, groupHash); }
	NATIVE_DECL void REMOVE_RELATIONSHIP_GROUP(Hash groupHash) { invoke<Void>(0xB6BA2444AB393DA2, groupHash); }
	NATIVE_DECL BOOL DOES_RELATIONSHIP_GROUP_EXIST(Hash groupHash) { return invoke<BOOL>(0xCC6E3B6BB69501F1, groupHash); }
	NATIVE_DECL int GET_RELATIONSHIP_BETWEEN_PEDS(Ped ped1, Ped ped2) { return invoke<int>(0xEBA5AD3A0EAF7121, ped1, ped2); }
	NATIVE_DECL Hash GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped) { return invoke<Hash>(0x42FDD0F017B1E38E, ped); }
	NATIVE_DECL Hash GET_PED_RELATIONSHIP_GROUP_HASH(Ped ped) { return invoke<Hash>(0x7DBDD04862D95F04, ped); }
	NATIVE_DECL int GET_RELATIONSHIP_BETWEEN_GROUPS(Hash group1, Hash group2) { return invoke<int>(0x9E6B70061662AE5C, group1, group2); }
	NATIVE_DECL void SET_RELATIONSHIP_GROUP_AFFECTS_WANTED_LEVEL(Hash group, BOOL p1) { invoke<Void>(0x5615E0C5EB2BC6E2, group, p1); }
	NATIVE_DECL void TELL_GROUP_PEDS_IN_AREA_TO_ATTACK(Ped ped, float x, float y, float z, float radius, Hash hash) { invoke<Void>(0xAD27D957598E49E9, ped, x, y, z, radius, hash); }
	NATIVE_DECL void SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(Ped ped, BOOL toggle) { invoke<Void>(0x4328652AE5769C71, ped, toggle); }
	NATIVE_DECL void SET_PED_TO_INFORM_RESPECTED_FRIENDS(Ped ped, float radius, int maxFriends) { invoke<Void>(0x112942C6E708F70B, ped, radius, maxFriends); }
	NATIVE_DECL BOOL IS_PED_RESPONDING_TO_EVENT(Ped ped, Any event) { return invoke<BOOL>(0x625B774D75C87068, ped, event); }
	NATIVE_DECL BOOL GET_POS_FROM_FIRED_EVENT(Ped ped, int eventType, Any* outData) { return invoke<BOOL>(0xBA656A3BB01BDEA3, ped, eventType, outData); }
	NATIVE_DECL void SET_PED_FIRING_PATTERN(Ped ped, Hash patternHash) { invoke<Void>(0x9AC577F5A12AD8A9, ped, patternHash); }
	NATIVE_DECL void SET_PED_SHOOT_RATE(Ped ped, int shootRate) { invoke<Void>(0x614DA022990752DC, ped, shootRate); }
	NATIVE_DECL void SET_COMBAT_FLOAT(Ped ped, int combatType, float p2) { invoke<Void>(0xFF41B4B141ED981C, ped, combatType, p2); }
	NATIVE_DECL float GET_COMBAT_FLOAT(Ped ped, int p1) { return invoke<float>(0x52DFF8A10508090A, ped, p1); }
	NATIVE_DECL void GET_GROUP_SIZE(int groupID, Any* p1, int* sizeInMembers) { invoke<Void>(0x8DE69FE35CA09A45, groupID, p1, sizeInMembers); }
	NATIVE_DECL BOOL DOES_GROUP_EXIST(int groupId) { return invoke<BOOL>(0x7C6B0C22F9F40BBE, groupId); }
	NATIVE_DECL int GET_PED_GROUP_INDEX(Ped ped) { return invoke<int>(0xF162E133B4E7A675, ped); }
	NATIVE_DECL BOOL IS_PED_IN_GROUP(Ped ped) { return invoke<BOOL>(0x5891CAC5D4ACFF74, ped); }
	NATIVE_DECL Player GET_PLAYER_PED_IS_FOLLOWING(Ped ped) { return invoke<Player>(0x6A3975DEA89F9A17, ped); }
	NATIVE_DECL void SET_GROUP_FORMATION(int groupId, int formationType) { invoke<Void>(0xCE2F5FC3AF7E8C1E, groupId, formationType); }
	NATIVE_DECL void SET_GROUP_FORMATION_SPACING(int groupId, float x, float y, float z) { invoke<Void>(0x1D9D45004C28C916, groupId, x, y, z); }
	NATIVE_DECL void RESET_GROUP_FORMATION_DEFAULT_SPACING(int groupHandle) { invoke<Void>(0x63DAB4CCB3273205, groupHandle); }
	NATIVE_DECL Vehicle GET_VEHICLE_PED_IS_USING(Ped ped) { return invoke<Vehicle>(0x6094AD011A2EA87D, ped); }
	NATIVE_DECL Vehicle GET_VEHICLE_PED_IS_ENTERING(Ped ped) { return invoke<Vehicle>(0xF92691AED837A5FC, ped); }
	NATIVE_DECL void SET_PED_GRAVITY(Ped ped, BOOL toggle) { invoke<Void>(0x9FF447B6B6AD960A, ped, toggle); }
	NATIVE_DECL BOOL _SET_PED_SURVIVES_BEING_OUT_OF_WATER(Ped ped, BOOL toggle) { return invoke<BOOL>(0x100CD221F572F6E1, ped, toggle); }
	NATIVE_DECL void APPLY_DAMAGE_TO_PED(Ped ped, int damageAmount, BOOL p2, Any p3, Hash weaponType) { invoke<Void>(0x697157CED63F18D4, ped, damageAmount, p2, p3, weaponType); }
	NATIVE_DECL void _GENERATE_PED_DAMAGE_EVENT(Ped ped, float x, float y, float z, Hash weaponType) { invoke<Void>(0x6D1FCD0950EFA3DD, ped, x, y, z, weaponType); }
	NATIVE_DECL int GET_TIME_PED_DAMAGED_BY_WEAPON(Ped ped, Hash weaponHash) { return invoke<int>(0x36B77BB84687C318, ped, weaponHash); }
	NATIVE_DECL void SET_PED_ALLOWED_TO_DUCK(Ped ped, BOOL toggle) { invoke<Void>(0xDA1F1B7BE1A8766F, ped, toggle); }
	NATIVE_DECL void SET_PED_NEVER_LEAVES_GROUP(Ped ped, BOOL toggle) { invoke<Void>(0x3DBFC55D5C9BB447, ped, toggle); }
	NATIVE_DECL int GET_PED_TYPE(Ped ped) { return invoke<int>(0xFF059E1E4C01E63C, ped); }
	NATIVE_DECL void SET_PED_AS_COP(Ped ped, BOOL toggle) { invoke<Void>(0xBB03C38DD3FB7FFD, ped, toggle); }
	NATIVE_DECL void SET_PED_HEALTH_PENDING_LAST_DAMAGE_EVENT_OVERRIDE_FLAG(BOOL toggle) { invoke<Void>(0xB3352E018D6F89DF, toggle); }
	NATIVE_DECL void SET_PED_MAX_HEALTH(Ped ped, int value) { invoke<Void>(0xF5F6378C4F3419D3, ped, value); }
	NATIVE_DECL int GET_PED_MAX_HEALTH(Ped ped) { return invoke<int>(0x4700A416E8324EF3, ped); }
	NATIVE_DECL void SET_PED_MAX_TIME_IN_WATER(Ped ped, float value) { invoke<Void>(0x43C851690662113D, ped, value); }
	NATIVE_DECL void SET_PED_MAX_TIME_UNDERWATER(Ped ped, float value) { invoke<Void>(0x6BA428C528D9E522, ped, value); }
	NATIVE_DECL void SET_CORPSE_RAGDOLL_FRICTION(Ped ped, float p1) { invoke<Void>(0x2735233A786B1BEF, ped, p1); }
	NATIVE_DECL void SET_PED_VEHICLE_FORCED_SEAT_USAGE(Ped ped, Vehicle vehicle, int seatIndex, int flags, Any p4) { invoke<Void>(0x952F06BEECD775CC, ped, vehicle, seatIndex, flags, p4); }
	NATIVE_DECL void CLEAR_ALL_PED_VEHICLE_FORCED_SEAT_USAGE(Ped ped) { invoke<Void>(0xE6CA85E7259CE16B, ped); }
	NATIVE_DECL void SET_PED_CAN_BE_KNOCKED_OFF_BIKE(Any p0, Any p1) { invoke<Void>(0xB282749D5E028163, p0, p1); }
	NATIVE_DECL void SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(Ped ped, int state) { invoke<Void>(0x7A6535691B477C48, ped, state); }
	NATIVE_DECL BOOL CAN_KNOCK_PED_OFF_VEHICLE(Ped ped) { return invoke<BOOL>(0x51AC07A44D4F5B8A, ped); }
	NATIVE_DECL void KNOCK_PED_OFF_VEHICLE(Ped ped) { invoke<Void>(0x45BBCBA77C29A841, ped); }
	NATIVE_DECL void SET_PED_COORDS_NO_GANG(Ped ped, float posX, float posY, float posZ) { invoke<Void>(0x87052FE446E07247, ped, posX, posY, posZ); }
	NATIVE_DECL Ped GET_PED_AS_GROUP_MEMBER(int groupID, int memberNumber) { return invoke<Ped>(0x51455483CF23ED97, groupID, memberNumber); }
	NATIVE_DECL Ped GET_PED_AS_GROUP_LEADER(int groupID) { return invoke<Ped>(0x5CCE68DBD5FE93EC, groupID); }
	NATIVE_DECL void SET_PED_KEEP_TASK(Ped ped, BOOL toggle) { invoke<Void>(0x971D38760FBC02EF, ped, toggle); }
	NATIVE_DECL void SET_PED_ALLOW_MINOR_REACTIONS_AS_MISSION_PED(Ped ped, BOOL toggle) { invoke<Void>(0x49E50BDB8BA4DAB2, ped, toggle); }
	NATIVE_DECL BOOL IS_PED_SWIMMING(Ped ped) { return invoke<BOOL>(0x9DE327631295B4C2, ped); }
	NATIVE_DECL BOOL IS_PED_SWIMMING_UNDER_WATER(Ped ped) { return invoke<BOOL>(0xC024869A53992F34, ped); }
	NATIVE_DECL void SET_PED_COORDS_KEEP_VEHICLE(Ped ped, float posX, float posY, float posZ) { invoke<Void>(0x9AFEFF481A85AB2E, ped, posX, posY, posZ); }
	NATIVE_DECL void SET_PED_DIES_IN_VEHICLE(Ped ped, BOOL toggle) { invoke<Void>(0x2A30922C90C9B42C, ped, toggle); }
	NATIVE_DECL void SET_CREATE_RANDOM_COPS(BOOL toggle) { invoke<Void>(0x102E68B2024D536D, toggle); }
	NATIVE_DECL void SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(BOOL toggle) { invoke<Void>(0x8A4986851C4EF6E7, toggle); }
	NATIVE_DECL void SET_CREATE_RANDOM_COPS_ON_SCENARIOS(BOOL toggle) { invoke<Void>(0x444CB7D7DBE6973D, toggle); }
	NATIVE_DECL BOOL CAN_CREATE_RANDOM_COPS() { return invoke<BOOL>(0x5EE2CAFF7F17770D); }
	NATIVE_DECL void SET_PED_AS_ENEMY(Ped ped, BOOL toggle) { invoke<Void>(0x02A0C9720B854BFA, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_SMASH_GLASS(Ped ped, BOOL p1, BOOL p2) { invoke<Void>(0x1CCE141467FF42A2, ped, p1, p2); }
	NATIVE_DECL BOOL IS_PED_IN_ANY_TRAIN(Ped ped) { return invoke<BOOL>(0x6F972C1AB75A1ED0, ped); }
	NATIVE_DECL BOOL IS_PED_GETTING_INTO_A_VEHICLE(Ped ped) { return invoke<BOOL>(0xBB062B2B5722478E, ped); }
	NATIVE_DECL BOOL IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(Ped ped) { return invoke<BOOL>(0x44D28D5DDFE5F68C, ped); }
	NATIVE_DECL void SET_ENABLE_HANDCUFFS(Ped ped, BOOL toggle) { invoke<Void>(0xDF1AF8B5D56542FA, ped, toggle); }
	NATIVE_DECL void SET_ENABLE_BOUND_ANKLES(Ped ped, BOOL toggle) { invoke<Void>(0xC52E0F855C58FC2E, ped, toggle); }
	NATIVE_DECL void SET_ENABLE_SCUBA(Ped ped, BOOL toggle) { invoke<Void>(0xF99F62004024D506, ped, toggle); }
	NATIVE_DECL void SET_CAN_ATTACK_FRIENDLY(Ped ped, BOOL toggle, BOOL p2) { invoke<Void>(0xB3B1CB349FF9C75D, ped, toggle, p2); }
	NATIVE_DECL int GET_PED_ALERTNESS(Ped ped) { return invoke<int>(0xF6AA118530443FD2, ped); }
	NATIVE_DECL void SET_PED_ALERTNESS(Ped ped, int value) { invoke<Void>(0xDBA71115ED9941A6, ped, value); }
	NATIVE_DECL void SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE(Ped ped, BOOL toggle) { invoke<Void>(0xBC0ED94165A48BC2, ped, toggle); }
	NATIVE_DECL void SET_PED_MOVEMENT_CLIPSET(Ped ped, const char* clipSet, float transitionSpeed) { invoke<Void>(0xAF8A94EDE7712BEF, ped, clipSet, transitionSpeed); }
	NATIVE_DECL void RESET_PED_MOVEMENT_CLIPSET(Ped ped, float p1) { invoke<Void>(0xAA74EC0CB0AAEA2C, ped, p1); }
	NATIVE_DECL void SET_PED_STRAFE_CLIPSET(Ped ped, const char* clipSet) { invoke<Void>(0x29A28F3F8CF6D854, ped, clipSet); }
	NATIVE_DECL void RESET_PED_STRAFE_CLIPSET(Ped ped) { invoke<Void>(0x20510814175EA477, ped); }
	NATIVE_DECL void SET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped, const char* clipSet) { invoke<Void>(0x2622E35B77D3ACA2, ped, clipSet); }
	NATIVE_DECL void RESET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped) { invoke<Void>(0x97B0DB5B4AA74E77, ped); }
	NATIVE_DECL void SET_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped, const char* clipset) { invoke<Void>(0xED34AB6C5CB36520, ped, clipset); }
	NATIVE_DECL void CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped) { invoke<Void>(0x4AFE3690D7E0B5AC, ped); }
	NATIVE_DECL void SET_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE(Ped ped, const char* p1) { invoke<Void>(0x9DBA107B4937F809, ped, p1); }
	NATIVE_DECL void CLEAR_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE(Ped ped) { invoke<Void>(0xC79196DCB36F6121, ped); }
	NATIVE_DECL void CLEAR_PED_FALL_UPPER_BODY_CLIPSET_OVERRIDE(Ped ped) { invoke<Void>(0x80054D7FCC70EEC6, ped); }
	NATIVE_DECL void SET_PED_IN_VEHICLE_CONTEXT(Ped ped, Hash context) { invoke<Void>(0x530071295899A8C6, ped, context); }
	NATIVE_DECL void RESET_PED_IN_VEHICLE_CONTEXT(Ped ped) { invoke<Void>(0x22EF8FF8778030EB, ped); }
	NATIVE_DECL BOOL IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM(Ped ped, const char* animDict, const char* anim) { return invoke<BOOL>(0x6EC47A344923E1ED, ped, animDict, anim); }
	NATIVE_DECL void SET_PED_ALTERNATE_WALK_ANIM(Ped ped, const char* animDict, const char* animName, float p3, BOOL p4) { invoke<Void>(0x6C60394CB4F75E9A, ped, animDict, animName, p3, p4); }
	NATIVE_DECL void CLEAR_PED_ALTERNATE_WALK_ANIM(Ped ped, float p1) { invoke<Void>(0x8844BBFCE30AA9E9, ped, p1); }
	NATIVE_DECL void SET_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, const char* animDictionary, const char* animationName, float p4, BOOL p5) { invoke<Void>(0x90A43CC281FFAB46, ped, stance, animDictionary, animationName, p4, p5); }
	NATIVE_DECL void CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, float p2) { invoke<Void>(0xD8D19675ED5FBDCE, ped, stance, p2); }
	NATIVE_DECL void SET_PED_GESTURE_GROUP(Ped ped, const char* animGroupGesture) { invoke<Void>(0xDDF803377F94AAA8, ped, animGroupGesture); }
	NATIVE_DECL Vector3 GET_ANIM_INITIAL_OFFSET_POSITION(const char* animDict, const char* animName, float x, float y, float z, float xRot, float yRot, float zRot, float p8, int p9) { return invoke<Vector3>(0xBE22B26DD764C040, animDict, animName, x, y, z, xRot, yRot, zRot, p8, p9); }
	NATIVE_DECL Vector3 GET_ANIM_INITIAL_OFFSET_ROTATION(const char* animDict, const char* animName, float x, float y, float z, float xRot, float yRot, float zRot, float p8, int p9) { return invoke<Vector3>(0x4B805E6046EE9E47, animDict, animName, x, y, z, xRot, yRot, zRot, p8, p9); }
	NATIVE_DECL int GET_PED_DRAWABLE_VARIATION(Ped ped, int componentId) { return invoke<int>(0x67F3780DD425D4FC, ped, componentId); }
	NATIVE_DECL int GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Ped ped, int componentId) { return invoke<int>(0x27561561732A7842, ped, componentId); }
	NATIVE_DECL int GET_PED_TEXTURE_VARIATION(Ped ped, int componentId) { return invoke<int>(0x04A355E041E004E6, ped, componentId); }
	NATIVE_DECL int GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(Ped ped, int componentId, int drawableId) { return invoke<int>(0x8F7156A3142A6BAD, ped, componentId, drawableId); }
	NATIVE_DECL int GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(Ped ped, int propId) { return invoke<int>(0x5FAF9754E789FB47, ped, propId); }
	NATIVE_DECL int GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(Ped ped, int propId, int drawableId) { return invoke<int>(0xA6E7F1CEB523E171, ped, propId, drawableId); }
	NATIVE_DECL int GET_PED_PALETTE_VARIATION(Ped ped, int componentId) { return invoke<int>(0xE3DD5F2A84B42281, ped, componentId); }
	NATIVE_DECL BOOL GET_MP_OUTFIT_DATA_FROM_METADATA(Any* p0, Any* p1) { return invoke<BOOL>(0x9E30E91FB03A2CAF, p0, p1); }
	NATIVE_DECL int GET_FM_MALE_SHOP_PED_APPAREL_ITEM_INDEX(int p0) { return invoke<int>(0x1E77FA7A62EE6C4C, p0); }
	NATIVE_DECL int GET_FM_FEMALE_SHOP_PED_APPAREL_ITEM_INDEX(int p0) { return invoke<int>(0xF033419D1B81FAE8, p0); }
	NATIVE_DECL BOOL IS_PED_COMPONENT_VARIATION_VALID(Ped ped, int componentId, int drawableId, int textureId) { return invoke<BOOL>(0xE825F6B6CEA7671D, ped, componentId, drawableId, textureId); }
	NATIVE_DECL void SET_PED_COMPONENT_VARIATION(Ped ped, int componentId, int drawableId, int textureId, int paletteId) { invoke<Void>(0x262B14F48D29DE80, ped, componentId, drawableId, textureId, paletteId); }
	NATIVE_DECL void SET_PED_RANDOM_COMPONENT_VARIATION(Ped ped, int p1) { invoke<Void>(0xC8A9481A01E63C28, ped, p1); }
	NATIVE_DECL void SET_PED_RANDOM_PROPS(Ped ped) { invoke<Void>(0xC44AA05345C992C6, ped); }
	NATIVE_DECL void SET_PED_DEFAULT_COMPONENT_VARIATION(Ped ped) { invoke<Void>(0x45EEE61580806D63, ped); }
	NATIVE_DECL void SET_PED_BLEND_FROM_PARENTS(Ped ped, Any p1, Any p2, float p3, float p4) { invoke<Void>(0x137BBD05230DB22D, ped, p1, p2, p3, p4); }
	NATIVE_DECL void SET_PED_HEAD_BLEND_DATA(Ped ped, int shapeFirstID, int shapeSecondID, int shapeThirdID, int skinFirstID, int skinSecondID, int skinThirdID, float shapeMix, float skinMix, float thirdMix, BOOL isParent) { invoke<Void>(0x9414E18B9434C2FE, ped, shapeFirstID, shapeSecondID, shapeThirdID, skinFirstID, skinSecondID, skinThirdID, shapeMix, skinMix, thirdMix, isParent); }
	NATIVE_DECL BOOL GET_PED_HEAD_BLEND_DATA(Ped ped, Any* headBlendData) { return invoke<BOOL>(0x2746BD9D88C5C5D0, ped, headBlendData); }
	NATIVE_DECL void UPDATE_PED_HEAD_BLEND_DATA(Ped ped, float shapeMix, float skinMix, float thirdMix) { invoke<Void>(0x723538F61C647C5A, ped, shapeMix, skinMix, thirdMix); }
	NATIVE_DECL void SET_HEAD_BLEND_EYE_COLOR(Ped ped, int index) { invoke<Void>(0x50B56988B170AFDF, ped, index); }
	NATIVE_DECL int GET_HEAD_BLEND_EYE_COLOR(Ped ped) { return invoke<int>(0x76BBA2CEE66D47E9, ped); }
	NATIVE_DECL void SET_PED_HEAD_OVERLAY(Ped ped, int overlayID, int index, float opacity) { invoke<Void>(0x48F44967FA05CC1E, ped, overlayID, index, opacity); }
	NATIVE_DECL int GET_PED_HEAD_OVERLAY(Ped ped, int overlayID) { return invoke<int>(0xA60EF3B6461A4D43, ped, overlayID); }
	NATIVE_DECL int GET_PED_HEAD_OVERLAY_NUM(int overlayID) { return invoke<int>(0xCF1CE768BB43480E, overlayID); }
	NATIVE_DECL void SET_PED_HEAD_OVERLAY_TINT(Ped ped, int overlayID, int colorType, int colorID, int secondColorID) { invoke<Void>(0x497BF74A7B9CB952, ped, overlayID, colorType, colorID, secondColorID); }
	NATIVE_DECL void SET_PED_HAIR_TINT(Ped ped, int colorID, int highlightColorID) { invoke<Void>(0x4CFFC65454C93A49, ped, colorID, highlightColorID); }
	NATIVE_DECL int GET_NUM_PED_HAIR_TINTS() { return invoke<int>(0xE5C0CF872C2AD150); }
	NATIVE_DECL int GET_NUM_PED_MAKEUP_TINTS() { return invoke<int>(0xD1F7CA1535D22818); }
	NATIVE_DECL void GET_PED_HAIR_TINT_COLOR(int hairColorIndex, int* outR, int* outG, int* outB) { invoke<Void>(0x4852FC386E2E1BB5, hairColorIndex, outR, outG, outB); }
	NATIVE_DECL void GET_PED_MAKEUP_TINT_COLOR(int makeupColorIndex, int* outR, int* outG, int* outB) { invoke<Void>(0x013E5CFC38CD5387, makeupColorIndex, outR, outG, outB); }
	NATIVE_DECL BOOL IS_PED_HAIR_TINT_FOR_CREATOR(int colorId) { return invoke<BOOL>(0xED6D8E27A43B8CDE, colorId); }
	NATIVE_DECL int GET_DEFAULT_SECONDARY_TINT_FOR_CREATOR(int colorId) { return invoke<int>(0xEA9960D07DADCF10, colorId); }
	NATIVE_DECL BOOL IS_PED_LIPSTICK_TINT_FOR_CREATOR(int colorId) { return invoke<BOOL>(0x3E802F11FBE27674, colorId); }
	NATIVE_DECL BOOL IS_PED_BLUSH_TINT_FOR_CREATOR(int colorId) { return invoke<BOOL>(0xF41B5D290C99A3D6, colorId); }
	NATIVE_DECL BOOL IS_PED_HAIR_TINT_FOR_BARBER(int colorID) { return invoke<BOOL>(0xE0D36E5D9E99CC21, colorID); }
	NATIVE_DECL int GET_DEFAULT_SECONDARY_TINT_FOR_BARBER(int colorID) { return invoke<int>(0xAAA6A3698A69E048, colorID); }
	NATIVE_DECL BOOL IS_PED_LIPSTICK_TINT_FOR_BARBER(int colorID) { return invoke<BOOL>(0x0525A2C2562F3CD4, colorID); }
	NATIVE_DECL BOOL IS_PED_BLUSH_TINT_FOR_BARBER(int colorID) { return invoke<BOOL>(0x604E810189EE3A59, colorID); }
	NATIVE_DECL BOOL IS_PED_BLUSH_FACEPAINT_TINT_FOR_BARBER(int colorId) { return invoke<BOOL>(0x09E7ECA981D9B210, colorId); }
	NATIVE_DECL int GET_TINT_INDEX_FOR_LAST_GEN_HAIR_TEXTURE(Hash modelHash, int drawableId, int textureId) { return invoke<int>(0xC56FBF2F228E1DAC, modelHash, drawableId, textureId); }
	NATIVE_DECL void SET_PED_MICRO_MORPH(Ped ped, int index, float scale) { invoke<Void>(0x71A5C1DBA060049E, ped, index, scale); }
	NATIVE_DECL BOOL HAS_PED_HEAD_BLEND_FINISHED(Ped ped) { return invoke<BOOL>(0x654CD0A825161131, ped); }
	NATIVE_DECL void FINALIZE_HEAD_BLEND(Ped ped) { invoke<Void>(0x4668D80430D6C299, ped); }
	NATIVE_DECL void SET_HEAD_BLEND_PALETTE_COLOR(Ped ped, int r, int g, int b, int id) { invoke<Void>(0xCC9682B8951C5229, ped, r, g, b, id); }
	NATIVE_DECL void DISABLE_HEAD_BLEND_PALETTE_COLOR(Ped ped) { invoke<Void>(0xA21C118553BBDF02, ped); }
	NATIVE_DECL int GET_PED_HEAD_BLEND_FIRST_INDEX(int type) { return invoke<int>(0x68D353AB88B97E0C, type); }
	NATIVE_DECL int GET_PED_HEAD_BLEND_NUM_HEADS(int type) { return invoke<int>(0x5EF37013A6539C9D, type); }
	NATIVE_DECL int SET_PED_PRELOAD_VARIATION_DATA(Ped ped, int slot, int drawableId, int textureId) { return invoke<int>(0x39D55A620FCB6A3A, ped, slot, drawableId, textureId); }
	NATIVE_DECL BOOL HAS_PED_PRELOAD_VARIATION_DATA_FINISHED(Ped ped) { return invoke<BOOL>(0x66680A92700F43DF, ped); }
	NATIVE_DECL void RELEASE_PED_PRELOAD_VARIATION_DATA(Ped ped) { invoke<Void>(0x5AAB586FFEC0FD96, ped); }
	NATIVE_DECL int SET_PED_PRELOAD_PROP_DATA(Ped ped, int componentId, int drawableId, int TextureId) { return invoke<int>(0x2B16A3BFF1FBCE49, ped, componentId, drawableId, TextureId); }
	NATIVE_DECL BOOL HAS_PED_PRELOAD_PROP_DATA_FINISHED(Ped ped) { return invoke<BOOL>(0x784002A632822099, ped); }
	NATIVE_DECL void RELEASE_PED_PRELOAD_PROP_DATA(Ped ped) { invoke<Void>(0xF79F9DEF0AADE61A, ped); }
	NATIVE_DECL int GET_PED_PROP_INDEX(Ped ped, int componentId, Any p2) { return invoke<int>(0x898CC20EA75BACD8, ped, componentId, p2); }
	NATIVE_DECL void SET_PED_PROP_INDEX(Ped ped, int componentId, int drawableId, int TextureId, BOOL attach, Any p5) { invoke<Void>(0x93376B65A266EB5F, ped, componentId, drawableId, TextureId, attach, p5); }
	NATIVE_DECL void KNOCK_OFF_PED_PROP(Ped ped, BOOL p1, BOOL p2, BOOL p3, BOOL p4) { invoke<Void>(0x6FD7816A36615F48, ped, p1, p2, p3, p4); }
	NATIVE_DECL void CLEAR_PED_PROP(Ped ped, int propId, Any p2) { invoke<Void>(0x0943E5B8E078E76E, ped, propId, p2); }
	NATIVE_DECL void CLEAR_ALL_PED_PROPS(Ped ped, Any p1) { invoke<Void>(0xCD8A7537A9B52F06, ped, p1); }
	NATIVE_DECL void DROP_AMBIENT_PROP(Ped ped) { invoke<Void>(0xAFF4710E2A0A6C12, ped); }
	NATIVE_DECL int GET_PED_PROP_TEXTURE_INDEX(Ped ped, int componentId) { return invoke<int>(0xE131A28626F81AB2, ped, componentId); }
	NATIVE_DECL void CLEAR_PED_PARACHUTE_PACK_VARIATION(Ped ped) { invoke<Void>(0x1280804F7CFD2D6C, ped); }
	NATIVE_DECL void SET_PED_SCUBA_GEAR_VARIATION(Ped ped) { invoke<Void>(0x36C6984C3ED0C911, ped); }
	NATIVE_DECL void CLEAR_PED_SCUBA_GEAR_VARIATION(Ped ped) { invoke<Void>(0xB50EB4CCB29704AC, ped); }
	NATIVE_DECL BOOL IS_USING_PED_SCUBA_GEAR_VARIATION(Any p0) { return invoke<BOOL>(0xFEC9A3B1820F3331, p0); }
	NATIVE_DECL void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, BOOL toggle) { invoke<Void>(0x9F8AA94D6D97DBF4, ped, toggle); }
	NATIVE_DECL void SET_PED_BOUNDS_ORIENTATION(Ped ped, float p1, float p2, float x, float y, float z) { invoke<Void>(0x4F5F651ACCC9C4CF, ped, p1, p2, x, y, z); }
	NATIVE_DECL void REGISTER_TARGET(Ped ped, Ped target) { invoke<Void>(0x2F25D9AEFA34FBA2, ped, target); }
	NATIVE_DECL void REGISTER_HATED_TARGETS_AROUND_PED(Ped ped, float radius) { invoke<Void>(0x9222F300BF8354FE, ped, radius); }
	NATIVE_DECL Ped GET_RANDOM_PED_AT_COORD(float x, float y, float z, float xRadius, float yRadius, float zRadius, int pedType) { return invoke<Ped>(0x876046A8E3A4B71C, x, y, z, xRadius, yRadius, zRadius, pedType); }
	NATIVE_DECL BOOL GET_CLOSEST_PED(float x, float y, float z, float radius, BOOL p4, BOOL p5, Ped* outPed, BOOL p7, BOOL p8, int pedType) { return invoke<BOOL>(0xC33AB876A77F8164, x, y, z, radius, p4, p5, outPed, p7, p8, pedType); }
	NATIVE_DECL void SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(BOOL value) { invoke<Void>(0x14F19A8782C8071E, value); }
	NATIVE_DECL BOOL GET_CAN_PED_BE_GRABBED_BY_SCRIPT(Ped ped, BOOL p1, BOOL p2, BOOL p3, BOOL p4, BOOL p5, BOOL p6, BOOL p7, Any p8) { return invoke<BOOL>(0x03EA03AF85A85CB7, ped, p1, p2, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL void SET_DRIVER_RACING_MODIFIER(Ped driver, float modifier) { invoke<Void>(0xDED5AF5A0EA4B297, driver, modifier); }
	NATIVE_DECL void SET_DRIVER_ABILITY(Ped driver, float ability) { invoke<Void>(0xB195FFA8042FC5C3, driver, ability); }
	NATIVE_DECL void SET_DRIVER_AGGRESSIVENESS(Ped driver, float aggressiveness) { invoke<Void>(0xA731F608CA104E3C, driver, aggressiveness); }
	NATIVE_DECL BOOL CAN_PED_RAGDOLL(Ped ped) { return invoke<BOOL>(0x128F79EDCECE4FD5, ped); }
	NATIVE_DECL BOOL SET_PED_TO_RAGDOLL(Ped ped, int time1, int time2, int ragdollType, BOOL p4, BOOL p5, BOOL p6) { return invoke<BOOL>(0xAE99FB955581844A, ped, time1, time2, ragdollType, p4, p5, p6); }
	NATIVE_DECL BOOL SET_PED_TO_RAGDOLL_WITH_FALL(Ped ped, int time, int p2, int ragdollType, float x, float y, float z, float velocity, float p8, float p9, float p10, float p11, float p12, float p13) { return invoke<BOOL>(0xD76632D99E4966C8, ped, time, p2, ragdollType, x, y, z, velocity, p8, p9, p10, p11, p12, p13); }
	NATIVE_DECL void SET_PED_RAGDOLL_ON_COLLISION(Ped ped, BOOL toggle) { invoke<Void>(0xF0A4F1BBF4FA7497, ped, toggle); }
	NATIVE_DECL BOOL IS_PED_RAGDOLL(Ped ped) { return invoke<BOOL>(0x47E4E977581C5B55, ped); }
	NATIVE_DECL BOOL IS_PED_RUNNING_RAGDOLL_TASK(Ped ped) { return invoke<BOOL>(0xE3B6097CC25AA69E, ped); }
	NATIVE_DECL void SET_PED_RAGDOLL_FORCE_FALL(Ped ped) { invoke<Void>(0x01F6594B923B9251, ped); }
	NATIVE_DECL void RESET_PED_RAGDOLL_TIMER(Ped ped) { invoke<Void>(0x9FA4664CF62E47E8, ped); }
	NATIVE_DECL void SET_PED_CAN_RAGDOLL(Ped ped, BOOL toggle) { invoke<Void>(0xB128377056A54E2A, ped, toggle); }
	NATIVE_DECL BOOL IS_PED_RUNNING_MELEE_TASK(Ped ped) { return invoke<BOOL>(0xD1871251F3B5ACD7, ped); }
	NATIVE_DECL BOOL IS_PED_RUNNING_MOBILE_PHONE_TASK(Ped ped) { return invoke<BOOL>(0x2AFE52F782F25775, ped); }
	NATIVE_DECL BOOL IS_MOBILE_PHONE_TO_PED_EAR(Ped ped) { return invoke<BOOL>(0xA3F3564A5B3646C0, ped); }
	NATIVE_DECL void SET_RAGDOLL_BLOCKING_FLAGS(Ped ped, int blockingFlag) { invoke<Void>(0x26695EC767728D84, ped, blockingFlag); }
	NATIVE_DECL void CLEAR_RAGDOLL_BLOCKING_FLAGS(Ped ped, int blockingFlag) { invoke<Void>(0xD86D101FCFD00A4B, ped, blockingFlag); }
	NATIVE_DECL void SET_PED_ANGLED_DEFENSIVE_AREA(Ped ped, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8, BOOL p9) { invoke<Void>(0xC7F76DF27A5045A1, ped, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	NATIVE_DECL void SET_PED_SPHERE_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float radius, BOOL p5, BOOL p6) { invoke<Void>(0x9D3151A373974804, ped, x, y, z, radius, p5, p6); }
	NATIVE_DECL void SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED(Ped ped, Ped target, float xOffset, float yOffset, float zOffset, float radius, BOOL p6) { invoke<Void>(0xF9B8F91AAD3B953E, ped, target, xOffset, yOffset, zOffset, radius, p6); }
	NATIVE_DECL void SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_VEHICLE(Ped ped, Vehicle target, float xOffset, float yOffset, float zOffset, float radius, BOOL p6) { invoke<Void>(0xE4723DB6E736CCFF, ped, target, xOffset, yOffset, zOffset, radius, p6); }
	NATIVE_DECL void SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(Ped ped, Ped attachPed, float p2, float p3, float p4, float p5, float p6, float p7, float p8, BOOL p9, BOOL p10) { invoke<Void>(0x4EF47FE21698A8B6, ped, attachPed, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	NATIVE_DECL void SET_PED_DEFENSIVE_AREA_DIRECTION(Ped ped, float p1, float p2, float p3, BOOL p4) { invoke<Void>(0x413C6C763A4AFFAD, ped, p1, p2, p3, p4); }
	NATIVE_DECL void REMOVE_PED_DEFENSIVE_AREA(Ped ped, BOOL toggle) { invoke<Void>(0x74D4E028107450A9, ped, toggle); }
	NATIVE_DECL Vector3 GET_PED_DEFENSIVE_AREA_POSITION(Ped ped, BOOL p1) { return invoke<Vector3>(0x3C06B8786DD94CD1, ped, p1); }
	NATIVE_DECL BOOL IS_PED_DEFENSIVE_AREA_ACTIVE(Ped ped, BOOL p1) { return invoke<BOOL>(0xBA63D9FE45412247, ped, p1); }
	NATIVE_DECL void SET_PED_PREFERRED_COVER_SET(Ped ped, Any itemSet) { invoke<Void>(0x8421EB4DA7E391B9, ped, itemSet); }
	NATIVE_DECL void REMOVE_PED_PREFERRED_COVER_SET(Ped ped) { invoke<Void>(0xFDDB234CF74073D9, ped); }
	NATIVE_DECL void REVIVE_INJURED_PED(Ped ped) { invoke<Void>(0x8D8ACD8388CD99CE, ped); }
	NATIVE_DECL void RESURRECT_PED(Ped ped) { invoke<Void>(0x71BC8E838B9C6035, ped); }
	NATIVE_DECL void SET_PED_NAME_DEBUG(Ped ped, const char* name) { invoke<Void>(0x98EFA132A4117BE1, ped, name); }
	NATIVE_DECL Vector3 GET_PED_EXTRACTED_DISPLACEMENT(Ped ped, BOOL worldSpace) { return invoke<Vector3>(0xE0AF41401ADF87E3, ped, worldSpace); }
	NATIVE_DECL void SET_PED_DIES_WHEN_INJURED(Ped ped, BOOL toggle) { invoke<Void>(0x5BA7919BED300023, ped, toggle); }
	NATIVE_DECL void SET_PED_ENABLE_WEAPON_BLOCKING(Ped ped, BOOL toggle) { invoke<Void>(0x97A790315D3831FD, ped, toggle); }
	NATIVE_DECL void SPECIAL_FUNCTION_DO_NOT_USE(Ped ped, BOOL p1) { invoke<Void>(0xF9ACF4A08098EA25, ped, p1); }
	NATIVE_DECL void RESET_PED_VISIBLE_DAMAGE(Ped ped) { invoke<Void>(0x3AC1F7B898F30C05, ped); }
	NATIVE_DECL void APPLY_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, Any p1, float p2, float p3, Any p4) { invoke<Void>(0x816F6981C60BF53B, ped, p1, p2, p3, p4); }
	NATIVE_DECL void APPLY_PED_BLOOD(Ped ped, int boneIndex, float xRot, float yRot, float zRot, const char* woundType) { invoke<Void>(0x83F7E01C7B769A26, ped, boneIndex, xRot, yRot, zRot, woundType); }
	NATIVE_DECL void APPLY_PED_BLOOD_BY_ZONE(Ped ped, int p1, float p2, float p3, const char* p4) { invoke<Void>(0x3311E47B91EDCBBC, ped, p1, p2, p3, p4); }
	NATIVE_DECL void APPLY_PED_BLOOD_SPECIFIC(Ped ped, int p1, float p2, float p3, float p4, float p5, int p6, float p7, const char* p8) { invoke<Void>(0xEF0D582CBF2D9B0F, ped, p1, p2, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL void APPLY_PED_DAMAGE_DECAL(Ped ped, int damageZone, float xOffset, float yOffset, float heading, float scale, float alpha, int variation, BOOL fadeIn, const char* decalName) { invoke<Void>(0x397C38AA7B4A5F83, ped, damageZone, xOffset, yOffset, heading, scale, alpha, variation, fadeIn, decalName); }
	NATIVE_DECL void APPLY_PED_DAMAGE_PACK(Ped ped, const char* damagePack, float damage, float mult) { invoke<Void>(0x46DF918788CB093F, ped, damagePack, damage, mult); }
	NATIVE_DECL void CLEAR_PED_BLOOD_DAMAGE(Ped ped) { invoke<Void>(0x8FE22675A5A45817, ped); }
	NATIVE_DECL void CLEAR_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, int p1) { invoke<Void>(0x56E3B78C5408D9F4, ped, p1); }
	NATIVE_DECL void HIDE_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, Any p1, BOOL p2) { invoke<Void>(0x62AB793144DE75DC, ped, p1, p2); }
	NATIVE_DECL void CLEAR_PED_DAMAGE_DECAL_BY_ZONE(Ped ped, int p1, const char* p2) { invoke<Void>(0x523C79AEEFCC4A2A, ped, p1, p2); }
	NATIVE_DECL int GET_PED_DECORATIONS_STATE(Ped ped) { return invoke<int>(0x71EAB450D86954A1, ped); }
	NATIVE_DECL void MARK_PED_DECORATIONS_AS_CLONED_FROM_LOCAL_PLAYER(Ped ped, BOOL p1) { invoke<Void>(0x2B694AFCF64E6994, ped, p1); }
	NATIVE_DECL void CLEAR_PED_WETNESS(Ped ped) { invoke<Void>(0x9C720776DAA43E7E, ped); }
	NATIVE_DECL void SET_PED_WETNESS_HEIGHT(Ped ped, float height) { invoke<Void>(0x44CB6447D2571AA0, ped, height); }
	NATIVE_DECL void SET_PED_WETNESS_ENABLED_THIS_FRAME(Ped ped) { invoke<Void>(0xB5485E4907B53019, ped); }
	NATIVE_DECL void SET_PED_WETNESS(Ped ped, float wetLevel) { invoke<Void>(0xAC0BB4D87777CAE2, ped, wetLevel); }
	NATIVE_DECL void CLEAR_PED_ENV_DIRT(Ped ped) { invoke<Void>(0x6585D955A68452A5, ped); }
	NATIVE_DECL void SET_PED_SWEAT(Ped ped, float sweat) { invoke<Void>(0x27B0405F59637D1F, ped, sweat); }
	NATIVE_DECL void ADD_PED_DECORATION_FROM_HASHES(Ped ped, Hash collection, Hash overlay) { invoke<Void>(0x5F5D1665E352A839, ped, collection, overlay); }
	NATIVE_DECL void ADD_PED_DECORATION_FROM_HASHES_IN_CORONA(Ped ped, Hash collection, Hash overlay) { invoke<Void>(0x5619BFA07CFD7833, ped, collection, overlay); }
	NATIVE_DECL int GET_PED_DECORATION_ZONE_FROM_HASHES(Hash collection, Hash overlay) { return invoke<int>(0x9FD452BFBE7A7A8B, collection, overlay); }
	NATIVE_DECL void CLEAR_PED_DECORATIONS(Ped ped) { invoke<Void>(0x0E5173C163976E38, ped); }
	NATIVE_DECL void CLEAR_PED_DECORATIONS_LEAVE_SCARS(Ped ped) { invoke<Void>(0xE3B27E70CEAB9F0C, ped); }
	NATIVE_DECL BOOL WAS_PED_SKELETON_UPDATED(Ped ped) { return invoke<BOOL>(0x11B499C1E0FF8559, ped); }
	NATIVE_DECL Vector3 GET_PED_BONE_COORDS(Ped ped, int boneId, float offsetX, float offsetY, float offsetZ) { return invoke<Vector3>(0x17C07FC640E86B4E, ped, boneId, offsetX, offsetY, offsetZ); }
	NATIVE_DECL void CREATE_NM_MESSAGE(BOOL startImmediately, int messageId) { invoke<Void>(0x418EF2A1BCE56685, startImmediately, messageId); }
	NATIVE_DECL void GIVE_PED_NM_MESSAGE(Ped ped) { invoke<Void>(0xB158DFCCC56E5C5B, ped); }
	NATIVE_DECL int ADD_SCENARIO_BLOCKING_AREA(float x1, float y1, float z1, float x2, float y2, float z2, BOOL p6, BOOL p7, BOOL p8, BOOL p9, Any p10) { return invoke<int>(0x1B5C85C612E5256E, x1, y1, z1, x2, y2, z2, p6, p7, p8, p9, p10); }
	NATIVE_DECL void REMOVE_SCENARIO_BLOCKING_AREAS() { invoke<Void>(0xD37401D78A929A49); }
	NATIVE_DECL void REMOVE_SCENARIO_BLOCKING_AREA(Any p0, BOOL p1) { invoke<Void>(0x31D16B74C6E29D66, p0, p1); }
	NATIVE_DECL void SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(float x, float y, float z, float range, int p4) { invoke<Void>(0x28157D43CF600981, x, y, z, range, p4); }
	NATIVE_DECL BOOL DOES_SCENARIO_BLOCKING_AREA_EXISTS(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<BOOL>(0x8A24B067D175A7BD, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL BOOL IS_PED_USING_SCENARIO(Ped ped, const char* scenario) { return invoke<BOOL>(0x1BF094736DD62C2E, ped, scenario); }
	NATIVE_DECL BOOL IS_PED_USING_ANY_SCENARIO(Ped ped) { return invoke<BOOL>(0x57AB4A3080F85143, ped); }
	NATIVE_DECL BOOL SET_PED_PANIC_EXIT_SCENARIO(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xFE07FF6495D52E2A, p0, p1, p2, p3); }
	NATIVE_DECL void TOGGLE_SCENARIO_PED_COWER_IN_PLACE(Ped ped, BOOL toggle) { invoke<Void>(0x9A77DFD295E29B09, ped, toggle); }
	NATIVE_DECL BOOL TRIGGER_PED_SCENARIO_PANICEXITTOFLEE(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x25361A96E0F7E419, p0, p1, p2, p3); }
	NATIVE_DECL BOOL SET_PED_SHOULD_PLAY_DIRECTED_NORMAL_SCENARIO_EXIT(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xEC6935EBE0847B90, p0, p1, p2, p3); }
	NATIVE_DECL void SET_PED_SHOULD_PLAY_NORMAL_SCENARIO_EXIT(Ped ped) { invoke<Void>(0xA3A9299C4F2ADB98, ped); }
	NATIVE_DECL void SET_PED_SHOULD_PLAY_IMMEDIATE_SCENARIO_EXIT(Ped ped) { invoke<Void>(0xF1C03A5352243A30, ped); }
	NATIVE_DECL BOOL SET_PED_SHOULD_PLAY_FLEE_SCENARIO_EXIT(Ped ped, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xEEED8FAFEC331A70, ped, p1, p2, p3); }
	NATIVE_DECL void SET_PED_SHOULD_IGNORE_SCENARIO_EXIT_COLLISION_CHECKS(Ped ped, BOOL p1) { invoke<Void>(0x425AECF167663F48, ped, p1); }
	NATIVE_DECL void SET_PED_SHOULD_IGNORE_SCENARIO_NAV_CHECKS(Any p0, BOOL p1) { invoke<Void>(0x5B6010B3CBC29095, p0, p1); }
	NATIVE_DECL void SET_PED_SHOULD_PROBE_FOR_SCENARIO_EXITS_IN_ONE_FRAME(Any p0, BOOL p1) { invoke<Void>(0xCEDA60A74219D064, p0, p1); }
	NATIVE_DECL BOOL IS_PED_GESTURING(Any p0) { return invoke<BOOL>(0xC30BDAEE47256C13, p0); }
	NATIVE_DECL void RESET_FACIAL_IDLE_ANIM(Ped ped) { invoke<Void>(0x007FDE5A7897E426, ped); }
	NATIVE_DECL void PLAY_FACIAL_ANIM(Ped ped, const char* animName, const char* animDict) { invoke<Void>(0xE1E65CA8AC9C00ED, ped, animName, animDict); }
	NATIVE_DECL void SET_FACIAL_CLIPSET(Ped ped, const char* animDict) { invoke<Void>(0x5687C7F05B39E401, ped, animDict); }
	NATIVE_DECL void SET_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped, const char* animName, const char* animDict) { invoke<Void>(0xFFC24B988B938B38, ped, animName, animDict); }
	NATIVE_DECL void CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped) { invoke<Void>(0x726256CC1EEB182F, ped); }
	NATIVE_DECL void SET_PED_CAN_PLAY_GESTURE_ANIMS(Ped ped, BOOL toggle) { invoke<Void>(0xBAF20C5432058024, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_PLAY_VISEME_ANIMS(Ped ped, BOOL toggle, BOOL p2) { invoke<Void>(0xF833DDBA3B104D43, ped, toggle, p2); }
	NATIVE_DECL void SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS(Ped ped, BOOL p1) { invoke<Void>(0x33A60D8BDD6E508C, ped, p1); }
	NATIVE_DECL void SET_PED_CAN_PLAY_AMBIENT_ANIMS(Ped ped, BOOL toggle) { invoke<Void>(0x6373D1349925A70E, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(Ped ped, BOOL toggle) { invoke<Void>(0x0EB0585D15254740, ped, toggle); }
	NATIVE_DECL void TRIGGER_IDLE_ANIMATION_ON_PED(Ped ped) { invoke<Void>(0xC2EE020F5FB4DB53, ped); }
	NATIVE_DECL void SET_PED_CAN_ARM_IK(Ped ped, BOOL toggle) { invoke<Void>(0x6C3B4D6D13B4C841, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_BODY_RECOIL_IK(Ped ped, BOOL toggle) { invoke<Void>(0xE84EC1735FB39663, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_HEAD_IK(Ped ped, BOOL toggle) { invoke<Void>(0xC11C18092C5530DC, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_LEG_IK(Ped ped, BOOL toggle) { invoke<Void>(0x73518ECE2485412B, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_TORSO_IK(Ped ped, BOOL toggle) { invoke<Void>(0xF2B7106D37947CE0, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_TORSO_REACT_IK(Ped ped, BOOL p1) { invoke<Void>(0xF5846EDB26A98A24, ped, p1); }
	NATIVE_DECL void SET_PED_CAN_TORSO_VEHICLE_IK(Ped ped, BOOL p1) { invoke<Void>(0x6647C5F6F5792496, ped, p1); }
	NATIVE_DECL void SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(Ped ped, BOOL toggle) { invoke<Void>(0xEC4686EC06434678, ped, toggle); }
	NATIVE_DECL BOOL IS_PED_HEADTRACKING_PED(Ped ped1, Ped ped2) { return invoke<BOOL>(0x5CD3CB88A7F8850D, ped1, ped2); }
	NATIVE_DECL BOOL IS_PED_HEADTRACKING_ENTITY(Ped ped, Entity entity) { return invoke<BOOL>(0x813A0A7C9D2E831F, ped, entity); }
	NATIVE_DECL void SET_PED_PRIMARY_LOOKAT(Ped ped, Ped lookAt) { invoke<Void>(0xCD17B554996A8D9E, ped, lookAt); }
	NATIVE_DECL void SET_PED_CLOTH_PIN_FRAMES(Any p0, Any p1) { invoke<Void>(0x78C4E9961DB3EB5B, p0, p1); }
	NATIVE_DECL void SET_PED_CLOTH_PACKAGE_INDEX(Any p0, Any p1) { invoke<Void>(0x82A3D6D9CC2CB8E3, p0, p1); }
	NATIVE_DECL void SET_PED_CLOTH_PRONE(Any p0, BOOL p1) { invoke<Void>(0xA660FAF550EB37E5, p0, p1); }
	NATIVE_DECL void SET_PED_CONFIG_FLAG(Ped ped, int flagId, BOOL value) { invoke<Void>(0x1913FE4CBF41C463, ped, flagId, value); }
	NATIVE_DECL void SET_PED_RESET_FLAG(Ped ped, int flagId, BOOL doReset) { invoke<Void>(0xC1E8A365BF3B29F2, ped, flagId, doReset); }
	NATIVE_DECL BOOL GET_PED_CONFIG_FLAG(Ped ped, int flagId, BOOL p2) { return invoke<BOOL>(0x7EE53118C892B513, ped, flagId, p2); }
	NATIVE_DECL BOOL GET_PED_RESET_FLAG(Ped ped, int flagId) { return invoke<BOOL>(0xAF9E59B1B1FBF2A0, ped, flagId); }
	NATIVE_DECL void SET_PED_GROUP_MEMBER_PASSENGER_INDEX(Ped ped, int index) { invoke<Void>(0x0BDDB8D9EC6BCF3C, ped, index); }
	NATIVE_DECL void SET_PED_CAN_EVASIVE_DIVE(Ped ped, BOOL toggle) { invoke<Void>(0x6B7A646C242A7059, ped, toggle); }
	NATIVE_DECL BOOL IS_PED_EVASIVE_DIVING(Ped ped, Entity* evadingEntity) { return invoke<BOOL>(0x414641C26E105898, ped, evadingEntity); }
	NATIVE_DECL void SET_PED_SHOOTS_AT_COORD(Ped ped, float x, float y, float z, BOOL toggle) { invoke<Void>(0x96A05E4FB321B1BA, ped, x, y, z, toggle); }
	NATIVE_DECL void SET_PED_MODEL_IS_SUPPRESSED(Hash modelHash, BOOL toggle) { invoke<Void>(0xE163A4BCE4DE6F11, modelHash, toggle); }
	NATIVE_DECL void STOP_ANY_PED_MODEL_BEING_SUPPRESSED() { invoke<Void>(0xB47BD05FA66B40CF); }
	NATIVE_DECL void SET_PED_CAN_BE_TARGETED_WHEN_INJURED(Ped ped, BOOL toggle) { invoke<Void>(0x638C03B0F9878F57, ped, toggle); }
	NATIVE_DECL void _BLOCK_PED_FROM_WRITHING_WHEN_INJURED(Ped ped, BOOL toggle) { invoke<Void>(0x5CBD1684E56BF99D, ped, toggle); }
	NATIVE_DECL void SET_PED_GENERATES_DEAD_BODY_EVENTS(Ped ped, BOOL toggle) { invoke<Void>(0x7FB17BA2E7DECA5B, ped, toggle); }
	NATIVE_DECL void BLOCK_PED_FROM_GENERATING_DEAD_BODY_EVENTS_WHEN_DEAD(Ped ped, BOOL toggle) { invoke<Void>(0xE43A13C9E4CCCBCF, ped, toggle); }
	NATIVE_DECL void SET_PED_WILL_ONLY_ATTACK_WANTED_PLAYER(Any p0, Any p1) { invoke<Void>(0x3E9679C1DFCF422C, p0, p1); }
	NATIVE_DECL void SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Ped ped, BOOL toggle) { invoke<Void>(0xDF993EE5E90ABA25, ped, toggle); }
	NATIVE_DECL void GIVE_PED_HELMET(Ped ped, BOOL cannotRemove, int helmetFlag, int textureIndex) { invoke<Void>(0x54C7C4A94367717E, ped, cannotRemove, helmetFlag, textureIndex); }
	NATIVE_DECL void REMOVE_PED_HELMET(Ped ped, BOOL instantly) { invoke<Void>(0xA7B2458D0AD6DED8, ped, instantly); }
	NATIVE_DECL BOOL IS_PED_TAKING_OFF_HELMET(Ped ped) { return invoke<BOOL>(0x14590DDBEDB1EC85, ped); }
	NATIVE_DECL void SET_PED_HELMET(Ped ped, BOOL canWearHelmet) { invoke<Void>(0x560A43136EB58105, ped, canWearHelmet); }
	NATIVE_DECL void SET_PED_HELMET_FLAG(Ped ped, int helmetFlag) { invoke<Void>(0xC0E78D5C2CE3EB25, ped, helmetFlag); }
	NATIVE_DECL void SET_PED_HELMET_PROP_INDEX(Ped ped, int propIndex, BOOL p2) { invoke<Void>(0x26D83693ED99291C, ped, propIndex, p2); }
	NATIVE_DECL void SET_PED_HELMET_VISOR_PROP_INDICES(Ped ped, BOOL p1, int p2, int p3) { invoke<Void>(0x3F7325574E41B44D, ped, p1, p2, p3); }
	NATIVE_DECL BOOL IS_PED_HELMET_VISOR_UP(Ped ped) { return invoke<BOOL>(0xB9496CE47546DB2C, ped); }
	NATIVE_DECL void SET_PED_HELMET_TEXTURE_INDEX(Ped ped, int textureIndex) { invoke<Void>(0xF1550C4BD22582E2, ped, textureIndex); }
	NATIVE_DECL BOOL IS_PED_WEARING_HELMET(Ped ped) { return invoke<BOOL>(0xF33BDFE19B309B19, ped); }
	NATIVE_DECL void CLEAR_PED_STORED_HAT_PROP(Ped ped) { invoke<Void>(0x687C0B594907D2E8, ped); }
	NATIVE_DECL int GET_PED_HELMET_STORED_HAT_PROP_INDEX(Ped ped) { return invoke<int>(0x451294E859ECC018, ped); }
	NATIVE_DECL int GET_PED_HELMET_STORED_HAT_TEX_INDEX(Ped ped) { return invoke<int>(0x9D728C1E12BF5518, ped); }
	NATIVE_DECL BOOL IS_CURRENT_HEAD_PROP_A_HELMET(Any p0) { return invoke<BOOL>(0xF2385935BFFD4D92, p0); }
	NATIVE_DECL void SET_PED_TO_LOAD_COVER(Ped ped, BOOL toggle) { invoke<Void>(0x332B562EEDA62399, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_COWER_IN_COVER(Ped ped, BOOL toggle) { invoke<Void>(0xCB7553CDCEF4A735, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_PEEK_IN_COVER(Ped ped, BOOL toggle) { invoke<Void>(0xC514825C507E3736, ped, toggle); }
	NATIVE_DECL void SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(Ped ped, BOOL toggle) { invoke<Void>(0x94D94BF1A75AED3D, ped, toggle); }
	NATIVE_DECL void SET_PED_LEG_IK_MODE(Ped ped, int mode) { invoke<Void>(0xC396F5B86FF9FEBD, ped, mode); }
	NATIVE_DECL void SET_PED_MOTION_BLUR(Ped ped, BOOL toggle) { invoke<Void>(0x0A986918B102B448, ped, toggle); }
	NATIVE_DECL void SET_PED_CAN_SWITCH_WEAPON(Ped ped, BOOL toggle) { invoke<Void>(0xED7F7EFE9FABF340, ped, toggle); }
	NATIVE_DECL void SET_PED_DIES_INSTANTLY_IN_WATER(Ped ped, BOOL toggle) { invoke<Void>(0xEEB64139BA29A7CF, ped, toggle); }
	NATIVE_DECL void SET_LADDER_CLIMB_INPUT_STATE(Ped ped, int p1) { invoke<Void>(0x1A330D297AAC6BC1, ped, p1); }
	NATIVE_DECL void STOP_PED_WEAPON_FIRING_WHEN_DROPPED(Ped ped) { invoke<Void>(0xC158D28142A34608, ped); }
	NATIVE_DECL void SET_SCRIPTED_ANIM_SEAT_OFFSET(Ped ped, float p1) { invoke<Void>(0x5917BBA32D06C230, ped, p1); }
	NATIVE_DECL void SET_PED_COMBAT_MOVEMENT(Ped ped, int combatMovement) { invoke<Void>(0x4D9CA1009AFBD057, ped, combatMovement); }
	NATIVE_DECL int GET_PED_COMBAT_MOVEMENT(Ped ped) { return invoke<int>(0xDEA92412FCAEB3F5, ped); }
	NATIVE_DECL void SET_PED_COMBAT_ABILITY(Ped ped, int abilityLevel) { invoke<Void>(0xC7622C0D36B2FDA8, ped, abilityLevel); }
	NATIVE_DECL void SET_PED_COMBAT_RANGE(Ped ped, int combatRange) { invoke<Void>(0x3C606747B23E497B, ped, combatRange); }
	NATIVE_DECL int GET_PED_COMBAT_RANGE(Ped ped) { return invoke<int>(0xF9D9F7F2DB8E2FA0, ped); }
	NATIVE_DECL void SET_PED_COMBAT_ATTRIBUTES(Ped ped, int attributeId, BOOL enabled) { invoke<Void>(0x9F7794730795E019, ped, attributeId, enabled); }
	NATIVE_DECL void SET_PED_TARGET_LOSS_RESPONSE(Ped ped, int responseType) { invoke<Void>(0x0703B9079823DA4A, ped, responseType); }
	NATIVE_DECL BOOL IS_PED_PERFORMING_MELEE_ACTION(Ped ped) { return invoke<BOOL>(0xDCCA191DF9980FD7, ped); }
	NATIVE_DECL BOOL IS_PED_PERFORMING_STEALTH_KILL(Ped ped) { return invoke<BOOL>(0xFD4CCDBCC59941B7, ped); }
	NATIVE_DECL BOOL IS_PED_PERFORMING_A_COUNTER_ATTACK(Ped ped) { return invoke<BOOL>(0xEBD0EDBA5BE957CF, ped); }
	NATIVE_DECL BOOL IS_PED_BEING_STEALTH_KILLED(Ped ped) { return invoke<BOOL>(0x863B23EFDE9C5DF2, ped); }
	NATIVE_DECL Ped GET_MELEE_TARGET_FOR_PED(Ped ped) { return invoke<Ped>(0x18A3E9EE1297FD39, ped); }
	NATIVE_DECL BOOL WAS_PED_KILLED_BY_STEALTH(Ped ped) { return invoke<BOOL>(0xF9800AA1A771B000, ped); }
	NATIVE_DECL BOOL WAS_PED_KILLED_BY_TAKEDOWN(Ped ped) { return invoke<BOOL>(0x7F08E26039C7347C, ped); }
	NATIVE_DECL BOOL WAS_PED_KNOCKED_OUT(Ped ped) { return invoke<BOOL>(0x61767F73EACEED21, ped); }
	NATIVE_DECL void SET_PED_FLEE_ATTRIBUTES(Ped ped, int attributeFlags, BOOL enable) { invoke<Void>(0x70A2D1137C8ED7C9, ped, attributeFlags, enable); }
	NATIVE_DECL void SET_PED_COWER_HASH(Ped ped, const char* p1) { invoke<Void>(0xA549131166868ED3, ped, p1); }
	NATIVE_DECL void SET_PED_STEERS_AROUND_DEAD_BODIES(Ped ped, BOOL toggle) { invoke<Void>(0x2016C603D6B8987C, ped, toggle); }
	NATIVE_DECL void SET_PED_STEERS_AROUND_PEDS(Ped ped, BOOL toggle) { invoke<Void>(0x46F2193B3AD1D891, ped, toggle); }
	NATIVE_DECL void SET_PED_STEERS_AROUND_OBJECTS(Ped ped, BOOL toggle) { invoke<Void>(0x1509C089ADC208BF, ped, toggle); }
	NATIVE_DECL void SET_PED_STEERS_AROUND_VEHICLES(Ped ped, BOOL toggle) { invoke<Void>(0xEB6FB9D48DDE23EC, ped, toggle); }
	NATIVE_DECL void SET_PED_IS_AVOIDED_BY_OTHERS(Any p0, BOOL p1) { invoke<Void>(0xA9B61A329BFDCBEA, p0, p1); }
	NATIVE_DECL void SET_PED_INCREASED_AVOIDANCE_RADIUS(Ped ped) { invoke<Void>(0x570389D1C3DE3C6B, ped); }
	NATIVE_DECL void SET_PED_BLOCKS_PATHING_WHEN_DEAD(Ped ped, BOOL toggle) { invoke<Void>(0x576594E8D64375E2, ped, toggle); }
	NATIVE_DECL void SET_PED_NO_TIME_DELAY_BEFORE_SHOT(Any p0) { invoke<Void>(0xA52D5247A4227E14, p0); }
	NATIVE_DECL BOOL IS_ANY_PED_NEAR_POINT(float x, float y, float z, float radius) { return invoke<BOOL>(0x083961498679DC9F, x, y, z, radius); }
	NATIVE_DECL void FORCE_PED_AI_AND_ANIMATION_UPDATE(Ped ped, BOOL p1, BOOL p2) { invoke<Void>(0x2208438012482A1A, ped, p1, p2); }
	NATIVE_DECL BOOL IS_PED_HEADING_TOWARDS_POSITION(Ped ped, float x, float y, float z, float p4) { return invoke<BOOL>(0xFCF37A457CB96DC0, ped, x, y, z, p4); }
	NATIVE_DECL void REQUEST_PED_VISIBILITY_TRACKING(Ped ped) { invoke<Void>(0x7D7A2E43E74E2EB8, ped); }
	NATIVE_DECL void REQUEST_PED_VEHICLE_VISIBILITY_TRACKING(Ped ped, BOOL p1) { invoke<Void>(0x2BC338A7B21F4608, ped, p1); }
	NATIVE_DECL void REQUEST_PED_RESTRICTED_VEHICLE_VISIBILITY_TRACKING(Ped ped, BOOL p1) { invoke<Void>(0xCD018C591F94CB43, ped, p1); }
	NATIVE_DECL void REQUEST_PED_USE_SMALL_BBOX_VISIBILITY_TRACKING(Ped ped, BOOL p1) { invoke<Void>(0x75BA1CB3B7D40CAF, ped, p1); }
	NATIVE_DECL BOOL IS_TRACKED_PED_VISIBLE(Ped ped) { return invoke<BOOL>(0x91C8E617F64188AC, ped); }
	NATIVE_DECL int GET_TRACKED_PED_PIXELCOUNT(Ped ped) { return invoke<int>(0x511F1A683387C7E2, ped); }
	NATIVE_DECL BOOL IS_PED_TRACKED(Ped ped) { return invoke<BOOL>(0x4C5E1F087CD10BB7, ped); }
	NATIVE_DECL BOOL HAS_PED_RECEIVED_EVENT(Ped ped, int eventId) { return invoke<BOOL>(0x8507BCB710FA6DC0, ped, eventId); }
	NATIVE_DECL BOOL CAN_PED_SEE_HATED_PED(Ped ped1, Ped ped2) { return invoke<BOOL>(0x6CD5A433374D4CFB, ped1, ped2); }
	NATIVE_DECL BOOL CAN_PED_SHUFFLE_TO_OR_FROM_TURRET_SEAT(Ped ped, int* p1) { return invoke<BOOL>(0x9C6A6C19B6C0C496, ped, p1); }
	NATIVE_DECL BOOL CAN_PED_SHUFFLE_TO_OR_FROM_EXTRA_SEAT(Ped ped, int* p1) { return invoke<BOOL>(0x2DFC81C9B9608549, ped, p1); }
	NATIVE_DECL int GET_PED_BONE_INDEX(Ped ped, int boneId) { return invoke<int>(0x3F428D08BE5AAE31, ped, boneId); }
	NATIVE_DECL int GET_PED_RAGDOLL_BONE_INDEX(Ped ped, int bone) { return invoke<int>(0x2057EF813397A772, ped, bone); }
	NATIVE_DECL void SET_PED_ENVEFF_SCALE(Ped ped, float value) { invoke<Void>(0xBF29516833893561, ped, value); }
	NATIVE_DECL float GET_PED_ENVEFF_SCALE(Ped ped) { return invoke<float>(0x9C14D30395A51A3C, ped); }
	NATIVE_DECL void SET_ENABLE_PED_ENVEFF_SCALE(Ped ped, BOOL toggle) { invoke<Void>(0xD2C5AA0C0E8D0F1E, ped, toggle); }
	NATIVE_DECL void SET_PED_ENVEFF_CPV_ADD(Ped ped, float p1) { invoke<Void>(0x110F526AB784111F, ped, p1); }
	NATIVE_DECL void SET_PED_ENVEFF_COLOR_MODULATOR(Ped ped, int p1, int p2, int p3) { invoke<Void>(0xD69411AA0CEBF9E9, ped, p1, p2, p3); }
	NATIVE_DECL void SET_PED_EMISSIVE_SCALE(Ped ped, float intensity) { invoke<Void>(0x4E90D746056E273D, ped, intensity); }
	NATIVE_DECL float GET_PED_EMISSIVE_SCALE(Ped ped) { return invoke<float>(0x1461B28A06717D68, ped); }
	NATIVE_DECL BOOL IS_PED_SHADER_READY(Ped ped) { return invoke<BOOL>(0x81AA517FBBA05D39, ped); }
	NATIVE_DECL void SET_PED_ENABLE_CREW_EMBLEM(Ped ped, BOOL toggle) { invoke<Void>(0xE906EC930F5FE7C8, ped, toggle); }
	NATIVE_DECL void REQUEST_RAGDOLL_BOUNDS_UPDATE(Any p0, Any p1) { invoke<Void>(0x1216E0BFA72CC703, p0, p1); }
	NATIVE_DECL void SET_PED_AO_BLOB_RENDERING(Ped ped, BOOL toggle) { invoke<Void>(0x2B5AA717A181FB4C, ped, toggle); }
	NATIVE_DECL BOOL IS_PED_SHELTERED(Ped ped) { return invoke<BOOL>(0xB8B52E498014F5B0, ped); }
	NATIVE_DECL int CREATE_SYNCHRONIZED_SCENE(float x, float y, float z, float roll, float pitch, float yaw, int p6) { return invoke<int>(0x8C18E0F9080ADD73, x, y, z, roll, pitch, yaw, p6); }
	NATIVE_DECL int CREATE_SYNCHRONIZED_SCENE_AT_MAP_OBJECT(float x, float y, float z, float radius, Hash object) { return invoke<int>(0x62EC273D00187DCA, x, y, z, radius, object); }
	NATIVE_DECL BOOL IS_SYNCHRONIZED_SCENE_RUNNING(int sceneId) { return invoke<BOOL>(0x25D39B935A038A26, sceneId); }
	NATIVE_DECL void SET_SYNCHRONIZED_SCENE_ORIGIN(int sceneID, float x, float y, float z, float roll, float pitch, float yaw, BOOL p7) { invoke<Void>(0x6ACF6B7225801CD7, sceneID, x, y, z, roll, pitch, yaw, p7); }
	NATIVE_DECL void SET_SYNCHRONIZED_SCENE_PHASE(int sceneID, float phase) { invoke<Void>(0x734292F4F0ABF6D0, sceneID, phase); }
	NATIVE_DECL float GET_SYNCHRONIZED_SCENE_PHASE(int sceneID) { return invoke<float>(0xE4A310B1D7FA73CC, sceneID); }
	NATIVE_DECL void SET_SYNCHRONIZED_SCENE_RATE(int sceneID, float rate) { invoke<Void>(0xB6C49F8A5E295A5D, sceneID, rate); }
	NATIVE_DECL float GET_SYNCHRONIZED_SCENE_RATE(int sceneID) { return invoke<float>(0xD80932D577274D40, sceneID); }
	NATIVE_DECL void SET_SYNCHRONIZED_SCENE_LOOPED(int sceneID, BOOL toggle) { invoke<Void>(0xD9A897A4C6C2974F, sceneID, toggle); }
	NATIVE_DECL BOOL IS_SYNCHRONIZED_SCENE_LOOPED(int sceneID) { return invoke<BOOL>(0x62522002E0C391BA, sceneID); }
	NATIVE_DECL void SET_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME(int sceneID, BOOL toggle) { invoke<Void>(0x394B9CD12435C981, sceneID, toggle); }
	NATIVE_DECL BOOL IS_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME(int sceneID) { return invoke<BOOL>(0x7F2F4F13AC5257EF, sceneID); }
	NATIVE_DECL void ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(int sceneID, Entity entity, int boneIndex) { invoke<Void>(0x272E4723B56A3B96, sceneID, entity, boneIndex); }
	NATIVE_DECL void DETACH_SYNCHRONIZED_SCENE(int sceneID) { invoke<Void>(0x6D38F1F04CBB37EA, sceneID); }
	NATIVE_DECL void TAKE_OWNERSHIP_OF_SYNCHRONIZED_SCENE(int scene) { invoke<Void>(0xCD9CC7E200A52A6F, scene); }
	NATIVE_DECL BOOL FORCE_PED_MOTION_STATE(Ped ped, Hash motionStateHash, BOOL p2, int p3, BOOL p4) { return invoke<BOOL>(0xF28965D04F570DCA, ped, motionStateHash, p2, p3, p4); }
	NATIVE_DECL BOOL GET_PED_CURRENT_MOVE_BLEND_RATIO(Ped ped, float* speedX, float* speedY) { return invoke<BOOL>(0xF60165E1D2C5370B, ped, speedX, speedY); }
	NATIVE_DECL void SET_PED_MAX_MOVE_BLEND_RATIO(Ped ped, float value) { invoke<Void>(0x433083750C5E064A, ped, value); }
	NATIVE_DECL void SET_PED_MIN_MOVE_BLEND_RATIO(Ped ped, float value) { invoke<Void>(0x01A898D26E2333DD, ped, value); }
	NATIVE_DECL void SET_PED_MOVE_RATE_OVERRIDE(Ped ped, float value) { invoke<Void>(0x085BF80FA50A39D1, ped, value); }
	NATIVE_DECL void SET_PED_MOVE_RATE_IN_WATER_OVERRIDE(Ped ped, float p1) { invoke<Void>(0x0B3E35AC043707D9, ped, p1); }
	NATIVE_DECL BOOL PED_HAS_SEXINESS_FLAG_SET(Ped ped, int sexinessFlag) { return invoke<BOOL>(0x46B05BCAE43856B0, ped, sexinessFlag); }
	NATIVE_DECL int GET_PED_NEARBY_VEHICLES(Ped ped, Any* sizeAndVehs) { return invoke<int>(0xCFF869CBFA210D82, ped, sizeAndVehs); }
	NATIVE_DECL int GET_PED_NEARBY_PEDS(Ped ped, Any* sizeAndPeds, int ignore) { return invoke<int>(0x23F8F5FC7E8C4A6B, ped, sizeAndPeds, ignore); }
	NATIVE_DECL BOOL HAVE_ALL_STREAMING_REQUESTS_COMPLETED(Ped ped) { return invoke<BOOL>(0x7350823473013C02, ped); }
	NATIVE_DECL BOOL IS_PED_USING_ACTION_MODE(Ped ped) { return invoke<BOOL>(0x00E73468D085F745, ped); }
	NATIVE_DECL void SET_PED_USING_ACTION_MODE(Ped ped, BOOL p1, int p2, const char* action) { invoke<Void>(0xD75ACCF5E0FB5367, ped, p1, p2, action); }
	NATIVE_DECL void SET_MOVEMENT_MODE_OVERRIDE(Ped ped, const char* name) { invoke<Void>(0x781DE8FA214E87D2, ped, name); }
	NATIVE_DECL void SET_PED_CAPSULE(Ped ped, float value) { invoke<Void>(0x364DF566EC833DE2, ped, value); }
	NATIVE_DECL int REGISTER_PEDHEADSHOT(Ped ped) { return invoke<int>(0x4462658788425076, ped); }
	NATIVE_DECL int REGISTER_PEDHEADSHOT_HIRES(Ped ped) { return invoke<int>(0xBA8805A1108A2515, ped); }
	NATIVE_DECL int REGISTER_PEDHEADSHOT_TRANSPARENT(Ped ped) { return invoke<int>(0x953563CE563143AF, ped); }
	NATIVE_DECL void UNREGISTER_PEDHEADSHOT(int id) { invoke<Void>(0x96B1361D9B24C2FF, id); }
	NATIVE_DECL BOOL IS_PEDHEADSHOT_VALID(int id) { return invoke<BOOL>(0xA0A9668F158129A2, id); }
	NATIVE_DECL BOOL IS_PEDHEADSHOT_READY(int id) { return invoke<BOOL>(0x7085228842B13A67, id); }
	NATIVE_DECL const char* GET_PEDHEADSHOT_TXD_STRING(int id) { return invoke<const char*>(0xDB4EACD4AD0A5D6B, id); }
	NATIVE_DECL BOOL REQUEST_PEDHEADSHOT_IMG_UPLOAD(int id) { return invoke<BOOL>(0xF0DAEF2F545BEE25, id); }
	NATIVE_DECL void RELEASE_PEDHEADSHOT_IMG_UPLOAD(int id) { invoke<Void>(0x5D517B27CF6ECD04, id); }
	NATIVE_DECL BOOL IS_PEDHEADSHOT_IMG_UPLOAD_AVAILABLE() { return invoke<BOOL>(0xEBB376779A760AA8); }
	NATIVE_DECL BOOL HAS_PEDHEADSHOT_IMG_UPLOAD_FAILED() { return invoke<BOOL>(0x876928DDDFCCC9CD); }
	NATIVE_DECL BOOL HAS_PEDHEADSHOT_IMG_UPLOAD_SUCCEEDED() { return invoke<BOOL>(0xE8A169E666CBC541); }
	NATIVE_DECL void SET_PED_HEATSCALE_OVERRIDE(Ped ped, float heatScale) { invoke<Void>(0xC1F6EBF9A3D55538, ped, heatScale); }
	NATIVE_DECL void DISABLE_PED_HEATSCALE_OVERRIDE(Ped ped) { invoke<Void>(0x600048C60D5C2C51, ped); }
	NATIVE_DECL void SPAWNPOINTS_START_SEARCH(float p0, float p1, float p2, float p3, float p4, int interiorFlags, float scale, int duration) { invoke<Void>(0x2DF9038C90AD5264, p0, p1, p2, p3, p4, interiorFlags, scale, duration); }
	NATIVE_DECL void SPAWNPOINTS_START_SEARCH_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, int interiorFlags, float scale, int duration) { invoke<Void>(0xB2AFF10216DEFA2F, x1, y1, z1, x2, y2, z2, width, interiorFlags, scale, duration); }
	NATIVE_DECL void SPAWNPOINTS_CANCEL_SEARCH() { invoke<Void>(0xFEE4A5459472A9F8); }
	NATIVE_DECL BOOL SPAWNPOINTS_IS_SEARCH_ACTIVE() { return invoke<BOOL>(0x3C67506996001F5E); }
	NATIVE_DECL BOOL SPAWNPOINTS_IS_SEARCH_COMPLETE() { return invoke<BOOL>(0xA586FBEB32A53DBB); }
	NATIVE_DECL BOOL SPAWNPOINTS_IS_SEARCH_FAILED() { return invoke<BOOL>(0xF445DE8DA80A1792); }
	NATIVE_DECL int SPAWNPOINTS_GET_NUM_SEARCH_RESULTS() { return invoke<int>(0xA635C11B8C44AFC2); }
	NATIVE_DECL void SPAWNPOINTS_GET_SEARCH_RESULT(int randomInt, float* x, float* y, float* z) { invoke<Void>(0x280C7E3AC7F56E90, randomInt, x, y, z); }
	NATIVE_DECL void SPAWNPOINTS_GET_SEARCH_RESULT_FLAGS(int p0, int* p1) { invoke<Void>(0xB782F8238512BAD5, p0, p1); }
	NATIVE_DECL void SET_IK_TARGET(Ped ped, int ikIndex, Entity entityLookAt, int boneLookAt, float offsetX, float offsetY, float offsetZ, Any p7, int blendInDuration, int blendOutDuration) { invoke<Void>(0xC32779C16FCEECD9, ped, ikIndex, entityLookAt, boneLookAt, offsetX, offsetY, offsetZ, p7, blendInDuration, blendOutDuration); }
	NATIVE_DECL void FORCE_INSTANT_LEG_IK_SETUP(Ped ped) { invoke<Void>(0xED3C76ADFA6D07C4, ped); }
	NATIVE_DECL void REQUEST_ACTION_MODE_ASSET(const char* asset) { invoke<Void>(0x290E2780BB7AA598, asset); }
	NATIVE_DECL BOOL HAS_ACTION_MODE_ASSET_LOADED(const char* asset) { return invoke<BOOL>(0xE4B5F4BF2CB24E65, asset); }
	NATIVE_DECL void REMOVE_ACTION_MODE_ASSET(const char* asset) { invoke<Void>(0x13E940F88470FA51, asset); }
	NATIVE_DECL void REQUEST_STEALTH_MODE_ASSET(const char* asset) { invoke<Void>(0x2A0A62FCDEE16D4F, asset); }
	NATIVE_DECL BOOL HAS_STEALTH_MODE_ASSET_LOADED(const char* asset) { return invoke<BOOL>(0xE977FC5B08AF3441, asset); }
	NATIVE_DECL void REMOVE_STEALTH_MODE_ASSET(const char* asset) { invoke<Void>(0x9219857D21F0E842, asset); }
	NATIVE_DECL void SET_PED_LOD_MULTIPLIER(Ped ped, float multiplier) { invoke<Void>(0xDC2C5C242AAC342B, ped, multiplier); }
	NATIVE_DECL void SET_PED_CAN_LOSE_PROPS_ON_DAMAGE(Ped ped, BOOL toggle, int p2) { invoke<Void>(0xE861D0B05C7662B8, ped, toggle, p2); }
	NATIVE_DECL void SET_FORCE_FOOTSTEP_UPDATE(Ped ped, BOOL toggle) { invoke<Void>(0x129466ED55140F8D, ped, toggle); }
	NATIVE_DECL void SET_FORCE_STEP_TYPE(Ped ped, BOOL p1, int type, int p3) { invoke<Void>(0xCB968B53FC7F916D, ped, p1, type, p3); }
	NATIVE_DECL BOOL IS_ANY_HOSTILE_PED_NEAR_POINT(Ped ped, float x, float y, float z, float radius) { return invoke<BOOL>(0x68772DB2B2526F9F, ped, x, y, z, radius); }
	NATIVE_DECL void SET_PED_CAN_PLAY_IN_CAR_IDLES(Ped ped, BOOL toggle) { invoke<Void>(0x820E9892A77E97CD, ped, toggle); }
	NATIVE_DECL BOOL IS_TARGET_PED_IN_PERCEPTION_AREA(Ped ped, Ped targetPed, float p2, float p3, float p4, float p5) { return invoke<BOOL>(0x06087579E7AA85A9, ped, targetPed, p2, p3, p4, p5); }
	NATIVE_DECL void SET_POP_CONTROL_SPHERE_THIS_FRAME(float x, float y, float z, float min, float max) { invoke<Void>(0xD8C3BE3EE94CAF2D, x, y, z, min, max); }
	NATIVE_DECL void FORCE_ZERO_MASS_IN_COLLISIONS(Ped ped) { invoke<Void>(0xD33DAA36272177C4, ped); }
	NATIVE_DECL void SET_DISABLE_HIGH_FALL_DEATH(Ped ped, BOOL toggle) { invoke<Void>(0x711794453CFD692B, ped, toggle); }
	NATIVE_DECL void SET_PED_PHONE_PALETTE_IDX(Any p0, Any p1) { invoke<Void>(0x83A169EABCDB10A2, p0, p1); }
	NATIVE_DECL void SET_PED_STEER_BIAS(Ped ped, float value) { invoke<Void>(0x288DF530C92DAD6F, ped, value); }
	NATIVE_DECL BOOL IS_PED_SWITCHING_WEAPON(Ped Ped) { return invoke<BOOL>(0x3795688A307E1EB6, Ped); }
	NATIVE_DECL void SET_PED_TREATED_AS_FRIENDLY(Any p0, Any p1, Any p2) { invoke<Void>(0x0F62619393661D6E, p0, p1, p2); }
	NATIVE_DECL void SET_DISABLE_PED_MAP_COLLISION(Ped ped) { invoke<Void>(0xDFE68C4B787E1BFB, ped); }
	NATIVE_DECL void ENABLE_MP_LIGHT(Ped ped, BOOL toggle) { invoke<Void>(0xEE2476B9EE4A094F, ped, toggle); }
	NATIVE_DECL BOOL GET_MP_LIGHT_ENABLED(Ped ped) { return invoke<BOOL>(0x88274C11CF0D866D, ped); }
	NATIVE_DECL void CLEAR_COVER_POINT_FOR_PED(Ped ped) { invoke<Void>(0x637822DC2AFEEBF8, ped); }
	NATIVE_DECL void SET_ALLOW_STUNT_JUMP_CAMERA(Ped ped, BOOL toggle) { invoke<Void>(0xFAB944D4D481ACCB, ped, toggle); }
}

namespace PHYSICS
{
	NATIVE_DECL int ADD_ROPE(float x, float y, float z, float rotX, float rotY, float rotZ, float length, int ropeType, float maxLength, float minLength, float windingSpeed, BOOL p11, BOOL p12, BOOL rigid, float p14, BOOL breakWhenShot, Any* unkPtr) { return invoke<int>(0xE832D760399EB220, x, y, z, rotX, rotY, rotZ, length, ropeType, maxLength, minLength, windingSpeed, p11, p12, rigid, p14, breakWhenShot, unkPtr); }
	NATIVE_DECL void DELETE_ROPE(int* ropeId) { invoke<Void>(0x52B4829281364649, ropeId); }
	NATIVE_DECL void DELETE_CHILD_ROPE(int ropeId) { invoke<Void>(0xAA5D6B1888E4DB20, ropeId); }
	NATIVE_DECL BOOL DOES_ROPE_EXIST(int* ropeId) { return invoke<BOOL>(0xFD5448BE3111ED96, ropeId); }
	NATIVE_DECL void ROPE_DRAW_ENABLED(int* ropeId, BOOL p1) { invoke<Void>(0xA1AE736541B0FCA3, ropeId, p1); }
	NATIVE_DECL void ROPE_DRAW_SHADOW_ENABLED(int* ropeId, BOOL toggle) { invoke<Void>(0xF159A63806BB5BA8, ropeId, toggle); }
	NATIVE_DECL void LOAD_ROPE_DATA(int ropeId, const char* rope_preset) { invoke<Void>(0xCBB203C04D1ABD27, ropeId, rope_preset); }
	NATIVE_DECL void PIN_ROPE_VERTEX(int ropeId, int vertex, float x, float y, float z) { invoke<Void>(0x2B320CF14146B69A, ropeId, vertex, x, y, z); }
	NATIVE_DECL void UNPIN_ROPE_VERTEX(int ropeId, int vertex) { invoke<Void>(0x4B5AE2EEE4A8F180, ropeId, vertex); }
	NATIVE_DECL int GET_ROPE_VERTEX_COUNT(int ropeId) { return invoke<int>(0x3655F544CD30F0B5, ropeId); }
	NATIVE_DECL void ATTACH_ENTITIES_TO_ROPE(int ropeId, Entity ent1, Entity ent2, float ent1_x, float ent1_y, float ent1_z, float ent2_x, float ent2_y, float ent2_z, float length, BOOL p10, BOOL p11, Any* p12, Any* p13) { invoke<Void>(0x3D95EC8B6D940AC3, ropeId, ent1, ent2, ent1_x, ent1_y, ent1_z, ent2_x, ent2_y, ent2_z, length, p10, p11, p12, p13); }
	NATIVE_DECL void ATTACH_ROPE_TO_ENTITY(int ropeId, Entity entity, float x, float y, float z, BOOL p5) { invoke<Void>(0x4B490A6832559A65, ropeId, entity, x, y, z, p5); }
	NATIVE_DECL void DETACH_ROPE_FROM_ENTITY(int ropeId, Entity entity) { invoke<Void>(0xBCF3026912A8647D, ropeId, entity); }
	NATIVE_DECL void ROPE_SET_UPDATE_PINVERTS(int ropeId) { invoke<Void>(0xC8D667EE52114ABA, ropeId); }
	NATIVE_DECL void ROPE_SET_UPDATE_ORDER(int ropeId, Any p1) { invoke<Void>(0xDC57A637A20006ED, ropeId, p1); }
	NATIVE_DECL void ROPE_SET_SMOOTH_REELIN(int ropeId, BOOL p1) { invoke<Void>(0x36CCB9BE67B970FD, ropeId, p1); }
	NATIVE_DECL BOOL IS_ROPE_ATTACHED_AT_BOTH_ENDS(int* ropeId) { return invoke<BOOL>(0x84DE3B5FB3E666F0, ropeId); }
	NATIVE_DECL Vector3 GET_ROPE_LAST_VERTEX_COORD(int ropeId) { return invoke<Vector3>(0x21BB0FBD3E217C2D, ropeId); }
	NATIVE_DECL Vector3 GET_ROPE_VERTEX_COORD(int ropeId, int vertex) { return invoke<Vector3>(0xEA61CA8E80F09E4D, ropeId, vertex); }
	NATIVE_DECL void START_ROPE_WINDING(int ropeId) { invoke<Void>(0x1461C72C889E343E, ropeId); }
	NATIVE_DECL void STOP_ROPE_WINDING(int ropeId) { invoke<Void>(0xCB2D4AB84A19AA7C, ropeId); }
	NATIVE_DECL void START_ROPE_UNWINDING_FRONT(int ropeId) { invoke<Void>(0x538D1179EC1AA9A9, ropeId); }
	NATIVE_DECL void STOP_ROPE_UNWINDING_FRONT(int ropeId) { invoke<Void>(0xFFF3A50779EFBBB3, ropeId); }
	NATIVE_DECL void ROPE_CONVERT_TO_SIMPLE(int ropeId) { invoke<Void>(0x5389D48EFA2F079A, ropeId); }
	NATIVE_DECL void ROPE_LOAD_TEXTURES() { invoke<Void>(0x9B9039DBF2D258C1); }
	NATIVE_DECL BOOL ROPE_ARE_TEXTURES_LOADED() { return invoke<BOOL>(0xF2D0E6A75CC05597); }
	NATIVE_DECL void ROPE_UNLOAD_TEXTURES() { invoke<Void>(0x6CE36C35C1AC8163); }
	NATIVE_DECL BOOL DOES_SCRIPT_OWN_ROPE(int ropeId) { return invoke<BOOL>(0x271C9D3ACA5D6409, ropeId); }
	NATIVE_DECL void ROPE_ATTACH_VIRTUAL_BOUND_GEOM(int ropeId, int p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13) { invoke<Void>(0xBC0CE682D4D05650, ropeId, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
	NATIVE_DECL void ROPE_CHANGE_SCRIPT_OWNER(Any p0, BOOL p1, BOOL p2) { invoke<Void>(0xB1B6216CA2E7B55E, p0, p1, p2); }
	NATIVE_DECL void ROPE_SET_REFFRAMEVELOCITY_COLLIDERORDER(int ropeId, int p1) { invoke<Void>(0xB743F735C03D7810, ropeId, p1); }
	NATIVE_DECL float ROPE_GET_DISTANCE_BETWEEN_ENDS(int ropeId) { return invoke<float>(0x73040398DFF9A4A6, ropeId); }
	NATIVE_DECL void ROPE_FORCE_LENGTH(int ropeId, float length) { invoke<Void>(0xD009F759A723DB1B, ropeId, length); }
	NATIVE_DECL void ROPE_RESET_LENGTH(int ropeId, float length) { invoke<Void>(0xC16DE94D9BEA14A0, ropeId, length); }
	NATIVE_DECL void APPLY_IMPULSE_TO_CLOTH(float posX, float posY, float posZ, float vecX, float vecY, float vecZ, float impulse) { invoke<Void>(0xE37F721824571784, posX, posY, posZ, vecX, vecY, vecZ, impulse); }
	NATIVE_DECL void SET_DAMPING(Entity entity, int vertex, float value) { invoke<Void>(0xEEA3B200A6FEB65B, entity, vertex, value); }
	NATIVE_DECL Vector3 GET_DAMPING(Entity entity, int type) { return invoke<Vector3>(0x8C520A929415BCD2, entity, type); }
	NATIVE_DECL void ACTIVATE_PHYSICS(Entity entity) { invoke<Void>(0x710311ADF0E20730, entity); }
	NATIVE_DECL void SET_CGOFFSET(Entity entity, float x, float y, float z) { invoke<Void>(0xD8FA3908D7B86904, entity, x, y, z); }
	NATIVE_DECL Vector3 GET_CGOFFSET(Entity entity) { return invoke<Vector3>(0x8214A4B5A7A33612, entity); }
	NATIVE_DECL void SET_CG_AT_BOUNDCENTER(Entity entity) { invoke<Void>(0xBE520D9761FF811F, entity); }
	NATIVE_DECL void BREAK_ENTITY_GLASS(Entity entity, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, Any p9, BOOL p10) { invoke<Void>(0x2E648D16F6E308F3, entity, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	NATIVE_DECL BOOL GET_IS_ENTITY_A_FRAG(Object object) { return invoke<BOOL>(0x0C112765300C7E1E, object); }
	NATIVE_DECL void SET_DISABLE_BREAKING(Object object, BOOL toggle) { invoke<Void>(0x5CEC1A84620E7D5B, object, toggle); }
	NATIVE_DECL void RESET_DISABLE_BREAKING(Object object) { invoke<Void>(0xCC6E963682533882, object); }
	NATIVE_DECL void SET_DISABLE_FRAG_DAMAGE(Object object, BOOL toggle) { invoke<Void>(0x01BA3AED21C16CFB, object, toggle); }
	NATIVE_DECL void SET_USE_KINEMATIC_PHYSICS(Entity entity, BOOL toggle) { invoke<Void>(0x15F944730C832252, entity, toggle); }
	NATIVE_DECL void SET_IN_STUNT_MODE(BOOL p0) { invoke<Void>(0x9EBD751E5787BAF2, p0); }
	NATIVE_DECL void SET_IN_ARENA_MODE(BOOL toggle) { invoke<Void>(0xAA6A6098851C396F, toggle); }
}

namespace PLAYER
{
	NATIVE_DECL Ped GET_PLAYER_PED(Player player) { return invoke<Ped>(0x43A66C31C68491C0, player); }
	NATIVE_DECL Ped GET_PLAYER_PED_SCRIPT_INDEX(Player player) { return invoke<Ped>(0x50FAC3A3E030A6E1, player); }
	NATIVE_DECL void SET_PLAYER_MODEL(Player player, Hash model) { invoke<Void>(0x00A1CADD00108836, player, model); }
	NATIVE_DECL void CHANGE_PLAYER_PED(Player player, Ped ped, BOOL p2, BOOL resetDamage) { invoke<Void>(0x048189FAC643DEEE, player, ped, p2, resetDamage); }
	NATIVE_DECL void GET_PLAYER_RGB_COLOUR(Player player, int* r, int* g, int* b) { invoke<Void>(0xE902EF951DCE178F, player, r, g, b); }
	NATIVE_DECL int GET_NUMBER_OF_PLAYERS() { return invoke<int>(0x407C7F91DDB46C16); }
	NATIVE_DECL int GET_PLAYER_TEAM(Player player) { return invoke<int>(0x37039302F4E0A008, player); }
	NATIVE_DECL void SET_PLAYER_TEAM(Player player, int team) { invoke<Void>(0x0299FA38396A4940, player, team); }
	NATIVE_DECL int GET_NUMBER_OF_PLAYERS_IN_TEAM(int team) { return invoke<int>(0x1FC200409F10E6F1, team); }
	NATIVE_DECL const char* GET_PLAYER_NAME(Player player) { return invoke<const char*>(0x6D0DE6A7B5DA71F8, player); }
	NATIVE_DECL float GET_WANTED_LEVEL_RADIUS(Player player) { return invoke<float>(0x085DEB493BE80812, player); }
	NATIVE_DECL Vector3 GET_PLAYER_WANTED_CENTRE_POSITION(Player player) { return invoke<Vector3>(0x0C92BA89F1AF26F8, player); }
	NATIVE_DECL void SET_PLAYER_WANTED_CENTRE_POSITION(Player player, float x, float y, float z) { invoke<Void>(0x520E541A97A13354, player, x, y, z); }
	NATIVE_DECL int GET_WANTED_LEVEL_THRESHOLD(int wantedLevel) { return invoke<int>(0xFDD179EAF45B556C, wantedLevel); }
	NATIVE_DECL void SET_PLAYER_WANTED_LEVEL(Player player, int wantedLevel, BOOL disableNoMission) { invoke<Void>(0x39FF19C64EF7DA5B, player, wantedLevel, disableNoMission); }
	NATIVE_DECL void SET_PLAYER_WANTED_LEVEL_NO_DROP(Player player, int wantedLevel, BOOL p2) { invoke<Void>(0x340E61DE7F471565, player, wantedLevel, p2); }
	NATIVE_DECL void SET_PLAYER_WANTED_LEVEL_NOW(Player player, BOOL p1) { invoke<Void>(0xE0A7D1E497FFCD6F, player, p1); }
	NATIVE_DECL BOOL ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(Player player) { return invoke<BOOL>(0xAFAF86043E5874E9, player); }
	NATIVE_DECL BOOL ARE_PLAYER_STARS_GREYED_OUT(Player player) { return invoke<BOOL>(0x0A6EB355EE14A2DB, player); }
	NATIVE_DECL BOOL IS_WANTED_AND_HAS_BEEN_SEEN_BY_COPS(Player player) { return invoke<BOOL>(0x7E07C78925D5FD96, player); }
	NATIVE_DECL void SET_DISPATCH_COPS_FOR_PLAYER(Player player, BOOL toggle) { invoke<Void>(0xDB172424876553F4, player, toggle); }
	NATIVE_DECL BOOL IS_PLAYER_WANTED_LEVEL_GREATER(Player player, int wantedLevel) { return invoke<BOOL>(0x238DB2A2C23EE9EF, player, wantedLevel); }
	NATIVE_DECL void CLEAR_PLAYER_WANTED_LEVEL(Player player) { invoke<Void>(0xB302540597885499, player); }
	NATIVE_DECL BOOL IS_PLAYER_DEAD(Player player) { return invoke<BOOL>(0x424D4687FA1E5652, player); }
	NATIVE_DECL BOOL IS_PLAYER_PRESSING_HORN(Player player) { return invoke<BOOL>(0xFA1E2BF8B10598F9, player); }
	NATIVE_DECL void SET_PLAYER_CONTROL(Player player, BOOL bHasControl, int flags) { invoke<Void>(0x8D32347D6D4C40A2, player, bHasControl, flags); }
	NATIVE_DECL int GET_PLAYER_WANTED_LEVEL(Player player) { return invoke<int>(0xE28E54788CE8F12D, player); }
	NATIVE_DECL void SET_MAX_WANTED_LEVEL(int maxWantedLevel) { invoke<Void>(0xAA5F02DB48D704B9, maxWantedLevel); }
	NATIVE_DECL void SET_POLICE_RADAR_BLIPS(BOOL toggle) { invoke<Void>(0x43286D561B72B8BF, toggle); }
	NATIVE_DECL void SET_POLICE_IGNORE_PLAYER(Player player, BOOL toggle) { invoke<Void>(0x32C62AA929C2DA6A, player, toggle); }
	NATIVE_DECL BOOL IS_PLAYER_PLAYING(Player player) { return invoke<BOOL>(0x5E9564D8246B909A, player); }
	NATIVE_DECL void SET_EVERYONE_IGNORE_PLAYER(Player player, BOOL toggle) { invoke<Void>(0x8EEDA153AD141BA4, player, toggle); }
	NATIVE_DECL void SET_ALL_RANDOM_PEDS_FLEE(Player player, BOOL toggle) { invoke<Void>(0x056E0FE8534C2949, player, toggle); }
	NATIVE_DECL void SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player) { invoke<Void>(0x471D2FF42A94B4F2, player); }
	NATIVE_DECL void SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE(Player player, BOOL toggle) { invoke<Void>(0xDE45D1A1EF45EE61, player, toggle); }
	NATIVE_DECL void SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player) { invoke<Void>(0xC3376F42B1FACCC6, player); }
	NATIVE_DECL void SET_LAW_PEDS_CAN_ATTACK_NON_WANTED_PLAYER_THIS_FRAME(Player player) { invoke<Void>(0xFAC75988A7D078D3, player); }
	NATIVE_DECL void SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(Player player, BOOL toggle) { invoke<Void>(0x596976B02B6B5700, player, toggle); }
	NATIVE_DECL void SET_WANTED_LEVEL_MULTIPLIER(float multiplier) { invoke<Void>(0x020E5F00CDA207BA, multiplier); }
	NATIVE_DECL void SET_WANTED_LEVEL_DIFFICULTY(Player player, float difficulty) { invoke<Void>(0x9B0BB33B04405E7A, player, difficulty); }
	NATIVE_DECL void RESET_WANTED_LEVEL_DIFFICULTY(Player player) { invoke<Void>(0xB9D0DD990DC141DD, player); }
	NATIVE_DECL int GET_WANTED_LEVEL_TIME_TO_ESCAPE() { return invoke<int>(0xA72200F51875FEA4); }
	NATIVE_DECL void SET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(Player player, int wantedLevel, int lossTime) { invoke<Void>(0x49B856B1360C47C7, player, wantedLevel, lossTime); }
	NATIVE_DECL void RESET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(Player player) { invoke<Void>(0x823EC8E82BA45986, player); }
	NATIVE_DECL void START_FIRING_AMNESTY(int duration) { invoke<Void>(0xBF9BD71691857E48, duration); }
	NATIVE_DECL void REPORT_CRIME(Player player, int crimeType, int wantedLvlThresh) { invoke<Void>(0xE9B09589827545E7, player, crimeType, wantedLvlThresh); }
	NATIVE_DECL void SUPPRESS_CRIME_THIS_FRAME(Player player, int crimeType) { invoke<Void>(0x9A987297ED8BD838, player, crimeType); }
	NATIVE_DECL void UPDATE_WANTED_POSITION_THIS_FRAME(Player player) { invoke<Void>(0xBC9490CA15AEA8FB, player); }
	NATIVE_DECL void SUPPRESS_LOSING_WANTED_LEVEL_IF_HIDDEN_THIS_FRAME(Player player) { invoke<Void>(0x4669B3ED80F24B4E, player); }
	NATIVE_DECL void ALLOW_EVASION_HUD_IF_DISABLING_HIDDEN_EVASION_THIS_FRAME(Player player, Any p1) { invoke<Void>(0x2F41A3BAE005E5FA, player, p1); }
	NATIVE_DECL void FORCE_START_HIDDEN_EVASION(Player player) { invoke<Void>(0xAD73CE5A09E42D12, player); }
	NATIVE_DECL void SUPPRESS_WITNESSES_CALLING_POLICE_THIS_FRAME(Player player) { invoke<Void>(0x36F1B38855F2A8DF, player); }
	NATIVE_DECL void REPORT_POLICE_SPOTTED_PLAYER(Player player) { invoke<Void>(0xDC64D2C53493ED12, player); }
	NATIVE_DECL void SET_LAW_RESPONSE_DELAY_OVERRIDE(float p0) { invoke<Void>(0xB45EFF719D8427A6, p0); }
	NATIVE_DECL void RESET_LAW_RESPONSE_DELAY_OVERRIDE() { invoke<Void>(0x0032A6DBA562C518); }
	NATIVE_DECL BOOL CAN_PLAYER_START_MISSION(Player player) { return invoke<BOOL>(0xDE7465A27D403C06, player); }
	NATIVE_DECL BOOL IS_PLAYER_READY_FOR_CUTSCENE(Player player) { return invoke<BOOL>(0x908CBECC2CAA3690, player); }
	NATIVE_DECL BOOL IS_PLAYER_TARGETTING_ENTITY(Player player, Entity entity) { return invoke<BOOL>(0x7912F7FC4F6264B6, player, entity); }
	NATIVE_DECL BOOL GET_PLAYER_TARGET_ENTITY(Player player, Entity* entity) { return invoke<BOOL>(0x13EDE1A5DBF797C9, player, entity); }
	NATIVE_DECL BOOL IS_PLAYER_FREE_AIMING(Player player) { return invoke<BOOL>(0x2E397FD2ECD37C87, player); }
	NATIVE_DECL BOOL IS_PLAYER_FREE_AIMING_AT_ENTITY(Player player, Entity entity) { return invoke<BOOL>(0x3C06B5C839B38F7B, player, entity); }
	NATIVE_DECL BOOL GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(Player player, Entity* entity) { return invoke<BOOL>(0x2975C866E6713290, player, entity); }
	NATIVE_DECL void SET_PLAYER_LOCKON_RANGE_OVERRIDE(Player player, float range) { invoke<Void>(0x29961D490E5814FD, player, range); }
	NATIVE_DECL void SET_PLAYER_CAN_DO_DRIVE_BY(Player player, BOOL toggle) { invoke<Void>(0x6E8834B52EC20C77, player, toggle); }
	NATIVE_DECL void SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(Player player, BOOL toggle) { invoke<Void>(0xD5E460AD7020A246, player, toggle); }
	NATIVE_DECL void SET_PLAYER_CAN_USE_COVER(Player player, BOOL toggle) { invoke<Void>(0xD465A8599DFF6814, player, toggle); }
	NATIVE_DECL int GET_MAX_WANTED_LEVEL() { return invoke<int>(0x462E0DB9B137DC5F); }
	NATIVE_DECL BOOL IS_PLAYER_TARGETTING_ANYTHING(Player player) { return invoke<BOOL>(0x78CFE51896B6B8A4, player); }
	NATIVE_DECL void SET_PLAYER_SPRINT(Player player, BOOL toggle) { invoke<Void>(0xA01B8075D8B92DF4, player, toggle); }
	NATIVE_DECL void RESET_PLAYER_STAMINA(Player player) { invoke<Void>(0xA6F312FCCE9C1DFE, player); }
	NATIVE_DECL void RESTORE_PLAYER_STAMINA(Player player, float p1) { invoke<Void>(0xA352C1B864CAFD33, player, p1); }
	NATIVE_DECL float GET_PLAYER_SPRINT_STAMINA_REMAINING(Player player) { return invoke<float>(0x3F9F16F8E65A7ED7, player); }
	NATIVE_DECL float GET_PLAYER_SPRINT_TIME_REMAINING(Player player) { return invoke<float>(0x1885BC9B108B4C99, player); }
	NATIVE_DECL float GET_PLAYER_UNDERWATER_TIME_REMAINING(Player player) { return invoke<float>(0xA1FCF8E6AF40B731, player); }
	NATIVE_DECL float SET_PLAYER_UNDERWATER_BREATH_PERCENT_REMAINING(Player player, float time) { return invoke<float>(0xA0D3E4F7AAFB7E78, player, time); }
	NATIVE_DECL int GET_PLAYER_GROUP(Player player) { return invoke<int>(0x0D127585F77030AF, player); }
	NATIVE_DECL int GET_PLAYER_MAX_ARMOUR(Player player) { return invoke<int>(0x92659B4CE1863CB3, player); }
	NATIVE_DECL BOOL IS_PLAYER_CONTROL_ON(Player player) { return invoke<BOOL>(0x49C32D60007AFA47, player); }
	NATIVE_DECL BOOL GET_ARE_CAMERA_CONTROLS_DISABLED() { return invoke<BOOL>(0x7C814D2FB49F40C0); }
	NATIVE_DECL BOOL IS_PLAYER_SCRIPT_CONTROL_ON(Player player) { return invoke<BOOL>(0x8A876A65283DD7D7, player); }
	NATIVE_DECL BOOL IS_PLAYER_CLIMBING(Player player) { return invoke<BOOL>(0x95E8F73DC65EFB9C, player); }
	NATIVE_DECL BOOL IS_PLAYER_BEING_ARRESTED(Player player, BOOL atArresting) { return invoke<BOOL>(0x388A47C51ABDAC8E, player, atArresting); }
	NATIVE_DECL void RESET_PLAYER_ARREST_STATE(Player player) { invoke<Void>(0x2D03E13C460760D6, player); }
	NATIVE_DECL Vehicle GET_PLAYERS_LAST_VEHICLE() { return invoke<Vehicle>(0xB6997A7EB3F5C8C0); }
	NATIVE_DECL Player GET_PLAYER_INDEX() { return invoke<Player>(0xA5EDC40EF369B48D); }
	NATIVE_DECL Player INT_TO_PLAYERINDEX(int value) { return invoke<Player>(0x41BD2A6B006AF756, value); }
	NATIVE_DECL int INT_TO_PARTICIPANTINDEX(int value) { return invoke<int>(0x9EC6603812C24710, value); }
	NATIVE_DECL int GET_TIME_SINCE_PLAYER_HIT_VEHICLE(Player player) { return invoke<int>(0x5D35ECF3A81A0EE0, player); }
	NATIVE_DECL int GET_TIME_SINCE_PLAYER_HIT_PED(Player player) { return invoke<int>(0xE36A25322DC35F42, player); }
	NATIVE_DECL int GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(Player player) { return invoke<int>(0xD559D2BE9E37853B, player); }
	NATIVE_DECL int GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(Player player) { return invoke<int>(0xDB89591E290D9182, player); }
	NATIVE_DECL BOOL IS_PLAYER_FREE_FOR_AMBIENT_TASK(Player player) { return invoke<BOOL>(0xDCCFD3F106C36AB4, player); }
	NATIVE_DECL Player PLAYER_ID() { return invoke<Player>(0x4F8644AF03D0E0D6); }
	NATIVE_DECL Ped PLAYER_PED_ID() { return invoke<Ped>(0xD80958FC74E988A6); }
	NATIVE_DECL int NETWORK_PLAYER_ID_TO_INT() { return invoke<int>(0xEE68096F9F37341E); }
	NATIVE_DECL BOOL HAS_FORCE_CLEANUP_OCCURRED(int cleanupFlags) { return invoke<BOOL>(0xC968670BFACE42D9, cleanupFlags); }
	NATIVE_DECL void FORCE_CLEANUP(int cleanupFlags) { invoke<Void>(0xBC8983F38F78ED51, cleanupFlags); }
	NATIVE_DECL void FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME(const char* name, int cleanupFlags) { invoke<Void>(0x4C68DDDDF0097317, name, cleanupFlags); }
	NATIVE_DECL void FORCE_CLEANUP_FOR_THREAD_WITH_THIS_ID(int id, int cleanupFlags) { invoke<Void>(0xF745B37630DF176B, id, cleanupFlags); }
	NATIVE_DECL int GET_CAUSE_OF_MOST_RECENT_FORCE_CLEANUP() { return invoke<int>(0x9A41CF4674A12272); }
	NATIVE_DECL void SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(Player player, Vehicle vehicle) { invoke<Void>(0x8026FF78F208978A, player, vehicle); }
	NATIVE_DECL void SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE(Player player) { invoke<Void>(0x1DE37BBF9E9CC14A, player); }
	NATIVE_DECL BOOL GIVE_ACHIEVEMENT_TO_PLAYER(int achievementId) { return invoke<BOOL>(0xBEC7076D64130195, achievementId); }
	NATIVE_DECL BOOL SET_ACHIEVEMENT_PROGRESS(int achievementId, int progress) { return invoke<BOOL>(0xC2AFFFDABBDC2C5C, achievementId, progress); }
	NATIVE_DECL int GET_ACHIEVEMENT_PROGRESS(int achievementId) { return invoke<int>(0x1C186837D0619335, achievementId); }
	NATIVE_DECL BOOL HAS_ACHIEVEMENT_BEEN_PASSED(int achievementId) { return invoke<BOOL>(0x867365E111A3B6EB, achievementId); }
	NATIVE_DECL BOOL IS_PLAYER_ONLINE() { return invoke<BOOL>(0xF25D331DC2627BBC); }
	NATIVE_DECL BOOL IS_PLAYER_LOGGING_IN_NP() { return invoke<BOOL>(0x74556E1420867ECA); }
	NATIVE_DECL void DISPLAY_SYSTEM_SIGNIN_UI(BOOL p0) { invoke<Void>(0x94DD7888C10A979E, p0); }
	NATIVE_DECL BOOL IS_SYSTEM_UI_BEING_DISPLAYED() { return invoke<BOOL>(0x5D511E3867C87139); }
	NATIVE_DECL void SET_PLAYER_INVINCIBLE(Player player, BOOL toggle) { invoke<Void>(0x239528EACDC3E7DE, player, toggle); }
	NATIVE_DECL BOOL GET_PLAYER_INVINCIBLE(Player player) { return invoke<BOOL>(0xB721981B2B939E07, player); }
	NATIVE_DECL BOOL GET_PLAYER_DEBUG_INVINCIBLE(Player player) { return invoke<BOOL>(0xDCC07526B8EC45AF, player); }
	NATIVE_DECL void SET_PLAYER_INVINCIBLE_BUT_HAS_REACTIONS(Player player, BOOL toggle) { invoke<Void>(0x6BC97F4F4BB3C04B, player, toggle); }
	NATIVE_DECL void SET_PLAYER_CAN_COLLECT_DROPPED_MONEY(Player player, BOOL p1) { invoke<Void>(0xCAC57395B151135F, player, p1); }
	NATIVE_DECL void REMOVE_PLAYER_HELMET(Player player, BOOL p2) { invoke<Void>(0xF3AC26D3CC576528, player, p2); }
	NATIVE_DECL void GIVE_PLAYER_RAGDOLL_CONTROL(Player player, BOOL toggle) { invoke<Void>(0x3C49C870E66F0A28, player, toggle); }
	NATIVE_DECL void SET_PLAYER_LOCKON(Player player, BOOL toggle) { invoke<Void>(0x5C8B2F450EE4328E, player, toggle); }
	NATIVE_DECL void SET_PLAYER_TARGETING_MODE(int targetMode) { invoke<Void>(0xB1906895227793F3, targetMode); }
	NATIVE_DECL int GET_PLAYER_TARGETING_MODE() { return invoke<int>(0x875BDD898B99C8CE); }
	NATIVE_DECL void SET_PLAYER_TARGET_LEVEL(int targetLevel) { invoke<Void>(0x5702B917B99DB1CD, targetLevel); }
	NATIVE_DECL BOOL GET_IS_USING_FPS_THIRD_PERSON_COVER() { return invoke<BOOL>(0xB9CF1F793A9F1BF1); }
	NATIVE_DECL BOOL GET_IS_USING_HOOD_CAMERA() { return invoke<BOOL>(0xCB645E85E97EA48B); }
	NATIVE_DECL void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(Player player) { invoke<Void>(0xF0B67A4DE6AB5F98, player); }
	NATIVE_DECL BOOL HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(Player player) { return invoke<BOOL>(0x20CE80B0C2BF4ACC, player); }
	NATIVE_DECL void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(Player player) { invoke<Void>(0x4AACB96203D11A31, player); }
	NATIVE_DECL BOOL HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(Player player) { return invoke<BOOL>(0xE4B90F367BD81752, player); }
	NATIVE_DECL void SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE(Player player, float multiplier) { invoke<Void>(0xCA7DC8329F0A1E9E, player, multiplier); }
	NATIVE_DECL void SET_SWIM_MULTIPLIER_FOR_PLAYER(Player player, float multiplier) { invoke<Void>(0xA91C6F0FF7D16A13, player, multiplier); }
	NATIVE_DECL void SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(Player player, float multiplier) { invoke<Void>(0x6DB47AA77FD94E09, player, multiplier); }
	NATIVE_DECL int GET_TIME_SINCE_LAST_ARREST() { return invoke<int>(0x5063F92F07C2A316); }
	NATIVE_DECL int GET_TIME_SINCE_LAST_DEATH() { return invoke<int>(0xC7034807558DDFCA); }
	NATIVE_DECL void ASSISTED_MOVEMENT_CLOSE_ROUTE() { invoke<Void>(0xAEBF081FFC0A0E5E); }
	NATIVE_DECL void ASSISTED_MOVEMENT_FLUSH_ROUTE() { invoke<Void>(0x8621390F0CDCFE1F); }
	NATIVE_DECL void SET_PLAYER_FORCED_AIM(Player player, BOOL toggle) { invoke<Void>(0x0FEE4F80AC44A726, player, toggle); }
	NATIVE_DECL void SET_PLAYER_FORCED_ZOOM(Player player, BOOL toggle) { invoke<Void>(0x75E7D505F2B15902, player, toggle); }
	NATIVE_DECL void SET_PLAYER_FORCE_SKIP_AIM_INTRO(Player player, BOOL toggle) { invoke<Void>(0x7651BC64AE59E128, player, toggle); }
	NATIVE_DECL void DISABLE_PLAYER_FIRING(Player player, BOOL toggle) { invoke<Void>(0x5E6CC07646BBEAB8, player, toggle); }
	NATIVE_DECL void DISABLE_PLAYER_THROW_GRENADE_WHILE_USING_GUN() { invoke<Void>(0xB885852C39CC265D); }
	NATIVE_DECL void SET_DISABLE_AMBIENT_MELEE_MOVE(Player player, BOOL toggle) { invoke<Void>(0x2E8AABFA40A84F8C, player, toggle); }
	NATIVE_DECL void SET_PLAYER_STEALTH_SPEED(Player player, int stealthSpeed) { invoke<Void>(0xE6200F3AF46AC0B5, player, stealthSpeed); }
	NATIVE_DECL void SET_PLAYER_MAX_ARMOUR(Player player, int value) { invoke<Void>(0x77DFCCF5948B8C71, player, value); }
	NATIVE_DECL void SPECIAL_ABILITY_ACTIVATE(Player player, int p1) { invoke<Void>(0x821FDC827D6F4090, player, p1); }
	NATIVE_DECL void SET_SPECIAL_ABILITY_MP(Player player, int p1, Any p2) { invoke<Void>(0xB214D570EAD7F81A, player, p1, p2); }
	NATIVE_DECL void SPECIAL_ABILITY_DEACTIVATE_MP(Player player, int p1) { invoke<Void>(0x17F7471EACA78290, player, p1); }
	NATIVE_DECL void SPECIAL_ABILITY_DEACTIVATE(Player player, Any p1) { invoke<Void>(0xD6A953C6D1492057, player, p1); }
	NATIVE_DECL void SPECIAL_ABILITY_DEACTIVATE_FAST(Player player, Any p1) { invoke<Void>(0x9CB5CE07A3968D5A, player, p1); }
	NATIVE_DECL void SPECIAL_ABILITY_RESET(Player player, Any p1) { invoke<Void>(0x375F0E738F861A94, player, p1); }
	NATIVE_DECL void SPECIAL_ABILITY_CHARGE_ON_MISSION_FAILED(Player player, Any p1) { invoke<Void>(0xC9A763D8FE87436A, player, p1); }
	NATIVE_DECL void SPECIAL_ABILITY_CHARGE_SMALL(Player player, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0x2E7B9B683481687D, player, p1, p2, p3); }
	NATIVE_DECL void SPECIAL_ABILITY_CHARGE_MEDIUM(Player player, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0xF113E3AA9BC54613, player, p1, p2, p3); }
	NATIVE_DECL void SPECIAL_ABILITY_CHARGE_LARGE(Player player, BOOL p1, BOOL p2, Any p3) { invoke<Void>(0xF733F45FA4497D93, player, p1, p2, p3); }
	NATIVE_DECL void SPECIAL_ABILITY_CHARGE_CONTINUOUS(Player player, Ped p1, Any p2) { invoke<Void>(0xED481732DFF7E997, player, p1, p2); }
	NATIVE_DECL void SPECIAL_ABILITY_CHARGE_ABSOLUTE(Player player, int p1, BOOL p2, Any p3) { invoke<Void>(0xB7B0870EB531D08D, player, p1, p2, p3); }
	NATIVE_DECL void SPECIAL_ABILITY_CHARGE_NORMALIZED(Player player, float normalizedValue, BOOL p2, Any p3) { invoke<Void>(0xA0696A65F009EE18, player, normalizedValue, p2, p3); }
	NATIVE_DECL void SPECIAL_ABILITY_FILL_METER(Player player, BOOL p1, Any p2) { invoke<Void>(0x3DACA8DDC6FD4980, player, p1, p2); }
	NATIVE_DECL void SPECIAL_ABILITY_DEPLETE_METER(Player player, BOOL p1, Any p2) { invoke<Void>(0x1D506DBBBC51E64B, player, p1, p2); }
	NATIVE_DECL void SPECIAL_ABILITY_LOCK(Hash playerModel, Any p1) { invoke<Void>(0x6A09D0D590A47D13, playerModel, p1); }
	NATIVE_DECL void SPECIAL_ABILITY_UNLOCK(Hash playerModel, Any p1) { invoke<Void>(0xF145F3BE2EFA9A3B, playerModel, p1); }
	NATIVE_DECL BOOL IS_SPECIAL_ABILITY_UNLOCKED(Hash playerModel) { return invoke<BOOL>(0xC6017F6A6CDFA694, playerModel); }
	NATIVE_DECL BOOL IS_SPECIAL_ABILITY_ACTIVE(Player player, Any p1) { return invoke<BOOL>(0x3E5F7FC85D854E15, player, p1); }
	NATIVE_DECL BOOL IS_SPECIAL_ABILITY_METER_FULL(Player player, Any p1) { return invoke<BOOL>(0x05A1FE504B7F2587, player, p1); }
	NATIVE_DECL void ENABLE_SPECIAL_ABILITY(Player player, BOOL toggle, Any p2) { invoke<Void>(0x181EC197DAEFE121, player, toggle, p2); }
	NATIVE_DECL BOOL IS_SPECIAL_ABILITY_ENABLED(Player player, Any p1) { return invoke<BOOL>(0xB1D200FE26AEF3CB, player, p1); }
	NATIVE_DECL void SET_SPECIAL_ABILITY_MULTIPLIER(float multiplier) { invoke<Void>(0xA49C426ED0CA4AB7, multiplier); }
	NATIVE_DECL void UPDATE_SPECIAL_ABILITY_FROM_STAT(Player player, Any p1) { invoke<Void>(0xFFEE8FA29AB9A18E, player, p1); }
	NATIVE_DECL BOOL GET_IS_PLAYER_DRIVING_ON_HIGHWAY(Player player) { return invoke<BOOL>(0x5FC472C501CCADB3, player); }
	NATIVE_DECL BOOL GET_IS_PLAYER_DRIVING_WRECKLESS(Player player, int p1) { return invoke<BOOL>(0xF10B44FD479D69F3, player, p1); }
	NATIVE_DECL BOOL GET_IS_MOPPING_AREA_FREE_IN_FRONT_OF_PLAYER(Player player, float p1) { return invoke<BOOL>(0xDD2620B7B9D16FF1, player, p1); }
	NATIVE_DECL void START_PLAYER_TELEPORT(Player player, float x, float y, float z, float heading, BOOL p5, BOOL findCollisionLand, BOOL p7) { invoke<Void>(0xAD15F075A4DA0FDE, player, x, y, z, heading, p5, findCollisionLand, p7); }
	NATIVE_DECL BOOL UPDATE_PLAYER_TELEPORT(Player player) { return invoke<BOOL>(0xE23D5873C2394C61, player); }
	NATIVE_DECL void STOP_PLAYER_TELEPORT() { invoke<Void>(0xC449EDED9D73009C); }
	NATIVE_DECL BOOL IS_PLAYER_TELEPORT_ACTIVE() { return invoke<BOOL>(0x02B15662D7F8886F); }
	NATIVE_DECL float GET_PLAYER_CURRENT_STEALTH_NOISE(Player player) { return invoke<float>(0x2F395D61F3A1F877, player); }
	NATIVE_DECL void SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(Player player, float regenRate) { invoke<Void>(0x5DB660B38DD98A31, player, regenRate); }
	NATIVE_DECL float GET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(Player player) { return invoke<float>(0x8BC515BAE4AAF8FF, player); }
	NATIVE_DECL void SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(Player player, float limit) { invoke<Void>(0xC388A0F065F5BC34, player, limit); }
	NATIVE_DECL void DISABLE_PLAYER_HEALTH_RECHARGE(Player player) { invoke<Void>(0xBCB06442F7E52666, player); }
	NATIVE_DECL void SET_PLAYER_FALL_DISTANCE_TO_TRIGGER_RAGDOLL_OVERRIDE(Player player, float p1) { invoke<Void>(0xEFD79FA81DFBA9CB, player, p1); }
	NATIVE_DECL void SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Player player, float modifier) { invoke<Void>(0xCE07B9F7817AADA3, player, modifier); }
	NATIVE_DECL void SET_PLAYER_WEAPON_DEFENSE_MODIFIER(Player player, float modifier) { invoke<Void>(0x2D83BC011CA14A3C, player, modifier); }
	NATIVE_DECL void SET_PLAYER_WEAPON_MINIGUN_DEFENSE_MODIFIER(Player player, float modifier) { invoke<Void>(0xBCFDE9EDE4CF27DC, player, modifier); }
	NATIVE_DECL void SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Player player, float modifier, BOOL p2) { invoke<Void>(0x4A3DC7ECCC321032, player, modifier, p2); }
	NATIVE_DECL void SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(Player player, float modifier) { invoke<Void>(0xAE540335B4ABC4E2, player, modifier); }
	NATIVE_DECL void SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(Player player, float modifier) { invoke<Void>(0xA50E117CDDF82F0C, player, modifier); }
	NATIVE_DECL void SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(Player player, float modifier) { invoke<Void>(0x4C60E6EFDAFF2462, player, modifier); }
	NATIVE_DECL void SET_PLAYER_MAX_EXPLOSIVE_DAMAGE(Player player, float p1) { invoke<Void>(0x8D768602ADEF2245, player, p1); }
	NATIVE_DECL void SET_PLAYER_EXPLOSIVE_DAMAGE_MODIFIER(Player player, Any p1) { invoke<Void>(0xD821056B9ACF8052, player, p1); }
	NATIVE_DECL void SET_PLAYER_WEAPON_TAKEDOWN_DEFENSE_MODIFIER(Player player, float p1) { invoke<Void>(0x31E90B8873A4CD3B, player, p1); }
	NATIVE_DECL void SET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int tintIndex) { invoke<Void>(0xA3D0E54541D9A5E5, player, tintIndex); }
	NATIVE_DECL void GET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int* tintIndex) { invoke<Void>(0x75D3F7A1B0D9B145, player, tintIndex); }
	NATIVE_DECL void SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int index) { invoke<Void>(0xAF04C87F5DC1DF38, player, index); }
	NATIVE_DECL void GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int* index) { invoke<Void>(0xD5A016BC3C09CF40, player, index); }
	NATIVE_DECL void SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int tintIndex) { invoke<Void>(0x93B0FB27C9A04060, player, tintIndex); }
	NATIVE_DECL void GET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int* tintIndex) { invoke<Void>(0x6E9C742F340CE5A2, player, tintIndex); }
	NATIVE_DECL void SET_PLAYER_HAS_RESERVE_PARACHUTE(Player player) { invoke<Void>(0x7DDAB28D31FAC363, player); }
	NATIVE_DECL BOOL GET_PLAYER_HAS_RESERVE_PARACHUTE(Player player) { return invoke<BOOL>(0x5DDFE2FF727F3CA3, player); }
	NATIVE_DECL void SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL(Player player, BOOL enabled) { invoke<Void>(0xF401B182DBA8AF53, player, enabled); }
	NATIVE_DECL void SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, int r, int g, int b) { invoke<Void>(0x8217FD371A4625CF, player, r, g, b); }
	NATIVE_DECL void GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, int* r, int* g, int* b) { invoke<Void>(0xEF56DBABD3CD4887, player, r, g, b); }
	NATIVE_DECL void SET_PLAYER_RESET_FLAG_PREFER_REAR_SEATS(Player player, Vehicle vehicle) { invoke<Void>(0xC1069B5E5B6EA13E, player, vehicle); }
	NATIVE_DECL void SET_PLAYER_PHONE_PALETTE_IDX(Player player, int idx) { invoke<Void>(0x11D5F725F0E780E0, player, idx); }
	NATIVE_DECL void SET_PLAYER_NOISE_MULTIPLIER(Player player, float multiplier) { invoke<Void>(0xDB89EF50FF25FCE9, player, multiplier); }
	NATIVE_DECL void SET_PLAYER_SNEAKING_NOISE_MULTIPLIER(Player player, float multiplier) { invoke<Void>(0xB2C1A29588A9F47C, player, multiplier); }
	NATIVE_DECL BOOL CAN_PED_HEAR_PLAYER(Player player, Ped ped) { return invoke<BOOL>(0xF297383AA91DCA29, player, ped); }
	NATIVE_DECL void SIMULATE_PLAYER_INPUT_GAIT(Player player, float amount, int gaitType, float speed, BOOL p4, BOOL p5, Any p6) { invoke<Void>(0x477D5D63E63ECA5D, player, amount, gaitType, speed, p4, p5, p6); }
	NATIVE_DECL void RESET_PLAYER_INPUT_GAIT(Player player) { invoke<Void>(0x19531C47A2ABD691, player); }
	NATIVE_DECL void SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(Player player, BOOL toggle) { invoke<Void>(0x9F343285A00B4BB6, player, toggle); }
	NATIVE_DECL void SET_AUTO_GIVE_SCUBA_GEAR_WHEN_EXIT_VEHICLE(Player player, BOOL toggle) { invoke<Void>(0xD2B315B6689D537D, player, toggle); }
	NATIVE_DECL void SET_PLAYER_STEALTH_PERCEPTION_MODIFIER(Player player, float value) { invoke<Void>(0x4E9021C1FCDD507A, player, value); }
	NATIVE_DECL BOOL IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(Player player) { return invoke<BOOL>(0x690A61A6D13583F6, player); }
	NATIVE_DECL void INCREASE_PLAYER_JUMP_SUPPRESSION_RANGE(Player player) { invoke<Void>(0x9EDD76E87D5D51BA, player); }
	NATIVE_DECL void SET_PLAYER_SIMULATE_AIMING(Player player, BOOL toggle) { invoke<Void>(0xC54C95DA968EC5B5, player, toggle); }
	NATIVE_DECL void SET_PLAYER_CLOTH_PIN_FRAMES(Player player, int p1) { invoke<Void>(0x749FADDF97DFE930, player, p1); }
	NATIVE_DECL void SET_PLAYER_CLOTH_PACKAGE_INDEX(int index) { invoke<Void>(0x9F7BBA2EA6372500, index); }
	NATIVE_DECL void SET_PLAYER_CLOTH_LOCK_COUNTER(int value) { invoke<Void>(0x14D913B777DFF5DA, value); }
	NATIVE_DECL void PLAYER_ATTACH_VIRTUAL_BOUND(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7) { invoke<Void>(0xED51733DC73AED51, p0, p1, p2, p3, p4, p5, p6, p7); }
	NATIVE_DECL void PLAYER_DETACH_VIRTUAL_BOUND() { invoke<Void>(0x1DD5897E2FA6E7C9); }
	NATIVE_DECL BOOL HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE(Player player) { return invoke<BOOL>(0xD705740BB0A1CF4C, player); }
	NATIVE_DECL BOOL IS_PLAYER_BATTLE_AWARE(Player player) { return invoke<BOOL>(0x38D28DA81E4E9BF9, player); }
	NATIVE_DECL BOOL GET_PLAYER_RECEIVED_BATTLE_EVENT_RECENTLY(Player player, int p1, BOOL p2) { return invoke<BOOL>(0xBC0753C9CA14B506, player, p1, p2); }
	NATIVE_DECL void EXTEND_WORLD_BOUNDARY_FOR_PLAYER(float x, float y, float z) { invoke<Void>(0x5006D96C995A5827, x, y, z); }
	NATIVE_DECL void RESET_WORLD_BOUNDARY_FOR_PLAYER() { invoke<Void>(0xDA1DF03D5A315F4E); }
	NATIVE_DECL BOOL IS_PLAYER_RIDING_TRAIN(Player player) { return invoke<BOOL>(0x4EC12697209F2196, player); }
	NATIVE_DECL BOOL HAS_PLAYER_LEFT_THE_WORLD(Player player) { return invoke<BOOL>(0xD55DDFB47991A294, player); }
	NATIVE_DECL void SET_PLAYER_LEAVE_PED_BEHIND(Player player, BOOL toggle) { invoke<Void>(0xFF300C7649724A0B, player, toggle); }
	NATIVE_DECL void SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player, int p1, Any p2, Any p3, BOOL p4) { invoke<Void>(0xD9284A8C0D48352C, player, p1, p2, p3, p4); }
	NATIVE_DECL void CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player) { invoke<Void>(0x0F4CC924CF8C7B21, player); }
	NATIVE_DECL void SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player, Hash model) { invoke<Void>(0x977DB4641F6FC3DB, player, model); }
	NATIVE_DECL void SET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player, Hash model) { invoke<Void>(0x0764486AEDE748DB, player, model); }
	NATIVE_DECL Hash GET_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player) { return invoke<Hash>(0xC219887CA3E65C41, player); }
	NATIVE_DECL Hash GET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player) { return invoke<Hash>(0x37FAAA68DCA9D08D, player); }
	NATIVE_DECL void CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player) { invoke<Void>(0x8753997EB5F6EE3F, player); }
	NATIVE_DECL void CLEAR_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player) { invoke<Void>(0x290D248E25815AE8, player); }
	NATIVE_DECL void SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player, Hash model) { invoke<Void>(0xDC80A4C2F18A2B64, player, model); }
	NATIVE_DECL void CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player) { invoke<Void>(0x10C54E4389C12B42, player); }
	NATIVE_DECL void DISABLE_PLAYER_VEHICLE_REWARDS(Player player) { invoke<Void>(0xC142BE3BB9CE125F, player); }
	NATIVE_DECL void SET_PLAYER_SPECTATED_VEHICLE_RADIO_OVERRIDE(BOOL p0) { invoke<Void>(0x2F7CEB6520288061, p0); }
	NATIVE_DECL void SET_PLAYER_BLUETOOTH_STATE(Player player, BOOL state) { invoke<Void>(0x5DC40A8869C22141, player, state); }
	NATIVE_DECL BOOL IS_PLAYER_BLUETOOTH_ENABLE(Player player) { return invoke<BOOL>(0x65FAEE425DE637B0, player); }
	NATIVE_DECL void DISABLE_CAMERA_VIEW_MODE_CYCLE(Player player) { invoke<Void>(0x5501B7A5CDB79D37, player); }
	NATIVE_DECL int GET_PLAYER_FAKE_WANTED_LEVEL(Player player) { return invoke<int>(0x56105E599CAB0EFA, player); }
	NATIVE_DECL void SET_PLAYER_CAN_DAMAGE_PLAYER(Player player1, Player player2, BOOL toggle) { invoke<Void>(0x55FCC0C390620314, player1, player2, toggle); }
	NATIVE_DECL void SET_APPLY_WAYPOINT_OF_PLAYER(Player player, int hudColor) { invoke<Void>(0x2382AB11450AE7BA, player, hudColor); }
	NATIVE_DECL BOOL IS_PLAYER_VEHICLE_WEAPON_TOGGLED_TO_NON_HOMING(Any p0) { return invoke<BOOL>(0x6E4361FF3E8CD7CA, p0); }
	NATIVE_DECL void SET_PLAYER_VEHICLE_WEAPON_TO_NON_HOMING(Any p0) { invoke<Void>(0x237440E46D918649, p0); }
	NATIVE_DECL void SET_PLAYER_HOMING_DISABLED_FOR_ALL_VEHICLE_WEAPONS(Any p0, Any p1) { invoke<Void>(0xEE4EBDD2593BA844, p0, p1); }
	NATIVE_DECL void ADD_PLAYER_TARGETABLE_ENTITY(Player player, Entity entity) { invoke<Void>(0x9097EB6D4BB9A12A, player, entity); }
	NATIVE_DECL void REMOVE_PLAYER_TARGETABLE_ENTITY(Player player, Entity entity) { invoke<Void>(0x9F260BFB59ADBCA3, player, entity); }
	NATIVE_DECL void SET_PLAYER_PREVIOUS_VARIATION_DATA(Player player, int p1, int p2, Any p3, Any p4, Any p5) { invoke<Void>(0x7BAE68775557AE0B, player, p1, p2, p3, p4, p5); }
	NATIVE_DECL void REMOVE_SCRIPT_FIRE_POSITION() { invoke<Void>(0x7148E0F43D11F0D9); }
	NATIVE_DECL void SET_SCRIPT_FIRE_POSITION(float coordX, float coordY, float coordZ) { invoke<Void>(0x70A382ADEC069DD3, coordX, coordY, coordZ); }
	static void _0x733A643B5B0C53C1(Player player, BOOL toggle) { invoke<Void>(0x733A643B5B0C53C1, player, toggle); } // 0x733A643B5B0C53C1 0xDFB9A2A2
}

namespace RECORDING
{
	NATIVE_DECL void REPLAY_START_EVENT(int p0) { invoke<Void>(0x48621C9FCA3EBD28, p0); }
	NATIVE_DECL void REPLAY_STOP_EVENT() { invoke<Void>(0x81CBAE94390F9F89); }
	NATIVE_DECL void REPLAY_CANCEL_EVENT() { invoke<Void>(0x13B350B8AD0EEE10); }
	NATIVE_DECL void REPLAY_RECORD_BACK_FOR_TIME(float p0, float p1, int p2) { invoke<Void>(0x293220DA1B46CEBC, p0, p1, p2); }
	NATIVE_DECL void REPLAY_CHECK_FOR_EVENT_THIS_FRAME(const char* missionNameLabel, Any p1) { invoke<Void>(0x208784099002BC30, missionNameLabel, p1); }
	NATIVE_DECL void REPLAY_PREVENT_RECORDING_THIS_FRAME() { invoke<Void>(0xEB2D525B57F42B40); }
	NATIVE_DECL void REPLAY_RESET_EVENT_INFO() { invoke<Void>(0xF854439EFBB3B583); }
	NATIVE_DECL void REPLAY_DISABLE_CAMERA_MOVEMENT_THIS_FRAME() { invoke<Void>(0xAF66DCEE6609B148); }
	NATIVE_DECL void RECORD_GREATEST_MOMENT(int p0, int p1, int p2) { invoke<Void>(0x66972397E0757E7A, p0, p1, p2); }
	NATIVE_DECL void START_REPLAY_RECORDING(int mode) { invoke<Void>(0xC3AC2FFF9612AC81, mode); }
	NATIVE_DECL void STOP_REPLAY_RECORDING() { invoke<Void>(0x071A5197D6AFC8B3); }
	NATIVE_DECL void CANCEL_REPLAY_RECORDING() { invoke<Void>(0x88BB3507ED41A240); }
	NATIVE_DECL BOOL SAVE_REPLAY_RECORDING() { return invoke<BOOL>(0x644546EC5287471B); }
	NATIVE_DECL BOOL IS_REPLAY_RECORDING() { return invoke<BOOL>(0x1897CA71995A90B4); }
	NATIVE_DECL BOOL IS_REPLAY_INITIALIZED() { return invoke<BOOL>(0xDF4B952F7D381B95); }
	NATIVE_DECL BOOL IS_REPLAY_AVAILABLE() { return invoke<BOOL>(0x4282E08174868BE3); }
	NATIVE_DECL BOOL IS_REPLAY_RECORD_SPACE_AVAILABLE(BOOL p0) { return invoke<BOOL>(0x33D47E85B476ABCD, p0); }
}

namespace REPLAY
{
	NATIVE_DECL void REGISTER_EFFECT_FOR_REPLAY_EDITOR(const char* p0, BOOL p1) { invoke<Void>(0x7E2BD3EF6C205F09, p0, p1); }
	NATIVE_DECL BOOL REPLAY_SYSTEM_HAS_REQUESTED_A_SCRIPT_CLEANUP() { return invoke<BOOL>(0x95AB8B5C992C7B58); }
	NATIVE_DECL void SET_SCRIPTS_HAVE_CLEANED_UP_FOR_REPLAY_SYSTEM() { invoke<Void>(0x5AD3932DAEB1E5D3); }
	NATIVE_DECL void SET_REPLAY_SYSTEM_PAUSED_FOR_SAVE(BOOL p0) { invoke<Void>(0xE058175F8EAFE79A, p0); }
	NATIVE_DECL void REPLAY_CONTROL_SHUTDOWN() { invoke<Void>(0x3353D13F09307691); }
	NATIVE_DECL void ACTIVATE_ROCKSTAR_EDITOR(int p0) { invoke<Void>(0x49DA8145672B2725, p0); }
}

namespace SAVEMIGRATION
{
	NATIVE_DECL BOOL SAVEMIGRATION_IS_MP_ENABLED() { return invoke<BOOL>(0x84B418E93894AC1C); }
	NATIVE_DECL BOOL SAVEMIGRATION_MP_REQUEST_ACCOUNTS() { return invoke<BOOL>(0x85F41F9225D08C72); }
	NATIVE_DECL int SAVEMIGRATION_MP_GET_ACCOUNTS_STATUS() { return invoke<int>(0xC8CB5999919EA2CA); }
	NATIVE_DECL int SAVEMIGRATION_MP_NUM_ACCOUNTS() { return invoke<int>(0x77A16200E18E0C55); }
	NATIVE_DECL BOOL SAVEMIGRATION_MP_GET_ACCOUNT(int p0, Any* p1) { return invoke<BOOL>(0xFCE2747EEF1D05FC, p0, p1); }
	NATIVE_DECL BOOL SAVEMIGRATION_MP_REQUEST_STATUS() { return invoke<BOOL>(0xE5E9746A66359F9D); }
	NATIVE_DECL int SAVEMIGRATION_MP_GET_STATUS() { return invoke<int>(0x690B76BD2763E068); }
}

namespace SCRIPT
{
	NATIVE_DECL void REQUEST_SCRIPT(const char* scriptName) { invoke<Void>(0x6EB5F71AA68F2E8E, scriptName); }
	NATIVE_DECL void SET_SCRIPT_AS_NO_LONGER_NEEDED(const char* scriptName) { invoke<Void>(0xC90D2DCACD56184C, scriptName); }
	NATIVE_DECL BOOL HAS_SCRIPT_LOADED(const char* scriptName) { return invoke<BOOL>(0xE6CC9F3BA0FB9EF1, scriptName); }
	NATIVE_DECL BOOL DOES_SCRIPT_EXIST(const char* scriptName) { return invoke<BOOL>(0xFC04745FBE67C19A, scriptName); }
	NATIVE_DECL void REQUEST_SCRIPT_WITH_NAME_HASH(Hash scriptHash) { invoke<Void>(0xD62A67D26D9653E6, scriptHash); }
	NATIVE_DECL void SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(Hash scriptHash) { invoke<Void>(0xC5BC038960E9DB27, scriptHash); }
	NATIVE_DECL BOOL HAS_SCRIPT_WITH_NAME_HASH_LOADED(Hash scriptHash) { return invoke<BOOL>(0x5F0F0C783EB16C04, scriptHash); }
	NATIVE_DECL BOOL DOES_SCRIPT_WITH_NAME_HASH_EXIST(Hash scriptHash) { return invoke<BOOL>(0xF86AA3C56BA31381, scriptHash); }
	NATIVE_DECL void TERMINATE_THREAD(int threadId) { invoke<Void>(0xC8B189ED9138BCD4, threadId); }
	NATIVE_DECL BOOL IS_THREAD_ACTIVE(int threadId) { return invoke<BOOL>(0x46E9AE36D8FA6417, threadId); }
	NATIVE_DECL const char* GET_NAME_OF_SCRIPT_WITH_THIS_ID(int threadId) { return invoke<const char*>(0x05A42BA9FC8DA96B, threadId); }
	NATIVE_DECL void SCRIPT_THREAD_ITERATOR_RESET() { invoke<Void>(0xDADFADA5A20143A8); }
	NATIVE_DECL int SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID() { return invoke<int>(0x30B4FA1C82DD4B9F); }
	NATIVE_DECL int GET_ID_OF_THIS_THREAD() { return invoke<int>(0xC30338E8088E2E21); }
	NATIVE_DECL void TERMINATE_THIS_THREAD() { invoke<Void>(0x1090044AD1DA76FA); }
	NATIVE_DECL int GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(Hash scriptHash) { return invoke<int>(0x2C83A9DA6BFFC4F9, scriptHash); }
	NATIVE_DECL const char* GET_THIS_SCRIPT_NAME() { return invoke<const char*>(0x442E0A7EDE4A738A); }
	NATIVE_DECL Hash GET_HASH_OF_THIS_SCRIPT_NAME() { return invoke<Hash>(0x8A1C8B1738FFE87E); }
	NATIVE_DECL int GET_NUMBER_OF_EVENTS(int eventGroup) { return invoke<int>(0x5F92A689A06620AA, eventGroup); }
	NATIVE_DECL BOOL GET_EVENT_EXISTS(int eventGroup, int eventIndex) { return invoke<BOOL>(0x936E6168A9BCEDB5, eventGroup, eventIndex); }
	NATIVE_DECL int GET_EVENT_AT_INDEX(int eventGroup, int eventIndex) { return invoke<int>(0xD8F66A3A60C62153, eventGroup, eventIndex); }
	NATIVE_DECL BOOL GET_EVENT_DATA(int eventGroup, int eventIndex, Any* eventData, int eventDataSize) { return invoke<BOOL>(0x2902843FCD2B2D79, eventGroup, eventIndex, eventData, eventDataSize); }
	NATIVE_DECL void TRIGGER_SCRIPT_EVENT(int eventGroup, Any* eventData, int eventDataSize, int playerBits) { invoke<Void>(0x5AE99C571D5BBE5D, eventGroup, eventData, eventDataSize, playerBits); }
	NATIVE_DECL void SHUTDOWN_LOADING_SCREEN() { invoke<Void>(0x078EBE9809CCD637); }
	NATIVE_DECL void SET_NO_LOADING_SCREEN(BOOL toggle) { invoke<Void>(0x5262CC1995D07E09, toggle); }
	NATIVE_DECL BOOL GET_NO_LOADING_SCREEN() { return invoke<BOOL>(0x18C1270EA7F199BC); }
	NATIVE_DECL void COMMIT_TO_LOADINGSCREEN_SELCTION() { invoke<Void>(0xB1577667C3708F9B); }
	NATIVE_DECL BOOL BG_IS_EXITFLAG_SET() { return invoke<BOOL>(0x836B62713E0534CA); }
	NATIVE_DECL void BG_SET_EXITFLAG_RESPONSE() { invoke<Void>(0x760910B49D2B98EA); }
	NATIVE_DECL void BG_START_CONTEXT_HASH(Hash contextHash) { invoke<Void>(0x75B18E49607874C7, contextHash); }
	NATIVE_DECL void BG_END_CONTEXT_HASH(Hash contextHash) { invoke<Void>(0x107E5CC7CA942BC1, contextHash); }
	NATIVE_DECL void BG_START_CONTEXT(const char* contextName) { invoke<Void>(0x9D5A25BADB742ACD, contextName); }
	NATIVE_DECL void BG_END_CONTEXT(const char* contextName) { invoke<Void>(0xDC2BACD920D0A0DD, contextName); }
	NATIVE_DECL BOOL BG_DOES_LAUNCH_PARAM_EXIST(int scriptIndex, const char* p1) { return invoke<BOOL>(0x0F6F1EBBC4E1D5E6, scriptIndex, p1); }
	NATIVE_DECL int BG_GET_LAUNCH_PARAM_VALUE(int scriptIndex, const char* p1) { return invoke<int>(0x22E21FBCFC88C149, scriptIndex, p1); }
	NATIVE_DECL int BG_GET_SCRIPT_ID_FROM_NAME_HASH(Hash p0) { return invoke<int>(0x829CD22E043A2577, p0); }
	NATIVE_DECL void _SEND_TU_SCRIPT_EVENT_NEW(int eventGroup, Any* eventData, int eventDataSize, int playerBits, Hash eventType) { invoke<Void>(0x71A6F836422FDD2B, eventGroup, eventData, eventDataSize, playerBits, eventType); }
}

namespace SECURITY
{
	NATIVE_DECL void REGISTER_SCRIPT_VARIABLE(Any* variable) { invoke<Void>(0x40EB1EFD921822BC, variable); }
	NATIVE_DECL void UNREGISTER_SCRIPT_VARIABLE(Any* variable) { invoke<Void>(0x340A36A700E99699, variable); }
	NATIVE_DECL void FORCE_CHECK_SCRIPT_VARIABLES() { invoke<Void>(0x8E580AB902917360); }
}

namespace SHAPETEST
{
	NATIVE_DECL int START_SHAPE_TEST_LOS_PROBE(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8) { return invoke<int>(0x7EE9F5D83DD4F90E, x1, y1, z1, x2, y2, z2, flags, entity, p8); }
	NATIVE_DECL int START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8) { return invoke<int>(0x377906D8A31E5586, x1, y1, z1, x2, y2, z2, flags, entity, p8); }
	NATIVE_DECL int START_SHAPE_TEST_BOUNDING_BOX(Entity entity, int flags1, int flags2) { return invoke<int>(0x052837721A854EC7, entity, flags1, flags2); }
	NATIVE_DECL int START_SHAPE_TEST_BOX(float x, float y, float z, float dimX, float dimY, float dimZ, float rotX, float rotY, float rotZ, Any p9, int flags, Entity entity, Any p12) { return invoke<int>(0xFE466162C4401D18, x, y, z, dimX, dimY, dimZ, rotX, rotY, rotZ, p9, flags, entity, p12); }
	NATIVE_DECL int START_SHAPE_TEST_BOUND(Entity entity, int flags1, int flags2) { return invoke<int>(0x37181417CE7C8900, entity, flags1, flags2); }
	NATIVE_DECL int START_SHAPE_TEST_CAPSULE(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int flags, Entity entity, int p9) { return invoke<int>(0x28579D1B8F8AAC80, x1, y1, z1, x2, y2, z2, radius, flags, entity, p9); }
	NATIVE_DECL int START_SHAPE_TEST_SWEPT_SPHERE(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int flags, Entity entity, Any p9) { return invoke<int>(0xE6AC6C45FBE83004, x1, y1, z1, x2, y2, z2, radius, flags, entity, p9); }
	NATIVE_DECL int START_SHAPE_TEST_MOUSE_CURSOR_LOS_PROBE(Vector3* pVec1, Vector3* pVec2, int flag, Entity entity, int flag2) { return invoke<int>(0xFF6BE494C7987F34, pVec1, pVec2, flag, entity, flag2); }
	NATIVE_DECL int GET_SHAPE_TEST_RESULT(int shapeTestHandle, BOOL* hit, Vector3* endCoords, Vector3* surfaceNormal, Entity* entityHit) { return invoke<int>(0x3D87450E15D98694, shapeTestHandle, hit, endCoords, surfaceNormal, entityHit); }
	NATIVE_DECL int GET_SHAPE_TEST_RESULT_INCLUDING_MATERIAL(int shapeTestHandle, BOOL* hit, Vector3* endCoords, Vector3* surfaceNormal, Hash* materialHash, Entity* entityHit) { return invoke<int>(0x65287525D951F6BE, shapeTestHandle, hit, endCoords, surfaceNormal, materialHash, entityHit); }
	NATIVE_DECL void RELEASE_SCRIPT_GUID_FROM_ENTITY(Entity entityHit) { invoke<Void>(0x2B3334BCA57CD799, entityHit); }
}

namespace SOCIALCLUB
{
	NATIVE_DECL int SC_INBOX_GET_TOTAL_NUM_MESSAGES() { return invoke<int>(0x03A93FF1A2CA0864); }
	NATIVE_DECL Hash SC_INBOX_GET_MESSAGE_TYPE_AT_INDEX(int msgIndex) { return invoke<Hash>(0xBB8EA16ECBC976C4, msgIndex); }
	NATIVE_DECL BOOL SC_INBOX_GET_MESSAGE_IS_READ_AT_INDEX(int msgIndex) { return invoke<BOOL>(0x93028F1DB42BFD08, msgIndex); }
	NATIVE_DECL BOOL SC_INBOX_SET_MESSAGE_AS_READ_AT_INDEX(int msgIndex) { return invoke<BOOL>(0x2C015348CF19CA1D, msgIndex); }
	NATIVE_DECL BOOL SC_INBOX_MESSAGE_GET_DATA_INT(int p0, const char* context, int* out) { return invoke<BOOL>(0xA00EFE4082C4056E, p0, context, out); }
	NATIVE_DECL BOOL SC_INBOX_MESSAGE_GET_DATA_BOOL(int p0, const char* p1) { return invoke<BOOL>(0xFFE5C16F402D851D, p0, p1); }
	NATIVE_DECL BOOL SC_INBOX_MESSAGE_GET_DATA_STRING(int p0, const char* context, char* out) { return invoke<BOOL>(0x7572EF42FC6A9B6D, p0, context, out); }
	NATIVE_DECL BOOL SC_INBOX_MESSAGE_DO_APPLY(int p0) { return invoke<BOOL>(0x9A2C8064B6C1E41A, p0); }
	NATIVE_DECL const char* SC_INBOX_MESSAGE_GET_RAW_TYPE_AT_INDEX(int p0) { return invoke<const char*>(0xF3E31D16CBDCB304, p0); }
	NATIVE_DECL void SC_INBOX_MESSAGE_PUSH_GAMER_T0_RECIP_LIST(Any* gamerHandle) { invoke<Void>(0xDA024BDBD600F44A, gamerHandle); }
	NATIVE_DECL void SC_INBOX_SEND_UGCSTATUPDATE_TO_RECIP_LIST(Any* data) { invoke<Void>(0xA68D3D229F4F3B06, data); }
	NATIVE_DECL BOOL SC_INBOX_MESSAGE_GET_UGCDATA(int p0, Any* p1) { return invoke<BOOL>(0x69D82604A1A5A254, p0, p1); }
	NATIVE_DECL BOOL SC_INBOX_GET_BOUNTY_DATA_AT_INDEX(int index, Any* outData) { return invoke<BOOL>(0x87E0052F08BD64E6, index, outData); }
	NATIVE_DECL void SC_EMAIL_RETRIEVE_EMAILS(int offset, int limit) { invoke<Void>(0x040ADDCBAFA1018A, offset, limit); }
	NATIVE_DECL int SC_EMAIL_GET_RETRIEVAL_STATUS() { return invoke<int>(0x16DA8172459434AA); }
	NATIVE_DECL int SC_EMAIL_GET_NUM_RETRIEVED_EMAILS() { return invoke<int>(0x7DB18CA8CAD5B098); }
	NATIVE_DECL BOOL SC_EMAIL_GET_EMAIL_AT_INDEX(int p0, Any* p1) { return invoke<BOOL>(0x4737980E8A283806, p0, p1); }
	NATIVE_DECL void _SC_EMAIL_MARKETING_EMAIL_OPENED(int index, Hash type) { invoke<Void>(0x69AA35F3F391CDBA, index, type); }
	NATIVE_DECL void SC_EMAIL_DELETE_EMAILS(Any* p0, Any p1) { invoke<Void>(0x44ACA259D67651DB, p0, p1); }
	NATIVE_DECL void SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST(Any* gamerHandle) { invoke<Void>(0x2330C12A7A605D16, gamerHandle); }
	NATIVE_DECL void SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST() { invoke<Void>(0x55DF6DB45179236E); }
	NATIVE_DECL void SC_EMAIL_SEND_EMAIL(const char* p0) { invoke<Void>(0x116FB94DC4B79F17, p0); }
	NATIVE_DECL BOOL SC_EMAIL_SET_CURRENT_EMAIL_TAG(Any p0) { return invoke<BOOL>(0x07DBD622D9533857, p0); }
	NATIVE_DECL void SC_CACHE_NEW_ROCKSTAR_MSGS(BOOL toggle) { invoke<Void>(0xBFA0A56A817C6C7D, toggle); }
	NATIVE_DECL BOOL SC_HAS_NEW_ROCKSTAR_MSG() { return invoke<BOOL>(0xBC1CC91205EC8D6E); }
	NATIVE_DECL const char* SC_GET_NEW_ROCKSTAR_MSG() { return invoke<const char*>(0xDF649C4E9AFDD788); }
	NATIVE_DECL BOOL SC_PRESENCE_ATTR_SET_INT(Hash attrHash, int value) { return invoke<BOOL>(0x1F1E9682483697C7, attrHash, value); }
	NATIVE_DECL BOOL SC_PRESENCE_ATTR_SET_FLOAT(Hash attrHash, float value) { return invoke<BOOL>(0xC4C4575F62534A24, attrHash, value); }
	NATIVE_DECL BOOL SC_PRESENCE_ATTR_SET_STRING(Hash attrHash, const char* value) { return invoke<BOOL>(0x287F1F75D2803595, attrHash, value); }
	NATIVE_DECL BOOL SC_PRESENCE_SET_ACTIVITY_RATING(Any p0, float p1) { return invoke<BOOL>(0x487912FD248EFDDF, p0, p1); }
	NATIVE_DECL BOOL SC_GAMERDATA_GET_INT(const char* name, int* value) { return invoke<BOOL>(0xC85A7127E7AD02AA, name, value); }
	NATIVE_DECL BOOL SC_GAMERDATA_GET_FLOAT(const char* name, float* value) { return invoke<BOOL>(0xA770C8EEC6FB2AC5, name, value); }
	NATIVE_DECL BOOL SC_GAMERDATA_GET_BOOL(const char* name) { return invoke<BOOL>(0x8416FE4E4629D7D7, name); }
	NATIVE_DECL BOOL SC_GAMERDATA_GET_STRING(const char* name, char* value) { return invoke<BOOL>(0x7FFCBFEE44ECFABF, name, value); }
	NATIVE_DECL BOOL SC_GAMERDATA_GET_ACTIVE_XP_BONUS(float* value) { return invoke<BOOL>(0x2D874D4AE612A65F, value); }
	NATIVE_DECL BOOL SC_PROFANITY_CHECK_STRING(const char* string, int* token) { return invoke<BOOL>(0x75632C5ECD7ED843, string, token); }
	NATIVE_DECL BOOL SC_PROFANITY_CHECK_STRING_UGC(const char* string, int* token) { return invoke<BOOL>(0xEB2BF817463DFA28, string, token); }
	NATIVE_DECL BOOL SC_PROFANITY_GET_CHECK_IS_VALID(int token) { return invoke<BOOL>(0x1753344C770358AE, token); }
	NATIVE_DECL BOOL SC_PROFANITY_GET_CHECK_IS_PENDING(int token) { return invoke<BOOL>(0x82E4A58BABC15AE7, token); }
	NATIVE_DECL BOOL SC_PROFANITY_GET_STRING_PASSED(int token) { return invoke<BOOL>(0x85535ACF97FC0969, token); }
	NATIVE_DECL int SC_PROFANITY_GET_STRING_STATUS(int token) { return invoke<int>(0x930DE22F07B1CCE3, token); }
	NATIVE_DECL BOOL SC_PROFANITY_GET_PROFANE_WORD(int token, char* outProfaneWord) { return invoke<BOOL>(0x75CC8931A11128C9, token, outProfaneWord); }
	NATIVE_DECL BOOL SC_LICENSEPLATE_CHECK_STRING(const char* p0, int* p1) { return invoke<BOOL>(0xF6BAAAF762E1BF40, p0, p1); }
	NATIVE_DECL BOOL SC_LICENSEPLATE_GET_CHECK_IS_VALID(Any p0) { return invoke<BOOL>(0xF22CA0FD74B80E7A, p0); }
	NATIVE_DECL BOOL SC_LICENSEPLATE_GET_CHECK_IS_PENDING(Any p0) { return invoke<BOOL>(0x9237E334F6E43156, p0); }
	NATIVE_DECL int SC_LICENSEPLATE_GET_COUNT(int token) { return invoke<int>(0x700569DBA175A77C, token); }
	NATIVE_DECL const char* SC_LICENSEPLATE_GET_PLATE(int token, int plateIndex) { return invoke<const char*>(0x1D4446A62D35B0D0, token, plateIndex); }
	NATIVE_DECL const char* SC_LICENSEPLATE_GET_PLATE_DATA(int token, int plateIndex) { return invoke<const char*>(0x2E89990DDFF670C3, token, plateIndex); }
	NATIVE_DECL BOOL SC_LICENSEPLATE_SET_PLATE_DATA(const char* oldPlateText, const char* newPlateText, Any* plateData) { return invoke<BOOL>(0xD0EE05FE193646EA, oldPlateText, newPlateText, plateData); }
	NATIVE_DECL BOOL SC_LICENSEPLATE_ADD(const char* plateText, Any* plateData, int* token) { return invoke<BOOL>(0x1989C6E6F67E76A8, plateText, plateData, token); }
	NATIVE_DECL BOOL SC_LICENSEPLATE_GET_ADD_IS_PENDING(int token) { return invoke<BOOL>(0x07C61676E5BB52CD, token); }
	NATIVE_DECL int SC_LICENSEPLATE_GET_ADD_STATUS(int token) { return invoke<int>(0x8147FFF6A718E1AD, token); }
	NATIVE_DECL BOOL SC_LICENSEPLATE_ISVALID(const char* plateText, int* token) { return invoke<BOOL>(0x0F73393BAC7E6730, plateText, token); }
	NATIVE_DECL BOOL SC_LICENSEPLATE_GET_ISVALID_IS_PENDING(int token) { return invoke<BOOL>(0xD302E99EDF0449CF, token); }
	NATIVE_DECL int SC_LICENSEPLATE_GET_ISVALID_STATUS(int token) { return invoke<int>(0x5C4EBFFA98BDB41C, token); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_IS_ACTIVE() { return invoke<BOOL>(0xFF8F3A92B75ED67A); }
	NATIVE_DECL int SC_COMMUNITY_EVENT_GET_EVENT_ID() { return invoke<int>(0x4ED9C8D6DA297639); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT(const char* p0, int* p1) { return invoke<BOOL>(0x710BCDA8071EDED1, p0, p1); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT(const char* p0, float* p1) { return invoke<BOOL>(0x50A8A36201DBF83E, p0, p1); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING(const char* p0, char* p1) { return invoke<BOOL>(0x9DE5D2F723575ED0, p0, p1); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_DISPLAY_NAME(char* p0) { return invoke<BOOL>(0xC2C97EA97711D1AE, p0); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_IS_ACTIVE_FOR_TYPE(const char* p0) { return invoke<BOOL>(0x450819D8CF90C416, p0); }
	NATIVE_DECL int SC_COMMUNITY_EVENT_GET_EVENT_ID_FOR_TYPE(const char* p0) { return invoke<int>(0x4A7D6E727F941747, p0); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_FOR_TYPE(const char* p0, int* p1, const char* p2) { return invoke<BOOL>(0xE75A4A2E5E316D86, p0, p1, p2); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_FOR_TYPE(const char* p0, float* p1, const char* p2) { return invoke<BOOL>(0x2570E26BE63964E3, p0, p1, p2); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_FOR_TYPE(const char* p0, char* p1, const char* p2) { return invoke<BOOL>(0x1D12A56FC95BE92E, p0, p1, p2); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_FOR_TYPE(char* p0, const char* p1) { return invoke<BOOL>(0x33DF47CC0642061B, p0, p1); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_IS_ACTIVE_BY_ID(int p0) { return invoke<BOOL>(0xA468E0BE12B12C70, p0); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_BY_ID(int p0, const char* p1, int* p2) { return invoke<BOOL>(0x8CC469AB4D349B7C, p0, p1, p2); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_BY_ID(int p0, const char* p1, float* p2) { return invoke<BOOL>(0xC5A35C73B68F3C49, p0, p1, p2); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_BY_ID(int p0, const char* p1, char* p2) { return invoke<BOOL>(0x699E4A5C8C893A18, p0, p1, p2); }
	NATIVE_DECL BOOL SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_BY_ID(int p0, char* p1) { return invoke<BOOL>(0x19853B5B17D77BCA, p0, p1); }
	NATIVE_DECL BOOL SC_TRANSITION_NEWS_SHOW(Any p0) { return invoke<BOOL>(0x6BFB12CE158E3DD4, p0); }
	NATIVE_DECL BOOL SC_TRANSITION_NEWS_SHOW_TIMED(Any p0, Any p1) { return invoke<BOOL>(0xFE4C1D0D3B9CC17E, p0, p1); }
	NATIVE_DECL BOOL SC_TRANSITION_NEWS_SHOW_NEXT_ITEM() { return invoke<BOOL>(0xD8122C407663B995); }
	NATIVE_DECL BOOL SC_TRANSITION_NEWS_HAS_EXTRA_DATA_TU() { return invoke<BOOL>(0x3001BEF2FECA3680); }
	NATIVE_DECL BOOL SC_TRANSITION_NEWS_GET_EXTRA_DATA_INT_TU(const char* p0, int* p1) { return invoke<BOOL>(0x92DA6E70EF249BD1, p0, p1); }
	NATIVE_DECL void SC_TRANSITION_NEWS_END() { invoke<Void>(0x675721C9F644D161); }
	NATIVE_DECL BOOL SC_PAUSE_NEWS_INIT_STARTER_PACK(Any p0) { return invoke<BOOL>(0xE4F6E8D07A2F0F51, p0); }
	NATIVE_DECL BOOL SC_PAUSE_NEWS_GET_PENDING_STORY(Any p0) { return invoke<BOOL>(0x8A4416C0DB05FA66, p0); }
	NATIVE_DECL void SC_PAUSE_NEWS_SHUTDOWN() { invoke<Void>(0xEA95C0853A27888E); }
	NATIVE_DECL const char* SC_ACCOUNT_INFO_GET_NICKNAME() { return invoke<const char*>(0x198D161F458ECC7F); }
	NATIVE_DECL BOOL SC_ACHIEVEMENT_INFO_STATUS(int* p0) { return invoke<BOOL>(0x225798743970412B, p0); }
	NATIVE_DECL BOOL SC_HAS_ACHIEVEMENT_BEEN_PASSED(int achievementId) { return invoke<BOOL>(0x418DC16FAE452C1C, achievementId); }
}

namespace STATS
{
	NATIVE_DECL BOOL STAT_CLEAR_SLOT_FOR_RELOAD(int statSlot) { return invoke<BOOL>(0xEB0A72181D4AA4AD, statSlot); }
	NATIVE_DECL BOOL STAT_LOAD(int statSlot) { return invoke<BOOL>(0xA651443F437B1CE6, statSlot); }
	NATIVE_DECL BOOL STAT_SAVE(int p0, BOOL p1, int p2, BOOL p3) { return invoke<BOOL>(0xE07BCA305B82D2FD, p0, p1, p2, p3); }
	NATIVE_DECL void STAT_SET_OPEN_SAVETYPE_IN_JOB(int p0) { invoke<Void>(0x5688585E6D563CD8, p0); }
	NATIVE_DECL BOOL STAT_LOAD_PENDING(int statSlot) { return invoke<BOOL>(0xA1750FFAFA181661, statSlot); }
	NATIVE_DECL BOOL STAT_SAVE_PENDING() { return invoke<BOOL>(0x7D3A583856F2C5AC); }
	NATIVE_DECL BOOL STAT_SAVE_PENDING_OR_REQUESTED() { return invoke<BOOL>(0xBBB6AD006F1BBEA3); }
	NATIVE_DECL BOOL STAT_DELETE_SLOT(int p0) { return invoke<BOOL>(0x49A49BED12794D70, p0); }
	NATIVE_DECL BOOL STAT_SLOT_IS_LOADED(int statSlot) { return invoke<BOOL>(0x0D0A9F0E7BD91E3C, statSlot); }
	NATIVE_DECL BOOL STAT_CLOUD_SLOT_LOAD_FAILED(int p0) { return invoke<BOOL>(0x7F2C4CDF2E82DF4C, p0); }
	NATIVE_DECL int STAT_CLOUD_SLOT_LOAD_FAILED_CODE(Any p0) { return invoke<int>(0xE496A53BA5F50A56, p0); }
	NATIVE_DECL void STAT_SET_BLOCK_SAVES(BOOL toggle) { invoke<Void>(0xF434A10BA01C37D0, toggle); }
	NATIVE_DECL BOOL STAT_GET_BLOCK_SAVES() { return invoke<BOOL>(0x6A7F19756F1A9016); }
	NATIVE_DECL BOOL STAT_CLOUD_SLOT_SAVE_FAILED(Any p0) { return invoke<BOOL>(0x7E6946F68A38B74F, p0); }
	NATIVE_DECL void STAT_CLEAR_PENDING_SAVES(Any p0) { invoke<Void>(0xA8733668D1047B51, p0); }
	NATIVE_DECL BOOL STAT_LOAD_DIRTY_READ_DETECTED() { return invoke<BOOL>(0xECB41AC6AB754401); }
	NATIVE_DECL void STAT_CLEAR_DIRTY_READ_DETECTED() { invoke<Void>(0x9B4BD21D69B1E609); }
	NATIVE_DECL BOOL STAT_GET_LOAD_SAFE_TO_PROGRESS_TO_MP_FROM_SP() { return invoke<BOOL>(0xC0E0D686DDFC6EAE); }
	NATIVE_DECL Hash _GET_STAT_HASH_FOR_CHARACTER_STAT(int dataType, int statIndex, int charSlot) { return invoke<Hash>(0xD69CE161FE614531, dataType, statIndex, charSlot); }
	NATIVE_DECL BOOL STAT_SET_INT(Hash statName, int value, BOOL save) { return invoke<BOOL>(0xB3271D7AB655B441, statName, value, save); }
	NATIVE_DECL BOOL STAT_SET_FLOAT(Hash statName, float value, BOOL save) { return invoke<BOOL>(0x4851997F37FE9B3C, statName, value, save); }
	NATIVE_DECL BOOL STAT_SET_BOOL(Hash statName, BOOL value, BOOL save) { return invoke<BOOL>(0x4B33C4243DE0C432, statName, value, save); }
	NATIVE_DECL BOOL STAT_SET_GXT_LABEL(Hash statName, const char* value, BOOL save) { return invoke<BOOL>(0x17695002FD8B2AE0, statName, value, save); }
	NATIVE_DECL BOOL STAT_SET_DATE(Hash statName, Any* value, int numFields, BOOL save) { return invoke<BOOL>(0x2C29BFB64F4FCBE4, statName, value, numFields, save); }
	NATIVE_DECL BOOL STAT_SET_STRING(Hash statName, const char* value, BOOL save) { return invoke<BOOL>(0xA87B2335D12531D7, statName, value, save); }
	NATIVE_DECL BOOL STAT_SET_POS(Hash statName, float x, float y, float z, BOOL save) { return invoke<BOOL>(0xDB283FDE680FE72E, statName, x, y, z, save); }
	NATIVE_DECL BOOL STAT_SET_MASKED_INT(Hash statName, int p1, int p2, int p3, BOOL save) { return invoke<BOOL>(0x7BBB1B54583ED410, statName, p1, p2, p3, save); }
	NATIVE_DECL BOOL STAT_SET_USER_ID(Hash statName, const char* value, BOOL save) { return invoke<BOOL>(0x8CDDF1E452BABE11, statName, value, save); }
	NATIVE_DECL BOOL STAT_SET_CURRENT_POSIX_TIME(Hash statName, BOOL p1) { return invoke<BOOL>(0xC2F84B7F9C4D0C61, statName, p1); }
	NATIVE_DECL BOOL STAT_GET_INT(Hash statHash, int* outValue, int p2) { return invoke<BOOL>(0x767FBC2AC802EF3D, statHash, outValue, p2); }
	NATIVE_DECL BOOL STAT_GET_FLOAT(Hash statHash, float* outValue, Any p2) { return invoke<BOOL>(0xD7AE6C9C9C6AC54C, statHash, outValue, p2); }
	NATIVE_DECL BOOL STAT_GET_BOOL(Hash statHash, BOOL* outValue, Any p2) { return invoke<BOOL>(0x11B5E6D2AE73F48E, statHash, outValue, p2); }
	NATIVE_DECL BOOL STAT_GET_DATE(Hash statHash, Any* outValue, int numFields, Any p3) { return invoke<BOOL>(0x8B0FACEFC36C824B, statHash, outValue, numFields, p3); }
	NATIVE_DECL const char* STAT_GET_STRING(Hash statHash, int p1) { return invoke<const char*>(0xE50384ACC2C3DB74, statHash, p1); }
	NATIVE_DECL BOOL STAT_GET_POS(Hash statName, float* outX, float* outY, float* outZ, Any p4) { return invoke<BOOL>(0x350F82CCB186AA1B, statName, outX, outY, outZ, p4); }
	NATIVE_DECL BOOL STAT_GET_MASKED_INT(Hash statHash, int* outValue, int p2, int p3, Any p4) { return invoke<BOOL>(0x655185A06D9EEAAB, statHash, outValue, p2, p3, p4); }
	NATIVE_DECL const char* STAT_GET_USER_ID(Hash statHash) { return invoke<const char*>(0x2365C388E393BBE2, statHash); }
	NATIVE_DECL const char* STAT_GET_LICENSE_PLATE(Hash statName) { return invoke<const char*>(0x5473D4195058B2E4, statName); }
	NATIVE_DECL BOOL STAT_SET_LICENSE_PLATE(Hash statName, const char* str) { return invoke<BOOL>(0x69FF13266D7296DA, statName, str); }
	NATIVE_DECL void STAT_INCREMENT(Hash statName, float value) { invoke<Void>(0x9B5A68C6489E9909, statName, value); }
	NATIVE_DECL BOOL STAT_COMMUNITY_START_SYNCH() { return invoke<BOOL>(0x5A556B229A169402); }
	NATIVE_DECL BOOL STAT_COMMUNITY_SYNCH_IS_PENDING() { return invoke<BOOL>(0xB1D2BB1E1631F5B1); }
	NATIVE_DECL BOOL STAT_COMMUNITY_GET_HISTORY(Hash statName, int p1, float* outValue) { return invoke<BOOL>(0xBED9F5693F34ED17, statName, p1, outValue); }
	NATIVE_DECL void STAT_RESET_ALL_ONLINE_CHARACTER_STATS(int p0) { invoke<Void>(0x26D7399B9587FE89, p0); }
	NATIVE_DECL void STAT_LOCAL_RESET_ALL_ONLINE_CHARACTER_STATS(int p0) { invoke<Void>(0xA78B8FA58200DA56, p0); }
	NATIVE_DECL int STAT_GET_NUMBER_OF_DAYS(Hash statName) { return invoke<int>(0xE0E854F5280FB769, statName); }
	NATIVE_DECL int STAT_GET_NUMBER_OF_HOURS(Hash statName) { return invoke<int>(0xF2D4B2FE415AAFC3, statName); }
	NATIVE_DECL int STAT_GET_NUMBER_OF_MINUTES(Hash statName) { return invoke<int>(0x7583B4BE4C5A41B5, statName); }
	NATIVE_DECL int STAT_GET_NUMBER_OF_SECONDS(Hash statName) { return invoke<int>(0x2CE056FF3723F00B, statName); }
	NATIVE_DECL void STAT_SET_PROFILE_SETTING_VALUE(int profileSetting, int value) { invoke<Void>(0x68F01422BE1D838F, profileSetting, value); }
	NATIVE_DECL void STATS_COMPLETED_CHARACTER_CREATION(Any p0) { invoke<Void>(0xC01D2470F22CDE5A, p0); }
	NATIVE_DECL int PACKED_STAT_GET_INT_STAT_INDEX(int p0) { return invoke<int>(0x94F12ABF9C79E339, p0); }
	NATIVE_DECL Hash GET_PACKED_INT_STAT_KEY(int index, BOOL spStat, BOOL charStat, int character) { return invoke<Hash>(0x61E111E323419E07, index, spStat, charStat, character); }
	NATIVE_DECL Hash GET_PACKED_TU_INT_STAT_KEY(int index, BOOL spStat, BOOL charStat, int character) { return invoke<Hash>(0xD16C2AD6B8E32854, index, spStat, charStat, character); }
	NATIVE_DECL Hash GET_PACKED_NG_INT_STAT_KEY(int index, BOOL spStat, BOOL charStat, int character, const char* section) { return invoke<Hash>(0x2B4CDCA6F07FF3DA, index, spStat, charStat, character, section); }
	NATIVE_DECL BOOL GET_PACKED_STAT_BOOL_CODE(int index, int characterSlot) { return invoke<BOOL>(0xDA7EBFC49AE3F1B0, index, characterSlot); }
	NATIVE_DECL int GET_PACKED_STAT_INT_CODE(int index, int characterSlot) { return invoke<int>(0x0BC900A6FE73770C, index, characterSlot); }
	NATIVE_DECL void SET_PACKED_STAT_BOOL_CODE(int index, BOOL value, int characterSlot) { invoke<Void>(0xDB8A58AEAA67CD07, index, value, characterSlot); }
	NATIVE_DECL void SET_PACKED_STAT_INT_CODE(int index, int value, int characterSlot) { invoke<Void>(0x1581503AE529CD2E, index, value, characterSlot); }
	NATIVE_DECL void PLAYSTATS_BACKGROUND_SCRIPT_ACTION(const char* action, int value) { invoke<Void>(0x5009DFD741329729, action, value); }
	NATIVE_DECL void _PLAYSTATS_FLOW_LOW(float posX, float posY, float posZ, const char* action, BOOL p4, int p5) { invoke<Void>(0xE6A27CDA42887F93, posX, posY, posZ, action, p4, p5); }
	NATIVE_DECL void _PLAYSTATS_FLOW_MEDIUM(float posX, float posY, float posZ, const char* action, BOOL p4, int p5) { invoke<Void>(0xC4493521BAA12CCE, posX, posY, posZ, action, p4, p5); }
	NATIVE_DECL void _PLAYSTATS_FLOW_HIGH(float posX, float posY, float posZ, const char* action, BOOL p4, int p5) { invoke<Void>(0xCFB0E9C3456319EA, posX, posY, posZ, action, p4, p5); }
	NATIVE_DECL void PLAYSTATS_NPC_INVITE(const char* p0) { invoke<Void>(0x93054C88E6AA7C44, p0); }
	NATIVE_DECL void PLAYSTATS_AWARD_XP(int amount, Hash type, Hash category) { invoke<Void>(0x46F917F6B4128FE4, amount, type, category); }
	NATIVE_DECL void PLAYSTATS_RANK_UP(int rank) { invoke<Void>(0xC7F2DE41D102BFB4, rank); }
	NATIVE_DECL void PLAYSTATS_STARTED_SESSION_IN_OFFLINEMODE() { invoke<Void>(0x098760C7461724CD); }
	NATIVE_DECL void PLAYSTATS_ACTIVITY_DONE(int p0, int activityId, Any p2) { invoke<Void>(0xA071E0ED98F91286, p0, activityId, p2); }
	NATIVE_DECL void PLAYSTATS_LEAVE_JOB_CHAIN(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xC5BE134EC7BA96A0, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_MISSION_STARTED(const char* p0, Any p1, Any p2, BOOL p3) { invoke<Void>(0xC19A2925C34D2231, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_MISSION_OVER(const char* p0, Any p1, Any p2, BOOL p3, BOOL p4, BOOL p5) { invoke<Void>(0x7C4BB33A8CED7324, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL void PLAYSTATS_MISSION_CHECKPOINT(const char* p0, Any p1, Any p2, Any p3) { invoke<Void>(0xC900596A63978C1D, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_RANDOM_MISSION_DONE(const char* name, Any p1, Any p2, Any p3) { invoke<Void>(0x71862B1D855F32E1, name, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_ROS_BET(int amount, int act, Player player, float cm) { invoke<Void>(0x121FB4DDDC2D5291, amount, act, player, cm); }
	NATIVE_DECL void PLAYSTATS_RACE_CHECKPOINT(Vehicle p0, Any p1, int p2, int p3, Any p4) { invoke<Void>(0x9C375C315099DDE4, p0, p1, p2, p3, p4); }
	NATIVE_DECL BOOL PLAYSTATS_CREATE_MATCH_HISTORY_ID_2(int* playerAccountId, int* posixTime) { return invoke<BOOL>(0x6DEE77AFF8C21BD1, playerAccountId, posixTime); }
	NATIVE_DECL void PLAYSTATS_MATCH_STARTED(Any p0, Any p1, Any p2) { invoke<Void>(0xBC80E22DED931E3D, p0, p1, p2); }
	NATIVE_DECL void PLAYSTATS_SHOP_ITEM(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x176852ACAAC173D1, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_CRATE_DROP_MISSION_DONE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x1CAE5D2E3F9A07F0, p0, p1, p2, p3, p4, p5, p6, p7); }
	NATIVE_DECL void PLAYSTATS_CRATE_CREATED(float p0, float p1, float p2) { invoke<Void>(0xAFC7E5E075A96F46, p0, p1, p2); }
	NATIVE_DECL void PLAYSTATS_HOLD_UP_MISSION_DONE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCB00196B31C39EB1, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_IMPORT_EXPORT_MISSION_DONE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x2B69F5074C894811, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_RACE_TO_POINT_MISSION_DONE(int p0, Any p1, Any p2, Any p3) { invoke<Void>(0xADDD1C754E2E2914, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_ACQUIRED_HIDDEN_PACKAGE(Any p0) { invoke<Void>(0x79AB33F0FBFAC40C, p0); }
	NATIVE_DECL void PLAYSTATS_WEBSITE_VISITED(Hash scaleformHash, int p1) { invoke<Void>(0xDDF24D535060F811, scaleformHash, p1); }
	NATIVE_DECL void PLAYSTATS_FRIEND_ACTIVITY(int p0, BOOL p1) { invoke<Void>(0x0F71DE29AB2258F1, p0, p1); }
	NATIVE_DECL void PLAYSTATS_ODDJOB_DONE(int totalTimeMs, int p1, BOOL p2) { invoke<Void>(0x69DEA3E9DB727B4C, totalTimeMs, p1, p2); }
	NATIVE_DECL void PLAYSTATS_PROP_CHANGE(Ped p0, int p1, int p2, int p3) { invoke<Void>(0xBA739D6D5A05D6E7, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_CLOTH_CHANGE(Ped p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x34B973047A2268B9, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_WEAPON_MODE_CHANGE(Hash weaponHash, Hash componentHashTo, Hash componentHashFrom) { invoke<Void>(0xE95C8A1875A02CA4, weaponHash, componentHashTo, componentHashFrom); }
	NATIVE_DECL void PLAYSTATS_CHEAT_APPLIED(const char* cheat) { invoke<Void>(0x6058665D72302D3F, cheat); }
	NATIVE_DECL void PLAYSTATS_JOB_ACTIVITY_END(Any* p0, Any* p1, Any* p2, Any* p3) { invoke<Void>(0xF8C54A461C3E11DC, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_JOB_BEND(Any* p0, Any* p1, Any* p2, Any* p3) { invoke<Void>(0xF5BB8DAC426A52C0, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_JOB_LTS_END(Any* p0, Any* p1, Any* p2, Any* p3) { invoke<Void>(0xA736CF7FB7C5BFF4, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_JOB_LTS_ROUND_END(Any* p0, Any* p1, Any* p2, Any* p3) { invoke<Void>(0x14E0B2D1AD1044E0, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_QUICKFIX_TOOL(int element, const char* item) { invoke<Void>(0x90D0622866E80445, element, item); }
	NATIVE_DECL void PLAYSTATS_IDLE_KICK(int msStoodIdle) { invoke<Void>(0x5DA3A8DE8CB6226F, msStoodIdle); }
	NATIVE_DECL void PLAYSTATS_SET_JOIN_TYPE(int joinType) { invoke<Void>(0xD1032E482629049E, joinType); }
	NATIVE_DECL void PLAYSTATS_HEIST_SAVE_CHEAT(Hash hash, int p1) { invoke<Void>(0xF4FF020A08BC8863, hash, p1); }
	NATIVE_DECL void PLAYSTATS_APPEND_DIRECTOR_METRIC(Any* p0) { invoke<Void>(0x46326E13DA4E0546, p0); }
	NATIVE_DECL void PLAYSTATS_AWARD_BAD_SPORT(int id) { invoke<Void>(0x47B32F5611E6E483, id); }
	NATIVE_DECL void PLAYSTATS_PEGASUS_AS_PERSONAL_AIRCRAFT(Hash modelHash) { invoke<Void>(0x9572BD4DD6B72122, modelHash); }
	NATIVE_DECL void _PLAYSTATS_SHOPMENU_NAV(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF96E9EA876D9DC92, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_CHALLENGES(Any p0) { invoke<Void>(0x6A60E43998228229, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_VEHICLETARGET(Any p0) { invoke<Void>(0xBFAFDB5FAAA5C5AB, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_URBANWARFARE(Any p0) { invoke<Void>(0x8C9D11605E59D955, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_CHECKPOINTCOLLECTION(Any p0) { invoke<Void>(0x3DE3AA516FB126A4, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_ATOB(Any p0) { invoke<Void>(0xBAA2F0490E146BE8, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_PENNEDIN(Any p0) { invoke<Void>(0x1A7CE7CD3E653485, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_PASSTHEPARCEL(Any p0) { invoke<Void>(0x419615486BBF1956, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_HOTPROPERTY(Any p0) { invoke<Void>(0x84DFC579C2FC214C, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_DEADDROP(Any p0) { invoke<Void>(0x0A9C7F36E5D7B683, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_KINGOFTHECASTLE(Any p0) { invoke<Void>(0x164C5FF663790845, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_CRIMINALDAMAGE(Any p0) { invoke<Void>(0xEDBF6C9B0D2C65C8, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_COMPETITIVEURBANWARFARE(Any p0) { invoke<Void>(0x6551B1F7F6CD46EA, p0); }
	NATIVE_DECL void PLAYSTATS_FM_EVENT_HUNTBEAST(Any p0) { invoke<Void>(0x2CD90358F67D0AA8, p0); }
	NATIVE_DECL void PLAYSTATS_PIMENU_HIDE_OPTIONS(Any* data) { invoke<Void>(0x203B381133817079, data); }
	NATIVE_DECL void _PLAYSTATS_NAMED_USER_CONTENT(BOOL isBoss, int bossType, int bossId1, int bossId2, int textType, const char* textString, int textSource) { invoke<Void>(0xAA434D7D0A89A95C, isBoss, bossType, bossId1, bossId2, textType, textString, textSource); }
	NATIVE_DECL int LEADERBOARDS_GET_NUMBER_OF_COLUMNS(int p0, Any p1) { return invoke<int>(0x117B45156D7EFF2E, p0, p1); }
	NATIVE_DECL int LEADERBOARDS_GET_COLUMN_ID(int p0, int p1, int p2) { return invoke<int>(0xC4B5467A1886EA7E, p0, p1, p2); }
	NATIVE_DECL int LEADERBOARDS_GET_COLUMN_TYPE(int p0, Any p1, Any p2) { return invoke<int>(0xBF4FEF46DB7894D3, p0, p1, p2); }
	NATIVE_DECL int LEADERBOARDS_READ_CLEAR_ALL() { return invoke<int>(0xA34CB6E6F0DF4A0B); }
	NATIVE_DECL int LEADERBOARDS_READ_CLEAR(Any p0, Any p1, Any p2) { return invoke<int>(0x7CCE5C737A665701, p0, p1, p2); }
	NATIVE_DECL BOOL LEADERBOARDS_READ_PENDING(Any p0, Any p1, Any p2) { return invoke<BOOL>(0xAC392C8483342AC2, p0, p1, p2); }
	NATIVE_DECL BOOL LEADERBOARDS_READ_ANY_PENDING() { return invoke<BOOL>(0xA31FD15197B192BD); }
	NATIVE_DECL BOOL LEADERBOARDS_READ_SUCCESSFUL(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x2FB19228983E832C, p0, p1, p2); }
	NATIVE_DECL BOOL LEADERBOARDS2_READ_FRIENDS_BY_ROW(Any* p0, Any* p1, Any p2, BOOL p3, Any p4, Any p5) { return invoke<BOOL>(0x918B101666F9CB83, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL BOOL LEADERBOARDS2_READ_BY_HANDLE(Any* p0, Any* p1) { return invoke<BOOL>(0xC30713A383BFBF0E, p0, p1); }
	NATIVE_DECL BOOL LEADERBOARDS2_READ_BY_RANK(Any* p0, Any p1, Any p2) { return invoke<BOOL>(0xBA2C7DB0C129449A, p0, p1, p2); }
	NATIVE_DECL BOOL LEADERBOARDS2_READ_BY_RADIUS(Any* p0, Any p1, Any* p2) { return invoke<BOOL>(0x5CE587FB5A42C8C4, p0, p1, p2); }
	NATIVE_DECL BOOL LEADERBOARDS2_READ_BY_SCORE_INT(Any* p0, Any p1, Any p2) { return invoke<BOOL>(0x7EEC7E4F6984A16A, p0, p1, p2); }
	NATIVE_DECL BOOL LEADERBOARDS2_READ_BY_SCORE_FLOAT(Any* p0, float p1, Any p2) { return invoke<BOOL>(0xE662C8B759D08F3C, p0, p1, p2); }
	NATIVE_DECL BOOL LEADERBOARDS2_READ_RANK_PREDICTION(Any* p0, Any* p1, Any* p2) { return invoke<BOOL>(0xC38DC1E90D22547C, p0, p1, p2); }
	NATIVE_DECL BOOL LEADERBOARDS2_READ_BY_PLAFORM(Any* p0, const char* gamerHandleCsv, const char* platformName) { return invoke<BOOL>(0xF1AE5DCDBFCA2721, p0, gamerHandleCsv, platformName); }
	NATIVE_DECL BOOL LEADERBOARDS2_READ_GET_ROW_DATA_START(Any* p0) { return invoke<BOOL>(0xA0F93D5465B3094D, p0); }
	NATIVE_DECL void LEADERBOARDS2_READ_GET_ROW_DATA_END() { invoke<Void>(0x71B008056E5692D6); }
	NATIVE_DECL BOOL LEADERBOARDS2_READ_GET_ROW_DATA_INFO(Any p0, Any* p1) { return invoke<BOOL>(0x34770B9CE0E03B91, p0, p1); }
	NATIVE_DECL int LEADERBOARDS2_READ_GET_ROW_DATA_INT(Any p0, Any p1) { return invoke<int>(0x88578F6EC36B4A3A, p0, p1); }
	NATIVE_DECL float LEADERBOARDS2_READ_GET_ROW_DATA_FLOAT(Any p0, Any p1) { return invoke<float>(0x38491439B6BA7F7D, p0, p1); }
	NATIVE_DECL BOOL LEADERBOARDS2_WRITE_DATA(Any* p0) { return invoke<BOOL>(0xAE2206545888AE49, p0); }
	NATIVE_DECL void LEADERBOARDS_WRITE_ADD_COLUMN(Any p0, Any p1, float p2) { invoke<Void>(0x0BCA1D2C47B0D269, p0, p1, p2); }
	NATIVE_DECL void LEADERBOARDS_WRITE_ADD_COLUMN_LONG(Any p0, Any p1, Any p2) { invoke<Void>(0x2E65248609523599, p0, p1, p2); }
	NATIVE_DECL BOOL LEADERBOARDS_CACHE_DATA_ROW(Any* p0) { return invoke<BOOL>(0xB9BB18E2C40142ED, p0); }
	NATIVE_DECL void LEADERBOARDS_CLEAR_CACHE_DATA() { invoke<Void>(0xD4B02A6B476E1FDC); }
	NATIVE_DECL void LEADERBOARDS_CLEAR_CACHE_DATA_ID(Any p0) { invoke<Void>(0x8EC74CEB042E7CFF, p0); }
	NATIVE_DECL BOOL LEADERBOARDS_GET_CACHE_EXISTS(Any p0) { return invoke<BOOL>(0x9C51349BE6CDFE2C, p0); }
	NATIVE_DECL int LEADERBOARDS_GET_CACHE_TIME(Any p0) { return invoke<int>(0xF04C1C27DA35F6C8, p0); }
	NATIVE_DECL int LEADERBOARDS_GET_CACHE_NUMBER_OF_ROWS(Any p0) { return invoke<int>(0x58A651CD201D89AD, p0); }
	NATIVE_DECL BOOL LEADERBOARDS_GET_CACHE_DATA_ROW(Any p0, Any p1, Any* p2) { return invoke<BOOL>(0x9120E8DBA3D69273, p0, p1, p2); }
	NATIVE_DECL void PRESENCE_EVENT_UPDATESTAT_INT(Hash statHash, int value, int p2) { invoke<Void>(0x11FF1C80276097ED, statHash, value, p2); }
	NATIVE_DECL void PRESENCE_EVENT_UPDATESTAT_FLOAT(Hash statHash, float value, int p2) { invoke<Void>(0x30A6614C1F7799B8, statHash, value, p2); }
	NATIVE_DECL void PRESENCE_EVENT_UPDATESTAT_INT_WITH_STRING(Hash statHash, int value, int p2, const char* string) { invoke<Void>(0x6483C25849031C4F, statHash, value, p2, string); }
	NATIVE_DECL BOOL GET_PLAYER_HAS_DRIVEN_ALL_VEHICLES() { return invoke<BOOL>(0x5EAD2BF6484852E4); }
	NATIVE_DECL void SET_HAS_POSTED_ALL_VEHICLES_DRIVEN() { invoke<Void>(0xC141B8917E0017EC); }
	NATIVE_DECL void SET_PROFILE_SETTING_PROLOGUE_COMPLETE() { invoke<Void>(0xB475F27C6A994D65); }
	NATIVE_DECL void SET_PROFILE_SETTING_SP_CHOP_MISSION_COMPLETE() { invoke<Void>(0xC67E2DA1CBE759E2); }
	NATIVE_DECL void SET_PROFILE_SETTING_CREATOR_RACES_DONE(int value) { invoke<Void>(0xF1A1803D3476F215, value); }
	NATIVE_DECL void SET_PROFILE_SETTING_CREATOR_DM_DONE(int value) { invoke<Void>(0x38BAAA5DD4C9D19F, value); }
	NATIVE_DECL void SET_PROFILE_SETTING_CREATOR_CTF_DONE(int value) { invoke<Void>(0x55384438FC55AD8E, value); }
	NATIVE_DECL void SET_JOB_ACTIVITY_ID_STARTED(Any p0, int characterSlot) { invoke<Void>(0x723C1CE13FBFDB67, p0, characterSlot); }
	NATIVE_DECL void SET_FREEMODE_PROLOGUE_DONE(Any p0, int characterSlot) { invoke<Void>(0x0D01D20616FC73FB, p0, characterSlot); }
	NATIVE_DECL void SET_FREEMODE_STRAND_PROGRESSION_STATUS(int profileSetting, int settingValue) { invoke<Void>(0x79D310A861697CC9, profileSetting, settingValue); }
	NATIVE_DECL void STAT_NETWORK_INCREMENT_ON_SUICIDE(Any p0, float p1) { invoke<Void>(0x428EAF89E24F6C36, p0, p1); }
	NATIVE_DECL void STAT_SET_CHEAT_IS_ACTIVE() { invoke<Void>(0x047CBED6F6F8B63C); }
	NATIVE_DECL BOOL LEADERBOARDS2_WRITE_DATA_FOR_EVENT_TYPE(Any* p0, Any* p1) { return invoke<BOOL>(0xC980E62E33DF1D5C, p0, p1); }
	NATIVE_DECL void FORCE_CLOUD_MP_STATS_DOWNLOAD_AND_OVERWRITE_LOCAL_SAVE() { invoke<Void>(0x6F361B8889A792A3); }
	NATIVE_DECL void STAT_MIGRATE_CLEAR_FOR_RESTART() { invoke<Void>(0xC847B43F369AC0B5); }
	NATIVE_DECL BOOL STAT_MIGRATE_SAVEGAME_START(const char* platformName) { return invoke<BOOL>(0xA5C80D8E768A9E66, platformName); }
	NATIVE_DECL int STAT_MIGRATE_SAVEGAME_GET_STATUS() { return invoke<int>(0x9A62EC95AE10E011); }
	NATIVE_DECL BOOL STAT_MIGRATE_CHECK_ALREADY_DONE() { return invoke<BOOL>(0x4C89FE2BDEB3F169); }
	NATIVE_DECL BOOL STAT_MIGRATE_CHECK_START() { return invoke<BOOL>(0xC6E0E2616A7576BB); }
	NATIVE_DECL int STAT_MIGRATE_CHECK_GET_IS_PLATFORM_AVAILABLE(int p0) { return invoke<int>(0x5BD5F255321C4AAF, p0); }
	NATIVE_DECL int STAT_MIGRATE_CHECK_GET_PLATFORM_STATUS(int p0, Any* p1) { return invoke<int>(0xDEAAF77EB3687E97, p0, p1); }
	NATIVE_DECL int STAT_GET_SAVE_MIGRATION_STATUS(Any* data) { return invoke<int>(0x886913BBEACA68C1, data); }
	NATIVE_DECL BOOL STAT_SAVE_MIGRATION_CANCEL_PENDING_OPERATION() { return invoke<BOOL>(0x4FEF53183C3C6414); }
	NATIVE_DECL int STAT_GET_CANCEL_SAVE_MIGRATION_STATUS() { return invoke<int>(0x567384DFA67029E6); }
	NATIVE_DECL BOOL STAT_SAVE_MIGRATION_CONSUME_CONTENT(Hash contentId, const char* srcPlatform, const char* srcGamerHandle) { return invoke<BOOL>(0x3270F67EED31FBC1, contentId, srcPlatform, srcGamerHandle); }
	NATIVE_DECL int STAT_GET_SAVE_MIGRATION_CONSUME_CONTENT_STATUS(int* p0) { return invoke<int>(0xCE5AA445ABA8DEE0, p0); }
	NATIVE_DECL void STAT_ENABLE_STATS_TRACKING() { invoke<Void>(0x98E2BC1CA26287C3); }
	NATIVE_DECL void STAT_DISABLE_STATS_TRACKING() { invoke<Void>(0x629526ABA383BCAA); }
	NATIVE_DECL BOOL STAT_IS_STATS_TRACKING_ENABLED() { return invoke<BOOL>(0xBE3DB208333D9844); }
	NATIVE_DECL BOOL STAT_START_RECORD_STAT(int statType, int valueType) { return invoke<BOOL>(0x33D72899E24C3365, statType, valueType); }
	NATIVE_DECL BOOL STAT_STOP_RECORD_STAT() { return invoke<BOOL>(0xA761D4AC6115623D); }
	NATIVE_DECL BOOL STAT_GET_RECORDED_VALUE(float* value) { return invoke<BOOL>(0xF11F01D98113536A, value); }
	NATIVE_DECL BOOL STAT_IS_RECORDING_STAT() { return invoke<BOOL>(0x8B9CDBD6C566C38C); }
	NATIVE_DECL int STAT_GET_CURRENT_NEAR_MISS_NOCRASH_PRECISE() { return invoke<int>(0xE8853FBCE7D8D0D6); }
	NATIVE_DECL float STAT_GET_CURRENT_REAR_WHEEL_DISTANCE() { return invoke<float>(0xA943FD1722E11EFD); }
	NATIVE_DECL float STAT_GET_CURRENT_FRONT_WHEEL_DISTANCE() { return invoke<float>(0x84A810B375E69C0E); }
	NATIVE_DECL float STAT_GET_CURRENT_JUMP_DISTANCE() { return invoke<float>(0x9EC8858184CD253A); }
	NATIVE_DECL float STAT_GET_CURRENT_DRIVE_NOCRASH_DISTANCE() { return invoke<float>(0xBA9749CC94C1FD85); }
	NATIVE_DECL float STAT_GET_CURRENT_SPEED() { return invoke<float>(0x55A8BECAF28A4EB7); }
	NATIVE_DECL float STAT_GET_CURRENT_DRIVING_REVERSE_DISTANCE() { return invoke<float>(0x32CAC93C9DE73D32); }
	NATIVE_DECL float STAT_GET_CURRENT_SKYDIVING_DISTANCE() { return invoke<float>(0xAFF47709F1D5DCCE); }
	NATIVE_DECL float STAT_GET_CHALLENGE_FLYING_DIST() { return invoke<float>(0x6E0A5253375C4584); }
	NATIVE_DECL BOOL STAT_GET_FLYING_ALTITUDE(float* outValue) { return invoke<BOOL>(0x1A8EA222F9C67DBB, outValue); }
	NATIVE_DECL BOOL STAT_IS_PLAYER_VEHICLE_ABOVE_OCEAN() { return invoke<BOOL>(0xF9F2922717B819EC); }
	NATIVE_DECL float STAT_GET_VEHICLE_BAIL_DISTANCE() { return invoke<float>(0x0B8B7F74BF061C6D); }
	NATIVE_DECL BOOL STAT_ROLLBACK_SAVE_MIGRATION() { return invoke<BOOL>(0xB3DA2606774A8E2D); }
	NATIVE_DECL void SET_HAS_SPECIALEDITION_CONTENT(int value) { invoke<Void>(0xDAC073C7901F9E15, value); }
	NATIVE_DECL void SET_SAVE_MIGRATION_TRANSACTION_ID_WARNING(int transactionId) { invoke<Void>(0xF6792800AC95350D, transactionId); }
	NATIVE_DECL void GET_BOSS_GOON_UUID(int characterSlot, Any p1, Any p2) { invoke<Void>(0x6BC0ACD0673ACEBE, characterSlot, p1, p2); }
	NATIVE_DECL void PLAYSTATS_BW_BOSSONBOSSDEATHMATCH(Any p0) { invoke<Void>(0x8D8ADB562F09A245, p0); }
	NATIVE_DECL void PLAYSTATS_BW_YATCHATTACK(Any p0) { invoke<Void>(0xD1A1EE3B4FA8E760, p0); }
	NATIVE_DECL void PLAYSTATS_BW_HUNT_THE_BOSS(Any p0) { invoke<Void>(0x88087EE1F28024AE, p0); }
	NATIVE_DECL void PLAYSTATS_BW_SIGHTSEER(Any p0) { invoke<Void>(0xFCC228E07217FCAC, p0); }
	NATIVE_DECL void PLAYSTATS_BW_ASSAULT(Any p0) { invoke<Void>(0x678F86D8FC040BDB, p0); }
	NATIVE_DECL void PLAYSTATS_BW_BELLY_OF_THE_BEAST(Any p0) { invoke<Void>(0xA6F54BB2FFCA35EA, p0); }
	NATIVE_DECL void PLAYSTATS_BW_HEAD_HUNTER(Any p0) { invoke<Void>(0x5FF2C33B13A02A11, p0); }
	NATIVE_DECL void PLAYSTATS_BW_FRAGILE_GOODS(Any p0) { invoke<Void>(0x282B6739644F4347, p0); }
	NATIVE_DECL void PLAYSTATS_BW_AIR_FREIGHT(Any p0) { invoke<Void>(0xF06A6F41CB445443, p0); }
	NATIVE_DECL void PLAYSTATS_BC_CAR_JACKING(Any p0) { invoke<Void>(0x7B18DA61F6BAE9D5, p0); }
	NATIVE_DECL void PLAYSTATS_BC_SMASH_AND_GRAB(Any p0) { invoke<Void>(0x06EAF70AE066441E, p0); }
	NATIVE_DECL void PLAYSTATS_BC_PROTECTION_RACKET(Any p0) { invoke<Void>(0x14EDA9EE27BD1626, p0); }
	NATIVE_DECL void PLAYSTATS_BC_MOST_WANTED(Any p0) { invoke<Void>(0x930F504203F561C9, p0); }
	NATIVE_DECL void PLAYSTATS_BC_FINDERS_KEEPERS(Any p0) { invoke<Void>(0xE3261D791EB44ACB, p0); }
	NATIVE_DECL void PLAYSTATS_BC_POINT_TO_POINT(Any p0) { invoke<Void>(0x73001E34F85137F8, p0); }
	NATIVE_DECL void PLAYSTATS_BC_CASHING(Any p0) { invoke<Void>(0x53CAE13E9B426993, p0); }
	NATIVE_DECL void PLAYSTATS_BC_SALVAGE(Any p0) { invoke<Void>(0x7D36291161859389, p0); }
	NATIVE_DECL void PLAYSTATS_SPENT_PI_CUSTOM_LOADOUT(int amount) { invoke<Void>(0xBE509B0A3693DE8B, amount); }
	NATIVE_DECL void PLAYSTATS_BUY_CONTRABAND_MISSION(Any* data) { invoke<Void>(0xD6781E42755531F7, data); }
	NATIVE_DECL void PLAYSTATS_SELL_CONTRABAND_MISSION(Any* data) { invoke<Void>(0xC729991A9065376E, data); }
	NATIVE_DECL void PLAYSTATS_DEFEND_CONTRABAND_MISSION(Any* data) { invoke<Void>(0x2605663BD4F23B5D, data); }
	NATIVE_DECL void PLAYSTATS_RECOVER_CONTRABAND_MISSION(Any* data) { invoke<Void>(0x04D90BA8207ADA2D, data); }
	NATIVE_DECL void PLAYSTATS_HIT_CONTRABAND_DESTROY_LIMIT(Any p0) { invoke<Void>(0x60EEDC12AF66E846, p0); }
	NATIVE_DECL void START_BEING_BOSS(Any p0, Any p1, Any p2) { invoke<Void>(0x3EBEAC6C3F81F6BD, p0, p1, p2); }
	NATIVE_DECL void START_BEING_GOON(Any p0, Any p1, Any p2) { invoke<Void>(0x96E6D5150DBF1C09, p0, p1, p2); }
	NATIVE_DECL void END_BEING_BOSS(Any p0, Any p1, Any p2) { invoke<Void>(0xA3C53804BDB68ED2, p0, p1, p2); }
	NATIVE_DECL void END_BEING_GOON(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x6BCCF9948492FD85, p0, p1, p2, p3, p4); }
	NATIVE_DECL void HIRED_LIMO(Any p0, Any p1) { invoke<Void>(0x792271AB35C356A4, p0, p1); }
	NATIVE_DECL void ORDER_BOSS_VEHICLE(Any p0, Any p1, Hash vehicleHash) { invoke<Void>(0xCEA553E35C2246E1, p0, p1, vehicleHash); }
	NATIVE_DECL void CHANGE_UNIFORM(Any p0, Any p1, Any p2) { invoke<Void>(0xD1C9B92BDD3F151D, p0, p1, p2); }
	NATIVE_DECL void CHANGE_GOON_LOOKING_FOR_WORK(Any p0) { invoke<Void>(0x44919CC079BB60BF, p0); }
	NATIVE_DECL void SEND_METRIC_GHOSTING_TO_PLAYER(Any p0) { invoke<Void>(0x7033EEFD9B28088E, p0); }
	NATIVE_DECL void SEND_METRIC_VIP_POACH(Any p0, Any p1, Any p2) { invoke<Void>(0xAA525DFF66BB82F5, p0, p1, p2); }
	NATIVE_DECL void SEND_METRIC_PUNISH_BODYGUARD(Any p0) { invoke<Void>(0x015B03EE1C43E6EC, p0); }
	NATIVE_DECL void PLAYSTATS_START_TRACKING_STUNTS() { invoke<Void>(0x928DBFB892638EF3); }
	NATIVE_DECL void PLAYSTATS_STOP_TRACKING_STUNTS() { invoke<Void>(0x8A800DACCC0DA55D); }
	NATIVE_DECL void PLAYSTATS_MISSION_ENDED(Any p0) { invoke<Void>(0xBF371CD2B64212FD, p0); }
	NATIVE_DECL void PLAYSTATS_IMPEXP_MISSION_ENDED(Any p0) { invoke<Void>(0x7D8BA05688AD64C7, p0); }
	NATIVE_DECL void PLAYSTATS_CHANGE_MC_ROLE(Any p0, Any p1, Any p2, Any p3, int role, int p5, Any p6) { invoke<Void>(0x0B565B0AAE56A0E8, p0, p1, p2, p3, role, p5, p6); }
	NATIVE_DECL void PLAYSTATS_CHANGE_MC_OUTFIT(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x28ECB8AC2F607DB2, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_SWITCH_MC_EMBLEM(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x0A50D2604E05CB94, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_MC_REQUEST_BIKE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xCC25A4553DFBF9EA, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_MC_KILLED_RIVAL_MC_MEMBER(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xF534D94DFA2EAD26, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_ABANDONED_MC(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xD558BEC0BBA7E8D2, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_EARNED_MC_POINTS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x501478855A6074CE, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL void PLAYSTATS_MC_FORMATION_ENDS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x03C2EEBB04B3FB72, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void PLAYSTATS_MC_CLUBHOUSE_ACTIVITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x8989CBD7B4E82534, p0, p1, p2, p3, p4, p5, p6, p7); }
	NATIVE_DECL void PLAYSTATS_RIVAL_BEHAVIOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x27AA1C973CACFE63, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	NATIVE_DECL void PLAYSTATS_COPY_RANK_INTO_NEW_SLOT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xB7257BA2550EA10A, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void PLAYSTATS_DUPE_DETECTED(Any* data) { invoke<Void>(0x848B66100EE33B05, data); }
	NATIVE_DECL void PLAYSTATS_BAN_ALERT(int p0) { invoke<Void>(0x516FC96EB88EEFE5, p0); }
	NATIVE_DECL void PLAYSTATS_GUNRUNNING_MISSION_ENDED(Any* data) { invoke<Void>(0x0EACDF8487D5155A, data); }
	NATIVE_DECL void PLAYSTATS_GUNRUNNING_RND(Any p0) { invoke<Void>(0xDAF80797FC534BEC, p0); }
	NATIVE_DECL void PLAYSTATS_BUSINESS_BATTLE_ENDED(Any p0) { invoke<Void>(0x316DB59CD14C1774, p0); }
	NATIVE_DECL void PLAYSTATS_WAREHOUSE_MISSION_ENDED(Any p0) { invoke<Void>(0x2D7A9B577E72385E, p0); }
	NATIVE_DECL void PLAYSTATS_NIGHTCLUB_MISSION_ENDED(Any p0) { invoke<Void>(0x830C3A44EB3F2CF9, p0); }
	NATIVE_DECL void PLAYSTATS_DJ_USAGE(Any p0, Any p1) { invoke<Void>(0xB26F670685631727, p0, p1); }
	NATIVE_DECL void PLAYSTATS_MINIGAME_USAGE(Any p0, Any p1, Any p2) { invoke<Void>(0xC14BD9F5337219B2, p0, p1, p2); }
	NATIVE_DECL void PLAYSTATS_STONE_HATCHET_ENDED(Any* data) { invoke<Void>(0x35E39E5570358630, data); }
	NATIVE_DECL void PLAYSTATS_SMUGGLER_MISSION_ENDED(Any* data) { invoke<Void>(0x320C35147D5B5DDD, data); }
	NATIVE_DECL void PLAYSTATS_FM_HEIST_PREP_ENDED(Any* data) { invoke<Void>(0xD8AFB345A9C5CCBB, data); }
	NATIVE_DECL void PLAYSTATS_INSTANCED_HEIST_ENDED(Any* data, Any p1, Any p2, Any p3) { invoke<Void>(0x1E1497D0D2108115, data, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_DAR_CHECKPOINT(Any* data) { invoke<Void>(0x0BC254FF3A911501, data); }
	NATIVE_DECL void PLAYSTATS_ENTER_SESSION_PACK(Any* data) { invoke<Void>(0x878FF156D36E9956, data); }
	NATIVE_DECL void PLAYSTATS_DRONE_USAGE(int p0, int p1, int p2) { invoke<Void>(0x66C7BB2416ED3FCE, p0, p1, p2); }
	NATIVE_DECL void PLAYSTATS_SPIN_WHEEL(int p0, int p1, int p2, int p3) { invoke<Void>(0x6731DE84A38BFAD0, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_ARENA_WARS_SPECTATOR(int p0, int p1, int p2, int p3, int p4) { invoke<Void>(0x6F4F599753F8200A, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_ARENA_WARS_ENDED(Any* data) { invoke<Void>(0xB479D9F0D48A1BC5, data); }
	NATIVE_DECL void PLAYSTATS_SWITCH_PASSIVE_MODE(BOOL p0, int p1, int p2, int p3) { invoke<Void>(0x35EEC6C2BC821A71, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_COLLECTIBLE_PICKED_UP(int p0, Hash objectHash, Any p2, Any p3, int moneyAmount, int rpAmount, int chipsAmount, Any p7, int p8, Any p9, Any p10) { invoke<Void>(0xCD0A8A9338681CF2, p0, objectHash, p2, p3, moneyAmount, rpAmount, chipsAmount, p7, p8, p9, p10); }
	NATIVE_DECL void PLAYSTATS_CASINO_STORY_MISSION_ENDED(Any p0, Any p1) { invoke<Void>(0xFCCCAC2BD3C1F180, p0, p1); }
	NATIVE_DECL void PLAYSTATS_CASINO_CHIP(Any p0) { invoke<Void>(0x0999F3F090EC5012, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_ROULETTE(Any p0) { invoke<Void>(0x95101C443A84E7F1, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_BLACKJACK(Any p0) { invoke<Void>(0x3EAE97309727E7AD, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_THREE_CARD_POKER(Any p0) { invoke<Void>(0xF740FB339D471C35, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_SLOT_MACHINE(Any p0) { invoke<Void>(0xEF5EC67D392B830A, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_INSIDE_TRACK(Any p0) { invoke<Void>(0x049F059625058A86, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_LUCKY_SEVEN(Any p0) { invoke<Void>(0x0C432C1435F5E4FA, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_ROULETTE_LIGHT(Any p0) { invoke<Void>(0x6572ABA3DE1197FC, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_BLACKJACK_LIGHT(Any p0) { invoke<Void>(0xD5451C7BF151EB6F, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_THREE_CARD_POKER_LIGHT(Any p0) { invoke<Void>(0xC9001364B4388F22, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_SLOT_MACHINE_LIGHT(Any p0) { invoke<Void>(0xE60054A0FAE8227F, p0); }
	NATIVE_DECL void PLAYSTATS_CASINO_INSIDE_TRACK_LIGHT(Any p0) { invoke<Void>(0x23A3CBCD50D54E47, p0); }
	NATIVE_DECL void PLAYSTATS_ARCADE_GAME(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x533A7D1EA58DF958, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void PLAYSTATS_ARCADE_LOVE_MATCH(Any p0, Any p1) { invoke<Void>(0x4FCDBD3F0A813C25, p0, p1); }
	NATIVE_DECL void PLAYSTATS_FREEMODE_CASINO_MISSION_ENDED(Any* data) { invoke<Void>(0x1A0D4A6C336B7BC5, data); }
	NATIVE_DECL void PLAYSTATS_HEIST3_DRONE(Any p0) { invoke<Void>(0xDFBD93BF2943E29B, p0); }
	NATIVE_DECL void PLAYSTATS_HEIST3_HACK(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x92FC0EEDFAC04A14, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL void PLAYSTATS_NPC_PHONE(Any* p0) { invoke<Void>(0x0077F15613D36993, p0); }
	NATIVE_DECL void PLAYSTATS_ARCADE_CABINET(Any p0) { invoke<Void>(0xF9096193DF1F99D4, p0); }
	NATIVE_DECL void PLAYSTATS_HEIST3_FINALE(Any p0) { invoke<Void>(0x2E0259BABC27A327, p0); }
	NATIVE_DECL void PLAYSTATS_HEIST3_PREP(Any p0) { invoke<Void>(0x53C31853EC9531FF, p0); }
	NATIVE_DECL void PLAYSTATS_MASTER_CONTROL(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x810B5FCC52EC7FF0, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_QUIT_MODE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x5BF29846C6527C54, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_MISSION_VOTE(Any p0) { invoke<Void>(0xC03FAB2C2F92289B, p0); }
	NATIVE_DECL void PLAYSTATS_NJVS_VOTE(Any p0) { invoke<Void>(0x5CDAED54B34B0ED0, p0); }
	NATIVE_DECL void _PLAYSTATS_DEATH_INFO(Ped victimPed, Ped killerPed, int mentalState, BOOL revengeKill, int victimKvK, int killerKvK) { invoke<Void>(0x01D8B04D02F1217F, victimPed, killerPed, mentalState, revengeKill, victimKvK, killerKvK); }
	NATIVE_DECL void PLAYSTATS_FM_MISSION_END(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x46A70777BE6CEAB9, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_HEIST4_PREP(Any p0) { invoke<Void>(0xDFCDB14317A9B361, p0); }
	NATIVE_DECL void PLAYSTATS_HEIST4_FINALE(Any p0) { invoke<Void>(0xC1E963C58664B556, p0); }
	NATIVE_DECL void PLAYSTATS_HEIST4_HACK(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x2FA3173480008493, p0, p1, p2, p3, p4); }
	NATIVE_DECL void PLAYSTATS_SUB_WEAP(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD4367D310F079DB0, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_FAST_TRVL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0x4DC416F246A41FC8, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	NATIVE_DECL void PLAYSTATS_HUB_ENTRY(Any p0) { invoke<Void>(0x2818FF6638CB09DE, p0); }
	NATIVE_DECL void PLAYSTATS_DJ_MISSION_ENDED(Any p0) { invoke<Void>(0xD6CA58B3B53A0F22, p0); }
	NATIVE_DECL void PLAYSTATS_ROBBERY_PREP(Any p0) { invoke<Void>(0x1A67DFBF1F5C3835, p0); }
	NATIVE_DECL void PLAYSTATS_ROBBERY_FINALE(Any p0) { invoke<Void>(0xBBA55BE9AAAABF44, p0); }
	NATIVE_DECL void PLAYSTATS_EXTRA_EVENT(Any p0) { invoke<Void>(0xFA5B74BAB8A7EF99, p0); }
	NATIVE_DECL void PLAYSTATS_CARCLUB_POINTS(Any p0) { invoke<Void>(0xFF14D6FEEC507BBE, p0); }
	NATIVE_DECL void PLAYSTATS_CARCLUB_CHALLENGE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x1187CB58D7F3BED7, p0, p1, p2, p3); }
	NATIVE_DECL void PLAYSTATS_CARCLUB_PRIZE(int p0, Hash vehicleModel) { invoke<Void>(0x69C922B677621428, p0, vehicleModel); }
	NATIVE_DECL void PLAYSTATS_AWARD_NAV(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x70F52471E758EBAE, p0, p1, p2, p3); }
	NATIVE_DECL void _PLAYSTATS_INIT_MULTIPLAYER(Any p0, Any p1, Any p2) { invoke<Void>(0x7E5EED10B11CEDBA, p0, p1, p2); }
	NATIVE_DECL void PLAYSTATS_INST_MISSION_END(Any p0) { invoke<Void>(0xFEA3F7E83C0610FA, p0); }
	NATIVE_DECL void PLAYSTATS_HUB_EXIT(Any p0) { invoke<Void>(0x5A46ACE5C4661132, p0); }
	NATIVE_DECL void PLAYSTATS_VEH_DEL(int bossId1, int bossId2, int bossType, int vehicleID, int reason) { invoke<Void>(0x10A691F5756416D0, bossId1, bossId2, bossType, vehicleID, reason); }
	NATIVE_DECL void PLAYSTATS_INVENTORY(Any p0) { invoke<Void>(0x887DAD63CF5B7908, p0); }
	NATIVE_DECL void _PLAYSTATS_ACID_MISSION_END(Any p0) { invoke<Void>(0x8A23D1324F6B2BAC, p0); }
	NATIVE_DECL void _PLAYSTATS_ACID_RND(Any p0) { invoke<Void>(0xCEACCF0550FDC5BA, p0); }
	NATIVE_DECL void _PLAYSTATS_IDLE(Any p0, Any p1, Any p2) { invoke<Void>(0xEC9553A178E8F1D1, p0, p1, p2); }
	NATIVE_DECL void _PLAYSTATS_PLAYER_STYLE(Any p0) { invoke<Void>(0x48FAC5DC7AC6EA99, p0); }
	NATIVE_DECL void _PLAYSTATS_RANDOM_EVENT(Any p0) { invoke<Void>(0x7EA06F970F999394, p0); }
	NATIVE_DECL void _PLAYSTATS_ALERT(Any* data) { invoke<Void>(0x5649CA22AF74E019, data); }
	NATIVE_DECL void _PLAYSTATS_ATTRITION_STAGE_END(Any p0) { invoke<Void>(0xBD642335A732F1A8, p0); }
	NATIVE_DECL void _PLAYSTATS_SHOWROOM_NAV(Any p0, Any p1, Hash entity) { invoke<Void>(0x961D4157B9B428DB, p0, p1, entity); }
	NATIVE_DECL void _PLAYSTATS_SHOWROOM_OVERVIEW(Any* data) { invoke<Void>(0x151D6C04C9E2742F, data); }
	NATIVE_DECL void _PLAYSTATS_PIMENU_NAV(Any* data) { invoke<Void>(0xE6D323A5E9EFFB76, data); }
	NATIVE_DECL void _PLAYSTATS_RECOVER_VEHICLE(Any* data) { invoke<Void>(0xBEB0D930B3CCE4D5, data); }
	NATIVE_DECL void _PLAYSTATS_SCRIPT_EVENT_FPOM(Any* data) { invoke<Void>(0x574A7808450E141C, data); }
	NATIVE_DECL void _PLAYSTATS_LOBBY_EXIT(Any* p0) { invoke<Void>(0x4649D80CE1A35BA1, p0); }
	NATIVE_DECL void _PLAYSTATS_LOBBY_STARTED(Any* p0) { invoke<Void>(0xDC00BB9C27347A8F, p0); }
	NATIVE_DECL void _PLAYSTATS_CREATOR_END(Any* p0) { invoke<Void>(0x72289B8C78B02962, p0); }
	NATIVE_DECL void _PLAYSTATS_HEIST5_FINALE(Any* data) { invoke<Void>(0x8897A71C988F7936, data); }
	NATIVE_DECL void _PLAYSTATS_HEIST5_PREP(Any* data) { invoke<Void>(0x3B144C0026DCBA41, data); }
	NATIVE_DECL void _PLAYSTATS_HEIST5_HACK(Any* data) { invoke<Void>(0xBE656648E63C73D7, data); }
}

namespace STREAMING
{
	NATIVE_DECL void LOAD_ALL_OBJECTS_NOW() { invoke<Void>(0xBD6E84632DD4CB3F); }
	NATIVE_DECL void LOAD_SCENE(float x, float y, float z) { invoke<Void>(0x4448EB75B4904BDB, x, y, z); }
	NATIVE_DECL BOOL NETWORK_UPDATE_LOAD_SCENE() { return invoke<BOOL>(0xC4582015556D1C46); }
	NATIVE_DECL BOOL IS_NETWORK_LOADING_SCENE() { return invoke<BOOL>(0x41CA5A33160EA4AB); }
	NATIVE_DECL void SET_INTERIOR_ACTIVE(int interiorID, BOOL toggle) { invoke<Void>(0xE37B76C387BE28ED, interiorID, toggle); }
	NATIVE_DECL void REQUEST_MODEL(Hash model) { invoke<Void>(0x963D27A58DF860AC, model); }
	NATIVE_DECL void REQUEST_MENU_PED_MODEL(Hash model) { invoke<Void>(0xA0261AEF7ACFC51E, model); }
	NATIVE_DECL BOOL HAS_MODEL_LOADED(Hash model) { return invoke<BOOL>(0x98A4EB5D89A0C952, model); }
	NATIVE_DECL void REQUEST_MODELS_IN_ROOM(Interior interior, const char* roomName) { invoke<Void>(0x8A7A40100EDFEC58, interior, roomName); }
	NATIVE_DECL void SET_MODEL_AS_NO_LONGER_NEEDED(Hash model) { invoke<Void>(0xE532F5D78798DAAB, model); }
	NATIVE_DECL BOOL IS_MODEL_IN_CDIMAGE(Hash model) { return invoke<BOOL>(0x35B9E0803292B641, model); }
	NATIVE_DECL BOOL IS_MODEL_VALID(Hash model) { return invoke<BOOL>(0xC0296A2EDF545E92, model); }
	NATIVE_DECL BOOL IS_MODEL_A_PED(Hash model) { return invoke<BOOL>(0x75816577FEA6DAD5, model); }
	NATIVE_DECL BOOL IS_MODEL_A_VEHICLE(Hash model) { return invoke<BOOL>(0x19AAC8F07BFEC53E, model); }
	NATIVE_DECL void REQUEST_COLLISION_AT_COORD(float x, float y, float z) { invoke<Void>(0x07503F7948F491A7, x, y, z); }
	NATIVE_DECL void REQUEST_COLLISION_FOR_MODEL(Hash model) { invoke<Void>(0x923CB32A3B874FCB, model); }
	NATIVE_DECL BOOL HAS_COLLISION_FOR_MODEL_LOADED(Hash model) { return invoke<BOOL>(0x22CCA434E368F03A, model); }
	NATIVE_DECL void REQUEST_ADDITIONAL_COLLISION_AT_COORD(float x, float y, float z) { invoke<Void>(0xC9156DC11411A9EA, x, y, z); }
	NATIVE_DECL BOOL DOES_ANIM_DICT_EXIST(const char* animDict) { return invoke<BOOL>(0x2DA49C3B79856961, animDict); }
	NATIVE_DECL void REQUEST_ANIM_DICT(const char* animDict) { invoke<Void>(0xD3BD40951412FEF6, animDict); }
	NATIVE_DECL BOOL HAS_ANIM_DICT_LOADED(const char* animDict) { return invoke<BOOL>(0xD031A9162D01088C, animDict); }
	NATIVE_DECL void REMOVE_ANIM_DICT(const char* animDict) { invoke<Void>(0xF66A602F829E2A06, animDict); }
	NATIVE_DECL void REQUEST_ANIM_SET(const char* animSet) { invoke<Void>(0x6EA47DAE7FAD0EED, animSet); }
	NATIVE_DECL BOOL HAS_ANIM_SET_LOADED(const char* animSet) { return invoke<BOOL>(0xC4EA073D86FB29B0, animSet); }
	NATIVE_DECL void REMOVE_ANIM_SET(const char* animSet) { invoke<Void>(0x16350528F93024B3, animSet); }
	NATIVE_DECL void REQUEST_CLIP_SET(const char* clipSet) { invoke<Void>(0xD2A71E1A77418A49, clipSet); }
	NATIVE_DECL BOOL HAS_CLIP_SET_LOADED(const char* clipSet) { return invoke<BOOL>(0x318234F4F3738AF3, clipSet); }
	NATIVE_DECL void REMOVE_CLIP_SET(const char* clipSet) { invoke<Void>(0x01F73A131C18CD94, clipSet); }
	NATIVE_DECL void REQUEST_IPL(const char* iplName) { invoke<Void>(0x41B4893843BBDB74, iplName); }
	NATIVE_DECL void REMOVE_IPL(const char* iplName) { invoke<Void>(0xEE6C5AD3ECE0A82D, iplName); }
	NATIVE_DECL BOOL IS_IPL_ACTIVE(const char* iplName) { return invoke<BOOL>(0x88A741E44A2B3495, iplName); }
	NATIVE_DECL void SET_STREAMING(BOOL toggle) { invoke<Void>(0x6E0C692677008888, toggle); }
	NATIVE_DECL void LOAD_GLOBAL_WATER_FILE(int waterType) { invoke<Void>(0x7E3F55ED251B76D3, waterType); }
	NATIVE_DECL int GET_GLOBAL_WATER_FILE() { return invoke<int>(0xF741BD853611592D); }
	NATIVE_DECL void SET_GAME_PAUSES_FOR_STREAMING(BOOL toggle) { invoke<Void>(0x717CD6E6FAEBBEDC, toggle); }
	NATIVE_DECL void SET_REDUCE_PED_MODEL_BUDGET(BOOL toggle) { invoke<Void>(0x77B5F9A36BF96710, toggle); }
	NATIVE_DECL void SET_REDUCE_VEHICLE_MODEL_BUDGET(BOOL toggle) { invoke<Void>(0x80C527893080CCF3, toggle); }
	NATIVE_DECL void SET_DITCH_POLICE_MODELS(BOOL toggle) { invoke<Void>(0x42CBE54462D92634, toggle); }
	NATIVE_DECL int GET_NUMBER_OF_STREAMING_REQUESTS() { return invoke<int>(0x4060057271CEBC89); }
	NATIVE_DECL void REQUEST_PTFX_ASSET() { invoke<Void>(0x944955FB2A3935C8); }
	NATIVE_DECL BOOL HAS_PTFX_ASSET_LOADED() { return invoke<BOOL>(0xCA7D9B86ECA7481B); }
	NATIVE_DECL void REMOVE_PTFX_ASSET() { invoke<Void>(0x88C6814073DD4A73); }
	NATIVE_DECL void REQUEST_NAMED_PTFX_ASSET(const char* fxName) { invoke<Void>(0xB80D8756B4668AB6, fxName); }
	NATIVE_DECL BOOL HAS_NAMED_PTFX_ASSET_LOADED(const char* fxName) { return invoke<BOOL>(0x8702416E512EC454, fxName); }
	NATIVE_DECL void REMOVE_NAMED_PTFX_ASSET(const char* fxName) { invoke<Void>(0x5F61EBBE1A00F96D, fxName); }
	NATIVE_DECL void SET_VEHICLE_POPULATION_BUDGET(int p0) { invoke<Void>(0xCB9E1EB3BE2AF4E9, p0); }
	NATIVE_DECL void SET_PED_POPULATION_BUDGET(int p0) { invoke<Void>(0x8C95333CFC3340F3, p0); }
	NATIVE_DECL void CLEAR_FOCUS() { invoke<Void>(0x31B73D1EA9F01DA2); }
	NATIVE_DECL void SET_FOCUS_POS_AND_VEL(float x, float y, float z, float offsetX, float offsetY, float offsetZ) { invoke<Void>(0xBB7454BAFF08FE25, x, y, z, offsetX, offsetY, offsetZ); }
	NATIVE_DECL void SET_FOCUS_ENTITY(Entity entity) { invoke<Void>(0x198F77705FA0931D, entity); }
	NATIVE_DECL BOOL IS_ENTITY_FOCUS(Entity entity) { return invoke<BOOL>(0x2DDFF3FB9075D747, entity); }
	NATIVE_DECL void SET_RESTORE_FOCUS_ENTITY(Entity p0) { invoke<Void>(0x0811381EF5062FEC, p0); }
	NATIVE_DECL void SET_MAPDATACULLBOX_ENABLED(const char* name, BOOL toggle) { invoke<Void>(0xAF12610C644A35C9, name, toggle); }
	NATIVE_DECL void SET_ALL_MAPDATA_CULLED(Any p0) { invoke<Void>(0x4E52E752C76E7E7A, p0); }
	NATIVE_DECL int STREAMVOL_CREATE_SPHERE(float x, float y, float z, float rad, Any p4, Any p5) { return invoke<int>(0x219C7B8D53E429FD, x, y, z, rad, p4, p5); }
	NATIVE_DECL int STREAMVOL_CREATE_FRUSTUM(float p0, float p1, float p2, float p3, float p4, float p5, float p6, Any p7, Any p8) { return invoke<int>(0x1F3F018BC3AFA77C, p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL int STREAMVOL_CREATE_LINE(float p0, float p1, float p2, float p3, float p4, float p5, Any p6) { return invoke<int>(0x0AD9710CEE2F590F, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void STREAMVOL_DELETE(Any unused) { invoke<Void>(0x1EE7D8DF4425F053, unused); }
	NATIVE_DECL BOOL STREAMVOL_HAS_LOADED(Any unused) { return invoke<BOOL>(0x7D41E9D2D17C5B2D, unused); }
	NATIVE_DECL BOOL STREAMVOL_IS_VALID(Any unused) { return invoke<BOOL>(0x07C313F94746702C, unused); }
	NATIVE_DECL BOOL IS_STREAMVOL_ACTIVE() { return invoke<BOOL>(0xBC9823AB80A3DCAC); }
	NATIVE_DECL BOOL NEW_LOAD_SCENE_START(float posX, float posY, float posZ, float offsetX, float offsetY, float offsetZ, float radius, int p7) { return invoke<BOOL>(0x212A8D0D2BABFAC2, posX, posY, posZ, offsetX, offsetY, offsetZ, radius, p7); }
	NATIVE_DECL BOOL NEW_LOAD_SCENE_START_SPHERE(float x, float y, float z, float radius, Any p4) { return invoke<BOOL>(0xACCFB4ACF53551B0, x, y, z, radius, p4); }
	NATIVE_DECL void NEW_LOAD_SCENE_STOP() { invoke<Void>(0xC197616D221FF4A4); }
	NATIVE_DECL BOOL IS_NEW_LOAD_SCENE_ACTIVE() { return invoke<BOOL>(0xA41A05B6CB741B85); }
	NATIVE_DECL BOOL IS_NEW_LOAD_SCENE_LOADED() { return invoke<BOOL>(0x01B8247A7A8B9AD1); }
	NATIVE_DECL BOOL IS_SAFE_TO_START_PLAYER_SWITCH() { return invoke<BOOL>(0x71E7B2E657449AAD); }
	NATIVE_DECL void START_PLAYER_SWITCH(Ped from, Ped to, int flags, int switchType) { invoke<Void>(0xFAA23F2CBA159D67, from, to, flags, switchType); }
	NATIVE_DECL void STOP_PLAYER_SWITCH() { invoke<Void>(0x95C0A5BBDC189AA1); }
	NATIVE_DECL BOOL IS_PLAYER_SWITCH_IN_PROGRESS() { return invoke<BOOL>(0xD9D2CFFF49FAB35F); }
	NATIVE_DECL int GET_PLAYER_SWITCH_TYPE() { return invoke<int>(0xB3C94A90D9FC9E62); }
	NATIVE_DECL int GET_IDEAL_PLAYER_SWITCH_TYPE(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<int>(0xB5D7B26B45720E05, x1, y1, z1, x2, y2, z2); }
	NATIVE_DECL int GET_PLAYER_SWITCH_STATE() { return invoke<int>(0x470555300D10B2A5); }
	NATIVE_DECL int GET_PLAYER_SHORT_SWITCH_STATE() { return invoke<int>(0x20F898A5D9782800); }
	NATIVE_DECL void SET_PLAYER_SHORT_SWITCH_STYLE(int p0) { invoke<Void>(0x5F2013F8BC24EE69, p0); }
	NATIVE_DECL int GET_PLAYER_SWITCH_JUMP_CUT_INDEX() { return invoke<int>(0x78C0D93253149435); }
	NATIVE_DECL void SET_PLAYER_SWITCH_OUTRO(float cameraCoordX, float cameraCoordY, float cameraCoordZ, float camRotationX, float camRotationY, float camRotationZ, float camFov, float camFarClip, int rotationOrder) { invoke<Void>(0xC208B673CE446B61, cameraCoordX, cameraCoordY, cameraCoordZ, camRotationX, camRotationY, camRotationZ, camFov, camFarClip, rotationOrder); }
	NATIVE_DECL void SET_PLAYER_SWITCH_ESTABLISHING_SHOT(const char* name) { invoke<Void>(0x0FDE9DBFC0A6BC65, name); }
	NATIVE_DECL void ALLOW_PLAYER_SWITCH_PAN() { invoke<Void>(0x43D1680C6D19A8E9); }
	NATIVE_DECL void ALLOW_PLAYER_SWITCH_OUTRO() { invoke<Void>(0x74DE2E8739086740); }
	NATIVE_DECL void ALLOW_PLAYER_SWITCH_ASCENT() { invoke<Void>(0x8E2A065ABDAE6994); }
	NATIVE_DECL void ALLOW_PLAYER_SWITCH_DESCENT() { invoke<Void>(0xAD5FDF34B81BFE79); }
	NATIVE_DECL BOOL IS_SWITCH_READY_FOR_DESCENT() { return invoke<BOOL>(0xDFA80CB25D0A19B3); }
	NATIVE_DECL void ENABLE_SWITCH_PAUSE_BEFORE_DESCENT() { invoke<Void>(0xD4793DFF3AF2ABCD); }
	NATIVE_DECL void DISABLE_SWITCH_OUTRO_FX() { invoke<Void>(0xBD605B8E0E18B3BB); }
	NATIVE_DECL void SWITCH_TO_MULTI_FIRSTPART(Ped ped, int flags, int switchType) { invoke<Void>(0xAAB3200ED59016BC, ped, flags, switchType); }
	NATIVE_DECL void SWITCH_TO_MULTI_SECONDPART(Ped ped) { invoke<Void>(0xD8295AF639FD9CB8, ped); }
	NATIVE_DECL BOOL IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED() { return invoke<BOOL>(0x933BBEEB8C61B5F4); }
	NATIVE_DECL int GET_PLAYER_SWITCH_INTERP_OUT_DURATION() { return invoke<int>(0x08C2D6C52A3104BB); }
	NATIVE_DECL int GET_PLAYER_SWITCH_INTERP_OUT_CURRENT_TIME() { return invoke<int>(0x5B48A06DD0E792A5); }
	NATIVE_DECL BOOL IS_SWITCH_SKIPPING_DESCENT() { return invoke<BOOL>(0x5B74EA8CFD5E3E7E); }
	NATIVE_DECL void SET_SCENE_STREAMING_TRACKS_CAM_POS_THIS_FRAME() { invoke<Void>(0x1E9057A74FD73E23); }
	NATIVE_DECL float GET_LODSCALE() { return invoke<float>(0x0C15B0E443B2349D); }
	NATIVE_DECL void OVERRIDE_LODSCALE_THIS_FRAME(float scaling) { invoke<Void>(0xA76359FC80B2438E, scaling); }
	NATIVE_DECL void REMAP_LODSCALE_RANGE_THIS_FRAME(float p0, float p1, float p2, float p3) { invoke<Void>(0xBED8CA5FF5E04113, p0, p1, p2, p3); }
	NATIVE_DECL void SUPPRESS_HD_MAP_STREAMING_THIS_FRAME() { invoke<Void>(0x472397322E92A856); }
	NATIVE_DECL void SET_RENDER_HD_ONLY(BOOL toggle) { invoke<Void>(0x40AEFD1A244741F2, toggle); }
	NATIVE_DECL void FORCE_ALLOW_TIME_BASED_FADING_THIS_FRAME() { invoke<Void>(0x03F1A106BDA7DD3E); }
	NATIVE_DECL void IPL_GROUP_SWAP_START(const char* iplName1, const char* iplName2) { invoke<Void>(0x95A7DABDDBB78AE7, iplName1, iplName2); }
	NATIVE_DECL void IPL_GROUP_SWAP_CANCEL() { invoke<Void>(0x63EB2B972A218CAC); }
	NATIVE_DECL BOOL IPL_GROUP_SWAP_IS_READY() { return invoke<BOOL>(0xFB199266061F820A); }
	NATIVE_DECL void IPL_GROUP_SWAP_FINISH() { invoke<Void>(0xF4A0DADB70F57FA6); }
	NATIVE_DECL BOOL IPL_GROUP_SWAP_IS_ACTIVE() { return invoke<BOOL>(0x5068F488DDB54DD8); }
	NATIVE_DECL void PREFETCH_SRL(const char* srl) { invoke<Void>(0x3D245789CE12982C, srl); }
	NATIVE_DECL BOOL IS_SRL_LOADED() { return invoke<BOOL>(0xD0263801A4C5B0BB); }
	NATIVE_DECL void BEGIN_SRL() { invoke<Void>(0x9BADDC94EF83B823); }
	NATIVE_DECL void END_SRL() { invoke<Void>(0x0A41540E63C9EE17); }
	NATIVE_DECL void SET_SRL_TIME(float p0) { invoke<Void>(0xA74A541C6884E7B8, p0); }
	NATIVE_DECL void SET_SRL_POST_CUTSCENE_CAMERA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xEF39EE20C537E98C, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL void SET_SRL_READAHEAD_TIMES(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xBEB2D9A1D9A8F55A, p0, p1, p2, p3); }
	NATIVE_DECL void SET_SRL_LONG_JUMP_MODE(BOOL p0) { invoke<Void>(0x20C6C7E4EB082A7F, p0); }
	NATIVE_DECL void SET_SRL_FORCE_PRESTREAM(Any p0) { invoke<Void>(0xF8155A7F03DDFC8E, p0); }
	NATIVE_DECL void SET_HD_AREA(float x, float y, float z, float radius) { invoke<Void>(0xB85F26619073E775, x, y, z, radius); }
	NATIVE_DECL void CLEAR_HD_AREA() { invoke<Void>(0xCE58B1CFB9290813); }
	NATIVE_DECL void INIT_CREATOR_BUDGET() { invoke<Void>(0xB5A4DB34FE89B88A); }
	NATIVE_DECL void SHUTDOWN_CREATOR_BUDGET() { invoke<Void>(0xCCE26000E9A6FAD7); }
	NATIVE_DECL BOOL ADD_MODEL_TO_CREATOR_BUDGET(Hash modelHash) { return invoke<BOOL>(0x0BC3144DEB678666, modelHash); }
	NATIVE_DECL void REMOVE_MODEL_FROM_CREATOR_BUDGET(Hash modelHash) { invoke<Void>(0xF086AD9354FAC3A3, modelHash); }
	NATIVE_DECL float GET_USED_CREATOR_BUDGET() { return invoke<float>(0x3D3D8B3BE5A83D35); }
	NATIVE_DECL float _GET_TOTAL_MODEL_COST(Hash modelHash) { return invoke<float>(0x4A91423C04BAADA1, modelHash); }
	NATIVE_DECL void SET_ISLAND_ENABLED(const char* name, BOOL toggle) { invoke<Void>(0x9A9D1BA639675CF1, name, toggle); }
	NATIVE_DECL void _SET_SPHERICAL_STREAM_DISTANT_HILODS_THIS_FRAME() { invoke<Void>(0x68F1C25420D5F6AA); }
}

namespace TASK
{
	NATIVE_DECL void TASK_PAUSE(Ped ped, int ms) { invoke<Void>(0xE73A266DB0CA9042, ped, ms); }
	NATIVE_DECL void TASK_STAND_STILL(Ped ped, int time) { invoke<Void>(0x919BE13EED931959, ped, time); }
	NATIVE_DECL void TASK_JUMP(Ped ped, BOOL usePlayerLaunchForce, BOOL doSuperJump, BOOL useFullSuperJumpForce) { invoke<Void>(0x0AE4086104E067B1, ped, usePlayerLaunchForce, doSuperJump, useFullSuperJumpForce); }
	NATIVE_DECL void TASK_COWER(Ped ped, int duration) { invoke<Void>(0x3EB1FE9E8E908E15, ped, duration); }
	NATIVE_DECL void TASK_HANDS_UP(Ped ped, int duration, Ped facingPed, int timeToFacePed, int flags) { invoke<Void>(0xF2EAB31979A7F910, ped, duration, facingPed, timeToFacePed, flags); }
	NATIVE_DECL void UPDATE_TASK_HANDS_UP_DURATION(Ped ped, int duration) { invoke<Void>(0xA98FCAFD7893C834, ped, duration); }
	NATIVE_DECL void TASK_OPEN_VEHICLE_DOOR(Ped ped, Vehicle vehicle, int timeOut, int seat, float speed) { invoke<Void>(0x965791A9A488A062, ped, vehicle, timeOut, seat, speed); }
	NATIVE_DECL void TASK_ENTER_VEHICLE(Ped ped, Vehicle vehicle, int timeout, int seat, float speed, int flag, const char* overrideEntryClipsetName) { invoke<Void>(0xC20E50AA46D09CA8, ped, vehicle, timeout, seat, speed, flag, overrideEntryClipsetName); }
	NATIVE_DECL void TASK_LEAVE_VEHICLE(Ped ped, Vehicle vehicle, int flags) { invoke<Void>(0xD3DBCE61A490BE02, ped, vehicle, flags); }
	NATIVE_DECL void TASK_GET_OFF_BOAT(Ped ped, Vehicle boat) { invoke<Void>(0x9C00E77AF14B2DFF, ped, boat); }
	NATIVE_DECL void TASK_SKY_DIVE(Ped ped, BOOL instant) { invoke<Void>(0x601736CFE536B0A0, ped, instant); }
	NATIVE_DECL void TASK_PARACHUTE(Ped ped, BOOL giveParachuteItem, BOOL instant) { invoke<Void>(0xD2F1C53C97EE81AB, ped, giveParachuteItem, instant); }
	NATIVE_DECL void TASK_PARACHUTE_TO_TARGET(Ped ped, float x, float y, float z) { invoke<Void>(0xB33E291AFA6BD03A, ped, x, y, z); }
	NATIVE_DECL void SET_PARACHUTE_TASK_TARGET(Ped ped, float x, float y, float z) { invoke<Void>(0xC313379AF0FCEDA7, ped, x, y, z); }
	NATIVE_DECL void SET_PARACHUTE_TASK_THRUST(Ped ped, float thrust) { invoke<Void>(0x0729BAC1B8C64317, ped, thrust); }
	NATIVE_DECL void TASK_RAPPEL_FROM_HELI(Ped ped, float minHeightAboveGround) { invoke<Void>(0x09693B0312F91649, ped, minHeightAboveGround); }
	NATIVE_DECL void TASK_VEHICLE_DRIVE_TO_COORD(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, Any p6, Hash vehicleModel, int drivingMode, float stopRange, float straightLineDistance) { invoke<Void>(0xE2A2AA2F659D77A7, ped, vehicle, x, y, z, speed, p6, vehicleModel, drivingMode, stopRange, straightLineDistance); }
	NATIVE_DECL void TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, int driveMode, float stopRange) { invoke<Void>(0x158BB33F920D360C, ped, vehicle, x, y, z, speed, driveMode, stopRange); }
	NATIVE_DECL void TASK_VEHICLE_DRIVE_WANDER(Ped ped, Vehicle vehicle, float speed, int drivingStyle) { invoke<Void>(0x480142959D337D00, ped, vehicle, speed, drivingStyle); }
	NATIVE_DECL void TASK_FOLLOW_TO_OFFSET_OF_ENTITY(Ped ped, Entity entity, float offsetX, float offsetY, float offsetZ, float movementSpeed, int timeout, float stoppingRange, BOOL persistFollowing) { invoke<Void>(0x304AE42E357B8C7E, ped, entity, offsetX, offsetY, offsetZ, movementSpeed, timeout, stoppingRange, persistFollowing); }
	NATIVE_DECL void TASK_GO_STRAIGHT_TO_COORD(Ped ped, float x, float y, float z, float speed, int timeout, float targetHeading, float distanceToSlide) { invoke<Void>(0xD76B57B44F1E6F8B, ped, x, y, z, speed, timeout, targetHeading, distanceToSlide); }
	NATIVE_DECL void TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY(Ped ped, Entity entity, float x, float y, float z, float moveBlendRatio, int time) { invoke<Void>(0x61E360B7E040D12E, ped, entity, x, y, z, moveBlendRatio, time); }
	NATIVE_DECL void TASK_ACHIEVE_HEADING(Ped ped, float heading, int timeout) { invoke<Void>(0x93B93A37987F1F3D, ped, heading, timeout); }
	NATIVE_DECL void TASK_FLUSH_ROUTE() { invoke<Void>(0x841142A1376E9006); }
	NATIVE_DECL void TASK_EXTEND_ROUTE(float x, float y, float z) { invoke<Void>(0x1E7889778264843A, x, y, z); }
	NATIVE_DECL void TASK_FOLLOW_POINT_ROUTE(Ped ped, float speed, int mode) { invoke<Void>(0x595583281858626E, ped, speed, mode); }
	NATIVE_DECL void TASK_GO_TO_ENTITY(Entity entity, Entity target, int duration, float distance, float moveBlendRatio, float slowDownDistance, int flags) { invoke<Void>(0x6A071245EB0D1882, entity, target, duration, distance, moveBlendRatio, slowDownDistance, flags); }
	NATIVE_DECL void TASK_SMART_FLEE_COORD(Ped ped, float x, float y, float z, float distance, int time, BOOL preferPavements, BOOL quitIfOutOfRange) { invoke<Void>(0x94587F17E9C365D5, ped, x, y, z, distance, time, preferPavements, quitIfOutOfRange); }
	NATIVE_DECL void TASK_SMART_FLEE_PED(Ped ped, Ped fleeTarget, float safeDistance, int fleeTime, BOOL preferPavements, BOOL updateToNearestHatedPed) { invoke<Void>(0x22B0D0E37CCB840D, ped, fleeTarget, safeDistance, fleeTime, preferPavements, updateToNearestHatedPed); }
	NATIVE_DECL void TASK_REACT_AND_FLEE_PED(Ped ped, Ped fleeTarget) { invoke<Void>(0x72C896464915D1B1, ped, fleeTarget); }
	NATIVE_DECL void TASK_SHOCKING_EVENT_REACT(Ped ped, int eventHandle) { invoke<Void>(0x452419CBD838065B, ped, eventHandle); }
	NATIVE_DECL void TASK_WANDER_IN_AREA(Ped ped, float x, float y, float z, float radius, float minimalLength, float timeBetweenWalks) { invoke<Void>(0xE054346CA3A0F315, ped, x, y, z, radius, minimalLength, timeBetweenWalks); }
	NATIVE_DECL void TASK_WANDER_STANDARD(Ped ped, float heading, int flags) { invoke<Void>(0xBB9CE077274F6A1B, ped, heading, flags); }
	NATIVE_DECL void TASK_WANDER_SPECIFIC(Ped ped, const char* conditionalAnimGroupStr, const char* conditionalAnimStr, float heading) { invoke<Void>(0x6919A2F136426098, ped, conditionalAnimGroupStr, conditionalAnimStr, heading); }
	NATIVE_DECL void TASK_VEHICLE_PARK(Ped ped, Vehicle vehicle, float x, float y, float z, float heading, int mode, float radius, BOOL keepEngineOn) { invoke<Void>(0x0F3E34E968EA374E, ped, vehicle, x, y, z, heading, mode, radius, keepEngineOn); }
	NATIVE_DECL void TASK_STEALTH_KILL(Ped killer, Ped target, Hash stealthKillActionResultHash, float desiredMoveBlendRatio, int stealthFlags) { invoke<Void>(0xAA5DC05579D60BD9, killer, target, stealthKillActionResultHash, desiredMoveBlendRatio, stealthFlags); }
	NATIVE_DECL void TASK_PLANT_BOMB(Ped ped, float x, float y, float z, float heading) { invoke<Void>(0x965FEC691D55E9BF, ped, x, y, z, heading); }
	NATIVE_DECL void TASK_SHARK_CIRCLE_COORD(Ped ped, float x, float y, float z, float moveBlendRatio, float radius) { invoke<Void>(0x60A19CF85FF4CEFA, ped, x, y, z, moveBlendRatio, radius); }
	NATIVE_DECL void TASK_FOLLOW_NAV_MESH_TO_COORD(Ped ped, float x, float y, float z, float moveBlendRatio, int time, float targetRadius, int flags, float targetHeading) { invoke<Void>(0x15D3A79D4E44B913, ped, x, y, z, moveBlendRatio, time, targetRadius, flags, targetHeading); }
	NATIVE_DECL void TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED(Ped ped, float x, float y, float z, float moveBlendRatio, int time, float targetRadius, int flags, float slideToCoordHeading, float maxSlopeNavigable, float clampMaxSearchDistance, float targetHeading) { invoke<Void>(0x17F58B88D085DBAC, ped, x, y, z, moveBlendRatio, time, targetRadius, flags, slideToCoordHeading, maxSlopeNavigable, clampMaxSearchDistance, targetHeading); }
	NATIVE_DECL void SET_PED_PATH_CAN_USE_CLIMBOVERS(Ped ped, BOOL Toggle) { invoke<Void>(0x8E06A6FE76C9EFF4, ped, Toggle); }
	NATIVE_DECL void SET_PED_PATH_CAN_USE_LADDERS(Ped ped, BOOL Toggle) { invoke<Void>(0x77A5B103C87F476E, ped, Toggle); }
	NATIVE_DECL void SET_PED_PATH_CAN_DROP_FROM_HEIGHT(Ped ped, BOOL Toggle) { invoke<Void>(0xE361C5C71C431A4F, ped, Toggle); }
	NATIVE_DECL void SET_PED_PATH_CLIMB_COST_MODIFIER(Ped ped, float modifier) { invoke<Void>(0x88E32DB8C1A4AA4B, ped, modifier); }
	NATIVE_DECL void SET_PED_PATH_MAY_ENTER_WATER(Ped ped, BOOL mayEnterWater) { invoke<Void>(0xF35425A4204367EC, ped, mayEnterWater); }
	NATIVE_DECL void SET_PED_PATH_PREFER_TO_AVOID_WATER(Ped ped, BOOL avoidWater) { invoke<Void>(0x38FE1EC73743793C, ped, avoidWater); }
	NATIVE_DECL void SET_PED_PATH_AVOID_FIRE(Ped ped, BOOL avoidFire) { invoke<Void>(0x4455517B28441E60, ped, avoidFire); }
	NATIVE_DECL void SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT(float height) { invoke<Void>(0x6C6B148586F934F7, height); }
	NATIVE_DECL int GET_NAVMESH_ROUTE_DISTANCE_REMAINING(Ped ped, float* distanceRemaining, BOOL* isPathReady) { return invoke<int>(0xC6F5C0BCDC74D62D, ped, distanceRemaining, isPathReady); }
	NATIVE_DECL int GET_NAVMESH_ROUTE_RESULT(Ped ped) { return invoke<int>(0x632E831F382A0FA8, ped); }
	NATIVE_DECL BOOL IS_CONTROLLED_VEHICLE_UNABLE_TO_GET_TO_ROAD(Ped ped) { return invoke<BOOL>(0x3E38E28A1D80DDF6, ped); }
	NATIVE_DECL void TASK_GO_TO_COORD_ANY_MEANS(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, BOOL useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets) { invoke<Void>(0x5BC448CB78FA3E88, ped, x, y, z, moveBlendRatio, vehicle, useLongRangeVehiclePathing, drivingFlags, maxRangeToShootTargets); }
	NATIVE_DECL void TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, BOOL useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets, float extraVehToTargetDistToPreferVehicle, float driveStraightLineDistance, int extraFlags, float warpTimerMS) { invoke<Void>(0x1DD45F9ECFDB1BC9, ped, x, y, z, moveBlendRatio, vehicle, useLongRangeVehiclePathing, drivingFlags, maxRangeToShootTargets, extraVehToTargetDistToPreferVehicle, driveStraightLineDistance, extraFlags, warpTimerMS); }
	NATIVE_DECL void TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, BOOL useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets, float extraVehToTargetDistToPreferVehicle, float driveStraightLineDistance, int extraFlags, float cruiseSpeed, float targetArriveDist) { invoke<Void>(0xB8ECD61F531A7B02, ped, x, y, z, moveBlendRatio, vehicle, useLongRangeVehiclePathing, drivingFlags, maxRangeToShootTargets, extraVehToTargetDistToPreferVehicle, driveStraightLineDistance, extraFlags, cruiseSpeed, targetArriveDist); }
	NATIVE_DECL void TASK_PLAY_ANIM(Ped ped, const char* animDictionary, const char* animationName, float blendInSpeed, float blendOutSpeed, int duration, int flag, float playbackRate, BOOL lockX, BOOL lockY, BOOL lockZ) { invoke<Void>(0xEA47FE3719165B94, ped, animDictionary, animationName, blendInSpeed, blendOutSpeed, duration, flag, playbackRate, lockX, lockY, lockZ); }
	NATIVE_DECL void TASK_PLAY_ANIM_ADVANCED(Ped ped, const char* animDict, const char* animName, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float animEnterSpeed, float animExitSpeed, int duration, Any flag, float animTime, int rotOrder, int ikFlags) { invoke<Void>(0x83CDB10EA29B370B, ped, animDict, animName, posX, posY, posZ, rotX, rotY, rotZ, animEnterSpeed, animExitSpeed, duration, flag, animTime, rotOrder, ikFlags); }
	NATIVE_DECL void STOP_ANIM_TASK(Entity entity, const char* animDictionary, const char* animationName, float blendDelta) { invoke<Void>(0x97FF36A1D40EA00A, entity, animDictionary, animationName, blendDelta); }
	NATIVE_DECL void TASK_SCRIPTED_ANIMATION(Ped ped, int* priorityLowData, int* priorityMidData, int* priorityHighData, float blendInDelta, float blendOutDelta) { invoke<Void>(0x126EF75F1E17ABE5, ped, priorityLowData, priorityMidData, priorityHighData, blendInDelta, blendOutDelta); }
	NATIVE_DECL void PLAY_ENTITY_SCRIPTED_ANIM(Entity entity, int* priorityLowData, int* priorityMidData, int* priorityHighData, float blendInDelta, float blendOutDelta) { invoke<Void>(0x77A1EEC547E7FCF1, entity, priorityLowData, priorityMidData, priorityHighData, blendInDelta, blendOutDelta); }
	NATIVE_DECL void STOP_ANIM_PLAYBACK(Entity entity, int priority, BOOL secondary) { invoke<Void>(0xEE08C992D238C5D1, entity, priority, secondary); }
	NATIVE_DECL void SET_ANIM_WEIGHT(Entity entity, float weight, int priority, int index, BOOL secondary) { invoke<Void>(0x207F1A47C0342F48, entity, weight, priority, index, secondary); }
	NATIVE_DECL void SET_ANIM_PHASE(Entity entity, float phase, int priority, BOOL secondary) { invoke<Void>(0xDDF3CB5A0A4C0B49, entity, phase, priority, secondary); }
	NATIVE_DECL void SET_ANIM_RATE(Entity entity, float rate, int priority, BOOL secondary) { invoke<Void>(0x032D49C5E359C847, entity, rate, priority, secondary); }
	NATIVE_DECL void SET_ANIM_LOOPED(Entity entity, BOOL looped, int priority, BOOL secondary) { invoke<Void>(0x70033C3CC29A1FF4, entity, looped, priority, secondary); }
	NATIVE_DECL void TASK_PLAY_PHONE_GESTURE_ANIMATION(Ped ped, const char* animDict, const char* animation, const char* boneMaskType, float blendInDuration, float blendOutDuration, BOOL isLooping, BOOL holdLastFrame) { invoke<Void>(0x8FBB6758B3B3E9EC, ped, animDict, animation, boneMaskType, blendInDuration, blendOutDuration, isLooping, holdLastFrame); }
	NATIVE_DECL void TASK_STOP_PHONE_GESTURE_ANIMATION(Ped ped, float blendOutOverride) { invoke<Void>(0x3FA00D4F4641BFAE, ped, blendOutOverride); }
	NATIVE_DECL BOOL IS_PLAYING_PHONE_GESTURE_ANIM(Ped ped) { return invoke<BOOL>(0xB8EBB1E9D3588C10, ped); }
	NATIVE_DECL float GET_PHONE_GESTURE_ANIM_CURRENT_TIME(Ped ped) { return invoke<float>(0x47619ABE8B268C60, ped); }
	NATIVE_DECL float GET_PHONE_GESTURE_ANIM_TOTAL_TIME(Ped ped) { return invoke<float>(0x1EE0F68A7C25DEC6, ped); }
	NATIVE_DECL void TASK_VEHICLE_PLAY_ANIM(Vehicle vehicle, const char* animationSet, const char* animationName) { invoke<Void>(0x69F5C3BD0F3EBD89, vehicle, animationSet, animationName); }
	NATIVE_DECL void TASK_LOOK_AT_COORD(Entity entity, float x, float y, float z, int duration, int flags, int priority) { invoke<Void>(0x6FA46612594F7973, entity, x, y, z, duration, flags, priority); }
	NATIVE_DECL void TASK_LOOK_AT_ENTITY(Ped ped, Entity lookAt, int duration, int flags, int priority) { invoke<Void>(0x69F4BE8C8CC4796C, ped, lookAt, duration, flags, priority); }
	NATIVE_DECL void TASK_CLEAR_LOOK_AT(Ped ped) { invoke<Void>(0x0F804F1DB19B9689, ped); }
	NATIVE_DECL void OPEN_SEQUENCE_TASK(int* taskSequenceId) { invoke<Void>(0xE8854A4326B9E12B, taskSequenceId); }
	NATIVE_DECL void CLOSE_SEQUENCE_TASK(int taskSequenceId) { invoke<Void>(0x39E72BC99E6360CB, taskSequenceId); }
	NATIVE_DECL void TASK_PERFORM_SEQUENCE(Ped ped, int taskSequenceId) { invoke<Void>(0x5ABA3986D90D8A3B, ped, taskSequenceId); }
	NATIVE_DECL void TASK_PERFORM_SEQUENCE_LOCALLY(Ped ped, int taskSequenceId) { invoke<Void>(0x8C33220C8D78CA0D, ped, taskSequenceId); }
	NATIVE_DECL void CLEAR_SEQUENCE_TASK(int* taskSequenceId) { invoke<Void>(0x3841422E9C488D8C, taskSequenceId); }
	NATIVE_DECL void SET_SEQUENCE_TO_REPEAT(int taskSequenceId, BOOL repeat) { invoke<Void>(0x58C70CF3A41E4AE7, taskSequenceId, repeat); }
	NATIVE_DECL void SET_SEQUENCE_PREVENT_MIGRATION(int taskSequenceId) { invoke<Void>(0xF5D1F489147CB683, taskSequenceId); }
	NATIVE_DECL int GET_SEQUENCE_PROGRESS(Ped ped) { return invoke<int>(0x00A9010CFE1E3533, ped); }
	NATIVE_DECL BOOL GET_IS_TASK_ACTIVE(Ped ped, int taskIndex) { return invoke<BOOL>(0xB0760331C7AA4155, ped, taskIndex); }
	NATIVE_DECL int GET_SCRIPT_TASK_STATUS(Ped ped, Hash taskHash) { return invoke<int>(0x77F1BEB8863288D5, ped, taskHash); }
	NATIVE_DECL int GET_ACTIVE_VEHICLE_MISSION_TYPE(Vehicle vehicle) { return invoke<int>(0x534AEBA6E5ED4CAB, vehicle); }
	NATIVE_DECL void TASK_LEAVE_ANY_VEHICLE(Ped ped, int delayTime, int flags) { invoke<Void>(0x504D54DF3F6F2247, ped, delayTime, flags); }
	NATIVE_DECL void TASK_AIM_GUN_SCRIPTED(Ped ped, Hash scriptTask, BOOL disableBlockingClip, BOOL instantBlendToAim) { invoke<Void>(0x7A192BE16D373D00, ped, scriptTask, disableBlockingClip, instantBlendToAim); }
	NATIVE_DECL void TASK_AIM_GUN_SCRIPTED_WITH_TARGET(Ped ped, Ped target, float x, float y, float z, int gunTaskType, BOOL disableBlockingClip, BOOL forceAim) { invoke<Void>(0x8605AF0DE8B3A5AC, ped, target, x, y, z, gunTaskType, disableBlockingClip, forceAim); }
	NATIVE_DECL void UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET(Ped ped, Ped target, float x, float y, float z, BOOL disableBlockingClip) { invoke<Void>(0x9724FB59A3E72AD0, ped, target, x, y, z, disableBlockingClip); }
	NATIVE_DECL const char* GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK(int gunTaskType) { return invoke<const char*>(0x3A8CADC7D37AACC5, gunTaskType); }
	NATIVE_DECL void TASK_AIM_GUN_AT_ENTITY(Ped ped, Entity entity, int duration, BOOL instantBlendToAim) { invoke<Void>(0x9B53BB6E8943AF53, ped, entity, duration, instantBlendToAim); }
	NATIVE_DECL void TASK_TURN_PED_TO_FACE_ENTITY(Ped ped, Entity entity, int duration) { invoke<Void>(0x5AD23D40115353AC, ped, entity, duration); }
	NATIVE_DECL void TASK_AIM_GUN_AT_COORD(Ped ped, float x, float y, float z, int time, BOOL instantBlendToAim, BOOL playAnimIntro) { invoke<Void>(0x6671F3EEC681BDA1, ped, x, y, z, time, instantBlendToAim, playAnimIntro); }
	NATIVE_DECL void TASK_SHOOT_AT_COORD(Ped ped, float x, float y, float z, int duration, Hash firingPattern) { invoke<Void>(0x46A6CC01E0826106, ped, x, y, z, duration, firingPattern); }
	NATIVE_DECL void TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(Ped ped, Vehicle vehicle, BOOL useAlternateShuffle) { invoke<Void>(0x7AA80209BDA643EB, ped, vehicle, useAlternateShuffle); }
	NATIVE_DECL void CLEAR_PED_TASKS(Ped ped) { invoke<Void>(0xE1EF3C1216AFF2CD, ped); }
	NATIVE_DECL void CLEAR_PED_SCRIPT_TASK_IF_RUNNING_THREAT_RESPONSE_NON_TEMP_TASK(Ped ped) { invoke<Void>(0xF6DC48E56BE1243A, ped); }
	NATIVE_DECL void CLEAR_PED_SECONDARY_TASK(Ped ped) { invoke<Void>(0x176CECF6F920D707, ped); }
	NATIVE_DECL void TASK_EVERYONE_LEAVE_VEHICLE(Vehicle vehicle) { invoke<Void>(0x7F93691AB4B92272, vehicle); }
	NATIVE_DECL void TASK_GOTO_ENTITY_OFFSET(Ped ped, Entity entity, int time, float seekRadius, float seekAngleDeg, float moveBlendRatio, int gotoEntityOffsetFlags) { invoke<Void>(0xE39B4FF4FDEBDE27, ped, entity, time, seekRadius, seekAngleDeg, moveBlendRatio, gotoEntityOffsetFlags); }
	NATIVE_DECL void TASK_GOTO_ENTITY_OFFSET_XY(Ped ped, Entity entity, int duration, float targetRadius, float offsetX, float offsetY, float moveBlendRatio, int gotoEntityOffsetFlags) { invoke<Void>(0x338E7EF52B6095A9, ped, entity, duration, targetRadius, offsetX, offsetY, moveBlendRatio, gotoEntityOffsetFlags); }
	NATIVE_DECL void TASK_TURN_PED_TO_FACE_COORD(Ped ped, float x, float y, float z, int duration) { invoke<Void>(0x1DDA930A0AC38571, ped, x, y, z, duration); }
	NATIVE_DECL void TASK_VEHICLE_TEMP_ACTION(Ped driver, Vehicle vehicle, int action, int time) { invoke<Void>(0xC429DCEEB339E129, driver, vehicle, action, time); }
	NATIVE_DECL void TASK_VEHICLE_MISSION(Ped driver, Vehicle vehicle, Vehicle vehicleTarget, int missionType, float cruiseSpeed, int drivingStyle, float targetReached, float straightLineDistance, BOOL DriveAgainstTraffic) { invoke<Void>(0x659427E0EF36BCDE, driver, vehicle, vehicleTarget, missionType, cruiseSpeed, drivingStyle, targetReached, straightLineDistance, DriveAgainstTraffic); }
	NATIVE_DECL void TASK_VEHICLE_MISSION_PED_TARGET(Ped ped, Vehicle vehicle, Ped pedTarget, int missionType, float maxSpeed, int drivingStyle, float minDistance, float straightLineDistance, BOOL DriveAgainstTraffic) { invoke<Void>(0x9454528DF15D657A, ped, vehicle, pedTarget, missionType, maxSpeed, drivingStyle, minDistance, straightLineDistance, DriveAgainstTraffic); }
	NATIVE_DECL void TASK_VEHICLE_MISSION_COORS_TARGET(Ped ped, Vehicle vehicle, float x, float y, float z, int mission, float cruiseSpeed, int drivingStyle, float targetReached, float straightLineDistance, BOOL DriveAgainstTraffic) { invoke<Void>(0xF0AF20AA7731F8C3, ped, vehicle, x, y, z, mission, cruiseSpeed, drivingStyle, targetReached, straightLineDistance, DriveAgainstTraffic); }
	NATIVE_DECL void TASK_VEHICLE_ESCORT(Ped ped, Vehicle vehicle, Vehicle targetVehicle, int mode, float speed, int drivingStyle, float minDistance, int minHeightAboveTerrain, float noRoadsDistance) { invoke<Void>(0x0FA6E4B75F302400, ped, vehicle, targetVehicle, mode, speed, drivingStyle, minDistance, minHeightAboveTerrain, noRoadsDistance); }
	NATIVE_DECL void TASK_VEHICLE_FOLLOW(Ped driver, Vehicle vehicle, Entity targetEntity, float speed, int drivingStyle, int minDistance) { invoke<Void>(0xFC545A9F0626E3B6, driver, vehicle, targetEntity, speed, drivingStyle, minDistance); }
	NATIVE_DECL void TASK_VEHICLE_CHASE(Ped driver, Entity targetEnt) { invoke<Void>(0x3C08A8E30363B353, driver, targetEnt); }
	NATIVE_DECL void TASK_VEHICLE_HELI_PROTECT(Ped pilot, Vehicle vehicle, Entity entityToFollow, float targetSpeed, int drivingFlags, float radius, int altitude, int heliFlags) { invoke<Void>(0x1E09C32048FEFD1C, pilot, vehicle, entityToFollow, targetSpeed, drivingFlags, radius, altitude, heliFlags); }
	NATIVE_DECL void SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(Ped ped, int flag, BOOL set) { invoke<Void>(0xCC665AAC360D31E7, ped, flag, set); }
	NATIVE_DECL void SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(Ped ped, float distance) { invoke<Void>(0x639B642FACBE4EDD, ped, distance); }
	NATIVE_DECL void TASK_HELI_CHASE(Ped pilot, Entity entityToFollow, float x, float y, float z) { invoke<Void>(0xAC83B1DB38D0ADA0, pilot, entityToFollow, x, y, z); }
	NATIVE_DECL void TASK_PLANE_CHASE(Ped pilot, Entity entityToFollow, float x, float y, float z) { invoke<Void>(0x2D2386F273FF7A25, pilot, entityToFollow, x, y, z); }
	NATIVE_DECL void TASK_PLANE_LAND(Ped pilot, Vehicle plane, float runwayStartX, float runwayStartY, float runwayStartZ, float runwayEndX, float runwayEndY, float runwayEndZ) { invoke<Void>(0xBF19721FA34D32C0, pilot, plane, runwayStartX, runwayStartY, runwayStartZ, runwayEndX, runwayEndY, runwayEndZ); }
	NATIVE_DECL void CLEAR_DEFAULT_PRIMARY_TASK(Ped ped) { invoke<Void>(0x6100B3CEFD43452E, ped); }
	NATIVE_DECL void CLEAR_PRIMARY_VEHICLE_TASK(Vehicle vehicle) { invoke<Void>(0xDBBC7A2432524127, vehicle); }
	NATIVE_DECL void CLEAR_VEHICLE_CRASH_TASK(Vehicle vehicle) { invoke<Void>(0x53DDC75BC3AC0A90, vehicle); }
	NATIVE_DECL void TASK_PLANE_GOTO_PRECISE_VTOL(Ped ped, Vehicle vehicle, float x, float y, float z, int flightHeight, int minHeightAboveTerrain, BOOL useDesiredOrientation, float desiredOrientation, BOOL autopilot) { invoke<Void>(0xF7F9DCCA89E7505B, ped, vehicle, x, y, z, flightHeight, minHeightAboveTerrain, useDesiredOrientation, desiredOrientation, autopilot); }
	NATIVE_DECL void TASK_SUBMARINE_GOTO_AND_STOP(Ped ped, Vehicle submarine, float x, float y, float z, BOOL autopilot) { invoke<Void>(0xC22B40579A498CA4, ped, submarine, x, y, z, autopilot); }
	NATIVE_DECL void TASK_HELI_MISSION(Ped pilot, Vehicle aircraft, Vehicle targetVehicle, Ped targetPed, float destinationX, float destinationY, float destinationZ, int missionFlag, float maxSpeed, float radius, float targetHeading, int maxHeight, int minHeight, float slowDownDistance, int behaviorFlags) { invoke<Void>(0xDAD029E187A2BEB4, pilot, aircraft, targetVehicle, targetPed, destinationX, destinationY, destinationZ, missionFlag, maxSpeed, radius, targetHeading, maxHeight, minHeight, slowDownDistance, behaviorFlags); }
	NATIVE_DECL void TASK_HELI_ESCORT_HELI(Ped pilot, Vehicle heli1, Vehicle heli2, float offsetX, float offsetY, float offsetZ) { invoke<Void>(0xB385523325077210, pilot, heli1, heli2, offsetX, offsetY, offsetZ); }
	NATIVE_DECL void TASK_PLANE_MISSION(Ped pilot, Vehicle aircraft, Vehicle targetVehicle, Ped targetPed, float destinationX, float destinationY, float destinationZ, int missionFlag, float angularDrag, float targetReached, float targetHeading, float maxZ, float minZ, BOOL precise) { invoke<Void>(0x23703CD154E83B88, pilot, aircraft, targetVehicle, targetPed, destinationX, destinationY, destinationZ, missionFlag, angularDrag, targetReached, targetHeading, maxZ, minZ, precise); }
	NATIVE_DECL void TASK_PLANE_TAXI(Ped pilot, Vehicle aircraft, float x, float y, float z, float cruiseSpeed, float targetReached) { invoke<Void>(0x92C360B5F15D2302, pilot, aircraft, x, y, z, cruiseSpeed, targetReached); }
	NATIVE_DECL void TASK_BOAT_MISSION(Ped pedDriver, Vehicle vehicle, Vehicle targetVehicle, Ped targetPed, float x, float y, float z, int mission, float maxSpeed, int drivingStyle, float targetReached, Any boatFlags) { invoke<Void>(0x15C86013127CE63F, pedDriver, vehicle, targetVehicle, targetPed, x, y, z, mission, maxSpeed, drivingStyle, targetReached, boatFlags); }
	NATIVE_DECL void TASK_DRIVE_BY(Ped driverPed, Ped targetPed, Vehicle targetVehicle, float targetX, float targetY, float targetZ, float distanceToShoot, int pedAccuracy, BOOL pushUnderneathDrivingTaskIfDriving, Hash firingPattern) { invoke<Void>(0x2F8AF0E82773A171, driverPed, targetPed, targetVehicle, targetX, targetY, targetZ, distanceToShoot, pedAccuracy, pushUnderneathDrivingTaskIfDriving, firingPattern); }
	NATIVE_DECL void SET_DRIVEBY_TASK_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, float x, float y, float z) { invoke<Void>(0xE5B302114D8162EE, shootingPed, targetPed, targetVehicle, x, y, z); }
	NATIVE_DECL void CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped) { invoke<Void>(0xC35B5CDB2824CF69, ped); }
	NATIVE_DECL BOOL IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped) { return invoke<BOOL>(0x8785E6E40C7A8818, ped); }
	NATIVE_DECL BOOL CONTROL_MOUNTED_WEAPON(Ped ped) { return invoke<BOOL>(0xDCFE42068FE0135A, ped); }
	NATIVE_DECL void SET_MOUNTED_WEAPON_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, float x, float y, float z, int taskMode, BOOL ignoreTargetVehDeadCheck) { invoke<Void>(0xCCD892192C6D2BB9, shootingPed, targetPed, targetVehicle, x, y, z, taskMode, ignoreTargetVehDeadCheck); }
	NATIVE_DECL BOOL IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK(Ped ped) { return invoke<BOOL>(0xA320EF046186FA3B, ped); }
	NATIVE_DECL void TASK_USE_MOBILE_PHONE(Ped ped, BOOL usePhone, int desiredPhoneMode) { invoke<Void>(0xBD2A8EC3AF4DE7DB, ped, usePhone, desiredPhoneMode); }
	NATIVE_DECL void TASK_USE_MOBILE_PHONE_TIMED(Ped ped, int duration) { invoke<Void>(0x5EE02954A14C69DB, ped, duration); }
	NATIVE_DECL void TASK_CHAT_TO_PED(Ped ped, Ped target, int flags, float goToLocationX, float goToLocationY, float goToLocationZ, float headingDegs, float idleTime) { invoke<Void>(0x8C338E0263E4FD19, ped, target, flags, goToLocationX, goToLocationY, goToLocationZ, headingDegs, idleTime); }
	NATIVE_DECL void TASK_WARP_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seat) { invoke<Void>(0x9A7D091411C5F684, ped, vehicle, seat); }
	NATIVE_DECL void TASK_SHOOT_AT_ENTITY(Entity entity, Entity target, int duration, Hash firingPattern) { invoke<Void>(0x08DA95E8298AE772, entity, target, duration, firingPattern); }
	NATIVE_DECL void TASK_CLIMB(Ped ped, BOOL usePlayerLaunchForce) { invoke<Void>(0x89D9FCC2435112F1, ped, usePlayerLaunchForce); }
	NATIVE_DECL void TASK_CLIMB_LADDER(Ped ped, BOOL fast) { invoke<Void>(0xB6C987F9285A3814, ped, fast); }
	NATIVE_DECL void TASK_RAPPEL_DOWN_WALL_USING_CLIPSET_OVERRIDE(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, float minZ, int ropeHandle, const char* clipSet, Any p10, Any p11) { invoke<Void>(0xEAF66ACDDC794793, ped, x1, y1, z1, x2, y2, z2, minZ, ropeHandle, clipSet, p10, p11); }
	NATIVE_DECL int GET_TASK_RAPPEL_DOWN_WALL_STATE(Ped ped) { return invoke<int>(0x9D252648778160DF, ped); }
	NATIVE_DECL void CLEAR_PED_TASKS_IMMEDIATELY(Ped ped) { invoke<Void>(0xAAA34F8A7CB32098, ped); }
	NATIVE_DECL void TASK_PERFORM_SEQUENCE_FROM_PROGRESS(Ped ped, int taskIndex, int progress1, int progress2) { invoke<Void>(0x89221B16730234F0, ped, taskIndex, progress1, progress2); }
	NATIVE_DECL void SET_NEXT_DESIRED_MOVE_STATE(float nextMoveState) { invoke<Void>(0xF1B9F16E89E2C93A, nextMoveState); }
	NATIVE_DECL void SET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped, float newMoveBlendRatio) { invoke<Void>(0x1E982AC8716912C5, ped, newMoveBlendRatio); }
	NATIVE_DECL float GET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped) { return invoke<float>(0x8517D4A6CA8513ED, ped); }
	NATIVE_DECL void TASK_GOTO_ENTITY_AIMING(Ped ped, Entity target, float distanceToStopAt, float StartAimingDist) { invoke<Void>(0xA9DA48FAB8A76C12, ped, target, distanceToStopAt, StartAimingDist); }
	NATIVE_DECL void TASK_SET_DECISION_MAKER(Ped ped, Hash decisionMakerId) { invoke<Void>(0xEB8517DDA73720DA, ped, decisionMakerId); }
	NATIVE_DECL void TASK_SET_SPHERE_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float radius) { invoke<Void>(0x933C06518B52A9A4, ped, x, y, z, radius); }
	NATIVE_DECL void TASK_CLEAR_DEFENSIVE_AREA(Ped ped) { invoke<Void>(0x95A6C46A31D1917D, ped); }
	NATIVE_DECL void TASK_PED_SLIDE_TO_COORD(Ped ped, float x, float y, float z, float heading, float speed) { invoke<Void>(0xD04FE6765D990A06, ped, x, y, z, heading, speed); }
	NATIVE_DECL void TASK_PED_SLIDE_TO_COORD_HDG_RATE(Ped ped, float x, float y, float z, float heading, float speed, float headingChangeRate) { invoke<Void>(0x5A4A6A6D3DC64F52, ped, x, y, z, heading, speed, headingChangeRate); }
	NATIVE_DECL ScrHandle ADD_COVER_POINT(float x, float y, float z, float direction, int usage, int height, int arc, BOOL isPriority) { return invoke<ScrHandle>(0xD5C12A75C7B9497F, x, y, z, direction, usage, height, arc, isPriority); }
	NATIVE_DECL void REMOVE_COVER_POINT(ScrHandle coverpoint) { invoke<Void>(0xAE287C923D891715, coverpoint); }
	NATIVE_DECL BOOL DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS(float x, float y, float z) { return invoke<BOOL>(0xA98B8E3C088E5A31, x, y, z); }
	NATIVE_DECL Vector3 GET_SCRIPTED_COVER_POINT_COORDS(ScrHandle coverpoint) { return invoke<Vector3>(0x594A1028FC2A3E85, coverpoint); }
	NATIVE_DECL void ADD_SCRIPTED_COVER_AREA(float x, float y, float z, float radius) { invoke<Void>(0x28B7B9BFDAF274AA, x, y, z, radius); }
	NATIVE_DECL void TASK_COMBAT_PED(Ped ped, Ped targetPed, int combatFlags, int threatResponseFlags) { invoke<Void>(0xF166E48407BAC484, ped, targetPed, combatFlags, threatResponseFlags); }
	NATIVE_DECL void TASK_COMBAT_PED_TIMED(Ped ped, Ped target, int time, int flags) { invoke<Void>(0x944F30DCB7096BDE, ped, target, time, flags); }
	NATIVE_DECL void TASK_SEEK_COVER_FROM_POS(Ped ped, float x, float y, float z, int duration, BOOL allowPeekingAndFiring) { invoke<Void>(0x75AC2B60386D89F2, ped, x, y, z, duration, allowPeekingAndFiring); }
	NATIVE_DECL void TASK_SEEK_COVER_FROM_PED(Ped ped, Ped target, int duration, BOOL allowPeekingAndFiring) { invoke<Void>(0x84D32B3BEC531324, ped, target, duration, allowPeekingAndFiring); }
	NATIVE_DECL void TASK_SEEK_COVER_TO_COVER_POINT(Ped ped, ScrHandle coverpoint, float x, float y, float z, int time, BOOL allowPeekingAndFiring) { invoke<Void>(0xD43D95C7A869447F, ped, coverpoint, x, y, z, time, allowPeekingAndFiring); }
	NATIVE_DECL void TASK_SEEK_COVER_TO_COORDS(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, int timeout, BOOL shortRoute) { invoke<Void>(0x39246A6958EF072C, ped, x1, y1, z1, x2, y2, z2, timeout, shortRoute); }
	NATIVE_DECL void TASK_PUT_PED_DIRECTLY_INTO_COVER(Ped ped, float x, float y, float z, int time, BOOL allowPeekingAndFiring, float blendInDuration, BOOL forceInitialFacingDirection, BOOL forceFaceLeft, int identifier, BOOL doEntry) { invoke<Void>(0x4172393E6BE1FECE, ped, x, y, z, time, allowPeekingAndFiring, blendInDuration, forceInitialFacingDirection, forceFaceLeft, identifier, doEntry); }
	NATIVE_DECL void TASK_WARP_PED_DIRECTLY_INTO_COVER(Ped ped, int time, BOOL allowPeekingAndFiring, BOOL forceInitialFacingDirection, BOOL forceFaceLeft, int identifier) { invoke<Void>(0x6E01E9E8D89F8276, ped, time, allowPeekingAndFiring, forceInitialFacingDirection, forceFaceLeft, identifier); }
	NATIVE_DECL void TASK_EXIT_COVER(Ped ped, int exitType, float x, float y, float z) { invoke<Void>(0x79B258E397854D29, ped, exitType, x, y, z); }
	NATIVE_DECL void TASK_PUT_PED_DIRECTLY_INTO_MELEE(Ped ped, Ped meleeTarget, float blendInDuration, float timeInMelee, float strafePhaseSync, int aiCombatFlags) { invoke<Void>(0x1C6CD14A876FFE39, ped, meleeTarget, blendInDuration, timeInMelee, strafePhaseSync, aiCombatFlags); }
	NATIVE_DECL void TASK_TOGGLE_DUCK(Ped ped, int toggleType) { invoke<Void>(0xAC96609B9995EDF8, ped, toggleType); }
	NATIVE_DECL void TASK_GUARD_CURRENT_POSITION(Ped ped, float maxPatrolProximity, float defensiveAreaRadius, BOOL setDefensiveArea) { invoke<Void>(0x4A58A47A72E3FCB4, ped, maxPatrolProximity, defensiveAreaRadius, setDefensiveArea); }
	NATIVE_DECL void TASK_GUARD_ASSIGNED_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float heading, float maxPatrolProximity, int timer) { invoke<Void>(0xD2A207EEBDF9889B, ped, x, y, z, heading, maxPatrolProximity, timer); }
	NATIVE_DECL void TASK_GUARD_SPHERE_DEFENSIVE_AREA(Ped ped, float defendPositionX, float defendPositionY, float defendPositionZ, float heading, float maxPatrolProximity, int time, float x, float y, float z, float defensiveAreaRadius) { invoke<Void>(0xC946FE14BE0EB5E2, ped, defendPositionX, defendPositionY, defendPositionZ, heading, maxPatrolProximity, time, x, y, z, defensiveAreaRadius); }
	NATIVE_DECL void TASK_STAND_GUARD(Ped ped, float x, float y, float z, float heading, const char* scenarioName) { invoke<Void>(0xAE032F8BBA959E90, ped, x, y, z, heading, scenarioName); }
	NATIVE_DECL void SET_DRIVE_TASK_CRUISE_SPEED(Ped driver, float cruiseSpeed) { invoke<Void>(0x5C9B84BD7D31D908, driver, cruiseSpeed); }
	NATIVE_DECL void SET_DRIVE_TASK_MAX_CRUISE_SPEED(Ped ped, float speed, BOOL updateBaseTask) { invoke<Void>(0x404A5AA9B9F0B746, ped, speed, updateBaseTask); }
	NATIVE_DECL void SET_DRIVE_TASK_DRIVING_STYLE(Ped ped, int drivingStyle) { invoke<Void>(0xDACE1BE37D88AF67, ped, drivingStyle); }
	NATIVE_DECL void ADD_COVER_BLOCKING_AREA(float startX, float startY, float startZ, float endX, float endY, float endZ, BOOL blockObjects, BOOL blockVehicles, BOOL blockMap, BOOL blockPlayer) { invoke<Void>(0x45C597097DD7CB81, startX, startY, startZ, endX, endY, endZ, blockObjects, blockVehicles, blockMap, blockPlayer); }
	NATIVE_DECL void REMOVE_ALL_COVER_BLOCKING_AREAS() { invoke<Void>(0xDB6708C0B46F56D8); }
	NATIVE_DECL void REMOVE_COVER_BLOCKING_AREAS_AT_POSITION(float x, float y, float z) { invoke<Void>(0xFA83CA6776038F64, x, y, z); }
	NATIVE_DECL void REMOVE_SPECIFIC_COVER_BLOCKING_AREAS(float startX, float startY, float startZ, float endX, float endY, float endZ, BOOL blockObjects, BOOL blockVehicles, BOOL blockMap, BOOL blockPlayer) { invoke<Void>(0x1F351CF1C6475734, startX, startY, startZ, endX, endY, endZ, blockObjects, blockVehicles, blockMap, blockPlayer); }
	NATIVE_DECL void TASK_START_SCENARIO_IN_PLACE(Ped ped, const char* scenarioName, int unkDelay, BOOL playEnterAnim) { invoke<Void>(0x142A02425FF02BD9, ped, scenarioName, unkDelay, playEnterAnim); }
	NATIVE_DECL void TASK_START_SCENARIO_AT_POSITION(Ped ped, const char* scenarioName, float x, float y, float z, float heading, int duration, BOOL sittingScenario, BOOL teleport) { invoke<Void>(0xFA4EFC79F69D4F07, ped, scenarioName, x, y, z, heading, duration, sittingScenario, teleport); }
	NATIVE_DECL void TASK_USE_NEAREST_SCENARIO_TO_COORD(Ped ped, float x, float y, float z, float distance, int duration) { invoke<Void>(0x277F471BA9DB000B, ped, x, y, z, distance, duration); }
	NATIVE_DECL void TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(Ped ped, float x, float y, float z, float radius, int timeToLeave) { invoke<Void>(0x58E2E0F23F6B76C3, ped, x, y, z, radius, timeToLeave); }
	NATIVE_DECL void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD(Ped ped, float x, float y, float z, float maxRange, int timeToLeave) { invoke<Void>(0x9FDA1B3D7E7028B3, ped, x, y, z, maxRange, timeToLeave); }
	NATIVE_DECL void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP(Ped ped, float x, float y, float z, float radius, int timeToLeave) { invoke<Void>(0x97A28E63F0BA5631, ped, x, y, z, radius, timeToLeave); }
	NATIVE_DECL BOOL DOES_SCENARIO_EXIST_IN_AREA(float x, float y, float z, float radius, BOOL mustBeFree) { return invoke<BOOL>(0x5A59271FFADD33C1, x, y, z, radius, mustBeFree); }
	NATIVE_DECL BOOL DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA(float x, float y, float z, const char* scenarioName, float radius, BOOL mustBeFree) { return invoke<BOOL>(0x0A9D0C2A3BBC86C1, x, y, z, scenarioName, radius, mustBeFree); }
	NATIVE_DECL BOOL IS_SCENARIO_OCCUPIED(float x, float y, float z, float maxRange, BOOL onlyUsersActuallyAtScenario) { return invoke<BOOL>(0x788756D73AC2E07C, x, y, z, maxRange, onlyUsersActuallyAtScenario); }
	NATIVE_DECL BOOL PED_HAS_USE_SCENARIO_TASK(Ped ped) { return invoke<BOOL>(0x295E3CCEC879CCD7, ped); }
	NATIVE_DECL void PLAY_ANIM_ON_RUNNING_SCENARIO(Ped ped, const char* animDict, const char* animName) { invoke<Void>(0x748040460F8DF5DC, ped, animDict, animName); }
	NATIVE_DECL BOOL DOES_SCENARIO_GROUP_EXIST(const char* scenarioGroup) { return invoke<BOOL>(0xF9034C136C9E00D3, scenarioGroup); }
	NATIVE_DECL BOOL IS_SCENARIO_GROUP_ENABLED(const char* scenarioGroup) { return invoke<BOOL>(0x367A09DED4E05B99, scenarioGroup); }
	NATIVE_DECL void SET_SCENARIO_GROUP_ENABLED(const char* scenarioGroup, BOOL enabled) { invoke<Void>(0x02C8E5B49848664E, scenarioGroup, enabled); }
	NATIVE_DECL void RESET_SCENARIO_GROUPS_ENABLED() { invoke<Void>(0xDD902D0349AFAD3A); }
	NATIVE_DECL void SET_EXCLUSIVE_SCENARIO_GROUP(const char* scenarioGroup) { invoke<Void>(0x535E97E1F7FC0C6A, scenarioGroup); }
	NATIVE_DECL void RESET_EXCLUSIVE_SCENARIO_GROUP() { invoke<Void>(0x4202BBCB8684563D); }
	NATIVE_DECL BOOL IS_SCENARIO_TYPE_ENABLED(const char* scenarioType) { return invoke<BOOL>(0x3A815DB3EA088722, scenarioType); }
	NATIVE_DECL void SET_SCENARIO_TYPE_ENABLED(const char* scenarioType, BOOL toggle) { invoke<Void>(0xEB47EC4E34FB7EE1, scenarioType, toggle); }
	NATIVE_DECL void RESET_SCENARIO_TYPES_ENABLED() { invoke<Void>(0x0D40EE2A7F2B2D6D); }
	NATIVE_DECL BOOL IS_PED_ACTIVE_IN_SCENARIO(Ped ped) { return invoke<BOOL>(0xAA135F9482C82CC3, ped); }
	NATIVE_DECL BOOL IS_PED_PLAYING_BASE_CLIP_IN_SCENARIO(Ped ped) { return invoke<BOOL>(0x621C6E4729388E41, ped); }
	NATIVE_DECL void SET_PED_CAN_PLAY_AMBIENT_IDLES(Ped ped, BOOL blockIdleClips, BOOL removeIdleClipIfPlaying) { invoke<Void>(0x8FD89A6240813FD0, ped, blockIdleClips, removeIdleClipIfPlaying); }
	NATIVE_DECL void TASK_COMBAT_HATED_TARGETS_IN_AREA(Ped ped, float x, float y, float z, float radius, int combatFlags) { invoke<Void>(0x4CF5F55DAC3280A0, ped, x, y, z, radius, combatFlags); }
	NATIVE_DECL void TASK_COMBAT_HATED_TARGETS_AROUND_PED(Ped ped, float radius, int combatFlags) { invoke<Void>(0x7BF835BB9E2698C8, ped, radius, combatFlags); }
	NATIVE_DECL void TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(Ped ped, float radius, int time, int combatFlags) { invoke<Void>(0x2BBA30B854534A0C, ped, radius, time, combatFlags); }
	NATIVE_DECL void TASK_THROW_PROJECTILE(Ped ped, float x, float y, float z, int ignoreCollisionEntityIndex, BOOL createInvincibleProjectile) { invoke<Void>(0x7285951DBF6B5A51, ped, x, y, z, ignoreCollisionEntityIndex, createInvincibleProjectile); }
	NATIVE_DECL void TASK_SWAP_WEAPON(Ped ped, BOOL drawWeapon) { invoke<Void>(0xA21C51255B205245, ped, drawWeapon); }
	NATIVE_DECL void TASK_RELOAD_WEAPON(Ped ped, BOOL drawWeapon) { invoke<Void>(0x62D2916F56B9CD2D, ped, drawWeapon); }
	NATIVE_DECL BOOL IS_PED_GETTING_UP(Ped ped) { return invoke<BOOL>(0x2A74E1D5F2F00EEC, ped); }
	NATIVE_DECL void TASK_WRITHE(Ped ped, Ped target, int minFireLoops, int startState, BOOL forceShootOnGround, int shootFromGroundTimer) { invoke<Void>(0xCDDC2B77CE54AC6E, ped, target, minFireLoops, startState, forceShootOnGround, shootFromGroundTimer); }
	NATIVE_DECL BOOL IS_PED_IN_WRITHE(Ped ped) { return invoke<BOOL>(0xDEB6D52126E7D640, ped); }
	NATIVE_DECL void OPEN_PATROL_ROUTE(const char* patrolRoute) { invoke<Void>(0xA36BFB5EE89F3D82, patrolRoute); }
	NATIVE_DECL void CLOSE_PATROL_ROUTE() { invoke<Void>(0xB043ECA801B8CBC1); }
	NATIVE_DECL void ADD_PATROL_ROUTE_NODE(int nodeId, const char* nodeType, float posX, float posY, float posZ, float headingX, float headingY, float headingZ, int duration) { invoke<Void>(0x8EDF950167586B7C, nodeId, nodeType, posX, posY, posZ, headingX, headingY, headingZ, duration); }
	NATIVE_DECL void ADD_PATROL_ROUTE_LINK(int nodeId1, int nodeId2) { invoke<Void>(0x23083260DEC3A551, nodeId1, nodeId2); }
	NATIVE_DECL void CREATE_PATROL_ROUTE() { invoke<Void>(0xAF8A443CCC8018DC); }
	NATIVE_DECL void DELETE_PATROL_ROUTE(const char* patrolRoute) { invoke<Void>(0x7767DD9D65E91319, patrolRoute); }
	NATIVE_DECL BOOL GET_PATROL_TASK_INFO(Ped ped, int* timeLeftAtNode, int* nodeId) { return invoke<BOOL>(0x52F734CEBE20DFBA, ped, timeLeftAtNode, nodeId); }
	NATIVE_DECL void TASK_PATROL(Ped ped, const char* patrolRouteName, int alertState, BOOL canChatToPeds, BOOL useHeadLookAt) { invoke<Void>(0xBDA5DF49D080FE4E, ped, patrolRouteName, alertState, canChatToPeds, useHeadLookAt); }
	NATIVE_DECL void TASK_STAY_IN_COVER(Ped ped) { invoke<Void>(0xE5DA8615A6180789, ped); }
	NATIVE_DECL void ADD_VEHICLE_SUBTASK_ATTACK_COORD(Ped ped, float x, float y, float z) { invoke<Void>(0x5CF0D8F9BBA0DD75, ped, x, y, z); }
	NATIVE_DECL void ADD_VEHICLE_SUBTASK_ATTACK_PED(Ped ped, Ped target) { invoke<Void>(0x85F462BADC7DA47F, ped, target); }
	NATIVE_DECL void TASK_VEHICLE_SHOOT_AT_PED(Ped ped, Ped target, float fireTolerance) { invoke<Void>(0x10AB107B887214D8, ped, target, fireTolerance); }
	NATIVE_DECL void TASK_VEHICLE_AIM_AT_PED(Ped ped, Ped target) { invoke<Void>(0xE41885592B08B097, ped, target); }
	NATIVE_DECL void TASK_VEHICLE_SHOOT_AT_COORD(Ped ped, float x, float y, float z, float fireTolerance) { invoke<Void>(0x5190796ED39C9B6D, ped, x, y, z, fireTolerance); }
	NATIVE_DECL void TASK_VEHICLE_AIM_AT_COORD(Ped ped, float x, float y, float z) { invoke<Void>(0x447C1E9EF844BC0F, ped, x, y, z); }
	NATIVE_DECL void TASK_VEHICLE_GOTO_NAVMESH(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, int behaviorFlag, float stoppingRange) { invoke<Void>(0x195AEEB13CEFE2EE, ped, vehicle, x, y, z, speed, behaviorFlag, stoppingRange); }
	NATIVE_DECL void TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(Ped ped, float x, float y, float z, float aimAtX, float aimAtY, float aimAtZ, float moveBlendRatio, BOOL shoot, float targetRadius, float slowDistance, BOOL useNavMesh, int navFlags, BOOL instantBlendToAim, Hash firingPattern) { invoke<Void>(0x11315AB3385B8AC0, ped, x, y, z, aimAtX, aimAtY, aimAtZ, moveBlendRatio, shoot, targetRadius, slowDistance, useNavMesh, navFlags, instantBlendToAim, firingPattern); }
	NATIVE_DECL void TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(Ped ped, float x, float y, float z, Entity aimAtID, float moveBlendRatio, BOOL shoot, float targetRadius, float slowDistance, BOOL useNavMesh, int navFlags, BOOL instantBlendToAim, Hash firingPattern, int time) { invoke<Void>(0xB2A16444EAD9AE47, ped, x, y, z, aimAtID, moveBlendRatio, shoot, targetRadius, slowDistance, useNavMesh, navFlags, instantBlendToAim, firingPattern, time); }
	NATIVE_DECL void TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(Ped pedHandle, float goToLocationX, float goToLocationY, float goToLocationZ, float focusLocationX, float focusLocationY, float focusLocationZ, float speed, BOOL shootAtEnemies, float distanceToStopAt, float noRoadsDistance, BOOL useNavMesh, int navFlags, int taskFlags, Hash firingPattern) { invoke<Void>(0xA55547801EB331FC, pedHandle, goToLocationX, goToLocationY, goToLocationZ, focusLocationX, focusLocationY, focusLocationZ, speed, shootAtEnemies, distanceToStopAt, noRoadsDistance, useNavMesh, navFlags, taskFlags, firingPattern); }
	NATIVE_DECL void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD(Ped ped, Entity entity, float aimX, float aimY, float aimZ, float moveBlendRatio, BOOL shoot, float targetRadius, float slowDistance, BOOL useNavMesh, BOOL instantBlendToAim, Hash firingPattern) { invoke<Void>(0x04701832B739DCE5, ped, entity, aimX, aimY, aimZ, moveBlendRatio, shoot, targetRadius, slowDistance, useNavMesh, instantBlendToAim, firingPattern); }
	NATIVE_DECL void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(Ped ped, Entity entityToWalkTo, Entity entityToAimAt, float speed, BOOL shootatEntity, float targetRadius, float slowDistance, BOOL useNavMesh, BOOL instantBlendToAim, Hash firingPattern) { invoke<Void>(0x97465886D35210E9, ped, entityToWalkTo, entityToAimAt, speed, shootatEntity, targetRadius, slowDistance, useNavMesh, instantBlendToAim, firingPattern); }
	NATIVE_DECL void SET_HIGH_FALL_TASK(Ped ped, int minTime, int maxTime, int entryType) { invoke<Void>(0x8C825BDC7741D37C, ped, minTime, maxTime, entryType); }
	NATIVE_DECL void REQUEST_WAYPOINT_RECORDING(const char* name) { invoke<Void>(0x9EEFB62EB27B5792, name); }
	NATIVE_DECL BOOL GET_IS_WAYPOINT_RECORDING_LOADED(const char* name) { return invoke<BOOL>(0xCB4E8BE8A0063C5D, name); }
	NATIVE_DECL void REMOVE_WAYPOINT_RECORDING(const char* name) { invoke<Void>(0xFF1B8B4AA1C25DC8, name); }
	NATIVE_DECL BOOL WAYPOINT_RECORDING_GET_NUM_POINTS(const char* name, int* points) { return invoke<BOOL>(0x5343532C01A07234, name, points); }
	NATIVE_DECL BOOL WAYPOINT_RECORDING_GET_COORD(const char* name, int point, Vector3* coord) { return invoke<BOOL>(0x2FB897405C90B361, name, point, coord); }
	NATIVE_DECL float WAYPOINT_RECORDING_GET_SPEED_AT_POINT(const char* name, int point) { return invoke<float>(0x005622AEBC33ACA9, name, point); }
	NATIVE_DECL BOOL WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT(const char* name, float x, float y, float z, int* point) { return invoke<BOOL>(0xB629A298081F876F, name, x, y, z, point); }
	NATIVE_DECL void TASK_FOLLOW_WAYPOINT_RECORDING(Ped ped, const char* name, int p2, int p3, int p4) { invoke<Void>(0x0759591819534F7B, ped, name, p2, p3, p4); }
	NATIVE_DECL BOOL IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED(Ped ped) { return invoke<BOOL>(0xE03B3F2D3DC59B64, ped); }
	NATIVE_DECL int GET_PED_WAYPOINT_PROGRESS(Ped ped) { return invoke<int>(0x2720AAA75001E094, ped); }
	NATIVE_DECL void SET_PED_WAYPOINT_PROGRESS(Ped ped, int progress) { invoke<Void>(0x686ECCD99D4E61BB, ped, progress); }
	NATIVE_DECL float GET_PED_WAYPOINT_DISTANCE(Any p0) { return invoke<float>(0xE6A877C64CAF1BC5, p0); }
	NATIVE_DECL BOOL SET_PED_WAYPOINT_ROUTE_OFFSET(Ped ped, float x, float y, float z) { return invoke<BOOL>(0xED98E10B0AFCE4B4, ped, x, y, z); }
	NATIVE_DECL float GET_WAYPOINT_DISTANCE_ALONG_ROUTE(const char* name, int point) { return invoke<float>(0xA5B769058763E497, name, point); }
	NATIVE_DECL BOOL WAYPOINT_PLAYBACK_GET_IS_PAUSED(Any p0) { return invoke<BOOL>(0x701375A7D43F01CB, p0); }
	NATIVE_DECL void WAYPOINT_PLAYBACK_PAUSE(Any p0, BOOL p1, BOOL p2) { invoke<Void>(0x0F342546AA06FED5, p0, p1, p2); }
	NATIVE_DECL void WAYPOINT_PLAYBACK_RESUME(Any p0, BOOL p1, Any p2, Any p3) { invoke<Void>(0x244F70C84C547D2D, p0, p1, p2, p3); }
	NATIVE_DECL void WAYPOINT_PLAYBACK_OVERRIDE_SPEED(Any p0, float p1, BOOL p2) { invoke<Void>(0x7D7D2B47FA788E85, p0, p1, p2); }
	NATIVE_DECL void WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(Any p0) { invoke<Void>(0x6599D834B12D0800, p0); }
	NATIVE_DECL void USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE(const char* name, BOOL p1, float p2, float p3) { invoke<Void>(0x5A353B8E6B1095B5, name, p1, p2, p3); }
	NATIVE_DECL void WAYPOINT_PLAYBACK_START_AIMING_AT_PED(Ped ped, Ped target, BOOL p2) { invoke<Void>(0x20E330937C399D29, ped, target, p2); }
	NATIVE_DECL void WAYPOINT_PLAYBACK_START_AIMING_AT_COORD(Ped ped, float x, float y, float z, BOOL p4) { invoke<Void>(0x8968400D900ED8B3, ped, x, y, z, p4); }
	NATIVE_DECL void WAYPOINT_PLAYBACK_START_SHOOTING_AT_PED(Ped ped, Ped ped2, BOOL p2, BOOL p3) { invoke<Void>(0xE70BA7B90F8390DC, ped, ped2, p2, p3); }
	NATIVE_DECL void WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD(Ped ped, float x, float y, float z, BOOL p4, Hash firingPattern) { invoke<Void>(0x057A25CFCC9DB671, ped, x, y, z, p4, firingPattern); }
	NATIVE_DECL void WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING(Ped ped) { invoke<Void>(0x47EFA040EBB8E2EA, ped); }
	NATIVE_DECL void ASSISTED_MOVEMENT_REQUEST_ROUTE(const char* route) { invoke<Void>(0x817268968605947A, route); }
	NATIVE_DECL void ASSISTED_MOVEMENT_REMOVE_ROUTE(const char* route) { invoke<Void>(0x3548536485DD792B, route); }
	NATIVE_DECL BOOL ASSISTED_MOVEMENT_IS_ROUTE_LOADED(const char* route) { return invoke<BOOL>(0x60F9A4393A21F741, route); }
	NATIVE_DECL void ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES(const char* route, int props) { invoke<Void>(0xD5002D78B7162E1B, route, props); }
	NATIVE_DECL void ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME(float dist) { invoke<Void>(0x13945951E16EF912, dist); }
	NATIVE_DECL void TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING(Ped ped, Vehicle vehicle, const char* WPRecording, int p3, int p4, int p5, int p6, float p7, BOOL p8, float p9) { invoke<Void>(0x3123FAA6DB1CF7ED, ped, vehicle, WPRecording, p3, p4, p5, p6, p7, p8, p9); }
	NATIVE_DECL BOOL IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE(Vehicle vehicle) { return invoke<BOOL>(0xF5134943EA29868C, vehicle); }
	NATIVE_DECL int GET_VEHICLE_WAYPOINT_PROGRESS(Vehicle vehicle) { return invoke<int>(0x9824CFF8FC66E159, vehicle); }
	NATIVE_DECL int GET_VEHICLE_WAYPOINT_TARGET_POINT(Vehicle vehicle) { return invoke<int>(0x416B62AC8B9E5BBD, vehicle); }
	NATIVE_DECL void VEHICLE_WAYPOINT_PLAYBACK_PAUSE(Vehicle vehicle) { invoke<Void>(0x8A4E6AC373666BC5, vehicle); }
	NATIVE_DECL BOOL VEHICLE_WAYPOINT_PLAYBACK_GET_IS_PAUSED(Vehicle vehicle) { return invoke<BOOL>(0xE435D3539EFDCD1B, vehicle); }
	NATIVE_DECL void VEHICLE_WAYPOINT_PLAYBACK_RESUME(Vehicle vehicle) { invoke<Void>(0xDC04FCAA7839D492, vehicle); }
	NATIVE_DECL void VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(Vehicle vehicle) { invoke<Void>(0x5CEB25A7D2848963, vehicle); }
	NATIVE_DECL void VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(Vehicle vehicle, float speed) { invoke<Void>(0x121F0593E0A431D7, vehicle, speed); }
	NATIVE_DECL void TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, BOOL toggle) { invoke<Void>(0x90D2156198831D69, ped, toggle); }
	NATIVE_DECL void TASK_FORCE_MOTION_STATE(Ped ped, Hash state, BOOL forceRestart) { invoke<Void>(0x4F056E1AFFEF17AB, ped, state, forceRestart); }
	NATIVE_DECL void TASK_MOVE_NETWORK_BY_NAME(Ped ped, const char* task, float multiplier, BOOL allowOverrideCloneUpdate, const char* animDict, int flags) { invoke<Void>(0x2D537BA194896636, ped, task, multiplier, allowOverrideCloneUpdate, animDict, flags); }
	NATIVE_DECL void TASK_MOVE_NETWORK_ADVANCED_BY_NAME(Ped ped, const char* network, float x, float y, float z, float rotX, float rotY, float rotZ, int rotOrder, float blendDuration, BOOL allowOverrideCloneUpdate, const char* animDict, int flags) { invoke<Void>(0xD5B35BEA41919ACB, ped, network, x, y, z, rotX, rotY, rotZ, rotOrder, blendDuration, allowOverrideCloneUpdate, animDict, flags); }
	NATIVE_DECL void TASK_MOVE_NETWORK_BY_NAME_WITH_INIT_PARAMS(Ped ped, const char* network, int* initialParameters, float blendDuration, BOOL allowOverrideCloneUpdate, const char* animDict, int flags) { invoke<Void>(0x3D45B0B355C5E0C9, ped, network, initialParameters, blendDuration, allowOverrideCloneUpdate, animDict, flags); }
	NATIVE_DECL void TASK_MOVE_NETWORK_ADVANCED_BY_NAME_WITH_INIT_PARAMS(Ped ped, const char* network, int* initialParameters, float x, float y, float z, float rotX, float rotY, float rotZ, int rotOrder, float blendDuration, BOOL allowOverrideCloneUpdate, const char* dictionary, int flags) { invoke<Void>(0x29682E2CCF21E9B5, ped, network, initialParameters, x, y, z, rotX, rotY, rotZ, rotOrder, blendDuration, allowOverrideCloneUpdate, dictionary, flags); }
	NATIVE_DECL BOOL IS_TASK_MOVE_NETWORK_ACTIVE(Ped ped) { return invoke<BOOL>(0x921CE12C489C4C41, ped); }
	NATIVE_DECL BOOL IS_TASK_MOVE_NETWORK_READY_FOR_TRANSITION(Ped ped) { return invoke<BOOL>(0x30ED88D5E0C56A37, ped); }
	NATIVE_DECL BOOL REQUEST_TASK_MOVE_NETWORK_STATE_TRANSITION(Ped ped, const char* name) { return invoke<BOOL>(0xD01015C7316AE176, ped, name); }
	NATIVE_DECL BOOL SET_EXPECTED_CLONE_NEXT_TASK_MOVE_NETWORK_STATE(Ped ped, const char* state) { return invoke<BOOL>(0xAB13A5565480B6D9, ped, state); }
	NATIVE_DECL const char* GET_TASK_MOVE_NETWORK_STATE(Ped ped) { return invoke<const char*>(0x717E4D1F2048376D, ped); }
	NATIVE_DECL void SET_TASK_MOVE_NETWORK_ANIM_SET(Ped ped, Hash clipSet, Hash variableClipSet) { invoke<Void>(0x8423541E8B3A1589, ped, clipSet, variableClipSet); }
	NATIVE_DECL void SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, const char* signalName, float value) { invoke<Void>(0xD5BB4025AE449A4E, ped, signalName, value); }
	NATIVE_DECL void SET_TASK_MOVE_NETWORK_SIGNAL_LOCAL_FLOAT(Ped ped, const char* signalName, float value) { invoke<Void>(0x373EF409B82697A3, ped, signalName, value); }
	NATIVE_DECL void SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT_LERP_RATE(Ped ped, const char* signalName, float value) { invoke<Void>(0x8634CEF2522D987B, ped, signalName, value); }
	NATIVE_DECL void SET_TASK_MOVE_NETWORK_SIGNAL_BOOL(Ped ped, const char* signalName, BOOL value) { invoke<Void>(0xB0A6CFD2C69C1088, ped, signalName, value); }
	NATIVE_DECL float GET_TASK_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, const char* signalName) { return invoke<float>(0x44AB0B3AFECCE242, ped, signalName); }
	NATIVE_DECL BOOL GET_TASK_MOVE_NETWORK_SIGNAL_BOOL(Ped ped, const char* signalName) { return invoke<BOOL>(0xA7FFBA498E4AAF67, ped, signalName); }
	NATIVE_DECL BOOL GET_TASK_MOVE_NETWORK_EVENT(Ped ped, const char* eventName) { return invoke<BOOL>(0xB4F47213DF45A64C, ped, eventName); }
	NATIVE_DECL BOOL SET_TASK_MOVE_NETWORK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED(Ped ped, BOOL enable) { return invoke<BOOL>(0x0FFB3C758E8C07B9, ped, enable); }
	NATIVE_DECL void _SET_SCRIPT_TASK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED(Ped ped, BOOL enable) { invoke<Void>(0x32F6EEF031F943DC, ped, enable); }
	NATIVE_DECL void _SET_AMBIENT_PED_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED(Ped ped, BOOL enable) { invoke<Void>(0x0EFE4834A2F40563, ped, enable); }
	NATIVE_DECL BOOL IS_MOVE_BLEND_RATIO_STILL(Ped ped) { return invoke<BOOL>(0x349CE7B56DAFD95C, ped); }
	NATIVE_DECL BOOL IS_MOVE_BLEND_RATIO_WALKING(Ped ped) { return invoke<BOOL>(0xF133BBBE91E1691F, ped); }
	NATIVE_DECL BOOL IS_MOVE_BLEND_RATIO_RUNNING(Ped ped) { return invoke<BOOL>(0xD4D8636C0199A939, ped); }
	NATIVE_DECL BOOL IS_MOVE_BLEND_RATIO_SPRINTING(Ped ped) { return invoke<BOOL>(0x24A2AD74FA9814E2, ped); }
	NATIVE_DECL BOOL IS_PED_STILL(Ped ped) { return invoke<BOOL>(0xAC29253EEF8F0180, ped); }
	NATIVE_DECL BOOL IS_PED_WALKING(Ped ped) { return invoke<BOOL>(0xDE4C184B2B9B071A, ped); }
	NATIVE_DECL BOOL IS_PED_RUNNING(Ped ped) { return invoke<BOOL>(0xC5286FFC176F28A2, ped); }
	NATIVE_DECL BOOL IS_PED_SPRINTING(Ped ped) { return invoke<BOOL>(0x57E457CD2C0FC168, ped); }
	NATIVE_DECL BOOL IS_PED_STRAFING(Ped ped) { return invoke<BOOL>(0xE45B7F222DE47E09, ped); }
	NATIVE_DECL void TASK_SYNCHRONIZED_SCENE(Ped ped, int scene, const char* animDictionary, const char* animationName, float blendIn, float blendOut, int flags, int ragdollBlockingFlags, float moverBlendDelta, int ikFlags) { invoke<Void>(0xEEA929141F699854, ped, scene, animDictionary, animationName, blendIn, blendOut, flags, ragdollBlockingFlags, moverBlendDelta, ikFlags); }
	NATIVE_DECL void TASK_AGITATED_ACTION_CONFRONT_RESPONSE(Ped ped, Ped ped2) { invoke<Void>(0x19D1B791CB3670FE, ped, ped2); }
	NATIVE_DECL void TASK_SWEEP_AIM_ENTITY(Ped ped, const char* animDict, const char* lowAnimName, const char* medAnimName, const char* hiAnimName, int runtime, Entity targetEntity, float turnRate, float blendInDuration) { invoke<Void>(0x2047C02158D6405A, ped, animDict, lowAnimName, medAnimName, hiAnimName, runtime, targetEntity, turnRate, blendInDuration); }
	NATIVE_DECL void UPDATE_TASK_SWEEP_AIM_ENTITY(Ped ped, Entity entity) { invoke<Void>(0xE4973DBDBE6E44B3, ped, entity); }
	NATIVE_DECL void TASK_SWEEP_AIM_POSITION(Ped ped, const char* animDict, const char* lowAnimName, const char* medAnimName, const char* hiAnimName, int runtime, float x, float y, float z, float turnRate, float blendInDuration) { invoke<Void>(0x7AFE8FDC10BC07D2, ped, animDict, lowAnimName, medAnimName, hiAnimName, runtime, x, y, z, turnRate, blendInDuration); }
	NATIVE_DECL void UPDATE_TASK_SWEEP_AIM_POSITION(Ped ped, float x, float y, float z) { invoke<Void>(0xBB106883F5201FC4, ped, x, y, z); }
	NATIVE_DECL void TASK_ARREST_PED(Ped ped, Ped target) { invoke<Void>(0xF3B9A78A178572B1, ped, target); }
	NATIVE_DECL BOOL IS_PED_RUNNING_ARREST_TASK(Ped ped) { return invoke<BOOL>(0x3DC52677769B4AE0, ped); }
	NATIVE_DECL BOOL IS_PED_BEING_ARRESTED(Ped ped) { return invoke<BOOL>(0x90A09F3A45FED688, ped); }
	NATIVE_DECL void UNCUFF_PED(Ped ped) { invoke<Void>(0x67406F2C8F87FC4F, ped); }
	NATIVE_DECL BOOL IS_PED_CUFFED(Ped ped) { return invoke<BOOL>(0x74E559B3BC910685, ped); }
}

namespace VEHICLE
{
	NATIVE_DECL Vehicle CREATE_VEHICLE(Hash modelHash, float x, float y, float z, float heading, BOOL isNetwork, BOOL bScriptHostVeh, BOOL p7) { return invoke<Vehicle>(0xAF35D0D2583051B0, modelHash, x, y, z, heading, isNetwork, bScriptHostVeh, p7); }
	NATIVE_DECL void DELETE_VEHICLE(Vehicle* vehicle) { invoke<Void>(0xEA386986E786A54F, vehicle); }
	NATIVE_DECL void SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON(Vehicle vehicle, BOOL toggle, BOOL p2) { invoke<Void>(0x7D6F9A3EF26136A0, vehicle, toggle, p2); }
	NATIVE_DECL BOOL _GET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON_SYNCED(Vehicle vehicle) { return invoke<BOOL>(0x613A431BCD5A22EB, vehicle); }
	NATIVE_DECL void SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON_SYNCED(Vehicle vehicle, BOOL canBeLockedOn, BOOL p2) { invoke<Void>(0x1DDA078D12879EEE, vehicle, canBeLockedOn, p2); }
	NATIVE_DECL void SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(Vehicle veh, BOOL toggle) { invoke<Void>(0x5D14D4154BFE7B2C, veh, toggle); }
	NATIVE_DECL int GET_VEHICLE_HOMING_LOCKON_STATE(Vehicle vehicle) { return invoke<int>(0xE6B0E8CFC3633BF0, vehicle); }
	NATIVE_DECL int GET_VEHICLE_HOMING_LOCKEDONTO_STATE(Any p0) { return invoke<int>(0x6EAAEFC76ACC311F, p0); }
	NATIVE_DECL void SET_VEHICLE_HOMING_LOCKEDONTO_STATE(Any p0, Any p1) { invoke<Void>(0x407DC5E97DB1A4D3, p0, p1); }
	NATIVE_DECL BOOL IS_VEHICLE_MODEL(Vehicle vehicle, Hash model) { return invoke<BOOL>(0x423E8DE37D934D89, vehicle, model); }
	NATIVE_DECL BOOL DOES_SCRIPT_VEHICLE_GENERATOR_EXIST(int vehicleGenerator) { return invoke<BOOL>(0xF6086BC836400876, vehicleGenerator); }
	NATIVE_DECL int CREATE_SCRIPT_VEHICLE_GENERATOR(float x, float y, float z, float heading, float p4, float p5, Hash modelHash, int p7, int p8, int p9, int p10, BOOL p11, BOOL p12, BOOL p13, BOOL p14, BOOL p15, int p16) { return invoke<int>(0x9DEF883114668116, x, y, z, heading, p4, p5, modelHash, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); }
	NATIVE_DECL void DELETE_SCRIPT_VEHICLE_GENERATOR(int vehicleGenerator) { invoke<Void>(0x22102C9ABFCF125D, vehicleGenerator); }
	NATIVE_DECL void SET_SCRIPT_VEHICLE_GENERATOR(int vehicleGenerator, BOOL enabled) { invoke<Void>(0xD9D620E0AC6DC4B0, vehicleGenerator, enabled); }
	NATIVE_DECL void SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, BOOL toggle, BOOL p7) { invoke<Void>(0xC12321827687FE4D, x1, y1, z1, x2, y2, z2, toggle, p7); }
	NATIVE_DECL void SET_ALL_VEHICLE_GENERATORS_ACTIVE() { invoke<Void>(0x34AD89078831A4BC); }
	NATIVE_DECL void SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(BOOL active) { invoke<Void>(0x608207E7A8FB787C, active); }
	NATIVE_DECL void SET_VEHICLE_GENERATOR_AREA_OF_INTEREST(float x, float y, float z, float radius) { invoke<Void>(0x9A75585FB2E54FAD, x, y, z, radius); }
	NATIVE_DECL void CLEAR_VEHICLE_GENERATOR_AREA_OF_INTEREST() { invoke<Void>(0x0A436B8643716D14); }
	NATIVE_DECL BOOL SET_VEHICLE_ON_GROUND_PROPERLY(Vehicle vehicle, float p1) { return invoke<BOOL>(0x49733E92263139D1, vehicle, p1); }
	NATIVE_DECL BOOL SET_VEHICLE_USE_CUTSCENE_WHEEL_COMPRESSION(Vehicle p0, BOOL p1, BOOL p2, BOOL p3) { return invoke<BOOL>(0xE023E8AC4EF7C117, p0, p1, p2, p3); }
	NATIVE_DECL BOOL IS_VEHICLE_STUCK_ON_ROOF(Vehicle vehicle) { return invoke<BOOL>(0xB497F06B288DCFDF, vehicle); }
	NATIVE_DECL void ADD_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle) { invoke<Void>(0xB72E26D81006005B, vehicle); }
	NATIVE_DECL void REMOVE_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle) { invoke<Void>(0xC53EB42A499A7E90, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_STOPPED(Vehicle vehicle) { return invoke<BOOL>(0x5721B434AD84D57A, vehicle); }
	NATIVE_DECL int GET_VEHICLE_NUMBER_OF_PASSENGERS(Vehicle vehicle, BOOL includeDriver, BOOL includeDeadOccupants) { return invoke<int>(0x24CB2137731FFE89, vehicle, includeDriver, includeDeadOccupants); }
	NATIVE_DECL int GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vehicle vehicle) { return invoke<int>(0xA7C4F2C6E744A550, vehicle); }
	NATIVE_DECL int GET_VEHICLE_MODEL_NUMBER_OF_SEATS(Hash modelHash) { return invoke<int>(0x2AD93716F184EDA4, modelHash); }
	NATIVE_DECL BOOL IS_SEAT_WARP_ONLY(Vehicle vehicle, int seatIndex) { return invoke<BOOL>(0xF7F203E31F96F6A1, vehicle, seatIndex); }
	NATIVE_DECL BOOL IS_TURRET_SEAT(Vehicle vehicle, int seatIndex) { return invoke<BOOL>(0xE33FFA906CE74880, vehicle, seatIndex); }
	NATIVE_DECL BOOL DOES_VEHICLE_ALLOW_RAPPEL(Vehicle vehicle) { return invoke<BOOL>(0x4E417C547182C84D, vehicle); }
	NATIVE_DECL void SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier) { invoke<Void>(0x245A6883D966D537, multiplier); }
	NATIVE_DECL void SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier) { invoke<Void>(0xB3B3359379FE77D3, multiplier); }
	NATIVE_DECL void SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier) { invoke<Void>(0xEAE6DCC7EEE3DB1D, multiplier); }
	NATIVE_DECL void SET_DISABLE_RANDOM_TRAINS_THIS_FRAME(BOOL toggle) { invoke<Void>(0xD4B8E3D1917BC86B, toggle); }
	NATIVE_DECL void SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME(float value) { invoke<Void>(0x90B6DA738A9A25DA, value); }
	NATIVE_DECL void SET_FAR_DRAW_VEHICLES(BOOL toggle) { invoke<Void>(0x26324F33423F3CC3, toggle); }
	NATIVE_DECL void SET_NUMBER_OF_PARKED_VEHICLES(int value) { invoke<Void>(0xCAA15F13EBD417FF, value); }
	NATIVE_DECL void SET_VEHICLE_DOORS_LOCKED(Vehicle vehicle, int doorLockStatus) { invoke<Void>(0xB664292EAECF7FA6, vehicle, doorLockStatus); }
	NATIVE_DECL void SET_VEHICLE_INDIVIDUAL_DOORS_LOCKED(Vehicle vehicle, int doorId, int doorLockStatus) { invoke<Void>(0xBE70724027F85BCD, vehicle, doorId, doorLockStatus); }
	NATIVE_DECL void SET_VEHICLE_HAS_MUTED_SIRENS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xD8050E0EB60CF274, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player, BOOL toggle) { invoke<Void>(0x517AAF684BB50CD1, vehicle, player, toggle); }
	NATIVE_DECL BOOL GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player) { return invoke<BOOL>(0xF6AF6CB341349015, vehicle, player); }
	NATIVE_DECL void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xA2F80B8D040727CC, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_DOORS_LOCKED_FOR_NON_SCRIPT_PLAYERS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x9737A37136F07E75, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_DOORS_LOCKED_FOR_TEAM(Vehicle vehicle, int team, BOOL toggle) { invoke<Void>(0xB81F6D4A8F5EEBA8, vehicle, team, toggle); }
	NATIVE_DECL void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_TEAMS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x203B527D1B77904C, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_DONT_TERMINATE_TASK_WHEN_ACHIEVED(Vehicle vehicle) { invoke<Void>(0x76D26A22750E849E, vehicle); }
	NATIVE_DECL void _SET_VEHICLE_MAX_LAUNCH_ENGINE_REVS(Vehicle vehicle, float modifier) { invoke<Void>(0x5AE614ECA5FDD423, vehicle, modifier); }
	NATIVE_DECL float _GET_VEHICLE_THROTTLE(Vehicle vehicle) { return invoke<float>(0x92D96892FC06AF22, vehicle); }
	NATIVE_DECL void EXPLODE_VEHICLE(Vehicle vehicle, BOOL isAudible, BOOL isInvisible) { invoke<Void>(0xBA71116ADF5B514C, vehicle, isAudible, isInvisible); }
	NATIVE_DECL void SET_VEHICLE_OUT_OF_CONTROL(Vehicle vehicle, BOOL killDriver, BOOL explodeOnImpact) { invoke<Void>(0xF19D095E42D430CC, vehicle, killDriver, explodeOnImpact); }
	NATIVE_DECL void SET_VEHICLE_TIMED_EXPLOSION(Vehicle vehicle, Ped ped, BOOL toggle) { invoke<Void>(0x2E0A74E1002380B1, vehicle, ped, toggle); }
	NATIVE_DECL void ADD_VEHICLE_PHONE_EXPLOSIVE_DEVICE(Vehicle vehicle) { invoke<Void>(0x99AD4CCCB128CBC9, vehicle); }
	NATIVE_DECL void CLEAR_VEHICLE_PHONE_EXPLOSIVE_DEVICE() { invoke<Void>(0xAA3F739ABDDCF21F); }
	NATIVE_DECL BOOL HAS_VEHICLE_PHONE_EXPLOSIVE_DEVICE() { return invoke<BOOL>(0x6ADAABD3068C5235); }
	NATIVE_DECL void DETONATE_VEHICLE_PHONE_EXPLOSIVE_DEVICE() { invoke<Void>(0xEF49CF0270307CBE); }
	NATIVE_DECL BOOL HAVE_VEHICLE_REAR_DOORS_BEEN_BLOWN_OPEN_BY_STICKYBOMB(Vehicle vehicle) { return invoke<BOOL>(0x6B407F2525E93644, vehicle); }
	NATIVE_DECL void SET_TAXI_LIGHTS(Vehicle vehicle, BOOL state) { invoke<Void>(0x598803E85E8448D9, vehicle, state); }
	NATIVE_DECL BOOL IS_TAXI_LIGHT_ON(Vehicle vehicle) { return invoke<BOOL>(0x7504C0F113AB50FC, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_IN_GARAGE_AREA(const char* garageName, Vehicle vehicle) { return invoke<BOOL>(0xCEE4490CD57BB3C2, garageName, vehicle); }
	NATIVE_DECL void SET_VEHICLE_COLOURS(Vehicle vehicle, int colorPrimary, int colorSecondary) { invoke<Void>(0x4F1D4BE3A7F24601, vehicle, colorPrimary, colorSecondary); }
	NATIVE_DECL void SET_VEHICLE_FULLBEAM(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x8B7FD87F0DDB421E, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_IS_RACING(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x07116E24E9D1929D, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int r, int g, int b) { invoke<Void>(0x7141766F91D15BEA, vehicle, r, g, b); }
	NATIVE_DECL void GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int* r, int* g, int* b) { invoke<Void>(0xB64CF2CCA9D95F52, vehicle, r, g, b); }
	NATIVE_DECL void CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle) { invoke<Void>(0x55E1D2758F34E437, vehicle); }
	NATIVE_DECL BOOL GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(Vehicle vehicle) { return invoke<BOOL>(0xF095C0405307B21B, vehicle); }
	NATIVE_DECL void SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int r, int g, int b) { invoke<Void>(0x36CED73BFED89754, vehicle, r, g, b); }
	NATIVE_DECL void GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int* r, int* g, int* b) { invoke<Void>(0x8389CD56CA8072DC, vehicle, r, g, b); }
	NATIVE_DECL void CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle) { invoke<Void>(0x5FFBDEEC3E8E2009, vehicle); }
	NATIVE_DECL BOOL GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Vehicle vehicle) { return invoke<BOOL>(0x910A32E7AAD2656C, vehicle); }
	NATIVE_DECL void SET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle, float fade) { invoke<Void>(0x3AFDC536C3D01674, vehicle, fade); }
	NATIVE_DECL float GET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle) { return invoke<float>(0xA82819CAC9C4C403, vehicle); }
	NATIVE_DECL void SET_CAN_RESPRAY_VEHICLE(Vehicle vehicle, BOOL state) { invoke<Void>(0x52BBA29D5EC69356, vehicle, state); }
	NATIVE_DECL void SET_GOON_BOSS_VEHICLE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xAB31EF4DE6800CE9, vehicle, toggle); }
	NATIVE_DECL void SET_OPEN_REAR_DOORS_ON_EXPLOSION(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x1B212B26DD3C04DF, vehicle, toggle); }
	NATIVE_DECL void FORCE_SUBMARINE_SURFACE_MODE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x33506883545AC0DF, vehicle, toggle); }
	NATIVE_DECL void FORCE_SUBMARINE_NEURTAL_BUOYANCY(Any p0, Any p1) { invoke<Void>(0xC67DB108A9ADE3BE, p0, p1); }
	NATIVE_DECL void SET_SUBMARINE_CRUSH_DEPTHS(Vehicle vehicle, BOOL p1, float depth1, float depth2, float depth3) { invoke<Void>(0xC59872A5134879C7, vehicle, p1, depth1, depth2, depth3); }
	NATIVE_DECL BOOL GET_SUBMARINE_IS_UNDER_DESIGN_DEPTH(Vehicle submarine) { return invoke<BOOL>(0x3E71D0B300B7AA79, submarine); }
	NATIVE_DECL int GET_SUBMARINE_NUMBER_OF_AIR_LEAKS(Vehicle submarine) { return invoke<int>(0x093D6DDCA5B8FBAE, submarine); }
	NATIVE_DECL void SET_BOAT_IGNORE_LAND_PROBES(Any p0, Any p1) { invoke<Void>(0xED5EDE9E676643C9, p0, p1); }
	NATIVE_DECL void _SET_BOUNDS_AFFECT_WATER_PROBES(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x85FC953F6C6CBDE1, vehicle, toggle); }
	NATIVE_DECL void SET_BOAT_ANCHOR(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x75DBEC174AEEAD10, vehicle, toggle); }
	NATIVE_DECL BOOL CAN_ANCHOR_BOAT_HERE(Vehicle vehicle) { return invoke<BOOL>(0x26C10ECBDA5D043B, vehicle); }
	NATIVE_DECL BOOL CAN_ANCHOR_BOAT_HERE_IGNORE_PLAYERS(Vehicle vehicle) { return invoke<BOOL>(0x24F4121D07579880, vehicle); }
	NATIVE_DECL void SET_BOAT_REMAINS_ANCHORED_WHILE_PLAYER_IS_DRIVER(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xE3EBAAE484798530, vehicle, toggle); }
	NATIVE_DECL void SET_FORCE_LOW_LOD_ANCHOR_MODE(Vehicle vehicle, BOOL p1) { invoke<Void>(0xB28B1FE5BFADD7F5, vehicle, p1); }
	NATIVE_DECL void SET_BOAT_LOW_LOD_ANCHOR_DISTANCE(Vehicle vehicle, float value) { invoke<Void>(0xE842A9398079BD82, vehicle, value); }
	NATIVE_DECL BOOL IS_BOAT_ANCHORED(Vehicle vehicle) { return invoke<BOOL>(0xB0AD1238A709B1A2, vehicle); }
	NATIVE_DECL void SET_BOAT_SINKS_WHEN_WRECKED(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x8F719973E1445BA2, vehicle, toggle); }
	NATIVE_DECL void SET_BOAT_WRECKED(Vehicle vehicle) { invoke<Void>(0xBD32E46AA95C1DD2, vehicle); }
	NATIVE_DECL void SET_VEHICLE_SIREN(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xF4924635A19EB37D, vehicle, toggle); }
	NATIVE_DECL BOOL IS_VEHICLE_SIREN_ON(Vehicle vehicle) { return invoke<BOOL>(0x4C9BF537BE2634B2, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_SIREN_AUDIO_ON(Vehicle vehicle) { return invoke<BOOL>(0xB5CC40FBCB586380, vehicle); }
	NATIVE_DECL void SET_VEHICLE_STRONG(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x3E8C8727991A8A0B, vehicle, toggle); }
	NATIVE_DECL void REMOVE_VEHICLE_STUCK_CHECK(Vehicle vehicle) { invoke<Void>(0x8386BFB614D06749, vehicle); }
	NATIVE_DECL void GET_VEHICLE_COLOURS(Vehicle vehicle, int* colorPrimary, int* colorSecondary) { invoke<Void>(0xA19435F193E081AC, vehicle, colorPrimary, colorSecondary); }
	NATIVE_DECL BOOL IS_VEHICLE_SEAT_FREE(Vehicle vehicle, int seatIndex, BOOL isTaskRunning) { return invoke<BOOL>(0x22AC59A870E6A669, vehicle, seatIndex, isTaskRunning); }
	NATIVE_DECL Ped GET_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int seatIndex, BOOL p2) { return invoke<Ped>(0xBB40DD2270B65366, vehicle, seatIndex, p2); }
	NATIVE_DECL Ped GET_LAST_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int seatIndex) { return invoke<Ped>(0x83F969AA1EE2A664, vehicle, seatIndex); }
	NATIVE_DECL BOOL GET_VEHICLE_LIGHTS_STATE(Vehicle vehicle, BOOL* lightsOn, BOOL* highbeamsOn) { return invoke<BOOL>(0xB91B4C20085BD12F, vehicle, lightsOn, highbeamsOn); }
	NATIVE_DECL BOOL IS_VEHICLE_TYRE_BURST(Vehicle vehicle, int wheelID, BOOL completely) { return invoke<BOOL>(0xBA291848A0815CA9, vehicle, wheelID, completely); }
	NATIVE_DECL void SET_VEHICLE_FORWARD_SPEED(Vehicle vehicle, float speed) { invoke<Void>(0xAB54A438726D25D5, vehicle, speed); }
	NATIVE_DECL void SET_VEHICLE_FORWARD_SPEED_XY(Vehicle vehicle, float speed) { invoke<Void>(0x6501129C9E0FFA05, vehicle, speed); }
	NATIVE_DECL void BRING_VEHICLE_TO_HALT(Vehicle vehicle, float distance, int duration, BOOL p3) { invoke<Void>(0x260BE8F09E326A20, vehicle, distance, duration, p3); }
	NATIVE_DECL void SET_VEHICLE_STEER_FOR_BUILDINGS(Vehicle vehicle, Any p1) { invoke<Void>(0xDCE97BDF8A0EABC8, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_CAUSES_SWERVING(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x9849DE24FCF23CCC, vehicle, toggle); }
	NATIVE_DECL void SET_IGNORE_PLANES_SMALL_PITCH_CHANGE(Any p0, Any p1) { invoke<Void>(0x8664170EF165C4A6, p0, p1); }
	NATIVE_DECL void STOP_BRINGING_VEHICLE_TO_HALT(Vehicle vehicle) { invoke<Void>(0x7C06330BFDDA182E, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_BEING_BROUGHT_TO_HALT(Vehicle vehicle) { return invoke<BOOL>(0xC69BB1D832A710EF, vehicle); }
	NATIVE_DECL void LOWER_FORKLIFT_FORKS(Vehicle forklift) { invoke<Void>(0x923A293361DF44E5, forklift); }
	NATIVE_DECL void SET_FORKLIFT_FORK_HEIGHT(Vehicle vehicle, float height) { invoke<Void>(0x37EBBF3117BD6A25, vehicle, height); }
	NATIVE_DECL BOOL IS_ENTITY_ATTACHED_TO_HANDLER_FRAME(Vehicle vehicle, Entity entity) { return invoke<BOOL>(0x57715966069157AD, vehicle, entity); }
	NATIVE_DECL BOOL IS_ANY_ENTITY_ATTACHED_TO_HANDLER_FRAME(Vehicle vehicle) { return invoke<BOOL>(0x62CA17B74C435651, vehicle); }
	NATIVE_DECL Vehicle FIND_HANDLER_VEHICLE_CONTAINER_IS_ATTACHED_TO(Entity entity) { return invoke<Vehicle>(0x375E7FC44F21C8AB, entity); }
	NATIVE_DECL BOOL IS_HANDLER_FRAME_LINED_UP_WITH_CONTAINER(Vehicle vehicle, Entity entity) { return invoke<BOOL>(0x89D630CF5EA96D23, vehicle, entity); }
	NATIVE_DECL void ATTACH_CONTAINER_TO_HANDLER_FRAME_WHEN_LINED_UP(Vehicle vehicle, Entity entity) { invoke<Void>(0x6A98C2ECF57FA5D4, vehicle, entity); }
	NATIVE_DECL void DETACH_CONTAINER_FROM_HANDLER_FRAME(Vehicle vehicle) { invoke<Void>(0x7C0043FDFF6436BC, vehicle); }
	NATIVE_DECL void SET_VEHICLE_DISABLE_HEIGHT_MAP_AVOIDANCE(Vehicle vehicle, BOOL p1) { invoke<Void>(0x8AA9180DE2FEDD45, vehicle, p1); }
	NATIVE_DECL void _SET_PLANE_AVOIDS_OTHERS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xBAFB99B304BC52A7, vehicle, toggle); }
	NATIVE_DECL void SET_BOAT_DISABLE_AVOIDANCE(Vehicle vehicle, BOOL p1) { invoke<Void>(0x0A6A279F3AA4FD70, vehicle, p1); }
	NATIVE_DECL BOOL IS_HELI_LANDING_AREA_BLOCKED(Vehicle vehicle) { return invoke<BOOL>(0x634148744F385576, vehicle); }
	NATIVE_DECL void SET_SHORT_SLOWDOWN_FOR_LANDING(Vehicle vehicle) { invoke<Void>(0x107A473D7A6647A9, vehicle); }
	NATIVE_DECL void SET_HELI_TURBULENCE_SCALAR(Vehicle vehicle, float p1) { invoke<Void>(0xE6F13851780394DA, vehicle, p1); }
	NATIVE_DECL void SET_CAR_BOOT_OPEN(Vehicle vehicle) { invoke<Void>(0xFC40CBF7B90CA77C, vehicle); }
	NATIVE_DECL void SET_VEHICLE_TYRE_BURST(Vehicle vehicle, int index, BOOL onRim, float p3) { invoke<Void>(0xEC6A202EE4960385, vehicle, index, onRim, p3); }
	NATIVE_DECL void SET_VEHICLE_DOORS_SHUT(Vehicle vehicle, BOOL closeInstantly) { invoke<Void>(0x781B3D62BB013EF5, vehicle, closeInstantly); }
	NATIVE_DECL void SET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xEB9DC3C7D8596C46, vehicle, toggle); }
	NATIVE_DECL BOOL GET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle) { return invoke<BOOL>(0x678B9BB8C3F58FEB, vehicle); }
	NATIVE_DECL void SET_VEHICLE_WHEELS_CAN_BREAK(Vehicle vehicle, BOOL enabled) { invoke<Void>(0x29B18B4FD460CA8F, vehicle, enabled); }
	NATIVE_DECL void SET_VEHICLE_DOOR_OPEN(Vehicle vehicle, int doorId, BOOL loose, BOOL openInstantly) { invoke<Void>(0x7C65DAC73C35C862, vehicle, doorId, loose, openInstantly); }
	NATIVE_DECL void SET_VEHICLE_DOOR_AUTO_LOCK(Vehicle vehicle, int doorId, BOOL toggle) { invoke<Void>(0x3B458DDB57038F08, vehicle, doorId, toggle); }
	NATIVE_DECL void SET_FLEEING_VEHICLES_USE_SWITCHED_OFF_NODES(Any p0) { invoke<Void>(0xA247F9EF01D8082E, p0); }
	NATIVE_DECL void REMOVE_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex) { invoke<Void>(0xA711568EEDB43069, vehicle, windowIndex); }
	NATIVE_DECL void ROLL_DOWN_WINDOWS(Vehicle vehicle) { invoke<Void>(0x85796B0549DDE156, vehicle); }
	NATIVE_DECL void ROLL_DOWN_WINDOW(Vehicle vehicle, int windowIndex) { invoke<Void>(0x7AD9E6CE657D69E3, vehicle, windowIndex); }
	NATIVE_DECL void ROLL_UP_WINDOW(Vehicle vehicle, int windowIndex) { invoke<Void>(0x602E548F46E24D59, vehicle, windowIndex); }
	NATIVE_DECL void SMASH_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex) { invoke<Void>(0x9E5B5E4D2CCD2259, vehicle, windowIndex); }
	NATIVE_DECL void FIX_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex) { invoke<Void>(0x772282EBEB95E682, vehicle, windowIndex); }
	NATIVE_DECL void POP_OUT_VEHICLE_WINDSCREEN(Vehicle vehicle) { invoke<Void>(0x6D645D59FB5F5AD3, vehicle); }
	NATIVE_DECL void POP_OFF_VEHICLE_ROOF_WITH_IMPULSE(Vehicle vehicle, float x, float y, float z) { invoke<Void>(0xE38CB9D7D39FDBCC, vehicle, x, y, z); }
	NATIVE_DECL void SET_VEHICLE_LIGHTS(Vehicle vehicle, int state) { invoke<Void>(0x34E710FF01247C5A, vehicle, state); }
	NATIVE_DECL void SET_VEHICLE_USE_PLAYER_LIGHT_SETTINGS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xC45C27EF50F36ADC, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_HEADLIGHT_SHADOWS(Vehicle vehicle, int p1) { invoke<Void>(0x1FD09E7390A74D54, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_ALARM(Vehicle vehicle, BOOL state) { invoke<Void>(0xCDE5E70C1DDB954C, vehicle, state); }
	NATIVE_DECL void START_VEHICLE_ALARM(Vehicle vehicle) { invoke<Void>(0xB8FF7AB45305C345, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_ALARM_ACTIVATED(Vehicle vehicle) { return invoke<BOOL>(0x4319E335B71FFF34, vehicle); }
	NATIVE_DECL void SET_VEHICLE_INTERIORLIGHT(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xBC2042F090AF6AD3, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_FORCE_INTERIORLIGHT(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x8821196D91FA2DE5, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_LIGHT_MULTIPLIER(Vehicle vehicle, float multiplier) { invoke<Void>(0xB385454F8791F57C, vehicle, multiplier); }
	NATIVE_DECL void ATTACH_VEHICLE_TO_TRAILER(Vehicle vehicle, Vehicle trailer, float radius) { invoke<Void>(0x3C7D42D58F770B54, vehicle, trailer, radius); }
	NATIVE_DECL void ATTACH_VEHICLE_ON_TO_TRAILER(Vehicle vehicle, Vehicle trailer, float offsetX, float offsetY, float offsetZ, float coordsX, float coordsY, float coordsZ, float rotationX, float rotationY, float rotationZ, float disableCollisions) { invoke<Void>(0x16B5E274BDE402F8, vehicle, trailer, offsetX, offsetY, offsetZ, coordsX, coordsY, coordsZ, rotationX, rotationY, rotationZ, disableCollisions); }
	NATIVE_DECL void STABILISE_ENTITY_ATTACHED_TO_HELI(Vehicle vehicle, Entity entity, float p2) { invoke<Void>(0x374706271354CB18, vehicle, entity, p2); }
	NATIVE_DECL void DETACH_VEHICLE_FROM_TRAILER(Vehicle vehicle) { invoke<Void>(0x90532EDF0D2BDD86, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_ATTACHED_TO_TRAILER(Vehicle vehicle) { return invoke<BOOL>(0xE7CF3C4F9F489F0C, vehicle); }
	NATIVE_DECL void SET_TRAILER_INVERSE_MASS_SCALE(Vehicle vehicle, float p1) { invoke<Void>(0x2A8F319B392E7B3F, vehicle, p1); }
	NATIVE_DECL void SET_TRAILER_LEGS_RAISED(Vehicle vehicle) { invoke<Void>(0x95CF53B3D687F9FA, vehicle); }
	NATIVE_DECL void SET_TRAILER_LEGS_LOWERED(Vehicle vehicle) { invoke<Void>(0x878C75C09FBDB942, vehicle); }
	NATIVE_DECL void SET_VEHICLE_TYRE_FIXED(Vehicle vehicle, int tyreIndex) { invoke<Void>(0x6E13FC662B882D1D, vehicle, tyreIndex); }
	NATIVE_DECL void SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle, const char* plateText) { invoke<Void>(0x95A88F0B409CDA47, vehicle, plateText); }
	NATIVE_DECL const char* GET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle) { return invoke<const char*>(0x7CE1CCB9B293020E, vehicle); }
	NATIVE_DECL int GET_NUMBER_OF_VEHICLE_NUMBER_PLATES() { return invoke<int>(0x4C4D6B2644F458CB); }
	NATIVE_DECL void SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle, int plateIndex) { invoke<Void>(0x9088EB5A43FFB0A1, vehicle, plateIndex); }
	NATIVE_DECL int GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle) { return invoke<int>(0xF11BC2DD9A3E7195, vehicle); }
	NATIVE_DECL void SET_RANDOM_TRAINS(BOOL toggle) { invoke<Void>(0x80D9F74197EA47D9, toggle); }
	NATIVE_DECL Vehicle CREATE_MISSION_TRAIN(int variation, float x, float y, float z, BOOL direction, Any p5, Any p6) { return invoke<Vehicle>(0x63C6CCA8E68AE8C8, variation, x, y, z, direction, p5, p6); }
	NATIVE_DECL void SWITCH_TRAIN_TRACK(int trackId, BOOL state) { invoke<Void>(0xFD813BB7DB977F20, trackId, state); }
	NATIVE_DECL void SET_TRAIN_TRACK_SPAWN_FREQUENCY(int trackIndex, int frequency) { invoke<Void>(0x21973BBF8D17EDFA, trackIndex, frequency); }
	NATIVE_DECL void ALLOW_TRAIN_TO_BE_REMOVED_BY_POPULATION(Any p0) { invoke<Void>(0x2310A8F9421EBF43, p0); }
	NATIVE_DECL void DELETE_ALL_TRAINS() { invoke<Void>(0x736A718577F39C7D); }
	NATIVE_DECL void SET_TRAIN_SPEED(Vehicle train, float speed) { invoke<Void>(0xAA0BC91BE0B796E3, train, speed); }
	NATIVE_DECL void SET_TRAIN_CRUISE_SPEED(Vehicle train, float speed) { invoke<Void>(0x16469284DB8C62B5, train, speed); }
	NATIVE_DECL void SET_RANDOM_BOATS(BOOL toggle) { invoke<Void>(0x84436EC293B1415F, toggle); }
	NATIVE_DECL void SET_RANDOM_BOATS_MP(BOOL toggle) { invoke<Void>(0xDA5E12F728DB30CA, toggle); }
	NATIVE_DECL void SET_GARBAGE_TRUCKS(BOOL toggle) { invoke<Void>(0x2AFD795EEAC8D30D, toggle); }
	NATIVE_DECL BOOL DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(Vehicle vehicle) { return invoke<BOOL>(0x57E4C39DE5EE8470, vehicle); }
	NATIVE_DECL int GET_VEHICLE_RECORDING_ID(int recording, const char* script) { return invoke<int>(0x21543C612379DB3C, recording, script); }
	NATIVE_DECL void REQUEST_VEHICLE_RECORDING(int recording, const char* script) { invoke<Void>(0xAF514CABE74CBF15, recording, script); }
	NATIVE_DECL BOOL HAS_VEHICLE_RECORDING_BEEN_LOADED(int recording, const char* script) { return invoke<BOOL>(0x300D614A4C785FC4, recording, script); }
	NATIVE_DECL void REMOVE_VEHICLE_RECORDING(int recording, const char* script) { invoke<Void>(0xF1160ACCF98A3FC8, recording, script); }
	NATIVE_DECL Vector3 GET_POSITION_OF_VEHICLE_RECORDING_ID_AT_TIME(int id, float time) { return invoke<Vector3>(0x92523B76657A517D, id, time); }
	NATIVE_DECL Vector3 GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME(int recording, float time, const char* script) { return invoke<Vector3>(0xD242728AA6F0FBA2, recording, time, script); }
	NATIVE_DECL Vector3 GET_ROTATION_OF_VEHICLE_RECORDING_ID_AT_TIME(int id, float time) { return invoke<Vector3>(0xF0F2103EFAF8CBA7, id, time); }
	NATIVE_DECL Vector3 GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME(int recording, float time, const char* script) { return invoke<Vector3>(0x2058206FBE79A8AD, recording, time, script); }
	NATIVE_DECL float GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID(int id) { return invoke<float>(0x102D125411A7B6E6, id); }
	NATIVE_DECL float GET_TOTAL_DURATION_OF_VEHICLE_RECORDING(int recording, const char* script) { return invoke<float>(0x0E48D1C262390950, recording, script); }
	NATIVE_DECL float GET_POSITION_IN_RECORDING(Vehicle vehicle) { return invoke<float>(0x2DACD605FC681475, vehicle); }
	NATIVE_DECL float GET_TIME_POSITION_IN_RECORDING(Vehicle vehicle) { return invoke<float>(0x5746F3A7AB7FE544, vehicle); }
	NATIVE_DECL void START_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle, int recording, const char* script, BOOL p3) { invoke<Void>(0x3F878F92B3A7A071, vehicle, recording, script, p3); }
	NATIVE_DECL void START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS(Vehicle vehicle, int recording, const char* script, int flags, int time, int drivingStyle) { invoke<Void>(0x7D80FD645D4DA346, vehicle, recording, script, flags, time, drivingStyle); }
	NATIVE_DECL void FORCE_PLAYBACK_RECORDED_VEHICLE_UPDATE(Vehicle vehicle, BOOL p1) { invoke<Void>(0x1F2E4E06DEA8992B, vehicle, p1); }
	NATIVE_DECL void STOP_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle) { invoke<Void>(0x54833611C17ABDEA, vehicle); }
	NATIVE_DECL void PAUSE_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle) { invoke<Void>(0x632A689BF42301B1, vehicle); }
	NATIVE_DECL void UNPAUSE_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle) { invoke<Void>(0x8879EE09268305D5, vehicle); }
	NATIVE_DECL BOOL IS_PLAYBACK_GOING_ON_FOR_VEHICLE(Vehicle vehicle) { return invoke<BOOL>(0x1C8A4C2C19E68EEC, vehicle); }
	NATIVE_DECL BOOL IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE(Vehicle vehicle) { return invoke<BOOL>(0xAEA8FD591FAD4106, vehicle); }
	NATIVE_DECL int GET_CURRENT_PLAYBACK_FOR_VEHICLE(Vehicle vehicle) { return invoke<int>(0x42BC05C27A946054, vehicle); }
	NATIVE_DECL void SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle) { invoke<Void>(0xAB8E2EDA0C0A5883, vehicle); }
	NATIVE_DECL void SET_PLAYBACK_SPEED(Vehicle vehicle, float speed) { invoke<Void>(0x6683AB880E427778, vehicle, speed); }
	NATIVE_DECL void START_PLAYBACK_RECORDED_VEHICLE_USING_AI(Vehicle vehicle, int recording, const char* script, float speed, int drivingStyle) { invoke<Void>(0x29DE5FA52D00428C, vehicle, recording, script, speed, drivingStyle); }
	NATIVE_DECL void SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle, float time) { invoke<Void>(0x9438F7AD68771A20, vehicle, time); }
	NATIVE_DECL void SET_PLAYBACK_TO_USE_AI(Vehicle vehicle, int drivingStyle) { invoke<Void>(0xA549C3B37EA28131, vehicle, drivingStyle); }
	NATIVE_DECL void SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER(Vehicle vehicle, int time, int drivingStyle, BOOL p3) { invoke<Void>(0x6E63860BBB190730, vehicle, time, drivingStyle, p3); }
	NATIVE_DECL void SET_ADDITIONAL_ROTATION_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z, Any p4) { invoke<Void>(0x5845066D8A1EA7F7, vehicle, x, y, z, p4); }
	NATIVE_DECL void SET_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z) { invoke<Void>(0x796A877E459B99EA, vehicle, x, y, z); }
	NATIVE_DECL void SET_GLOBAL_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z) { invoke<Void>(0xFAF2A78061FD9EF4, vehicle, x, y, z); }
	NATIVE_DECL void SET_SHOULD_LERP_FROM_AI_TO_FULL_RECORDING(Vehicle vehicle, BOOL p1) { invoke<Void>(0x063AE2B2CC273588, vehicle, p1); }
	NATIVE_DECL void EXPLODE_VEHICLE_IN_CUTSCENE(Vehicle vehicle, BOOL p1) { invoke<Void>(0x786A4EB67B01BF0B, vehicle, p1); }
	NATIVE_DECL void ADD_VEHICLE_STUCK_CHECK_WITH_WARP(Any p0, float p1, Any p2, BOOL p3, BOOL p4, BOOL p5, Any p6) { invoke<Void>(0x2FA9923062DD396C, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void SET_VEHICLE_MODEL_IS_SUPPRESSED(Hash model, BOOL suppressed) { invoke<Void>(0x0FC2D89AC25A5814, model, suppressed); }
	NATIVE_DECL Vehicle GET_RANDOM_VEHICLE_IN_SPHERE(float x, float y, float z, float radius, Hash modelHash, int flags) { return invoke<Vehicle>(0x386F6CE5BAF6091C, x, y, z, radius, modelHash, flags); }
	NATIVE_DECL Vehicle GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6) { return invoke<Vehicle>(0xC5574E0AEB86BA68, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL Vehicle GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6) { return invoke<Vehicle>(0xB50807EABE20A8DC, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL Vehicle GET_CLOSEST_VEHICLE(float x, float y, float z, float radius, Hash modelHash, int flags) { return invoke<Vehicle>(0xF73EB622C4F1689B, x, y, z, radius, modelHash, flags); }
	NATIVE_DECL Vehicle GET_TRAIN_CARRIAGE(Vehicle train, int trailerNumber) { return invoke<Vehicle>(0x08AAFD0814722BC3, train, trailerNumber); }
	NATIVE_DECL void _SET_MAKE_TRAIN_SCAN_FOR_BLOCKING_ENTITIES(Vehicle train, BOOL toggle) { invoke<Void>(0x559B6073DB7FFFF9, train, toggle); }
	NATIVE_DECL int _GET_MISSION_TRAIN_CONFIG_INDEX_BY_NAME(const char* name) { return invoke<int>(0x7DFAD92A34F09C00, name); }
	NATIVE_DECL BOOL IS_MISSION_TRAIN(Vehicle train) { return invoke<BOOL>(0xAD464F2E18836BFC, train); }
	NATIVE_DECL void DELETE_MISSION_TRAIN(Vehicle* train) { invoke<Void>(0x5B76B14AE875C795, train); }
	NATIVE_DECL void SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED(Vehicle* train, BOOL p1) { invoke<Void>(0xBBE7648349B49BE8, train, p1); }
	NATIVE_DECL void SET_MISSION_TRAIN_COORDS(Vehicle train, float x, float y, float z) { invoke<Void>(0x591CA673AA6AB736, train, x, y, z); }
	NATIVE_DECL BOOL IS_THIS_MODEL_A_BOAT(Hash model) { return invoke<BOOL>(0x45A9187928F4B9E3, model); }
	NATIVE_DECL BOOL IS_THIS_MODEL_A_JETSKI(Hash model) { return invoke<BOOL>(0x9537097412CF75FE, model); }
	NATIVE_DECL BOOL IS_THIS_MODEL_A_PLANE(Hash model) { return invoke<BOOL>(0xA0948AB42D7BA0DE, model); }
	NATIVE_DECL BOOL IS_THIS_MODEL_A_HELI(Hash model) { return invoke<BOOL>(0xDCE4334788AF94EA, model); }
	NATIVE_DECL BOOL IS_THIS_MODEL_A_CAR(Hash model) { return invoke<BOOL>(0x7F6DB52EEFC96DF8, model); }
	NATIVE_DECL BOOL IS_THIS_MODEL_A_TRAIN(Hash model) { return invoke<BOOL>(0xAB935175B22E822B, model); }
	NATIVE_DECL BOOL IS_THIS_MODEL_A_BIKE(Hash model) { return invoke<BOOL>(0xB50C0B0CEDC6CE84, model); }
	NATIVE_DECL BOOL IS_THIS_MODEL_A_BICYCLE(Hash model) { return invoke<BOOL>(0xBF94DD42F63BDED2, model); }
	NATIVE_DECL BOOL IS_THIS_MODEL_A_QUADBIKE(Hash model) { return invoke<BOOL>(0x39DAC362EE65FA28, model); }
	NATIVE_DECL BOOL IS_THIS_MODEL_AN_AMPHIBIOUS_CAR(Hash model) { return invoke<BOOL>(0x633F6F44A537EBB6, model); }
	NATIVE_DECL BOOL IS_THIS_MODEL_AN_AMPHIBIOUS_QUADBIKE(Hash model) { return invoke<BOOL>(0xA1A9FC1C76A6730D, model); }
	NATIVE_DECL void SET_HELI_BLADES_FULL_SPEED(Vehicle vehicle) { invoke<Void>(0xA178472EBB8AE60D, vehicle); }
	NATIVE_DECL void SET_HELI_BLADES_SPEED(Vehicle vehicle, float speed) { invoke<Void>(0xFD280B4D7F3ABC4D, vehicle, speed); }
	NATIVE_DECL void FORCE_SUB_THROTTLE_FOR_TIME(Vehicle vehicle, float p1, float p2) { invoke<Void>(0x99CAD8E7AFDB60FA, vehicle, p1, p2); }
	NATIVE_DECL void SET_VEHICLE_CAN_BE_TARGETTED(Vehicle vehicle, BOOL state) { invoke<Void>(0x3750146A28097A82, vehicle, state); }
	NATIVE_DECL void SET_DONT_ALLOW_PLAYER_TO_ENTER_VEHICLE_IF_LOCKED_FOR_PLAYER(Vehicle vehicle, BOOL p1) { invoke<Void>(0xDBC631F109350B8C, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(Vehicle vehicle, BOOL state) { invoke<Void>(0x4C7028F78FFD3681, vehicle, state); }
	NATIVE_DECL void SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x1AA8A837D2169D94, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_RESPECTS_LOCKS_WHEN_HAS_DRIVER(Vehicle vehicle, BOOL p1) { invoke<Void>(0x2311DD7159F00582, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_CAN_EJECT_PASSENGERS_IF_LOCKED(Any p0, Any p1) { invoke<Void>(0x065D03A9D6B2C6B5, p0, p1); }
	NATIVE_DECL float GET_VEHICLE_DIRT_LEVEL(Vehicle vehicle) { return invoke<float>(0x8F17BC8BA08DA62B, vehicle); }
	NATIVE_DECL void SET_VEHICLE_DIRT_LEVEL(Vehicle vehicle, float dirtLevel) { invoke<Void>(0x79D3B596FE44EE8B, vehicle, dirtLevel); }
	NATIVE_DECL BOOL GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(Vehicle vehicle) { return invoke<BOOL>(0xBCDC5017D3CE1E9E, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_DOOR_FULLY_OPEN(Vehicle vehicle, int doorId) { return invoke<BOOL>(0x3E933CFF7B111C22, vehicle, doorId); }
	NATIVE_DECL void SET_VEHICLE_ENGINE_ON(Vehicle vehicle, BOOL value, BOOL instantly, BOOL disableAutoStart) { invoke<Void>(0x2497C4717C8B881E, vehicle, value, instantly, disableAutoStart); }
	NATIVE_DECL void SET_VEHICLE_UNDRIVEABLE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x8ABA6AF54B942B95, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_PROVIDES_COVER(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x5AFEEDD9BB2899D7, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_DOOR_CONTROL(Vehicle vehicle, int doorId, int speed, float angle) { invoke<Void>(0xF2BFA0430F0A0FCB, vehicle, doorId, speed, angle); }
	NATIVE_DECL void SET_VEHICLE_DOOR_LATCHED(Vehicle vehicle, int doorId, BOOL p2, BOOL p3, BOOL p4) { invoke<Void>(0xA5A9653A8D2CAF48, vehicle, doorId, p2, p3, p4); }
	NATIVE_DECL float GET_VEHICLE_DOOR_ANGLE_RATIO(Vehicle vehicle, int doorId) { return invoke<float>(0xFE3F9C29F7B32BD5, vehicle, doorId); }
	NATIVE_DECL Ped GET_PED_USING_VEHICLE_DOOR(Vehicle vehicle, int doord) { return invoke<Ped>(0x218297BF0CFD853B, vehicle, doord); }
	NATIVE_DECL void SET_VEHICLE_DOOR_SHUT(Vehicle vehicle, int doorId, BOOL closeInstantly) { invoke<Void>(0x93D9BD300D7789E5, vehicle, doorId, closeInstantly); }
	NATIVE_DECL void SET_VEHICLE_DOOR_BROKEN(Vehicle vehicle, int doorId, BOOL deleteDoor) { invoke<Void>(0xD4D4F6A4AB575A33, vehicle, doorId, deleteDoor); }
	NATIVE_DECL void SET_VEHICLE_CAN_BREAK(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x59BF8C3D52C92F66, vehicle, toggle); }
	NATIVE_DECL BOOL DOES_VEHICLE_HAVE_ROOF(Vehicle vehicle) { return invoke<BOOL>(0x8AC862B0B32C5B80, vehicle); }
	NATIVE_DECL void SET_VEHICLE_REMOVE_AGGRESSIVE_CARJACK_MISSION(Any p0) { invoke<Void>(0xC4B3347BD68BD609, p0); }
	NATIVE_DECL void SET_VEHICLE_AVOID_PLAYER_VEHICLE_RIOT_VAN_MISSION(Any p0) { invoke<Void>(0xD3301660A57C9272, p0); }
	NATIVE_DECL void SET_CARJACK_MISSION_REMOVAL_PARAMETERS(Any p0, Any p1) { invoke<Void>(0xB9562064627FF9DB, p0, p1); }
	NATIVE_DECL BOOL IS_BIG_VEHICLE(Vehicle vehicle) { return invoke<BOOL>(0x9F243D3919F442FE, vehicle); }
	NATIVE_DECL int GET_NUMBER_OF_VEHICLE_COLOURS(Vehicle vehicle) { return invoke<int>(0x3B963160CD65D41E, vehicle); }
	NATIVE_DECL void SET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle, int colorCombination) { invoke<Void>(0x33E8CD3322E2FE31, vehicle, colorCombination); }
	NATIVE_DECL int GET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle) { return invoke<int>(0x6A842D197F845D56, vehicle); }
	NATIVE_DECL void SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(Vehicle vehicle, int colorIndex) { invoke<Void>(0xE41033B25D003A07, vehicle, colorIndex); }
	NATIVE_DECL int GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(Vehicle vehicle) { return invoke<int>(0x3DFF319A831E0CDB, vehicle); }
	NATIVE_DECL void SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x31B927BBC44156CD, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_WILL_FORCE_OTHER_VEHICLES_TO_STOP(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xBE5C1255A1830FF5, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_ACT_AS_IF_HAS_SIREN_ON(Vehicle vehicle, BOOL p1) { invoke<Void>(0x9BECD4B9FEF3F8A6, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_USE_MORE_RESTRICTIVE_SPAWN_CHECKS(Vehicle vehicle, BOOL p1) { invoke<Void>(0x88BC673CA9E0AE99, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_MAY_BE_USED_BY_GOTO_POINT_ANY_MEANS(Vehicle vehicle, BOOL p1) { invoke<Void>(0xE851E480B814D4BA, vehicle, p1); }
	NATIVE_DECL void GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(BOOL p0, Hash* modelHash, int* successIndicator) { invoke<Void>(0x055BF0AC0C34F4FD, p0, modelHash, successIndicator); }
	NATIVE_DECL int GET_VEHICLE_DOOR_LOCK_STATUS(Vehicle vehicle) { return invoke<int>(0x25BC98A59C2EA962, vehicle); }
	NATIVE_DECL int GET_VEHICLE_INDIVIDUAL_DOOR_LOCK_STATUS(Vehicle vehicle, int doorId) { return invoke<int>(0xCA4AC3EAAE46EC7B, vehicle, doorId); }
	NATIVE_DECL BOOL IS_VEHICLE_DOOR_DAMAGED(Vehicle veh, int doorID) { return invoke<BOOL>(0xB8E181E559464527, veh, doorID); }
	NATIVE_DECL void SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF(Vehicle vehicle, int doorId, BOOL isBreakable) { invoke<Void>(0x2FA133A4A9D37ED8, vehicle, doorId, isBreakable); }
	NATIVE_DECL BOOL IS_VEHICLE_BUMPER_BOUNCING(Vehicle vehicle, BOOL frontBumper) { return invoke<BOOL>(0x27B926779DEB502D, vehicle, frontBumper); }
	NATIVE_DECL BOOL IS_VEHICLE_BUMPER_BROKEN_OFF(Vehicle vehicle, BOOL frontBumper) { return invoke<BOOL>(0x468056A6BB6F3846, vehicle, frontBumper); }
	NATIVE_DECL BOOL IS_COP_VEHICLE_IN_AREA_3D(float x1, float x2, float y1, float y2, float z1, float z2) { return invoke<BOOL>(0x7EEF65D5F153E26A, x1, x2, y1, y2, z1, z2); }
	NATIVE_DECL BOOL IS_VEHICLE_ON_ALL_WHEELS(Vehicle vehicle) { return invoke<BOOL>(0xB104CD1BABF302E2, vehicle); }
	NATIVE_DECL int GET_VEHICLE_MODEL_VALUE(Hash vehicleModel) { return invoke<int>(0x5873C14A52D74236, vehicleModel); }
	NATIVE_DECL Hash GET_VEHICLE_LAYOUT_HASH(Vehicle vehicle) { return invoke<Hash>(0x28D37D4F71AC5C58, vehicle); }
	NATIVE_DECL Hash GET_IN_VEHICLE_CLIPSET_HASH_FOR_SEAT(Vehicle vehicle, int p1) { return invoke<Hash>(0xA01BC64DD4BFBBAC, vehicle, p1); }
	NATIVE_DECL void SET_RENDER_TRAIN_AS_DERAILED(Vehicle train, BOOL toggle) { invoke<Void>(0x317B11A312DF5534, train, toggle); }
	NATIVE_DECL void SET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int pearlescentColor, int wheelColor) { invoke<Void>(0x2036F561ADD12E33, vehicle, pearlescentColor, wheelColor); }
	NATIVE_DECL void GET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int* pearlescentColor, int* wheelColor) { invoke<Void>(0x3BC4245933A166F7, vehicle, pearlescentColor, wheelColor); }
	NATIVE_DECL void SET_VEHICLE_EXTRA_COLOUR_5(Vehicle vehicle, int color) { invoke<Void>(0xF40DD601A65F7F19, vehicle, color); }
	NATIVE_DECL void GET_VEHICLE_EXTRA_COLOUR_5(Vehicle vehicle, int* color) { invoke<Void>(0x7D1464D472D32136, vehicle, color); }
	NATIVE_DECL void SET_VEHICLE_EXTRA_COLOUR_6(Vehicle vehicle, int color) { invoke<Void>(0x6089CDF6A57F326C, vehicle, color); }
	NATIVE_DECL void GET_VEHICLE_EXTRA_COLOUR_6(Vehicle vehicle, int* color) { invoke<Void>(0xB7635E80A5C31BFF, vehicle, color); }
	NATIVE_DECL void STOP_ALL_GARAGE_ACTIVITY() { invoke<Void>(0x0F87E938BDF29D66); }
	NATIVE_DECL void SET_VEHICLE_FIXED(Vehicle vehicle) { invoke<Void>(0x115722B1B9C14C1C, vehicle); }
	NATIVE_DECL void SET_VEHICLE_DEFORMATION_FIXED(Vehicle vehicle) { invoke<Void>(0x953DA1E1B12C0491, vehicle); }
	NATIVE_DECL void SET_VEHICLE_CAN_ENGINE_MISSFIRE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x206BC5DC9D1AC70A, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_CAN_LEAK_OIL(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x51BB2D88D31A914B, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_CAN_LEAK_PETROL(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x192547247864DFDD, vehicle, toggle); }
	NATIVE_DECL void SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x465BF26AB9684352, vehicle, toggle); }
	NATIVE_DECL void SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x37C8252A7C92D017, vehicle, toggle); }
	NATIVE_DECL void SET_DISABLE_VEHICLE_ENGINE_FIRES(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x91A0BD635321F145, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_LIMIT_SPEED_WHEN_PLAYER_INACTIVE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xC50CE861B55EAB8B, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_STOP_INSTANTLY_WHEN_PLAYER_INACTIVE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x6EBFB22D646FFC18, vehicle, toggle); }
	NATIVE_DECL void SET_DISABLE_PRETEND_OCCUPANTS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x25367DE49D64CF16, vehicle, toggle); }
	NATIVE_DECL void REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, Any p6) { invoke<Void>(0x46A1E1A299EC4BBA, x1, y1, z1, x2, y2, z2, p6); }
	NATIVE_DECL void SET_VEHICLE_STEER_BIAS(Vehicle vehicle, float value) { invoke<Void>(0x42A8EC77D5150CBE, vehicle, value); }
	NATIVE_DECL BOOL IS_VEHICLE_EXTRA_TURNED_ON(Vehicle vehicle, int extraId) { return invoke<BOOL>(0xD2E6822DBFD6C8BD, vehicle, extraId); }
	NATIVE_DECL void SET_VEHICLE_EXTRA(Vehicle vehicle, int extraId, BOOL disable) { invoke<Void>(0x7EE3A3C5E4A40CC9, vehicle, extraId, disable); }
	NATIVE_DECL BOOL DOES_EXTRA_EXIST(Vehicle vehicle, int extraId) { return invoke<BOOL>(0x1262D55792428154, vehicle, extraId); }
	NATIVE_DECL BOOL IS_EXTRA_BROKEN_OFF(Vehicle vehicle, int extraId) { return invoke<BOOL>(0x534E36D4DB9ECC5D, vehicle, extraId); }
	NATIVE_DECL void SET_CONVERTIBLE_ROOF(Vehicle vehicle, BOOL p1) { invoke<Void>(0xF39C4F538B5124C2, vehicle, p1); }
	NATIVE_DECL void LOWER_CONVERTIBLE_ROOF(Vehicle vehicle, BOOL instantlyLower) { invoke<Void>(0xDED51F703D0FA83D, vehicle, instantlyLower); }
	NATIVE_DECL void RAISE_CONVERTIBLE_ROOF(Vehicle vehicle, BOOL instantlyRaise) { invoke<Void>(0x8F5FB35D7E88FC70, vehicle, instantlyRaise); }
	NATIVE_DECL int GET_CONVERTIBLE_ROOF_STATE(Vehicle vehicle) { return invoke<int>(0xF8C397922FC03F41, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_A_CONVERTIBLE(Vehicle vehicle, BOOL p1) { return invoke<BOOL>(0x52F357A30698BCCE, vehicle, p1); }
	NATIVE_DECL BOOL TRANSFORM_TO_SUBMARINE(Vehicle vehicle, BOOL noAnimation) { return invoke<BOOL>(0xBE4C854FFDB6EEBE, vehicle, noAnimation); }
	NATIVE_DECL void TRANSFORM_TO_CAR(Vehicle vehicle, BOOL noAnimation) { invoke<Void>(0x2A69FFD1B42BFF9E, vehicle, noAnimation); }
	NATIVE_DECL BOOL IS_VEHICLE_IN_SUBMARINE_MODE(Vehicle vehicle) { return invoke<BOOL>(0xA77DC70BD689A1E5, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(Vehicle vehicle) { return invoke<BOOL>(0x2959F696AE390A99, vehicle); }
	NATIVE_DECL void SET_VEHICLE_DAMAGE(Vehicle vehicle, float xOffset, float yOffset, float zOffset, float damage, float radius, BOOL focusOnModel) { invoke<Void>(0xA1DD317EA8FD4F29, vehicle, xOffset, yOffset, zOffset, damage, radius, focusOnModel); }
	NATIVE_DECL void SET_VEHICLE_OCCUPANTS_TAKE_EXPLOSIVE_DAMAGE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x35BB21DE06784373, vehicle, toggle); }
	NATIVE_DECL float GET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle) { return invoke<float>(0xC45D23BAF168AAB8, vehicle); }
	NATIVE_DECL void SET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle, float health) { invoke<Void>(0x45F6D8EEF34ABEF1, vehicle, health); }
	NATIVE_DECL void SET_PLANE_ENGINE_HEALTH(Vehicle vehicle, float health) { invoke<Void>(0x2A86A0475B6A1434, vehicle, health); }
	NATIVE_DECL float GET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle) { return invoke<float>(0x7D5DABE888D2D074, vehicle); }
	NATIVE_DECL void SET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle, float health) { invoke<Void>(0x70DB57649FA8D0D8, vehicle, health); }
	NATIVE_DECL BOOL IS_VEHICLE_STUCK_TIMER_UP(Vehicle vehicle, int p1, int ms) { return invoke<BOOL>(0x679BE1DAF71DA874, vehicle, p1, ms); }
	NATIVE_DECL void RESET_VEHICLE_STUCK_TIMER(Vehicle vehicle, int nullAttributes) { invoke<Void>(0xD7591B0065AFAA7A, vehicle, nullAttributes); }
	NATIVE_DECL BOOL IS_VEHICLE_DRIVEABLE(Vehicle vehicle, BOOL isOnFireCheck) { return invoke<BOOL>(0x4C241E39B23DF959, vehicle, isOnFireCheck); }
	NATIVE_DECL void SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(Vehicle vehicle, BOOL owned) { invoke<Void>(0x2B5F9D2AF1F1722D, vehicle, owned); }
	NATIVE_DECL void SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xFBA550EA44404EE6, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_BLIP_THROTTLE_RANDOMLY(Vehicle vehicle, BOOL p1) { invoke<Void>(0x9F3F689B814F2599, vehicle, p1); }
	NATIVE_DECL void SET_POLICE_FOCUS_WILL_TRACK_VEHICLE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x4E74E62E0A97E901, vehicle, toggle); }
	NATIVE_DECL void START_VEHICLE_HORN(Vehicle vehicle, int duration, Hash mode, BOOL forever) { invoke<Void>(0x9C8C6504B5B63D2C, vehicle, duration, mode, forever); }
	NATIVE_DECL void SET_VEHICLE_IN_CAR_MOD_SHOP(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x9D44FCCE98450843, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_HAS_STRONG_AXLES(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x92F0CF722BC4202F, vehicle, toggle); }
	NATIVE_DECL const char* GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(Hash modelHash) { return invoke<const char*>(0xB215AAC32D25D019, modelHash); }
	NATIVE_DECL const char* GET_MAKE_NAME_FROM_VEHICLE_MODEL(Hash modelHash) { return invoke<const char*>(0xF7AF4F159FF99F97, modelHash); }
	NATIVE_DECL Vector3 GET_VEHICLE_DEFORMATION_AT_POS(Vehicle vehicle, float offsetX, float offsetY, float offsetZ) { return invoke<Vector3>(0x4EC6CFBC7B2E9536, vehicle, offsetX, offsetY, offsetZ); }
	NATIVE_DECL void SET_VEHICLE_LIVERY(Vehicle vehicle, int livery) { invoke<Void>(0x60BF608F1B8CD1B6, vehicle, livery); }
	NATIVE_DECL int GET_VEHICLE_LIVERY(Vehicle vehicle) { return invoke<int>(0x2BB9230590DA5E8A, vehicle); }
	NATIVE_DECL int GET_VEHICLE_LIVERY_COUNT(Vehicle vehicle) { return invoke<int>(0x87B63E25A529D526, vehicle); }
	NATIVE_DECL void SET_VEHICLE_LIVERY2(Vehicle vehicle, int livery) { invoke<Void>(0xA6D3A8750DC73270, vehicle, livery); }
	NATIVE_DECL int GET_VEHICLE_LIVERY2(Vehicle vehicle) { return invoke<int>(0x60190048C0764A26, vehicle); }
	NATIVE_DECL int GET_VEHICLE_LIVERY2_COUNT(Vehicle vehicle) { return invoke<int>(0x5ECB40269053C0D4, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_WINDOW_INTACT(Vehicle vehicle, int windowIndex) { return invoke<BOOL>(0x46E571A0E20D01F1, vehicle, windowIndex); }
	NATIVE_DECL BOOL ARE_ALL_VEHICLE_WINDOWS_INTACT(Vehicle vehicle) { return invoke<BOOL>(0x11D862A3E977A9EF, vehicle); }
	NATIVE_DECL BOOL ARE_ANY_VEHICLE_SEATS_FREE(Vehicle vehicle) { return invoke<BOOL>(0x2D34FC3BC4ADB780, vehicle); }
	NATIVE_DECL void RESET_VEHICLE_WHEELS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x21D2E5662C1F6FED, vehicle, toggle); }
	NATIVE_DECL BOOL IS_HELI_PART_BROKEN(Vehicle vehicle, BOOL p1, BOOL p2, BOOL p3) { return invoke<BOOL>(0xBC74B4BE25EB6C8A, vehicle, p1, p2, p3); }
	NATIVE_DECL float GET_HELI_MAIN_ROTOR_HEALTH(Vehicle vehicle) { return invoke<float>(0xE4CB7541F413D2C5, vehicle); }
	NATIVE_DECL float GET_HELI_TAIL_ROTOR_HEALTH(Vehicle vehicle) { return invoke<float>(0xAE8CE82A4219AC8C, vehicle); }
	NATIVE_DECL float GET_HELI_TAIL_BOOM_HEALTH(Vehicle vehicle) { return invoke<float>(0xAC51915D27E4A5F7, vehicle); }
	NATIVE_DECL void SET_HELI_MAIN_ROTOR_HEALTH(Vehicle vehicle, float health) { invoke<Void>(0x4056EA1105F5ABD7, vehicle, health); }
	NATIVE_DECL void SET_HELI_TAIL_ROTOR_HEALTH(Vehicle vehicle, float health) { invoke<Void>(0xFE205F38AAA58E5B, vehicle, health); }
	NATIVE_DECL BOOL SET_HELI_TAIL_BOOM_CAN_BREAK_OFF(Vehicle vehicle, BOOL toggle) { return invoke<BOOL>(0x3EC8BF18AA453FE9, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_NAME_DEBUG(Vehicle vehicle, const char* name) { invoke<Void>(0xBFDF984E2C22B94F, vehicle, name); }
	NATIVE_DECL void SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x71B0892EC081D60A, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_EXPLODES_ON_EXPLOSION_DAMAGE_AT_ZERO_BODY_HEALTH(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xD565F438137F0E10, vehicle, toggle); }
	NATIVE_DECL void SET_ALLOW_VEHICLE_EXPLODES_ON_CONTACT(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x3441CAD2F2231923, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_DISABLE_TOWING(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x2B6747FAA9DB9D6B, vehicle, toggle); }
	NATIVE_DECL BOOL GET_VEHICLE_HAS_LANDING_GEAR(Vehicle vehicle) { return invoke<BOOL>(0xE43701C36CAFF1A4, vehicle); }
	NATIVE_DECL void CONTROL_LANDING_GEAR(Vehicle vehicle, int state) { invoke<Void>(0xCFC8BE9A5E1FE575, vehicle, state); }
	NATIVE_DECL int GET_LANDING_GEAR_STATE(Vehicle vehicle) { return invoke<int>(0x9B0F3DCA3DB0F4CD, vehicle); }
	NATIVE_DECL BOOL IS_ANY_VEHICLE_NEAR_POINT(float x, float y, float z, float radius) { return invoke<BOOL>(0x61E1DD6125A3EEE6, x, y, z, radius); }
	NATIVE_DECL void REQUEST_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle) { invoke<Void>(0xA6E9FDCB2C76785E, vehicle); }
	NATIVE_DECL int _GET_VEHICLE_MODEL_NUM_DRIVE_GEARS(Hash vehicleModel) { return invoke<int>(0x61F02E4E9A7A61EA, vehicleModel); }
	NATIVE_DECL int _GET_VEHICLE_MAX_DRIVE_GEAR_COUNT(Vehicle vehicle) { return invoke<int>(0x24910C3D66BA770D, vehicle); }
	NATIVE_DECL BOOL _GET_IS_VEHICLE_ELECTRIC(Hash vehicleModel) { return invoke<BOOL>(0x1FCB07FE230B6639, vehicleModel); }
	NATIVE_DECL int _GET_VEHICLE_DRIVETRAIN_TYPE(Hash vehicleModel) { return invoke<int>(0x1423725069EE1D14, vehicleModel); }
	NATIVE_DECL int _GET_VEHICLE_CURRENT_DRIVE_GEAR(Vehicle vehicle) { return invoke<int>(0x56185A25D45A0DCD, vehicle); }
	NATIVE_DECL float _GET_VEHICLE_CURRENT_REV_RATIO(Vehicle vehicle) { return invoke<float>(0xF9DDA40BC293A61E, vehicle); }
	NATIVE_DECL void REMOVE_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle) { invoke<Void>(0x00689CDE5F7C6787, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_HIGH_DETAIL(Vehicle vehicle) { return invoke<BOOL>(0x1F25887F3C104278, vehicle); }
	NATIVE_DECL void REQUEST_VEHICLE_ASSET(Hash vehicleHash, int vehicleAsset) { invoke<Void>(0x81A15811460FAB3A, vehicleHash, vehicleAsset); }
	NATIVE_DECL BOOL HAS_VEHICLE_ASSET_LOADED(int vehicleAsset) { return invoke<BOOL>(0x1BBE0523B8DB9A21, vehicleAsset); }
	NATIVE_DECL void REMOVE_VEHICLE_ASSET(int vehicleAsset) { invoke<Void>(0xACE699C71AB9DEB5, vehicleAsset); }
	NATIVE_DECL void SET_VEHICLE_TOW_TRUCK_ARM_POSITION(Vehicle vehicle, float position) { invoke<Void>(0xFE54B92A344583CA, vehicle, position); }
	NATIVE_DECL void _SET_ATTACHED_VEHICLE_TO_TOW_TRUCK_ARM(Vehicle towTruck, Vehicle vehicle) { invoke<Void>(0x48BD57D0DD17786A, towTruck, vehicle); }
	NATIVE_DECL void ATTACH_VEHICLE_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle, BOOL rear, float hookOffsetX, float hookOffsetY, float hookOffsetZ) { invoke<Void>(0x29A16F8D621C4508, towTruck, vehicle, rear, hookOffsetX, hookOffsetY, hookOffsetZ); }
	NATIVE_DECL void DETACH_VEHICLE_FROM_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle) { invoke<Void>(0xC2DB6B6708350ED8, towTruck, vehicle); }
	NATIVE_DECL BOOL DETACH_VEHICLE_FROM_ANY_TOW_TRUCK(Vehicle vehicle) { return invoke<BOOL>(0xD0E9CE05A1E68CD8, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle) { return invoke<BOOL>(0x146DF9EC4C4B9FD4, towTruck, vehicle); }
	NATIVE_DECL Entity GET_ENTITY_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck) { return invoke<Entity>(0xEFEA18DCF10F8F75, towTruck); }
	NATIVE_DECL Entity SET_VEHICLE_AUTOMATICALLY_ATTACHES(Vehicle vehicle, BOOL p1, Any p2) { return invoke<Entity>(0x8BA6F76BC53A1493, vehicle, p1, p2); }
	NATIVE_DECL void SET_VEHICLE_BULLDOZER_ARM_POSITION(Vehicle vehicle, float position, BOOL p2) { invoke<Void>(0xF8EBCCC96ADB9FB7, vehicle, position, p2); }
	NATIVE_DECL void SET_VEHICLE_TANK_TURRET_POSITION(Vehicle vehicle, float position, BOOL p2) { invoke<Void>(0x56B94C6D7127DFBA, vehicle, position, p2); }
	NATIVE_DECL void SET_VEHICLE_TURRET_TARGET(Vehicle vehicle, BOOL p1, float x, float y, float z, BOOL p5) { invoke<Void>(0x0581730AB9380412, vehicle, p1, x, y, z, p5); }
	NATIVE_DECL void SET_VEHICLE_TANK_STATIONARY(Vehicle vehicle, BOOL p1) { invoke<Void>(0x737E398138550FFF, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_TURRET_SPEED_THIS_FRAME(Vehicle vehicle, float speed) { invoke<Void>(0x1093408B4B9D1146, vehicle, speed); }
	NATIVE_DECL void DISABLE_VEHICLE_TURRET_MOVEMENT_THIS_FRAME(Vehicle vehicle) { invoke<Void>(0x32CAEDF24A583345, vehicle); }
	NATIVE_DECL void SET_VEHICLE_FLIGHT_NOZZLE_POSITION(Vehicle vehicle, float angleRatio) { invoke<Void>(0x30D779DE7C4F6DD3, vehicle, angleRatio); }
	NATIVE_DECL void SET_VEHICLE_FLIGHT_NOZZLE_POSITION_IMMEDIATE(Vehicle vehicle, float angle) { invoke<Void>(0x9AA47FFF660CB932, vehicle, angle); }
	NATIVE_DECL float GET_VEHICLE_FLIGHT_NOZZLE_POSITION(Vehicle plane) { return invoke<float>(0xDA62027C8BDB326E, plane); }
	NATIVE_DECL void SET_DISABLE_VERTICAL_FLIGHT_MODE_TRANSITION(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xCE2B43770B655F8F, vehicle, toggle); }
	NATIVE_DECL BOOL GENERATE_VEHICLE_CREATION_POS_FROM_PATHS(Vector3* outVec, Any p1, Vector3* outVec1, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<BOOL>(0xA4822F1CF23F4810, outVec, p1, outVec1, p3, p4, p5, p6, p7, p8); }
	NATIVE_DECL void SET_VEHICLE_BURNOUT(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xFB8794444A7D60FB, vehicle, toggle); }
	NATIVE_DECL BOOL IS_VEHICLE_IN_BURNOUT(Vehicle vehicle) { return invoke<BOOL>(0x1297A88E081430EB, vehicle); }
	NATIVE_DECL void SET_VEHICLE_REDUCE_GRIP(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x222FF6A823D122E2, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_REDUCE_GRIP_LEVEL(Vehicle vehicle, int val) { invoke<Void>(0x6DEE944E1EE90CFB, vehicle, val); }
	NATIVE_DECL void SET_VEHICLE_INDICATOR_LIGHTS(Vehicle vehicle, int turnSignal, BOOL toggle) { invoke<Void>(0xB5D45264751B7DF0, vehicle, turnSignal, toggle); }
	NATIVE_DECL void SET_VEHICLE_BRAKE_LIGHTS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x92B35082E0B42F66, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_TAIL_LIGHTS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x5815BD2763178DF4, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_HANDBRAKE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x684785568EF26A22, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_BRAKE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xE4E2FD323574965C, vehicle, toggle); }
	NATIVE_DECL void INSTANTLY_FILL_VEHICLE_POPULATION() { invoke<Void>(0x48ADC8A773564670); }
	NATIVE_DECL BOOL HAS_INSTANT_FILL_VEHICLE_POPULATION_FINISHED() { return invoke<BOOL>(0x91D6DD290888CBAB); }
	NATIVE_DECL void NETWORK_ENABLE_EMPTY_CROWDING_VEHICLES_REMOVAL(BOOL toggle) { invoke<Void>(0x51DB102F4A3BA5E0, toggle); }
	NATIVE_DECL void NETWORK_CAP_EMPTY_CROWDING_VEHICLES_REMOVAL(int p0) { invoke<Void>(0xA4A9A4C40E615885, p0); }
	NATIVE_DECL BOOL GET_VEHICLE_TRAILER_VEHICLE(Vehicle vehicle, Vehicle* trailer) { return invoke<BOOL>(0x1CDD6BADC297830D, vehicle, trailer); }
	NATIVE_DECL Vehicle _GET_VEHICLE_TRAILER_PARENT_VEHICLE(Vehicle trailer) { return invoke<Vehicle>(0x80D9D32636369C92, trailer); }
	NATIVE_DECL void SET_VEHICLE_USES_LARGE_REAR_RAMP(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xCAC66558B944DA67, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_RUDDER_BROKEN(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x09606148B6C71DEF, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_TAIL_BROKEN(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x6CB5B84B78AC55FE, vehicle, toggle); }
	NATIVE_DECL void SET_CONVERTIBLE_ROOF_LATCH_STATE(Vehicle vehicle, BOOL state) { invoke<Void>(0x1A78AD3D8240536F, vehicle, state); }
	NATIVE_DECL float GET_VEHICLE_ESTIMATED_MAX_SPEED(Vehicle vehicle) { return invoke<float>(0x53AF99BAA671CA47, vehicle); }
	NATIVE_DECL float GET_VEHICLE_MAX_BRAKING(Vehicle vehicle) { return invoke<float>(0xAD7E85FC227197C4, vehicle); }
	NATIVE_DECL float GET_VEHICLE_MAX_TRACTION(Vehicle vehicle) { return invoke<float>(0xA132FB5370554DB0, vehicle); }
	NATIVE_DECL float GET_VEHICLE_ACCELERATION(Vehicle vehicle) { return invoke<float>(0x5DD35C8D074E57AE, vehicle); }
	NATIVE_DECL float GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(Hash modelHash) { return invoke<float>(0xF417C2502FFFED43, modelHash); }
	NATIVE_DECL float GET_VEHICLE_MODEL_MAX_BRAKING(Hash modelHash) { return invoke<float>(0xDC53FD41B4ED944C, modelHash); }
	NATIVE_DECL float GET_VEHICLE_MODEL_MAX_BRAKING_MAX_MODS(Hash modelHash) { return invoke<float>(0xBFBA3BA79CFF7EBF, modelHash); }
	NATIVE_DECL float GET_VEHICLE_MODEL_MAX_TRACTION(Hash modelHash) { return invoke<float>(0x539DE94D44FDFD0D, modelHash); }
	NATIVE_DECL float GET_VEHICLE_MODEL_ACCELERATION(Hash modelHash) { return invoke<float>(0x8C044C5C84505B6A, modelHash); }
	NATIVE_DECL float GET_VEHICLE_MODEL_ACCELERATION_MAX_MODS(Hash modelHash) { return invoke<float>(0x53409B5163D5B846, modelHash); }
	NATIVE_DECL float GET_FLYING_VEHICLE_MODEL_AGILITY(Hash modelHash) { return invoke<float>(0xC6AD107DDC9054CC, modelHash); }
	NATIVE_DECL float GET_BOAT_VEHICLE_MODEL_AGILITY(Hash modelHash) { return invoke<float>(0x5AA3F878A178C4FC, modelHash); }
	NATIVE_DECL float GET_VEHICLE_CLASS_ESTIMATED_MAX_SPEED(int vehicleClass) { return invoke<float>(0x00C09F246ABEDD82, vehicleClass); }
	NATIVE_DECL float GET_VEHICLE_CLASS_MAX_TRACTION(int vehicleClass) { return invoke<float>(0xDBC86D85C5059461, vehicleClass); }
	NATIVE_DECL float GET_VEHICLE_CLASS_MAX_AGILITY(int vehicleClass) { return invoke<float>(0x4F930AD022D6DE3B, vehicleClass); }
	NATIVE_DECL float GET_VEHICLE_CLASS_MAX_ACCELERATION(int vehicleClass) { return invoke<float>(0x2F83E7E45D9EA7AE, vehicleClass); }
	NATIVE_DECL float GET_VEHICLE_CLASS_MAX_BRAKING(int vehicleClass) { return invoke<float>(0x4BF54C16EC8FEC03, vehicleClass); }
	NATIVE_DECL int ADD_ROAD_NODE_SPEED_ZONE(float x, float y, float z, float radius, float speed, BOOL p5) { return invoke<int>(0x2CE544C68FB812A0, x, y, z, radius, speed, p5); }
	NATIVE_DECL BOOL REMOVE_ROAD_NODE_SPEED_ZONE(int speedzone) { return invoke<BOOL>(0x1033371FC8E842A7, speedzone); }
	NATIVE_DECL void OPEN_BOMB_BAY_DOORS(Vehicle vehicle) { invoke<Void>(0x87E7F24270732CB1, vehicle); }
	NATIVE_DECL void CLOSE_BOMB_BAY_DOORS(Vehicle vehicle) { invoke<Void>(0x3556041742A0DC74, vehicle); }
	NATIVE_DECL BOOL GET_ARE_BOMB_BAY_DOORS_OPEN(Vehicle aircraft) { return invoke<BOOL>(0xD0917A423314BBA8, aircraft); }
	NATIVE_DECL BOOL IS_VEHICLE_SEARCHLIGHT_ON(Vehicle vehicle) { return invoke<BOOL>(0xC0F97FCE55094987, vehicle); }
	NATIVE_DECL void SET_VEHICLE_SEARCHLIGHT(Vehicle heli, BOOL toggle, BOOL canBeUsedByAI) { invoke<Void>(0x14E85C5EE7A4D542, heli, toggle, canBeUsedByAI); }
	NATIVE_DECL BOOL DOES_VEHICLE_HAVE_SEARCHLIGHT(Vehicle vehicle) { return invoke<BOOL>(0x99015ED7DBEA5113, vehicle); }
	NATIVE_DECL BOOL IS_ENTRY_POINT_FOR_SEAT_CLEAR(Ped ped, Vehicle vehicle, int seatIndex, BOOL side, BOOL onEnter) { return invoke<BOOL>(0x639431E895B9AA57, ped, vehicle, seatIndex, side, onEnter); }
	NATIVE_DECL Vector3 GET_ENTRY_POINT_POSITION(Vehicle vehicle, int doorId) { return invoke<Vector3>(0xC0572928C0ABFDA3, vehicle, doorId); }
	NATIVE_DECL BOOL CAN_SHUFFLE_SEAT(Vehicle vehicle, int seatIndex) { return invoke<BOOL>(0x30785D90C956BF35, vehicle, seatIndex); }
	NATIVE_DECL int GET_NUM_MOD_KITS(Vehicle vehicle) { return invoke<int>(0x33F2E3FE70EAAE1D, vehicle); }
	NATIVE_DECL void SET_VEHICLE_MOD_KIT(Vehicle vehicle, int modKit) { invoke<Void>(0x1F2AA07F00B3217A, vehicle, modKit); }
	NATIVE_DECL int GET_VEHICLE_MOD_KIT(Vehicle vehicle) { return invoke<int>(0x6325D1A044AE510D, vehicle); }
	NATIVE_DECL int GET_VEHICLE_MOD_KIT_TYPE(Vehicle vehicle) { return invoke<int>(0xFC058F5121E54C32, vehicle); }
	NATIVE_DECL int GET_VEHICLE_WHEEL_TYPE(Vehicle vehicle) { return invoke<int>(0xB3ED1BFB4BE636DC, vehicle); }
	NATIVE_DECL void SET_VEHICLE_WHEEL_TYPE(Vehicle vehicle, int WheelType) { invoke<Void>(0x487EB21CC7295BA1, vehicle, WheelType); }
	NATIVE_DECL int GET_NUM_MOD_COLORS(int paintType, BOOL p1) { return invoke<int>(0xA551BE18C11A476D, paintType, p1); }
	NATIVE_DECL void SET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int paintType, int color, int pearlescentColor) { invoke<Void>(0x43FEB945EE7F85B8, vehicle, paintType, color, pearlescentColor); }
	NATIVE_DECL void SET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int paintType, int color) { invoke<Void>(0x816562BADFDEC83E, vehicle, paintType, color); }
	NATIVE_DECL void GET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int* paintType, int* color, int* pearlescentColor) { invoke<Void>(0xE8D65CA700C9A693, vehicle, paintType, color, pearlescentColor); }
	NATIVE_DECL void GET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int* paintType, int* color) { invoke<Void>(0x81592BE4E3878728, vehicle, paintType, color); }
	NATIVE_DECL const char* GET_VEHICLE_MOD_COLOR_1_NAME(Vehicle vehicle, BOOL p1) { return invoke<const char*>(0xB45085B721EFD38C, vehicle, p1); }
	NATIVE_DECL const char* GET_VEHICLE_MOD_COLOR_2_NAME(Vehicle vehicle) { return invoke<const char*>(0x4967A516ED23A5A1, vehicle); }
	NATIVE_DECL BOOL HAVE_VEHICLE_MODS_STREAMED_IN(Vehicle vehicle) { return invoke<BOOL>(0x9A83F5F9963775EF, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_MOD_GEN9_EXCLUSIVE(Vehicle vehicle, int modType, int modIndex) { return invoke<BOOL>(0x00834EAC4A96E010, vehicle, modType, modIndex); }
	NATIVE_DECL void SET_VEHICLE_MOD(Vehicle vehicle, int modType, int modIndex, BOOL customTires) { invoke<Void>(0x6AF0636DDEDCB6DD, vehicle, modType, modIndex, customTires); }
	NATIVE_DECL int GET_VEHICLE_MOD(Vehicle vehicle, int modType) { return invoke<int>(0x772960298DA26FDB, vehicle, modType); }
	NATIVE_DECL int GET_VEHICLE_MOD_VARIATION(Vehicle vehicle, int modType) { return invoke<int>(0xB3924ECD70E095DC, vehicle, modType); }
	NATIVE_DECL int GET_NUM_VEHICLE_MODS(Vehicle vehicle, int modType) { return invoke<int>(0xE38E9162A2500646, vehicle, modType); }
	NATIVE_DECL void REMOVE_VEHICLE_MOD(Vehicle vehicle, int modType) { invoke<Void>(0x92D619E420858204, vehicle, modType); }
	NATIVE_DECL void TOGGLE_VEHICLE_MOD(Vehicle vehicle, int modType, BOOL toggle) { invoke<Void>(0x2A1F4F37F95BAD08, vehicle, modType, toggle); }
	NATIVE_DECL BOOL IS_TOGGLE_MOD_ON(Vehicle vehicle, int modType) { return invoke<BOOL>(0x84B233A8C8FC8AE7, vehicle, modType); }
	NATIVE_DECL const char* GET_MOD_TEXT_LABEL(Vehicle vehicle, int modType, int modValue) { return invoke<const char*>(0x8935624F8C5592CC, vehicle, modType, modValue); }
	NATIVE_DECL const char* GET_MOD_SLOT_NAME(Vehicle vehicle, int modType) { return invoke<const char*>(0x51F0FEB9F6AE98C0, vehicle, modType); }
	NATIVE_DECL const char* GET_LIVERY_NAME(Vehicle vehicle, int liveryIndex) { return invoke<const char*>(0xB4C7A93837C91A1F, vehicle, liveryIndex); }
	NATIVE_DECL int GET_VEHICLE_MOD_MODIFIER_VALUE(Vehicle vehicle, int modType, int modIndex) { return invoke<int>(0x90A38E9838E0A8C1, vehicle, modType, modIndex); }
	NATIVE_DECL Hash GET_VEHICLE_MOD_IDENTIFIER_HASH(Vehicle vehicle, int modType, int modIndex) { return invoke<Hash>(0x4593CF82AA179706, vehicle, modType, modIndex); }
	NATIVE_DECL void PRELOAD_VEHICLE_MOD(Vehicle vehicle, int modType, int modIndex) { invoke<Void>(0x758F49C24925568A, vehicle, modType, modIndex); }
	NATIVE_DECL BOOL HAS_PRELOAD_MODS_FINISHED(Vehicle vehicle) { return invoke<BOOL>(0x06F43E5175EB6D96, vehicle); }
	NATIVE_DECL void RELEASE_PRELOAD_MODS(Vehicle vehicle) { invoke<Void>(0x445D79F995508307, vehicle); }
	NATIVE_DECL void SET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int r, int g, int b) { invoke<Void>(0xB5BA80F839791C0F, vehicle, r, g, b); }
	NATIVE_DECL void GET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int* r, int* g, int* b) { invoke<Void>(0xB635392A4938B3C3, vehicle, r, g, b); }
	NATIVE_DECL void SET_VEHICLE_WINDOW_TINT(Vehicle vehicle, int tint) { invoke<Void>(0x57C51E6BAD752696, vehicle, tint); }
	NATIVE_DECL int GET_VEHICLE_WINDOW_TINT(Vehicle vehicle) { return invoke<int>(0x0EE21293DAD47C95, vehicle); }
	NATIVE_DECL int GET_NUM_VEHICLE_WINDOW_TINTS() { return invoke<int>(0x9D1224004B3A6707); }
	NATIVE_DECL void GET_VEHICLE_COLOR(Vehicle vehicle, int* r, int* g, int* b) { invoke<Void>(0xF3CC740D36221548, vehicle, r, g, b); }
	NATIVE_DECL int GET_VEHICLE_COLOURS_WHICH_CAN_BE_SET(Vehicle vehicle) { return invoke<int>(0xEEBFC7A7EFDC35B4, vehicle); }
	NATIVE_DECL Hash GET_VEHICLE_CAUSE_OF_DESTRUCTION(Vehicle vehicle) { return invoke<Hash>(0xE495D1EF4C91FD20, vehicle); }
	NATIVE_DECL void OVERRIDE_PLANE_DAMAGE_THREHSOLD(Vehicle vehicle, float health) { invoke<Void>(0x5EE5632F47AE9695, vehicle, health); }
	NATIVE_DECL void _SET_TRANSMISSION_REDUCED_GEAR_RATIO(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x337EF33DA3DDB990, vehicle, toggle); }
	NATIVE_DECL int _GET_VEHICLE_DESIRED_DRIVE_GEAR(Vehicle vehicle) { return invoke<int>(0xFD8CE53356B5D745, vehicle); }
	NATIVE_DECL BOOL GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle) { return invoke<BOOL>(0x5EF77C9ADD3B11A3, vehicle); }
	NATIVE_DECL BOOL GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle) { return invoke<BOOL>(0xA7ECB73355EB2F20, vehicle); }
	NATIVE_DECL BOOL GET_BOTH_VEHICLE_HEADLIGHTS_DAMAGED(Vehicle vehicle) { return invoke<BOOL>(0xEC69ADF931AAE0C3, vehicle); }
	NATIVE_DECL void MODIFY_VEHICLE_TOP_SPEED(Vehicle vehicle, float value) { invoke<Void>(0x93A3996368C94158, vehicle, value); }
	NATIVE_DECL void SET_VEHICLE_MAX_SPEED(Vehicle vehicle, float speed) { invoke<Void>(0xBAA045B4E42F3C06, vehicle, speed); }
	NATIVE_DECL void SET_VEHICLE_STAYS_FROZEN_WHEN_CLEANED_UP(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x1CF38D529D7441D9, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_ACT_AS_IF_HIGH_SPEED_FOR_FRAG_SMASHING(Vehicle vehicle, BOOL p1) { invoke<Void>(0x1F9FB66F3A3842D2, vehicle, p1); }
	NATIVE_DECL void SET_PEDS_CAN_FALL_OFF_THIS_VEHICLE_FROM_LARGE_FALL_DAMAGE(Vehicle vehicle, BOOL toggle, float p2) { invoke<Void>(0x59C3757B3B7408E8, vehicle, toggle, p2); }
	NATIVE_DECL int ADD_VEHICLE_COMBAT_ANGLED_AVOIDANCE_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6) { return invoke<int>(0x54B0F614960F4A5F, p0, p1, p2, p3, p4, p5, p6); }
	NATIVE_DECL void REMOVE_VEHICLE_COMBAT_AVOIDANCE_AREA(int p0) { invoke<Void>(0xE30524E1871F481D, p0); }
	NATIVE_DECL BOOL IS_ANY_PED_RAPPELLING_FROM_HELI(Vehicle vehicle) { return invoke<BOOL>(0x291E373D483E7EE7, vehicle); }
	NATIVE_DECL void SET_VEHICLE_CHEAT_POWER_INCREASE(Vehicle vehicle, float value) { invoke<Void>(0xB59E4BD37AE292DB, vehicle, value); }
	NATIVE_DECL void SET_VEHICLE_INFLUENCES_WANTED_LEVEL(Any p0, BOOL p1) { invoke<Void>(0x0AD9E8F87FF7C16F, p0, p1); }
	NATIVE_DECL void SET_VEHICLE_IS_WANTED(Vehicle vehicle, BOOL state) { invoke<Void>(0xF7EC25A3EBEEC726, vehicle, state); }
	NATIVE_DECL void SWING_BOAT_BOOM_TO_RATIO(Vehicle vehicle, float ratio) { invoke<Void>(0xF488C566413B4232, vehicle, ratio); }
	NATIVE_DECL void SWING_BOAT_BOOM_FREELY(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xC1F981A6F74F0C23, vehicle, toggle); }
	NATIVE_DECL void ALLOW_BOAT_BOOM_TO_ANIMATE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x0F3B4D4E43177236, vehicle, toggle); }
	NATIVE_DECL float GET_BOAT_BOOM_POSITION_RATIO(Vehicle vehicle) { return invoke<float>(0x6636C535F6CC2725, vehicle); }
	NATIVE_DECL void DISABLE_PLANE_AILERON(Vehicle vehicle, BOOL p1, BOOL p2) { invoke<Void>(0x23428FC53C60919C, vehicle, p1, p2); }
	NATIVE_DECL BOOL GET_IS_VEHICLE_ENGINE_RUNNING(Vehicle vehicle) { return invoke<BOOL>(0xAE31E7DF9B5B132E, vehicle); }
	NATIVE_DECL void SET_VEHICLE_USE_ALTERNATE_HANDLING(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x1D97D1E3A70A649F, vehicle, toggle); }
	NATIVE_DECL void SET_BIKE_ON_STAND(Vehicle vehicle, float x, float y) { invoke<Void>(0x9CFA4896C3A53CBB, vehicle, x, y); }
	NATIVE_DECL void SET_VEHICLE_NOT_STEALABLE_AMBIENTLY(Vehicle vehicle, BOOL p1) { invoke<Void>(0xAB04325045427AAE, vehicle, p1); }
	NATIVE_DECL void LOCK_DOORS_WHEN_NO_LONGER_NEEDED(Vehicle vehicle) { invoke<Void>(0xCFD778E7904C255E, vehicle); }
	NATIVE_DECL void SET_LAST_DRIVEN_VEHICLE(Vehicle vehicle) { invoke<Void>(0xACFB2463CC22BED2, vehicle); }
	NATIVE_DECL Vehicle GET_LAST_DRIVEN_VEHICLE() { return invoke<Vehicle>(0xB2D06FAEDE65B577); }
	NATIVE_DECL void CLEAR_LAST_DRIVEN_VEHICLE() { invoke<Void>(0xE01903C47C7AC89E); }
	NATIVE_DECL void SET_VEHICLE_HAS_BEEN_DRIVEN_FLAG(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x02398B627547189C, vehicle, toggle); }
	NATIVE_DECL void SET_TASK_VEHICLE_GOTO_PLANE_MIN_HEIGHT_ABOVE_TERRAIN(Vehicle plane, int height) { invoke<Void>(0xB893215D8D4C015B, plane, height); }
	NATIVE_DECL void SET_VEHICLE_LOD_MULTIPLIER(Vehicle vehicle, float multiplier) { invoke<Void>(0x93AE6A61BE015BF1, vehicle, multiplier); }
	NATIVE_DECL void SET_VEHICLE_CAN_SAVE_IN_GARAGE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x428BACCDF5E26EAD, vehicle, toggle); }
	NATIVE_DECL int GET_VEHICLE_NUM_OF_BROKEN_OFF_PARTS(Vehicle vehicle) { return invoke<int>(0x42A4BEB35D372407, vehicle); }
	NATIVE_DECL int GET_VEHICLE_NUM_OF_BROKEN_LOOSEN_PARTS(Vehicle vehicle) { return invoke<int>(0x2C8CBFE1EA5FC631, vehicle); }
	NATIVE_DECL void SET_FORCE_VEHICLE_ENGINE_DAMAGE_BY_BULLET(Any p0, BOOL p1) { invoke<Void>(0x4D9D109F63FEE1D4, p0, p1); }
	NATIVE_DECL void SET_VEHICLE_GENERATES_ENGINE_SHOCKING_EVENTS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x279D50DE5652D935, vehicle, toggle); }
	NATIVE_DECL void COPY_VEHICLE_DAMAGES(Vehicle sourceVehicle, Vehicle targetVehicle) { invoke<Void>(0xE44A982368A4AF23, sourceVehicle, targetVehicle); }
	NATIVE_DECL void DISABLE_VEHICLE_EXPLOSION_BREAK_OFF_PARTS() { invoke<Void>(0xF25E02CB9C5818F8); }
	NATIVE_DECL void SET_LIGHTS_CUTOFF_DISTANCE_TWEAK(float distance) { invoke<Void>(0xBC3CCA5844452B06, distance); }
	NATIVE_DECL void SET_VEHICLE_SHOOT_AT_TARGET(Ped driver, Entity entity, float xTarget, float yTarget, float zTarget) { invoke<Void>(0x74CD9A9327A282EA, driver, entity, xTarget, yTarget, zTarget); }
	NATIVE_DECL BOOL GET_VEHICLE_LOCK_ON_TARGET(Vehicle vehicle, Entity* entity) { return invoke<BOOL>(0x8F5EBAB1F260CFCE, vehicle, entity); }
	NATIVE_DECL void SET_FORCE_HD_VEHICLE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x97CE68CB032583F0, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_CUSTOM_PATH_NODE_STREAMING_RADIUS(Vehicle vehicle, float p1) { invoke<Void>(0x182F266C2D9E2BEB, vehicle, p1); }
	NATIVE_DECL int GET_VEHICLE_PLATE_TYPE(Vehicle vehicle) { return invoke<int>(0x9CCC9525BF2408E0, vehicle); }
	NATIVE_DECL void TRACK_VEHICLE_VISIBILITY(Vehicle vehicle) { invoke<Void>(0x64473AEFDCF47DCA, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_VISIBLE(Vehicle vehicle) { return invoke<BOOL>(0xAA0A52D24FB98293, vehicle); }
	NATIVE_DECL void SET_VEHICLE_GRAVITY(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x89F149B6131E57DA, vehicle, toggle); }
	NATIVE_DECL void SET_ENABLE_VEHICLE_SLIPSTREAMING(BOOL toggle) { invoke<Void>(0xE6C0C80B8C867537, toggle); }
	NATIVE_DECL void SET_VEHICLE_SLIPSTREAMING_SHOULD_TIME_OUT(BOOL toggle) { invoke<Void>(0xF051D9BFB6BA39C0, toggle); }
	NATIVE_DECL float GET_VEHICLE_CURRENT_TIME_IN_SLIP_STREAM(Vehicle vehicle) { return invoke<float>(0x36492C2F0D134C56, vehicle); }
	NATIVE_DECL BOOL IS_VEHICLE_PRODUCING_SLIP_STREAM(Vehicle vehicle) { return invoke<BOOL>(0x48C633E94A8142A7, vehicle); }
	NATIVE_DECL void SET_VEHICLE_INACTIVE_DURING_PLAYBACK(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x06582AFF74894C75, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_ACTIVE_DURING_PLAYBACK(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xDFFCEF48E511DB48, vehicle, toggle); }
	NATIVE_DECL BOOL IS_VEHICLE_SPRAYABLE(Vehicle vehicle) { return invoke<BOOL>(0x8D474C8FAEFF6CDE, vehicle); }
	NATIVE_DECL void SET_VEHICLE_ENGINE_CAN_DEGRADE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x983765856F2564F9, vehicle, toggle); }
	NATIVE_DECL void DISABLE_VEHCILE_DYNAMIC_AMBIENT_SCALES(Vehicle vehicle, int p1, int p2) { invoke<Void>(0xF0E4BA16D1DB546C, vehicle, p1, p2); }
	NATIVE_DECL void ENABLE_VEHICLE_DYNAMIC_AMBIENT_SCALES(Vehicle vehicle) { invoke<Void>(0xF87D9F2301F7D206, vehicle); }
	NATIVE_DECL BOOL IS_PLANE_LANDING_GEAR_INTACT(Vehicle plane) { return invoke<BOOL>(0x4198AB0022B15F87, plane); }
	NATIVE_DECL BOOL ARE_PLANE_PROPELLERS_INTACT(Vehicle plane) { return invoke<BOOL>(0x755D6D5267CBBD7E, plane); }
	NATIVE_DECL BOOL SET_PLANE_PROPELLER_HEALTH(Vehicle plane, float health) { return invoke<BOOL>(0x4C815EB175086F84, plane, health); }
	NATIVE_DECL void SET_VEHICLE_CAN_DEFORM_WHEELS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x0CDDA42F9E360CA6, vehicle, toggle); }
	NATIVE_DECL BOOL IS_VEHICLE_STOLEN(Vehicle vehicle) { return invoke<BOOL>(0x4AF9BD80EEBEB453, vehicle); }
	NATIVE_DECL void SET_VEHICLE_IS_STOLEN(Vehicle vehicle, BOOL isStolen) { invoke<Void>(0x67B2C79AA7FF5738, vehicle, isStolen); }
	NATIVE_DECL void SET_PLANE_TURBULENCE_MULTIPLIER(Vehicle vehicle, float multiplier) { invoke<Void>(0xAD2D28A1AFDFF131, vehicle, multiplier); }
	NATIVE_DECL BOOL ARE_WINGS_OF_PLANE_INTACT(Vehicle plane) { return invoke<BOOL>(0x5991A01434CE9677, plane); }
	NATIVE_DECL void ALLOW_AMBIENT_VEHICLES_TO_AVOID_ADVERSE_CONDITIONS(Vehicle vehicle) { invoke<Void>(0xB264C4D2F2B0A78B, vehicle); }
	NATIVE_DECL void DETACH_VEHICLE_FROM_CARGOBOB(Vehicle vehicle, Vehicle cargobob) { invoke<Void>(0x0E21D3DF1051399D, vehicle, cargobob); }
	NATIVE_DECL BOOL DETACH_VEHICLE_FROM_ANY_CARGOBOB(Vehicle vehicle) { return invoke<BOOL>(0xADF7BE450512C12F, vehicle); }
	NATIVE_DECL BOOL DETACH_ENTITY_FROM_CARGOBOB(Vehicle cargobob, Entity entity) { return invoke<BOOL>(0xAF03011701811146, cargobob, entity); }
	NATIVE_DECL BOOL IS_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob, Vehicle vehicleAttached) { return invoke<BOOL>(0xD40148F22E81A1D9, cargobob, vehicleAttached); }
	NATIVE_DECL Vehicle GET_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob) { return invoke<Vehicle>(0x873B82D42AC2B9E5, cargobob); }
	NATIVE_DECL Entity GET_ENTITY_ATTACHED_TO_CARGOBOB(Any p0) { return invoke<Entity>(0x99093F60746708CA, p0); }
	NATIVE_DECL void ATTACH_VEHICLE_TO_CARGOBOB(Vehicle cargobob, Vehicle vehicle, int p2, float x, float y, float z) { invoke<Void>(0x4127F1D84E347769, cargobob, vehicle, p2, x, y, z); }
	NATIVE_DECL void ATTACH_ENTITY_TO_CARGOBOB(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xA1DD82F3CCF9A01E, p0, p1, p2, p3, p4, p5); }
	NATIVE_DECL void SET_CARGOBOB_FORCE_DONT_DETACH_VEHICLE(Vehicle cargobob, BOOL toggle) { invoke<Void>(0x571FEB383F629926, cargobob, toggle); }
	NATIVE_DECL void SET_CARGOBOB_EXCLUDE_FROM_PICKUP_ENTITY(Any p0, Any p1) { invoke<Void>(0x1F34B0626C594380, p0, p1); }
	NATIVE_DECL BOOL CAN_CARGOBOB_PICK_UP_ENTITY(Any p0, Any p1) { return invoke<BOOL>(0x2C1D8B3B19E517CC, p0, p1); }
	NATIVE_DECL Vector3 GET_ATTACHED_PICK_UP_HOOK_POSITION(Vehicle cargobob) { return invoke<Vector3>(0xCBDB9B923CACC92D, cargobob); }
	NATIVE_DECL BOOL DOES_CARGOBOB_HAVE_PICK_UP_ROPE(Vehicle cargobob) { return invoke<BOOL>(0x1821D91AD4B56108, cargobob); }
	NATIVE_DECL void CREATE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob, int state) { invoke<Void>(0x7BEB0C7A235F6F3B, cargobob, state); }
	NATIVE_DECL void REMOVE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob) { invoke<Void>(0x9768CF648F54C804, cargobob); }
	NATIVE_DECL void SET_PICKUP_ROPE_LENGTH_FOR_CARGOBOB(Vehicle cargobob, float length1, float length2, BOOL p3) { invoke<Void>(0x877C1EAEAC531023, cargobob, length1, length2, p3); }
	NATIVE_DECL void SET_PICKUP_ROPE_LENGTH_WITHOUT_CREATING_ROPE_FOR_CARGOBOB(Any p0, Any p1, Any p2) { invoke<Void>(0xC0ED6438E6D39BA8, p0, p1, p2); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_ROPE_DAMPING_MULTIPLIER(Any p0, Any p1) { invoke<Void>(0xCF1182F682F65307, p0, p1); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_ROPE_TYPE(Any p0, Any p1) { invoke<Void>(0x0D5F65A8F4EBDAB5, p0, p1); }
	NATIVE_DECL BOOL DOES_CARGOBOB_HAVE_PICKUP_MAGNET(Vehicle cargobob) { return invoke<BOOL>(0x6E08BF5B3722BAC9, cargobob); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(Vehicle cargobob, BOOL isActive) { invoke<Void>(0x9A665550F8DA349B, cargobob, isActive); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(Vehicle cargobob, float strength) { invoke<Void>(0xBCBFCD9D1DAC19E2, cargobob, strength); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_MAGNET_FALLOFF(Vehicle cargobob, float p1) { invoke<Void>(0xA17BAD153B51547E, cargobob, p1); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_MAGNET_REDUCED_STRENGTH(Vehicle cargobob, float p1) { invoke<Void>(0x66979ACF5102FD2F, cargobob, p1); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_MAGNET_REDUCED_FALLOFF(Vehicle cargobob, float p1) { invoke<Void>(0x6D8EAC07506291FB, cargobob, p1); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_MAGNET_PULL_STRENGTH(Vehicle cargobob, float p1) { invoke<Void>(0xED8286F71A819BAA, cargobob, p1); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_MAGNET_PULL_ROPE_LENGTH(Vehicle vehicle, float p1) { invoke<Void>(0x685D5561680D088B, vehicle, p1); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_MAGNET_SET_TARGETED_MODE(Vehicle vehicle, Vehicle cargobob) { invoke<Void>(0xE301BD63E9E13CF0, vehicle, cargobob); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_MAGNET_SET_AMBIENT_MODE(Vehicle vehicle, BOOL p1, BOOL p2) { invoke<Void>(0x9BDDC73CC6A115D4, vehicle, p1, p2); }
	NATIVE_DECL void SET_CARGOBOB_PICKUP_MAGNET_ENSURE_PICKUP_ENTITY_UPRIGHT(Vehicle vehicle, BOOL p1) { invoke<Void>(0x56EB5E94318D3FB6, vehicle, p1); }
	NATIVE_DECL BOOL DOES_VEHICLE_HAVE_WEAPONS(Vehicle vehicle) { return invoke<BOOL>(0x25ECB9F8017D98E0, vehicle); }
	NATIVE_DECL void SET_VEHICLE_WILL_TELL_OTHERS_TO_HURRY(Vehicle vehicle, BOOL p1) { invoke<Void>(0x2C4A1590ABF43E8B, vehicle, p1); }
	NATIVE_DECL void DISABLE_VEHICLE_WEAPON(BOOL disabled, Hash weaponHash, Vehicle vehicle, Ped owner) { invoke<Void>(0xF4FC6A6F67D8D856, disabled, weaponHash, vehicle, owner); }
	NATIVE_DECL BOOL IS_VEHICLE_WEAPON_DISABLED(Hash weaponHash, Vehicle vehicle, Ped owner) { return invoke<BOOL>(0x563B65A643ED072E, weaponHash, vehicle, owner); }
	NATIVE_DECL void SET_VEHICLE_USED_FOR_PILOT_SCHOOL(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xE05DD0E9707003A3, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_ACTIVE_FOR_PED_NAVIGATION(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x21115BCD6E44656A, vehicle, toggle); }
	NATIVE_DECL int GET_VEHICLE_CLASS(Vehicle vehicle) { return invoke<int>(0x29439776AAA00A62, vehicle); }
	NATIVE_DECL int GET_VEHICLE_CLASS_FROM_NAME(Hash modelHash) { return invoke<int>(0xDEDF1C8BD47C2200, modelHash); }
	NATIVE_DECL void SET_PLAYERS_LAST_VEHICLE(Vehicle vehicle) { invoke<Void>(0xBCDF8BAF56C87B6A, vehicle); }
	NATIVE_DECL void SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x300504B23BD3B711, vehicle, toggle); }
	NATIVE_DECL void SET_AIRCRAFT_PILOT_SKILL_NOISE_SCALAR(Vehicle vehicle, float p1) { invoke<Void>(0xE5810AC70602F2F5, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_DROPS_MONEY_WHEN_BLOWN_UP(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x068F64F2470F9656, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_KEEP_ENGINE_ON_WHEN_ABANDONED(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xB8FBC8B1330CA9B4, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_IMPATIENCE_TIMER(Vehicle vehicle, Any p1) { invoke<Void>(0x6A973569BA094650, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_HANDLING_OVERRIDE(Vehicle vehicle, Hash hash) { invoke<Void>(0x10655FAB9915623D, vehicle, hash); }
	NATIVE_DECL void SET_VEHICLE_EXTENDED_REMOVAL_RANGE(Vehicle vehicle, int range) { invoke<Void>(0x79DF7E806202CE01, vehicle, range); }
	NATIVE_DECL void SET_VEHICLE_STEERING_BIAS_SCALAR(Any p0, float p1) { invoke<Void>(0x9007A2F21DC108D4, p0, p1); }
	NATIVE_DECL void SET_HELI_CONTROL_LAGGING_RATE_SCALAR(Vehicle helicopter, float multiplier) { invoke<Void>(0x6E0859B530A365CC, helicopter, multiplier); }
	NATIVE_DECL void SET_VEHICLE_FRICTION_OVERRIDE(Vehicle vehicle, float friction) { invoke<Void>(0x1837AF7C627009BA, vehicle, friction); }
	NATIVE_DECL void SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xA37B9A517B133349, vehicle, toggle); }
	NATIVE_DECL BOOL ARE_PLANE_CONTROL_PANELS_INTACT(Vehicle vehicle, BOOL p1) { return invoke<BOOL>(0xF78F94D60248C737, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_CEILING_HEIGHT(Vehicle vehicle, float height) { invoke<Void>(0xA46413066687A328, vehicle, height); }
	NATIVE_DECL void SET_VEHICLE_NO_EXPLOSION_DAMAGE_FROM_DRIVER(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x5E569EC46EC21CAE, vehicle, toggle); }
	NATIVE_DECL void CLEAR_VEHICLE_ROUTE_HISTORY(Vehicle vehicle) { invoke<Void>(0x6D6AF961B72728AE, vehicle); }
	NATIVE_DECL Vehicle DOES_VEHICLE_EXIST_WITH_DECORATOR(const char* decorator) { return invoke<Vehicle>(0x956B409B984D9BF7, decorator); }
	NATIVE_DECL void SET_VEHICLE_AI_CAN_USE_EXCLUSIVE_SEATS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x41062318F23ED854, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_EXCLUSIVE_DRIVER(Vehicle vehicle, Ped ped, int index) { invoke<Void>(0xB5C51B5502E85E83, vehicle, ped, index); }
	NATIVE_DECL BOOL IS_PED_EXCLUSIVE_DRIVER_OF_VEHICLE(Ped ped, Vehicle vehicle, int* outIndex) { return invoke<BOOL>(0xB09D25E77C33EB3F, ped, vehicle, outIndex); }
	NATIVE_DECL void DISABLE_INDIVIDUAL_PLANE_PROPELLER(Vehicle vehicle, int propeller) { invoke<Void>(0x500873A45724C863, vehicle, propeller); }
	NATIVE_DECL void _ENABLE_INDIVIDUAL_PLANE_PROPELLER(Vehicle vehicle, int propeller) { invoke<Void>(0xDC05D2777F855F44, vehicle, propeller); }
	NATIVE_DECL void SET_VEHICLE_FORCE_AFTERBURNER(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xB055A34527CB8FD7, vehicle, toggle); }
	NATIVE_DECL void SET_DONT_PROCESS_VEHICLE_GLASS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x1087BC8EC540DAEB, vehicle, toggle); }
	NATIVE_DECL void SET_DISABLE_WANTED_CONES_RESPONSE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x4AD280EB48B2D8E6, vehicle, toggle); }
	NATIVE_DECL void SET_USE_DESIRED_Z_CRUISE_SPEED_FOR_LANDING(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xB68CFAF83A02768D, vehicle, toggle); }
	NATIVE_DECL void SET_ARRIVE_DISTANCE_OVERRIDE_FOR_VEHICLE_PERSUIT_ATTACK(Vehicle vehicle, float p1) { invoke<Void>(0x0205F5365292D2EB, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_READY_FOR_CLEANUP(Any p0) { invoke<Void>(0xCF9159024555488C, p0); }
	NATIVE_DECL void SET_DISTANT_CARS_ENABLED(BOOL toggle) { invoke<Void>(0xF796359A959DF65D, toggle); }
	NATIVE_DECL void SET_VEHICLE_NEON_COLOUR(Vehicle vehicle, int r, int g, int b) { invoke<Void>(0x8E0A582209A62695, vehicle, r, g, b); }
	NATIVE_DECL void SET_VEHICLE_NEON_INDEX_COLOUR(Vehicle vehicle, int index) { invoke<Void>(0xB93B2867F7B479D1, vehicle, index); }
	NATIVE_DECL void GET_VEHICLE_NEON_COLOUR(Vehicle vehicle, int* r, int* g, int* b) { invoke<Void>(0x7619EEE8C886757F, vehicle, r, g, b); }
	NATIVE_DECL void SET_VEHICLE_NEON_ENABLED(Vehicle vehicle, int index, BOOL toggle) { invoke<Void>(0x2AA720E4287BF269, vehicle, index, toggle); }
	NATIVE_DECL BOOL GET_VEHICLE_NEON_ENABLED(Vehicle vehicle, int index) { return invoke<BOOL>(0x8C4B92553E4766A5, vehicle, index); }
	NATIVE_DECL void SET_AMBIENT_VEHICLE_NEON_ENABLED(BOOL p0) { invoke<Void>(0x35E0654F4BAD7971, p0); }
	NATIVE_DECL void SUPPRESS_NEONS_ON_VEHICLE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x83F813570FF519DE, vehicle, toggle); }
	NATIVE_DECL void SET_DISABLE_SUPERDUMMY(Vehicle vehicle, BOOL p1) { invoke<Void>(0xB088E9A47AE6EDD5, vehicle, p1); }
	NATIVE_DECL void REQUEST_VEHICLE_DIAL(Vehicle vehicle) { invoke<Void>(0xDBA3C090E3D74690, vehicle); }
	NATIVE_DECL float GET_VEHICLE_BODY_HEALTH(Vehicle vehicle) { return invoke<float>(0xF271147EB7B40F12, vehicle); }
	NATIVE_DECL void SET_VEHICLE_BODY_HEALTH(Vehicle vehicle, float value) { invoke<Void>(0xB77D05AC8C78AADB, vehicle, value); }
	NATIVE_DECL void GET_VEHICLE_SIZE(Vehicle vehicle, Vector3* out1, Vector3* out2) { invoke<Void>(0xDF7E3EEB29642C38, vehicle, out1, out2); }
	NATIVE_DECL float GET_FAKE_SUSPENSION_LOWERING_AMOUNT(Vehicle vehicle) { return invoke<float>(0x53952FD2BAA19F17, vehicle); }
	NATIVE_DECL void SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER(float multiplier) { invoke<Void>(0x84FD40F56075E816, multiplier); }
	NATIVE_DECL int GET_NUMBER_OF_VEHICLE_DOORS(Vehicle vehicle) { return invoke<int>(0x92922A607497B14D, vehicle); }
	NATIVE_DECL void SET_HYDRAULICS_CONTROL(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x28B18377EB6E25F6, vehicle, toggle); }
	NATIVE_DECL void SET_CAN_ADJUST_GROUND_CLEARANCE(Vehicle vehicle, BOOL p1) { invoke<Void>(0xA7DCDF4DED40A8F4, vehicle, p1); }
	NATIVE_DECL float GET_VEHICLE_HEALTH_PERCENTAGE(Vehicle vehicle, float maxEngineHealth, float maxPetrolTankHealth, float maxBodyHealth, float maxMainRotorHealth, float maxTailRotorHealth, float maxUnkHealth) { return invoke<float>(0xB8EF61207C2393A9, vehicle, maxEngineHealth, maxPetrolTankHealth, maxBodyHealth, maxMainRotorHealth, maxTailRotorHealth, maxUnkHealth); }
	NATIVE_DECL BOOL GET_VEHICLE_IS_MERCENARY(Vehicle vehicle) { return invoke<BOOL>(0xD4C4642CB7F50B5D, vehicle); }
	NATIVE_DECL void SET_VEHICLE_BROKEN_PARTS_DONT_AFFECT_AI_HANDLING(Vehicle vehicle, BOOL p1) { invoke<Void>(0xC361AA040D6637A8, vehicle, p1); }
	NATIVE_DECL void SET_VEHICLE_KERS_ALLOWED(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x99C82F8A139F3E4E, vehicle, toggle); }
	NATIVE_DECL BOOL GET_VEHICLE_HAS_KERS(Vehicle vehicle) { return invoke<BOOL>(0x50634E348C8D44EF, vehicle); }
	NATIVE_DECL void SET_PLANE_RESIST_TO_EXPLOSION(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xE16142B94664DEFD, vehicle, toggle); }
	NATIVE_DECL void SET_HELI_RESIST_TO_EXPLOSION(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x8074CC1886802912, vehicle, toggle); }
	NATIVE_DECL void SET_DISABLE_BMX_EXTRA_TRICK_FORCES(Any p0) { invoke<Void>(0x26D99D5A82FD18E8, p0); }
	NATIVE_DECL void SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(Vehicle vehicle, int wheelId, float value) { invoke<Void>(0x84EA99C62CB3EF0C, vehicle, wheelId, value); }
	NATIVE_DECL float GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(Vehicle vehicle, int wheelId) { return invoke<float>(0x0BB5CBDDD0F25AE3, vehicle, wheelId); }
	NATIVE_DECL void SET_CAN_USE_HYDRAULICS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x1201E8A3290A3B98, vehicle, toggle); }
	NATIVE_DECL void SET_HYDRAULIC_VEHICLE_STATE(Vehicle vehicle, int state) { invoke<Void>(0x8EA86DF356801C7D, vehicle, state); }
	NATIVE_DECL void SET_HYDRAULIC_WHEEL_STATE(Vehicle vehicle, int wheelId, int state, float value, Any p4) { invoke<Void>(0xC24075310A8B9CD1, vehicle, wheelId, state, value, p4); }
	NATIVE_DECL BOOL HAS_VEHICLE_PETROLTANK_SET_ON_FIRE_BY_ENTITY(Any p0, Any p1) { return invoke<BOOL>(0x5BA68A0840D546AC, p0, p1); }
	NATIVE_DECL void CLEAR_VEHICLE_PETROLTANK_FIRE_CULPRIT(Vehicle vehicle) { invoke<Void>(0x4419966C9936071A, vehicle); }
	NATIVE_DECL void SET_VEHICLE_BOBBLEHEAD_VELOCITY(float x, float y, float p2) { invoke<Void>(0x870B8B7A766615C8, x, y, p2); }
	NATIVE_DECL BOOL GET_VEHICLE_IS_DUMMY(Any p0) { return invoke<BOOL>(0x8533CAFDE1F0F336, p0); }
	NATIVE_DECL BOOL SET_VEHICLE_DAMAGE_SCALE(Vehicle vehicle, float p1) { return invoke<BOOL>(0x4E20D2A627011E8E, vehicle, p1); }
	NATIVE_DECL Any _SET_VEHICLE_EXPLOSIVE_DAMAGE_SCALE(Vehicle vehicle, float scale) { return invoke<Any>(0x84D7FFD223CAAFFD, vehicle, scale); }
	NATIVE_DECL BOOL SET_VEHICLE_WEAPON_DAMAGE_SCALE(Vehicle vehicle, float multiplier) { return invoke<BOOL>(0x45A561A9421AB6AD, vehicle, multiplier); }
	NATIVE_DECL BOOL SET_DISABLE_DAMAGE_WITH_PICKED_UP_ENTITY(Any p0, Any p1) { return invoke<BOOL>(0xD4196117AF7BB974, p0, p1); }
	NATIVE_DECL void SET_VEHICLE_USES_MP_PLAYER_DAMAGE_MULTIPLIER(Any p0, Any p1) { invoke<Void>(0xBB2333BB87DDD87F, p0, p1); }
	NATIVE_DECL void SET_BIKE_EASY_TO_LAND(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x73561D4425A021A2, vehicle, toggle); }
	NATIVE_DECL void SET_INVERT_VEHICLE_CONTROLS(Vehicle vehicle, BOOL state) { invoke<Void>(0x5B91B229243351A8, vehicle, state); }
	NATIVE_DECL void SET_SPEED_BOOST_EFFECT_DISABLED(BOOL disabled) { invoke<Void>(0x7BBE7FF626A591FE, disabled); }
	NATIVE_DECL void SET_SLOW_DOWN_EFFECT_DISABLED(BOOL disabled) { invoke<Void>(0x65B080555EA48149, disabled); }
	NATIVE_DECL void SET_FORMATION_LEADER(Vehicle vehicle, float x, float y, float z, float p4) { invoke<Void>(0x428AD3E26C8D9EB0, vehicle, x, y, z, p4); }
	NATIVE_DECL void RESET_FORMATION_LEADER() { invoke<Void>(0xE2F53F172B45EDE1); }
	NATIVE_DECL BOOL GET_IS_BOAT_CAPSIZED(Vehicle vehicle) { return invoke<BOOL>(0xBA91D045575699AD, vehicle); }
	NATIVE_DECL void SET_ALLOW_RAMMING_SOOP_OR_RAMP(Any p0, Any p1) { invoke<Void>(0x80E3357FDEF45C21, p0, p1); }
	NATIVE_DECL void SET_SCRIPT_RAMP_IMPULSE_SCALE(Vehicle vehicle, float impulseScale) { invoke<Void>(0xEFC13B1CE30D755D, vehicle, impulseScale); }
	NATIVE_DECL BOOL GET_IS_DOOR_VALID(Vehicle vehicle, int doorId) { return invoke<BOOL>(0x645F4B6E8499F632, vehicle, doorId); }
	NATIVE_DECL void SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME(Vehicle vehicle, float seconds) { invoke<Void>(0xE00F2AB100B76E89, vehicle, seconds); }
	NATIVE_DECL BOOL GET_HAS_ROCKET_BOOST(Vehicle vehicle) { return invoke<BOOL>(0x36D782F68B309BDA, vehicle); }
	NATIVE_DECL BOOL IS_ROCKET_BOOST_ACTIVE(Vehicle vehicle) { return invoke<BOOL>(0x3D34E80EED4AE3BE, vehicle); }
	NATIVE_DECL void SET_ROCKET_BOOST_ACTIVE(Vehicle vehicle, BOOL active) { invoke<Void>(0x81E1552E35DC3839, vehicle, active); }
	NATIVE_DECL BOOL GET_HAS_RETRACTABLE_WHEELS(Vehicle vehicle) { return invoke<BOOL>(0xDCA174A42133F08C, vehicle); }
	NATIVE_DECL BOOL GET_IS_WHEELS_RETRACTED(Vehicle vehicle) { return invoke<BOOL>(0x1DA0DA9CB3F0C8BF, vehicle); }
	NATIVE_DECL void SET_WHEELS_EXTENDED_INSTANTLY(Vehicle vehicle) { invoke<Void>(0xF660602546D27BA8, vehicle); }
	NATIVE_DECL void SET_WHEELS_RETRACTED_INSTANTLY(Vehicle vehicle) { invoke<Void>(0x5335BE58C083E74E, vehicle); }
	NATIVE_DECL BOOL GET_CAR_HAS_JUMP(Vehicle vehicle) { return invoke<BOOL>(0x9078C0C5EF8C19E9, vehicle); }
	NATIVE_DECL void SET_USE_HIGHER_CAR_JUMP(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xF06A16CA55D138D8, vehicle, toggle); }
	NATIVE_DECL void SET_CLEAR_FREEZE_WAITING_ON_COLLISION_ONCE_PLAYER_ENTERS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xB2E0C0D6922D31F2, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_WEAPON_RESTRICTED_AMMO(Vehicle vehicle, int weaponIndex, int capacity) { invoke<Void>(0x44CD1F493DB2A0A6, vehicle, weaponIndex, capacity); }
	NATIVE_DECL int GET_VEHICLE_WEAPON_RESTRICTED_AMMO(Vehicle vehicle, int weaponIndex) { return invoke<int>(0x8181CE2F25CB9BB7, vehicle, weaponIndex); }
	NATIVE_DECL BOOL GET_VEHICLE_HAS_PARACHUTE(Vehicle vehicle) { return invoke<BOOL>(0xBC9CFF381338CB4F, vehicle); }
	NATIVE_DECL BOOL GET_VEHICLE_CAN_DEPLOY_PARACHUTE(Vehicle vehicle) { return invoke<BOOL>(0xA916396DF4154EE3, vehicle); }
	NATIVE_DECL void VEHICLE_START_PARACHUTING(Vehicle vehicle, BOOL active) { invoke<Void>(0x0BFFB028B3DD0A97, vehicle, active); }
	NATIVE_DECL BOOL IS_VEHICLE_PARACHUTE_DEPLOYED(Vehicle vehicle) { return invoke<BOOL>(0x3DE51E9C80B116CF, vehicle); }
	NATIVE_DECL void VEHICLE_SET_RAMP_AND_RAMMING_CARS_TAKE_DAMAGE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x28D034A93FE31BF5, vehicle, toggle); }
	NATIVE_DECL void VEHICLE_SET_ENABLE_RAMP_CAR_SIDE_IMPULSE(Any p0, Any p1) { invoke<Void>(0x1BBAC99C0BC53656, p0, p1); }
	NATIVE_DECL void VEHICLE_SET_ENABLE_NORMALISE_RAMP_CAR_VERTICAL_VELOCTIY(Any p0, Any p1) { invoke<Void>(0x756AE6E962168A04, p0, p1); }
	NATIVE_DECL void VEHICLE_SET_JET_WASH_FORCE_ENABLED(Any p0) { invoke<Void>(0x9D30687C57BAA0BB, p0); }
	NATIVE_DECL void SET_VEHICLE_WEAPON_CAN_TARGET_OBJECTS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x86B4B6212CB8B627, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_USE_BOOST_BUTTON_FOR_WHEEL_RETRACT(BOOL toggle) { invoke<Void>(0x41290B40FA63E6DA, toggle); }
	NATIVE_DECL void _SET_VEHICLE_USE_HORN_BUTTON_FOR_NITROUS(BOOL toggle) { invoke<Void>(0x1980F68872CC2C3D, toggle); }
	NATIVE_DECL void VEHICLE_SET_PARACHUTE_MODEL_OVERRIDE(Vehicle vehicle, Hash modelHash) { invoke<Void>(0x4D610C6B56031351, vehicle, modelHash); }
	NATIVE_DECL void VEHICLE_SET_PARACHUTE_MODEL_TINT_INDEX(Vehicle vehicle, int textureVariation) { invoke<Void>(0xA74AD2439468C883, vehicle, textureVariation); }
	NATIVE_DECL int VEHICLE_SET_OVERRIDE_EXTENABLE_SIDE_RATIO(Any p0, Any p1) { return invoke<int>(0x0419B167EE128F33, p0, p1); }
	NATIVE_DECL int VEHICLE_SET_EXTENABLE_SIDE_TARGET_RATIO(Any p0, Any p1) { return invoke<int>(0xF3B0E0AED097A3F5, p0, p1); }
	NATIVE_DECL int VEHICLE_SET_OVERRIDE_SIDE_RATIO(Any p0, Any p1) { return invoke<int>(0xD3E51C0AB8C26EEE, p0, p1); }
	NATIVE_DECL int GET_ALL_VEHICLES(Any* vehsStruct) { return invoke<int>(0x9B8E1BF04B51F2E8, vehsStruct); }
	NATIVE_DECL void SET_CARGOBOB_EXTA_PICKUP_RANGE(Any p0, Any p1) { invoke<Void>(0x72BECCF4B829522E, p0, p1); }
	NATIVE_DECL void SET_OVERRIDE_VEHICLE_DOOR_TORQUE(Any p0, Any p1, Any p2) { invoke<Void>(0x66E3AAFACE2D1EB8, p0, p1, p2); }
	NATIVE_DECL void SET_WHEELIE_ENABLED(Vehicle vehicle, BOOL enabled) { invoke<Void>(0x1312DDD8385AEE4E, vehicle, enabled); }
	NATIVE_DECL void SET_DISABLE_HELI_EXPLODE_FROM_BODY_DAMAGE(Vehicle vehicle, BOOL disable) { invoke<Void>(0xEDBC8405B3895CC9, vehicle, disable); }
	NATIVE_DECL void SET_DISABLE_EXPLODE_FROM_BODY_DAMAGE_ON_COLLISION(Vehicle vehicle, BOOL disable) { invoke<Void>(0x26E13D440E7F6064, vehicle, disable); }
	NATIVE_DECL void _SET_DISABLE_EXPLODE_FROM_BODY_DAMAGE_RECEIVED_BY_AI_VEHICLE(Vehicle vehicle, BOOL disable) { invoke<Void>(0xB0B7DF5CB876FF5E, vehicle, disable); }
	NATIVE_DECL void SET_TRAILER_ATTACHMENT_ENABLED(Any p0, Any p1) { invoke<Void>(0x2FA2494B47FDD009, p0, p1); }
	NATIVE_DECL void SET_ROCKET_BOOST_FILL(Vehicle vehicle, float percentage) { invoke<Void>(0xFEB2DDED3509562E, vehicle, percentage); }
	NATIVE_DECL void SET_GLIDER_ACTIVE(Vehicle vehicle, BOOL state) { invoke<Void>(0x544996C0081ABDEB, vehicle, state); }
	NATIVE_DECL void SET_SHOULD_RESET_TURRET_IN_SCRIPTED_CAMERAS(Vehicle vehicle, BOOL shouldReset) { invoke<Void>(0x78CEEE41F49F421F, vehicle, shouldReset); }
	NATIVE_DECL void SET_VEHICLE_DISABLE_COLLISION_UPON_CREATION(Vehicle vehicle, BOOL disable) { invoke<Void>(0xAF60E6A2936F982A, vehicle, disable); }
	NATIVE_DECL void SET_GROUND_EFFECT_REDUCES_DRAG(BOOL toggle) { invoke<Void>(0x430A7631A84C9BE7, toggle); }
	NATIVE_DECL void SET_DISABLE_MAP_COLLISION(Vehicle vehicle) { invoke<Void>(0x75627043C6AA90AD, vehicle); }
	NATIVE_DECL void SET_DISABLE_PED_STAND_ON_TOP(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x8235F1BEAD557629, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_DAMAGE_SCALES(Vehicle vehicle, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x9640E30A7F395E4B, vehicle, p1, p2, p3, p4); }
	NATIVE_DECL void SET_PLANE_SECTION_DAMAGE_SCALE(Vehicle vehicle, Any p1, Any p2) { invoke<Void>(0x0BBB9A7A8FFE931B, vehicle, p1, p2); }
	NATIVE_DECL void SET_PLANE_CONTROL_SECTIONS_SHOULD_BREAK_OFF_FROM_EXPLOSIONS(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xDD8A2D3337F04196, vehicle, toggle); }
	NATIVE_DECL void SET_HELI_CAN_PICKUP_ENTITY_THAT_HAS_PICK_UP_DISABLED(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x94A68DA412C4007D, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_BOMB_AMMO(Vehicle vehicle, int bombCount) { invoke<Void>(0xF4B2ED59DEB5D774, vehicle, bombCount); }
	NATIVE_DECL int GET_VEHICLE_BOMB_AMMO(Vehicle vehicle) { return invoke<int>(0xEA12BD130D7569A1, vehicle); }
	NATIVE_DECL void SET_VEHICLE_COUNTERMEASURE_AMMO(Vehicle vehicle, int counterMeasureCount) { invoke<Void>(0x9BDA23BF666F0855, vehicle, counterMeasureCount); }
	NATIVE_DECL int GET_VEHICLE_COUNTERMEASURE_AMMO(Vehicle vehicle) { return invoke<int>(0xF846AA63DF56B804, vehicle); }
	NATIVE_DECL void SET_HELI_COMBAT_OFFSET(Vehicle vehicle, float x, float y, float z) { invoke<Void>(0x0A3F820A9A9A9AC5, vehicle, x, y, z); }
	NATIVE_DECL BOOL GET_CAN_VEHICLE_BE_PLACED_HERE(Vehicle vehicle, float x, float y, float z, float rotX, float rotY, float rotZ, int p7, Any p8) { return invoke<BOOL>(0x51F30DB60626A20E, vehicle, x, y, z, rotX, rotY, rotZ, p7, p8); }
	NATIVE_DECL void SET_DISABLE_AUTOMATIC_CRASH_TASK(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x97841634EF7DF1D6, vehicle, toggle); }
	NATIVE_DECL void SET_SPECIAL_FLIGHT_MODE_RATIO(Vehicle vehicle, float ratio) { invoke<Void>(0xD138FA15C9776837, vehicle, ratio); }
	NATIVE_DECL void SET_SPECIAL_FLIGHT_MODE_TARGET_RATIO(Vehicle vehicle, float targetRatio) { invoke<Void>(0x438B3D7CA026FE91, vehicle, targetRatio); }
	NATIVE_DECL void SET_SPECIAL_FLIGHT_MODE_ALLOWED(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xF1211889DF15A763, vehicle, toggle); }
	NATIVE_DECL void SET_DISABLE_HOVER_MODE_FLIGHT(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x2D55FE374D5FDB91, vehicle, toggle); }
	NATIVE_DECL BOOL GET_OUTRIGGERS_DEPLOYED(Vehicle vehicle) { return invoke<BOOL>(0x3A9128352EAC9E85, vehicle); }
	NATIVE_DECL Vector3 FIND_SPAWN_COORDINATES_FOR_HELI(Ped ped) { return invoke<Vector3>(0x8DC9675797123522, ped); }
	NATIVE_DECL void SET_DEPLOY_FOLDING_WINGS(Vehicle vehicle, BOOL deploy, BOOL p2) { invoke<Void>(0xB251E0B33E58B424, vehicle, deploy, p2); }
	NATIVE_DECL BOOL ARE_FOLDING_WINGS_DEPLOYED(Vehicle vehicle) { return invoke<BOOL>(0xAEF12960FA943792, vehicle); }
	NATIVE_DECL void _SET_DEPLOY_MISSILE_BAYS(Vehicle vehicle, BOOL deploy) { invoke<Void>(0x0C02468829E4AA65, vehicle, deploy); }
	NATIVE_DECL BOOL _ARE_MISSILE_BAYS_DEPLOYED(Vehicle vehicle) { return invoke<BOOL>(0xEA4743874D515F13, vehicle); }
	NATIVE_DECL void SET_DIP_STRAIGHT_DOWN_WHEN_CRASHING_PLANE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xAA653AE61924B0A0, vehicle, toggle); }
	NATIVE_DECL void SET_TURRET_HIDDEN(Vehicle vehicle, int index, BOOL toggle) { invoke<Void>(0xC60060EB0D8AC7B1, vehicle, index, toggle); }
	NATIVE_DECL void SET_HOVER_MODE_WING_RATIO(Vehicle vehicle, float ratio) { invoke<Void>(0x70A252F60A3E036B, vehicle, ratio); }
	NATIVE_DECL void SET_DISABLE_TURRET_MOVEMENT(Vehicle vehicle, int turretId) { invoke<Void>(0xE615BB7A7752C76A, vehicle, turretId); }
	NATIVE_DECL void SET_FORCE_FIX_LINK_MATRICES(Vehicle vehicle) { invoke<Void>(0x887FA38787DE8C72, vehicle); }
	NATIVE_DECL void SET_TRANSFORM_RATE_FOR_ANIMATION(Vehicle vehicle, float transformRate) { invoke<Void>(0x498218259FB7C72D, vehicle, transformRate); }
	NATIVE_DECL void SET_TRANSFORM_TO_SUBMARINE_USES_ALTERNATE_INPUT(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x41B9FB92EDED32A6, vehicle, toggle); }
	NATIVE_DECL void SET_VEHICLE_COMBAT_MODE(BOOL toggle) { invoke<Void>(0x36DE109527A2C0C4, toggle); }
	NATIVE_DECL void SET_VEHICLE_DETONATION_MODE(BOOL toggle) { invoke<Void>(0x82E0AC411E41A5B4, toggle); }
	NATIVE_DECL void SET_VEHICLE_SHUNT_ON_STICK(BOOL toggle) { invoke<Void>(0x99A05839C46CE316, toggle); }
	NATIVE_DECL BOOL _IS_VEHICLE_ON_BOOST_PAD(Vehicle vehicle) { return invoke<BOOL>(0x71C6302CBCA6CA35, vehicle); }
	NATIVE_DECL BOOL GET_IS_VEHICLE_SHUNTING(Vehicle vehicle) { return invoke<BOOL>(0xA2459F72C14E2E8D, vehicle); }
	NATIVE_DECL BOOL GET_HAS_VEHICLE_BEEN_HIT_BY_SHUNT(Vehicle vehicle) { return invoke<BOOL>(0xE8718FAF591FD224, vehicle); }
	NATIVE_DECL Vehicle GET_LAST_SHUNT_VEHICLE(Vehicle vehicle) { return invoke<Vehicle>(0x04F2FA6E234162F7, vehicle); }
	NATIVE_DECL void SET_DISABLE_VEHICLE_EXPLOSIONS_DAMAGE(BOOL toggle) { invoke<Void>(0x143921E45EC44D62, toggle); }
	NATIVE_DECL void SET_OVERRIDE_NITROUS_LEVEL(Vehicle vehicle, BOOL toggle, float level, float power, float rechargeTime, BOOL disableSound) { invoke<Void>(0xC8E9B6B71B8E660D, vehicle, toggle, level, power, rechargeTime, disableSound); }
	NATIVE_DECL void _SET_NITROUS_IS_VISIBLE(Vehicle vehicle, BOOL enabled) { invoke<Void>(0x465EEA70AF251045, vehicle, enabled); }
	NATIVE_DECL void _SET_OVERRIDE_TRACTION_LOSS_MULTIPLIER(Vehicle vehicle, float modifier) { invoke<Void>(0xAFD262ACCA64479A, vehicle, modifier); }
	NATIVE_DECL void _SET_DRIFT_SLIP_ANGLE_LIMITS(Vehicle vehicle, float durationScalar, float amplitudeScalar, float slipAngleLimit) { invoke<Void>(0xDAF4C98C18AC6F06, vehicle, durationScalar, amplitudeScalar, slipAngleLimit); }
	NATIVE_DECL void _SET_MINIMUM_TIME_BETWEEN_GEAR_SHIFTS(Vehicle vehicle, int time) { invoke<Void>(0x16CFBC5E7EB32861, vehicle, time); }
	NATIVE_DECL void FULLY_CHARGE_NITROUS(Vehicle vehicle) { invoke<Void>(0x1A2BCC8C636F9226, vehicle); }
	NATIVE_DECL void _SET_REMAINING_NITROUS_DURATION(Vehicle vehicle, float duration) { invoke<Void>(0x1AD0F63A94E10EFF, vehicle, duration); }
	NATIVE_DECL float _GET_REMAINING_NITROUS_DURATION(Vehicle vehicle) { return invoke<float>(0xBEC4B8653462450E, vehicle); }
	NATIVE_DECL BOOL IS_NITROUS_ACTIVE(Vehicle vehicle) { return invoke<BOOL>(0x491E822B2C464FE4, vehicle); }
	NATIVE_DECL void CLEAR_NITROUS(Vehicle vehicle) { invoke<Void>(0xC889AE921400E1ED, vehicle); }
	NATIVE_DECL void SET_NITROUS_IS_ACTIVE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x9E566EA551F4F1A6, vehicle, toggle); }
	NATIVE_DECL void SET_INCREASE_WHEEL_CRUSH_DAMAGE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x2970EAA18FD5E42F, vehicle, toggle); }
	NATIVE_DECL void SET_DISABLE_WEAPON_BLADE_FORCES(BOOL toggle) { invoke<Void>(0x211E95CE9903940C, toggle); }
	NATIVE_DECL void SET_USE_DOUBLE_CLICK_FOR_CAR_JUMP(BOOL toggle) { invoke<Void>(0x5BBCF35BF6E456F7, toggle); }
	NATIVE_DECL BOOL GET_DOES_VEHICLE_HAVE_TOMBSTONE(Vehicle vehicle) { return invoke<BOOL>(0x71AFB258CCED3A27, vehicle); }
	NATIVE_DECL void HIDE_TOMBSTONE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xAE71FB656C600587, vehicle, toggle); }
	NATIVE_DECL void APPLY_EMP_EFFECT(Vehicle vehicle) { invoke<Void>(0x249249D74F813EB2, vehicle); }
	NATIVE_DECL BOOL GET_IS_VEHICLE_DISABLED_BY_EMP(Vehicle vehicle) { return invoke<BOOL>(0x0506ED94363AD905, vehicle); }
	NATIVE_DECL void SET_DISABLE_RETRACTING_WEAPON_BLADES(BOOL toggle) { invoke<Void>(0x8F0D5BA1C2CC91D7, toggle); }
	NATIVE_DECL float GET_TYRE_HEALTH(Vehicle vehicle, int wheelIndex) { return invoke<float>(0x55EAB010FAEE9380, vehicle, wheelIndex); }
	NATIVE_DECL void SET_TYRE_HEALTH(Vehicle vehicle, int wheelIndex, float health) { invoke<Void>(0x74C68EF97645E79D, vehicle, wheelIndex, health); }
	NATIVE_DECL float GET_TYRE_WEAR_RATE(Vehicle vehicle, int wheelIndex) { return invoke<float>(0x6E387895952F4F71, vehicle, wheelIndex); }
	NATIVE_DECL void SET_TYRE_WEAR_RATE(Vehicle vehicle, int wheelIndex, float multiplier) { invoke<Void>(0x01894E2EDE923CA2, vehicle, wheelIndex, multiplier); }
	NATIVE_DECL void SET_TYRE_WEAR_RATE_SCALE(Vehicle vehicle, int wheelIndex, float multiplier) { invoke<Void>(0x392183BB9EA57697, vehicle, wheelIndex, multiplier); }
	NATIVE_DECL void SET_TYRE_MAXIMUM_GRIP_DIFFERENCE_DUE_TO_WEAR_RATE(Vehicle vehicle, int wheelIndex, float multiplier) { invoke<Void>(0xC970D0E0FC31D768, vehicle, wheelIndex, multiplier); }
	NATIVE_DECL void SET_AIRCRAFT_IGNORE_HIGHTMAP_OPTIMISATION(Vehicle vehicle, int p1) { invoke<Void>(0xF8B49F5BA7F850E7, vehicle, p1); }
	NATIVE_DECL void SET_REDUCED_SUSPENSION_FORCE(Vehicle vehicle, BOOL enable) { invoke<Void>(0x3A375167F5782A65, vehicle, enable); }
	NATIVE_DECL void SET_DRIFT_TYRES(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x5AC79C98C5C17F05, vehicle, toggle); }
	NATIVE_DECL BOOL GET_DRIFT_TYRES_SET(Vehicle vehicle) { return invoke<BOOL>(0x2F5A72430E78C8D3, vehicle); }
	NATIVE_DECL void NETWORK_USE_HIGH_PRECISION_TRAIN_BLENDING(Vehicle vehicle, BOOL toggle) { invoke<Void>(0xEC0C1D4922AF9754, vehicle, toggle); }
	NATIVE_DECL void SET_CHECK_FOR_ENOUGH_ROOM_FOR_PED(Vehicle vehicle, BOOL p1) { invoke<Void>(0xEF9D388F8D377F44, vehicle, p1); }
	NATIVE_DECL void _SET_ALLOW_COLLISION_WHEN_IN_VEHICLE(Vehicle vehicle, BOOL toggle) { invoke<Void>(0x27D27223E8EF22ED, vehicle, toggle); }
	NATIVE_DECL BOOL _IS_VEHICLE_GEN9_EXCLUSIVE_MODEL(Hash vehicleModel) { return invoke<BOOL>(0x6638C0F19DE692FE, vehicleModel); }
	NATIVE_DECL int _GET_VEHICLE_MAX_EXHAUST_BONE_COUNT() { return invoke<int>(0x3EE18B00CD86C54F); }
	NATIVE_DECL BOOL _GET_VEHICLE_EXHAUST_BONE(Vehicle vehicle, int index, int* boneIndex, BOOL* axisX) { return invoke<BOOL>(0xE728F090D538CB18, vehicle, index, boneIndex, axisX); }
}

namespace WATER
{
	NATIVE_DECL BOOL GET_WATER_HEIGHT(float x, float y, float z, float* height) { return invoke<BOOL>(0xF6829842C06AE524, x, y, z, height); }
	NATIVE_DECL BOOL GET_WATER_HEIGHT_NO_WAVES(float x, float y, float z, float* height) { return invoke<BOOL>(0x8EE6B53CE13A9794, x, y, z, height); }
	NATIVE_DECL BOOL TEST_PROBE_AGAINST_WATER(float x1, float y1, float z1, float x2, float y2, float z2, Vector3* result) { return invoke<BOOL>(0xFFA5D878809819DB, x1, y1, z1, x2, y2, z2, result); }
	NATIVE_DECL int TEST_PROBE_AGAINST_ALL_WATER(float x1, float y1, float z1, float x2, float y2, float z2, int flags, float* waterHeight) { return invoke<int>(0x8974647ED222EA5F, x1, y1, z1, x2, y2, z2, flags, waterHeight); }
	NATIVE_DECL int TEST_VERTICAL_PROBE_AGAINST_ALL_WATER(float x, float y, float z, int flags, float* waterHeight) { return invoke<int>(0x2B3451FA1E3142E2, x, y, z, flags, waterHeight); }
	NATIVE_DECL void MODIFY_WATER(float x, float y, float radius, float height) { invoke<Void>(0xC443FD757C3BA637, x, y, radius, height); }
	NATIVE_DECL int ADD_EXTRA_CALMING_QUAD(float xLow, float yLow, float xHigh, float yHigh, float height) { return invoke<int>(0xFDBF4CDBC07E1706, xLow, yLow, xHigh, yHigh, height); }
	NATIVE_DECL void REMOVE_EXTRA_CALMING_QUAD(int calmingQuad) { invoke<Void>(0xB1252E3E59A82AAF, calmingQuad); }
	NATIVE_DECL void SET_DEEP_OCEAN_SCALER(float intensity) { invoke<Void>(0xB96B00E976BE977F, intensity); }
	NATIVE_DECL float GET_DEEP_OCEAN_SCALER() { return invoke<float>(0x2B2A2CC86778B619); }
	NATIVE_DECL void SET_CALMED_WAVE_HEIGHT_SCALER(float height) { invoke<Void>(0x547237AA71AB44DE, height); }
	NATIVE_DECL void RESET_DEEP_OCEAN_SCALER() { invoke<Void>(0x5E5E99285AE812DB); }
}

namespace WEAPON
{
	NATIVE_DECL void ENABLE_LASER_SIGHT_RENDERING(BOOL toggle) { invoke<Void>(0xC8B46D7727D864AA, toggle); }
	NATIVE_DECL Hash GET_WEAPON_COMPONENT_TYPE_MODEL(Hash componentHash) { return invoke<Hash>(0x0DB57B41EC1DB083, componentHash); }
	NATIVE_DECL Hash GET_WEAPONTYPE_MODEL(Hash weaponHash) { return invoke<Hash>(0xF46CDC33180FDA94, weaponHash); }
	NATIVE_DECL Hash GET_WEAPONTYPE_SLOT(Hash weaponHash) { return invoke<Hash>(0x4215460B9B8B7FA0, weaponHash); }
	NATIVE_DECL Hash GET_WEAPONTYPE_GROUP(Hash weaponHash) { return invoke<Hash>(0xC3287EE3050FB74C, weaponHash); }
	NATIVE_DECL int GET_WEAPON_COMPONENT_VARIANT_EXTRA_COUNT(Hash componentHash) { return invoke<int>(0x6558AC7C17BFEF58, componentHash); }
	NATIVE_DECL Hash GET_WEAPON_COMPONENT_VARIANT_EXTRA_MODEL(Hash componentHash, int extraComponentIndex) { return invoke<Hash>(0x4D1CB8DC40208A17, componentHash, extraComponentIndex); }
	NATIVE_DECL void SET_CURRENT_PED_WEAPON(Ped ped, Hash weaponHash, BOOL bForceInHand) { invoke<Void>(0xADF692B254977C0C, ped, weaponHash, bForceInHand); }
	NATIVE_DECL BOOL GET_CURRENT_PED_WEAPON(Ped ped, Hash* weaponHash, BOOL doDeadCheck) { return invoke<BOOL>(0x3A87E44BB9A01D54, ped, weaponHash, doDeadCheck); }
	NATIVE_DECL Entity GET_CURRENT_PED_WEAPON_ENTITY_INDEX(Ped ped, BOOL doDeadCheck) { return invoke<Entity>(0x3B390A939AF0B5FC, ped, doDeadCheck); }
	NATIVE_DECL Hash GET_BEST_PED_WEAPON(Ped ped, BOOL bIgnoreAmmoCheck) { return invoke<Hash>(0x8483E98E8B888AE2, ped, bIgnoreAmmoCheck); }
	NATIVE_DECL BOOL SET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash weaponHash) { return invoke<BOOL>(0x75C55983C2C39DAA, ped, weaponHash); }
	NATIVE_DECL BOOL GET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash* weaponHash) { return invoke<BOOL>(0x1017582BCD3832DC, ped, weaponHash); }
	NATIVE_DECL void SET_PED_CYCLE_VEHICLE_WEAPONS_ONLY(Ped ped) { invoke<Void>(0x50276EF8172F5F12, ped); }
	NATIVE_DECL BOOL IS_PED_ARMED(Ped ped, int typeFlags) { return invoke<BOOL>(0x475768A975D5AD17, ped, typeFlags); }
	NATIVE_DECL BOOL IS_WEAPON_VALID(Hash weaponHash) { return invoke<BOOL>(0x937C71165CF334B3, weaponHash); }
	NATIVE_DECL BOOL HAS_PED_GOT_WEAPON(Ped ped, Hash weaponHash, BOOL p2) { return invoke<BOOL>(0x8DECB02F88F428BC, ped, weaponHash, p2); }
	NATIVE_DECL BOOL IS_PED_WEAPON_READY_TO_SHOOT(Ped ped) { return invoke<BOOL>(0xB80CA294F2F26749, ped); }
	NATIVE_DECL Hash GET_PED_WEAPONTYPE_IN_SLOT(Ped ped, Hash weaponSlot) { return invoke<Hash>(0xEFFED78E9011134D, ped, weaponSlot); }
	NATIVE_DECL int GET_AMMO_IN_PED_WEAPON(Ped ped, Hash weaponhash) { return invoke<int>(0x015A522136D7F951, ped, weaponhash); }
	NATIVE_DECL void ADD_AMMO_TO_PED(Ped ped, Hash weaponHash, int ammo) { invoke<Void>(0x78F0424C34306220, ped, weaponHash, ammo); }
	NATIVE_DECL void SET_PED_AMMO(Ped ped, Hash weaponHash, int ammo, BOOL p3) { invoke<Void>(0x14E56BC5B5DB6A19, ped, weaponHash, ammo, p3); }
	NATIVE_DECL void SET_PED_INFINITE_AMMO(Ped ped, BOOL toggle, Hash weaponHash) { invoke<Void>(0x3EDCB0505123623B, ped, toggle, weaponHash); }
	NATIVE_DECL void SET_PED_INFINITE_AMMO_CLIP(Ped ped, BOOL toggle) { invoke<Void>(0x183DADC6AA953186, ped, toggle); }
	NATIVE_DECL void SET_PED_STUN_GUN_FINITE_AMMO(Any p0, Any p1) { invoke<Void>(0x24C024BA8379A70A, p0, p1); }
	NATIVE_DECL void GIVE_WEAPON_TO_PED(Ped ped, Hash weaponHash, int ammoCount, BOOL isHidden, BOOL bForceInHand) { invoke<Void>(0xBF0FD6E56C964FCB, ped, weaponHash, ammoCount, isHidden, bForceInHand); }
	NATIVE_DECL void GIVE_DELAYED_WEAPON_TO_PED(Ped ped, Hash weaponHash, int ammoCount, BOOL bForceInHand) { invoke<Void>(0xB282DC6EBD803C75, ped, weaponHash, ammoCount, bForceInHand); }
	NATIVE_DECL void REMOVE_ALL_PED_WEAPONS(Ped ped, BOOL p1) { invoke<Void>(0xF25DF915FA38C5F3, ped, p1); }
	NATIVE_DECL void REMOVE_WEAPON_FROM_PED(Ped ped, Hash weaponHash) { invoke<Void>(0x4899CB088EDF59B8, ped, weaponHash); }
	NATIVE_DECL void HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(Ped ped, BOOL toggle) { invoke<Void>(0x6F6981D2253C208F, ped, toggle); }
	NATIVE_DECL void SET_PED_CURRENT_WEAPON_VISIBLE(Ped ped, BOOL visible, BOOL deselectWeapon, BOOL p3, BOOL p4) { invoke<Void>(0x0725A4CCFDED9A70, ped, visible, deselectWeapon, p3, p4); }
	NATIVE_DECL void SET_PED_DROPS_WEAPONS_WHEN_DEAD(Ped ped, BOOL toggle) { invoke<Void>(0x476AE72C1D19D1A8, ped, toggle); }
	NATIVE_DECL BOOL HAS_PED_BEEN_DAMAGED_BY_WEAPON(Ped ped, Hash weaponHash, int weaponType) { return invoke<BOOL>(0x2D343D2219CD027A, ped, weaponHash, weaponType); }
	NATIVE_DECL void CLEAR_PED_LAST_WEAPON_DAMAGE(Ped ped) { invoke<Void>(0x0E98F88A24C5F4B8, ped); }
	NATIVE_DECL BOOL HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(Entity entity, Hash weaponHash, int weaponType) { return invoke<BOOL>(0x131D401334815E94, entity, weaponHash, weaponType); }
	NATIVE_DECL void CLEAR_ENTITY_LAST_WEAPON_DAMAGE(Entity entity) { invoke<Void>(0xAC678E40BE7C74D2, entity); }
	NATIVE_DECL void SET_PED_DROPS_WEAPON(Ped ped) { invoke<Void>(0x6B7513D9966FBEC0, ped); }
	NATIVE_DECL void SET_PED_DROPS_INVENTORY_WEAPON(Ped ped, Hash weaponHash, float xOffset, float yOffset, float zOffset, int ammoCount) { invoke<Void>(0x208A1888007FC0E6, ped, weaponHash, xOffset, yOffset, zOffset, ammoCount); }
	NATIVE_DECL int GET_MAX_AMMO_IN_CLIP(Ped ped, Hash weaponHash, BOOL p2) { return invoke<int>(0xA38DCFFCEA8962FA, ped, weaponHash, p2); }
	NATIVE_DECL int _GET_TIME_BEFORE_VEHICLE_WEAPON_RELOAD_FINISHES(Vehicle vehicle, int seat) { return invoke<int>(0xC8C6F4B1CDEB40EF, vehicle, seat); }
	NATIVE_DECL BOOL _HAS_WEAPON_RELOADING_IN_VEHICLE(Vehicle vehicle, int seat) { return invoke<BOOL>(0x8062F07153F4446F, vehicle, seat); }
	NATIVE_DECL float _GET_VEHICLE_WEAPON_RELOAD_TIME(Vehicle vehicle, int seat) { return invoke<float>(0xD0AD348FFD7A6868, vehicle, seat); }
	NATIVE_DECL BOOL _GET_AMMO_IN_VEHICLE_WEAPON_CLIP(Vehicle vehicle, int seat, int* ammo) { return invoke<BOOL>(0x2857938C5D407AFA, vehicle, seat, ammo); }
	NATIVE_DECL BOOL GET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int* ammo) { return invoke<BOOL>(0x2E1202248937775C, ped, weaponHash, ammo); }
	NATIVE_DECL BOOL _SET_AMMO_IN_VEHICLE_WEAPON_CLIP(Vehicle vehicle, int seat, int ammo) { return invoke<BOOL>(0x873906720EE842C3, vehicle, seat, ammo); }
	NATIVE_DECL BOOL SET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int ammo) { return invoke<BOOL>(0xDCD2A934D65CB497, ped, weaponHash, ammo); }
	NATIVE_DECL BOOL GET_MAX_AMMO(Ped ped, Hash weaponHash, int* ammo) { return invoke<BOOL>(0xDC16122C7A20C933, ped, weaponHash, ammo); }
	NATIVE_DECL BOOL GET_MAX_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int* ammo) { return invoke<BOOL>(0x585847C5E4E11709, ped, ammoTypeHash, ammo); }
	NATIVE_DECL void ADD_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int ammo) { invoke<Void>(0x2472622CE1F2D45F, ped, ammoTypeHash, ammo); }
	NATIVE_DECL void SET_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int ammo) { invoke<Void>(0x5FD1E1F011E76D7E, ped, ammoTypeHash, ammo); }
	NATIVE_DECL int GET_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash) { return invoke<int>(0x39D22031557946C1, ped, ammoTypeHash); }
	NATIVE_DECL void SET_PED_AMMO_TO_DROP(Ped ped, int p1) { invoke<Void>(0xA4EFEF9440A5B0EF, ped, p1); }
	NATIVE_DECL void SET_PICKUP_AMMO_AMOUNT_SCALER(float p0) { invoke<Void>(0xE620FD3512A04F18, p0); }
	NATIVE_DECL Hash GET_PED_AMMO_TYPE_FROM_WEAPON(Ped ped, Hash weaponHash) { return invoke<Hash>(0x7FEAD38B326B9F74, ped, weaponHash); }
	NATIVE_DECL Hash GET_PED_ORIGINAL_AMMO_TYPE_FROM_WEAPON(Ped ped, Hash weaponHash) { return invoke<Hash>(0xF489B44DD5AF4BD9, ped, weaponHash); }
	NATIVE_DECL BOOL GET_PED_LAST_WEAPON_IMPACT_COORD(Ped ped, Vector3* coords) { return invoke<BOOL>(0x6C4D0409BA1A2BC2, ped, coords); }
	NATIVE_DECL void SET_PED_GADGET(Ped ped, Hash gadgetHash, BOOL p2) { invoke<Void>(0xD0D7B1E680ED4A1A, ped, gadgetHash, p2); }
	NATIVE_DECL BOOL GET_IS_PED_GADGET_EQUIPPED(Ped ped, Hash gadgetHash) { return invoke<BOOL>(0xF731332072F5156C, ped, gadgetHash); }
	NATIVE_DECL Hash GET_SELECTED_PED_WEAPON(Ped ped) { return invoke<Hash>(0x0A6DB4965674D243, ped); }
	NATIVE_DECL void EXPLODE_PROJECTILES(Ped ped, Hash weaponHash, BOOL instant) { invoke<Void>(0xFC4BD125DE7611E4, ped, weaponHash, instant); }
	NATIVE_DECL void REMOVE_ALL_PROJECTILES_OF_TYPE(Hash weaponHash, BOOL explode) { invoke<Void>(0xFC52E0F37E446528, weaponHash, explode); }
	NATIVE_DECL float GET_LOCKON_DISTANCE_OF_CURRENT_PED_WEAPON(Ped ped) { return invoke<float>(0x840F03E9041E2C9C, ped); }
	NATIVE_DECL float GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(Ped ped) { return invoke<float>(0x814C9D19DFD69679, ped); }
	NATIVE_DECL BOOL HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(Ped driver, Vehicle vehicle, Hash weaponHash, Any p3) { return invoke<BOOL>(0x717C8481234E3B88, driver, vehicle, weaponHash, p3); }
	NATIVE_DECL void GIVE_WEAPON_COMPONENT_TO_PED(Ped ped, Hash weaponHash, Hash componentHash) { invoke<Void>(0xD966D51AA5B28BB9, ped, weaponHash, componentHash); }
	NATIVE_DECL void REMOVE_WEAPON_COMPONENT_FROM_PED(Ped ped, Hash weaponHash, Hash componentHash) { invoke<Void>(0x1E8BE90C74FB4C09, ped, weaponHash, componentHash); }
	NATIVE_DECL BOOL HAS_PED_GOT_WEAPON_COMPONENT(Ped ped, Hash weaponHash, Hash componentHash) { return invoke<BOOL>(0xC593212475FAE340, ped, weaponHash, componentHash); }
	NATIVE_DECL BOOL IS_PED_WEAPON_COMPONENT_ACTIVE(Ped ped, Hash weaponHash, Hash componentHash) { return invoke<BOOL>(0x0D78DE0572D3969E, ped, weaponHash, componentHash); }
	NATIVE_DECL BOOL REFILL_AMMO_INSTANTLY(Ped ped) { return invoke<BOOL>(0x8C0D57EA686FAD87, ped); }
	NATIVE_DECL BOOL MAKE_PED_RELOAD(Ped ped) { return invoke<BOOL>(0x20AE33F3AC9C0033, ped); }
	NATIVE_DECL BOOL _TRIGGER_VEHICLE_WEAPON_RELOAD(Vehicle vehicle, int seat, Ped ped) { return invoke<BOOL>(0x5B1513F27F279A44, vehicle, seat, ped); }
	NATIVE_DECL void REQUEST_WEAPON_ASSET(Hash weaponHash, int p1, int p2) { invoke<Void>(0x5443438F033E29C3, weaponHash, p1, p2); }
	NATIVE_DECL BOOL HAS_WEAPON_ASSET_LOADED(Hash weaponHash) { return invoke<BOOL>(0x36E353271F0E90EE, weaponHash); }
	NATIVE_DECL void REMOVE_WEAPON_ASSET(Hash weaponHash) { invoke<Void>(0xAA08EF13F341C8FC, weaponHash); }
	NATIVE_DECL BOOL HAS_PED_GOT_WEAPON_MANAGER(Ped ped) { return invoke<BOOL>(0xDB7CCCD153740D8E, ped); }
	NATIVE_DECL Object CREATE_WEAPON_OBJECT(Hash weaponHash, int ammoCount, float x, float y, float z, BOOL showWorldModel, float scale, Any p7, Any p8, Any p9) { return invoke<Object>(0x9541D3CF0D398F36, weaponHash, ammoCount, x, y, z, showWorldModel, scale, p7, p8, p9); }
	NATIVE_DECL void GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(Object weaponObject, Hash componentHash) { invoke<Void>(0x33E179436C0B31DB, weaponObject, componentHash); }
	NATIVE_DECL void REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(Object object, Hash componentHash) { invoke<Void>(0xF7D82B0D66777611, object, componentHash); }
	NATIVE_DECL BOOL HAS_WEAPON_GOT_WEAPON_COMPONENT(Object weapon, Hash componentHash) { return invoke<BOOL>(0x76A18844E743BF91, weapon, componentHash); }
	NATIVE_DECL void GIVE_WEAPON_OBJECT_TO_PED(Object weaponObject, Ped ped) { invoke<Void>(0xB1FA61371AF7C4B7, weaponObject, ped); }
	NATIVE_DECL BOOL DOES_WEAPON_TAKE_WEAPON_COMPONENT(Hash weaponHash, Hash componentHash) { return invoke<BOOL>(0x5CEE3DF569CECAB0, weaponHash, componentHash); }
	NATIVE_DECL Object GET_WEAPON_OBJECT_FROM_PED(Ped ped, BOOL p1) { return invoke<Object>(0xCAE1DC9A0E22A16D, ped, p1); }
	NATIVE_DECL void GIVE_LOADOUT_TO_PED(Ped ped, Hash loadoutHash) { invoke<Void>(0x68F8BE6AF5CDF8A6, ped, loadoutHash); }
	NATIVE_DECL void SET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash, int tintIndex) { invoke<Void>(0x50969B9B89ED5738, ped, weaponHash, tintIndex); }
	NATIVE_DECL int GET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash) { return invoke<int>(0x2B9EEDC07BD06B9F, ped, weaponHash); }
	NATIVE_DECL void SET_WEAPON_OBJECT_TINT_INDEX(Object weapon, int tintIndex) { invoke<Void>(0xF827589017D4E4A9, weapon, tintIndex); }
	NATIVE_DECL int GET_WEAPON_OBJECT_TINT_INDEX(Object weapon) { return invoke<int>(0xCD183314F7CD2E57, weapon); }
	NATIVE_DECL int GET_WEAPON_TINT_COUNT(Hash weaponHash) { return invoke<int>(0x5DCF6C5CAB2E9BF7, weaponHash); }
	NATIVE_DECL void SET_PED_WEAPON_COMPONENT_TINT_INDEX(Ped ped, Hash weaponHash, Hash camoComponentHash, int colorIndex) { invoke<Void>(0x9FE5633880ECD8ED, ped, weaponHash, camoComponentHash, colorIndex); }
	NATIVE_DECL int GET_PED_WEAPON_COMPONENT_TINT_INDEX(Ped ped, Hash weaponHash, Hash camoComponentHash) { return invoke<int>(0xF0A60040BE558F2D, ped, weaponHash, camoComponentHash); }
	NATIVE_DECL void SET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(Object weaponObject, Hash camoComponentHash, int colorIndex) { invoke<Void>(0x5DA825A85D0EA6E6, weaponObject, camoComponentHash, colorIndex); }
	NATIVE_DECL int GET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(Object weaponObject, Hash camoComponentHash) { return invoke<int>(0xB3EA4FEABF41464B, weaponObject, camoComponentHash); }
	NATIVE_DECL int GET_PED_WEAPON_CAMO_INDEX(Ped ped, Hash weaponHash) { return invoke<int>(0xA2C9AC24B4061285, ped, weaponHash); }
	NATIVE_DECL void SET_WEAPON_OBJECT_CAMO_INDEX(Object weaponObject, int p1) { invoke<Void>(0x977CA98939E82E4B, weaponObject, p1); }
	NATIVE_DECL BOOL GET_WEAPON_HUD_STATS(Hash weaponHash, Any* outData) { return invoke<BOOL>(0xD92C739EE34C9EBA, weaponHash, outData); }
	NATIVE_DECL BOOL GET_WEAPON_COMPONENT_HUD_STATS(Hash componentHash, Any* outData) { return invoke<BOOL>(0xB3CAF387AE12E9F8, componentHash, outData); }
	NATIVE_DECL float GET_WEAPON_DAMAGE(Hash weaponHash, Hash componentHash) { return invoke<float>(0x3133B907D8B32053, weaponHash, componentHash); }
	NATIVE_DECL int GET_WEAPON_CLIP_SIZE(Hash weaponHash) { return invoke<int>(0x583BE370B1EC6EB4, weaponHash); }
	NATIVE_DECL float GET_WEAPON_TIME_BETWEEN_SHOTS(Hash weaponHash) { return invoke<float>(0x065D2AACAD8CF7A4, weaponHash); }
	NATIVE_DECL void SET_PED_CHANCE_OF_FIRING_BLANKS(Ped ped, float xBias, float yBias) { invoke<Void>(0x8378627201D5497D, ped, xBias, yBias); }
	NATIVE_DECL Object SET_PED_SHOOT_ORDNANCE_WEAPON(Ped ped, float p1) { return invoke<Object>(0xB4C8D77C80C0421E, ped, p1); }
	NATIVE_DECL void REQUEST_WEAPON_HIGH_DETAIL_MODEL(Entity weaponObject) { invoke<Void>(0x48164DBB970AC3F0, weaponObject); }
	NATIVE_DECL void _SET_WEAPON_PED_DAMAGE_MODIFIER(Hash weapon, float damageModifier) { invoke<Void>(0x1091922715B68DF0, weapon, damageModifier); }
	NATIVE_DECL void SET_WEAPON_DAMAGE_MODIFIER(Hash weaponHash, float damageMultiplier) { invoke<Void>(0x4757F00BC6323CFE, weaponHash, damageMultiplier); }
	NATIVE_DECL void SET_WEAPON_AOE_MODIFIER(Hash weaponHash, float multiplier) { invoke<Void>(0x4AE5AC8B852D642C, weaponHash, multiplier); }
	NATIVE_DECL void SET_WEAPON_EFFECT_DURATION_MODIFIER(Hash p0, float p1) { invoke<Void>(0xE6D2CEDD370FF98E, p0, p1); }
	NATIVE_DECL BOOL IS_PED_CURRENT_WEAPON_SILENCED(Ped ped) { return invoke<BOOL>(0x65F0C5AE05943EC7, ped); }
	NATIVE_DECL BOOL IS_FLASH_LIGHT_ON(Ped ped) { return invoke<BOOL>(0x4B7620C47217126C, ped); }
	NATIVE_DECL BOOL SET_FLASH_LIGHT_FADE_DISTANCE(float distance) { return invoke<BOOL>(0xCEA66DAD478CD39B, distance); }
	NATIVE_DECL void SET_FLASH_LIGHT_ACTIVE_HISTORY(Ped ped, BOOL toggle) { invoke<Void>(0x988DB6FE9B3AC000, ped, toggle); }
	NATIVE_DECL void SET_WEAPON_ANIMATION_OVERRIDE(Ped ped, Hash animStyle) { invoke<Void>(0x1055AC3A667F09D9, ped, animStyle); }
	NATIVE_DECL int GET_WEAPON_DAMAGE_TYPE(Hash weaponHash) { return invoke<int>(0x3BE0BB12D25FB305, weaponHash); }
	NATIVE_DECL void SET_EQIPPED_WEAPON_START_SPINNING_AT_FULL_SPEED(Ped ped) { invoke<Void>(0xE4DCEC7FD5B739A5, ped); }
	NATIVE_DECL BOOL CAN_USE_WEAPON_ON_PARACHUTE(Hash weaponHash) { return invoke<BOOL>(0xBC7BE5ABC0879F74, weaponHash); }
	NATIVE_DECL int CREATE_AIR_DEFENCE_SPHERE(float x, float y, float z, float radius, float p4, float p5, float p6, Hash weaponHash) { return invoke<int>(0x91EF34584710BE99, x, y, z, radius, p4, p5, p6, weaponHash); }
	NATIVE_DECL int CREATE_AIR_DEFENCE_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float radius, Hash weaponHash) { return invoke<int>(0x9DA58CDBF6BDBC08, p0, p1, p2, p3, p4, p5, p6, p7, p8, radius, weaponHash); }
	NATIVE_DECL BOOL REMOVE_AIR_DEFENCE_SPHERE(int zoneId) { return invoke<BOOL>(0x0ABF535877897560, zoneId); }
	NATIVE_DECL void REMOVE_ALL_AIR_DEFENCE_SPHERES() { invoke<Void>(0x1E45B34ADEBEE48E); }
	NATIVE_DECL void SET_PLAYER_TARGETTABLE_FOR_AIR_DEFENCE_SPHERE(Player player, int zoneId, BOOL enable) { invoke<Void>(0xECDC202B25E5CF48, player, zoneId, enable); }
	NATIVE_DECL BOOL IS_AIR_DEFENCE_SPHERE_IN_AREA(float x, float y, float z, float radius, int* outZoneId) { return invoke<BOOL>(0xDAB963831DBFD3F4, x, y, z, radius, outZoneId); }
	NATIVE_DECL void FIRE_AIR_DEFENCE_SPHERE_WEAPON_AT_POSITION(int zoneId, float x, float y, float z) { invoke<Void>(0x44F1012B69313374, zoneId, x, y, z); }
	NATIVE_DECL BOOL DOES_AIR_DEFENCE_SPHERE_EXIST(int zoneId) { return invoke<BOOL>(0xCD79A550999D7D4F, zoneId); }
	NATIVE_DECL void SET_CAN_PED_SELECT_INVENTORY_WEAPON(Ped ped, Hash weaponHash, BOOL toggle) { invoke<Void>(0xB4771B9AAF4E68E4, ped, weaponHash, toggle); }
	NATIVE_DECL void SET_CAN_PED_SELECT_ALL_WEAPONS(Ped ped, BOOL toggle) { invoke<Void>(0xEFF296097FF1E509, ped, toggle); }
}

namespace ZONE
{
	NATIVE_DECL int GET_ZONE_AT_COORDS(float x, float y, float z) { return invoke<int>(0x27040C25DE6CB2F4, x, y, z); }
	NATIVE_DECL int GET_ZONE_FROM_NAME_ID(const char* zoneName) { return invoke<int>(0x98CD1D2934B76CC1, zoneName); }
	NATIVE_DECL int GET_ZONE_POPSCHEDULE(int zoneId) { return invoke<int>(0x4334BC40AA0CB4BB, zoneId); }
	NATIVE_DECL const char* GET_NAME_OF_ZONE(float x, float y, float z) { return invoke<const char*>(0xCD90657D4C30E1CA, x, y, z); }
	NATIVE_DECL void SET_ZONE_ENABLED(int zoneId, BOOL toggle) { invoke<Void>(0xBA5ECEEA120E5611, zoneId, toggle); }
	NATIVE_DECL int GET_ZONE_SCUMMINESS(int zoneId) { return invoke<int>(0x5F7B268D15BA0739, zoneId); }
	NATIVE_DECL void OVERRIDE_POPSCHEDULE_VEHICLE_MODEL(int scheduleId, Hash vehicleHash) { invoke<Void>(0x5F7D596BAC2E7777, scheduleId, vehicleHash); }
	NATIVE_DECL void CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL(int scheduleId) { invoke<Void>(0x5C0DE367AA0D911C, scheduleId); }
	NATIVE_DECL Hash GET_HASH_OF_MAP_AREA_AT_COORDS(float x, float y, float z) { return invoke<Hash>(0x7EE64D51E8498728, x, y, z); }
}

// Temporary migration shim: forwards old namespace/name/signatures that
// changed in this update to their new equivalents, so every existing call
// site keeps compiling and behaving identically until each is migrated to
// call the new names directly. See natives_compat_shim.h.
#include "natives_compat_shim.h"

