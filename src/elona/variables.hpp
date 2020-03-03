#pragma once

#include "elona.hpp"
#include "optional.hpp"
#include "position.hpp"
#include "random.hpp"
#include "talk.hpp"


#ifdef ELONA_DEFINE_GLOBAL_INSTANCE
#define ELONA_EXTERN(declaration) declaration
#else
#define ELONA_EXTERN(declaration) extern declaration
#endif

namespace elona
{

struct Item;
struct Character;



ELONA_EXTERN(elona_vector1<int> ap);
ELONA_EXTERN(int nooracle);

// casino.cpp / casino_card.cpp
ELONA_EXTERN(std::string atxbg);
ELONA_EXTERN(std::string atxbgbk);
ELONA_EXTERN(elona_vector1<std::string> atxinfon);
ELONA_EXTERN(elona_vector1<int> fsetwear);
ELONA_EXTERN(elona_vector1<int> fsetitem);
ELONA_EXTERN(int txtadvscreenupdate);
ELONA_EXTERN(elona_vector2<int> matref);
ELONA_EXTERN(elona_vector1<std::string> matname);

// fov.cpp
ELONA_EXTERN(elona_vector2<int> route);
ELONA_EXTERN(int maxroute);

// building.cpp
ELONA_EXTERN(int tlocinitx);
ELONA_EXTERN(int tlocinity);
ELONA_EXTERN(elona_vector1<int> isethirerole);
ELONA_EXTERN(elona_vector1<int> isethire);
ELONA_EXTERN(elona_vector1<int> income);
ELONA_EXTERN(elona_vector2<std::string> rankn);
ELONA_EXTERN(int renewmulti);
ELONA_EXTERN(elona_vector2<int> bdref);

// ui.cpp
ELONA_EXTERN(int inf_clocky);
ELONA_EXTERN(int inf_msgh);
ELONA_EXTERN(int inf_ver);

// ui.cpp/menu.cpp
ELONA_EXTERN(int autoturn);
ELONA_EXTERN(int firstautoturn);
ELONA_EXTERN(int racount);
ELONA_EXTERN(elona_vector1<std::string> matdesc);
ELONA_EXTERN(std::string nquestdate);
ELONA_EXTERN(int lv);
ELONA_EXTERN(elona_vector3<int> pochart);
ELONA_EXTERN(elona_vector2<int> podata);
ELONA_EXTERN(int refreshmode);
ELONA_EXTERN(bool quest_teleport);
ELONA_EXTERN(int gspdorg);
ELONA_EXTERN(int gspd);
ELONA_EXTERN(int scposval);
ELONA_EXTERN(int weatherbk);


// crafting.cpp / blending.cpp
ELONA_EXTERN(elona_vector1<int> rpsourcelist);
ELONA_EXTERN(int prodtype);
ELONA_EXTERN(elona_vector2<int> matspot);

// quest.cpp
ELONA_EXTERN(elona_vector1<int> fsetcollect);
ELONA_EXTERN(elona_vector1<int> asettown);
ELONA_EXTERN(elona_vector1<int> fsetdeliver);
ELONA_EXTERN(elona_vector1<int> fsetsupply);
ELONA_EXTERN(elona_vector1<int> fsetmagic);
ELONA_EXTERN(elona_vector1<int> fsetarmor);
ELONA_EXTERN(elona_vector1<int> fsetweapon);
ELONA_EXTERN(elona_vector1<int> fsetrewardsupply);

// map.cpp/mapgen.cpp
ELONA_EXTERN(int tile_trap);
ELONA_EXTERN(int tile_doorclosed4);
ELONA_EXTERN(int tile_dooropen);
ELONA_EXTERN(int tile_downlocked);
ELONA_EXTERN(int tile_re);
ELONA_EXTERN(int tile_plant);
ELONA_EXTERN(elona_vector1<int> isetgod);
ELONA_EXTERN(elona_vector1<int> isetcrop);
ELONA_EXTERN(int rdtry);

// food.cpp
ELONA_EXTERN(int enc);

// talk.cpp
ELONA_EXTERN(elona_vector2<std::string> actor);

// mef.cpp
ELONA_EXTERN(elona_vector2<int> mef);
ELONA_EXTERN(elona_vector2<int> mefsubref);

// map_cell.cpp
ELONA_EXTERN(int cellchara);
ELONA_EXTERN(int cellfeat);

// enchantment.cpp
ELONA_EXTERN(elona_vector2<int> encammoref);

// item.hpp/itemgen.hpp
ELONA_EXTERN(elona_vector1<int> isetbook);
ELONA_EXTERN(elona_vector1<int> moneybox);

// ai.cpp
ELONA_EXTERN(elona_vector1<int> isetthrowpotionminor);
ELONA_EXTERN(elona_vector1<int> isetthrowpotionmajor);
ELONA_EXTERN(elona_vector1<int> isetthrowpotiongreater);

// command.cpp
ELONA_EXTERN(int usermapid);
ELONA_EXTERN(int refx);
ELONA_EXTERN(int refy);
ELONA_EXTERN(int movx);
ELONA_EXTERN(int movy);
ELONA_EXTERN(int ri);

// dmgheal.cpp
ELONA_EXTERN(std::string ndeathcause);
ELONA_EXTERN(int catitem);
ELONA_EXTERN(int rollanatomy);
ELONA_EXTERN(int rtdmg);

// turn_sequence.cpp
ELONA_EXTERN(int tgloc);
ELONA_EXTERN(int dbg_skipevent);
ELONA_EXTERN(int findlocmode);
ELONA_EXTERN(int dirsub);
ELONA_EXTERN(int mousex);
ELONA_EXTERN(int mousey);

// initialize_map.cpp
ELONA_EXTERN(int noaggrorefresh);

ELONA_EXTERN(elona_vector1<int> arenaop);
ELONA_EXTERN(elona_vector1<int> commark);
ELONA_EXTERN(elona_vector1<int> cyclemax);
ELONA_EXTERN(elona_vector1<int> deck);
ELONA_EXTERN(elona_vector1<int> deliver);
ELONA_EXTERN(elona_vector1<int> dir);
ELONA_EXTERN(elona_vector1<int> drop);
ELONA_EXTERN(elona_vector1<int> dx);
ELONA_EXTERN(elona_vector1<int> feat);
ELONA_EXTERN(elona_vector1<int> fishanime);
ELONA_EXTERN(elona_vector1<int> fixeditemenc);
ELONA_EXTERN(elona_vector1<int> floorstack);
ELONA_EXTERN(elona_vector1<int> followerexist);
ELONA_EXTERN(elona_vector1<int> followerin);
ELONA_EXTERN(elona_vector1<int> fsetchest);
ELONA_EXTERN(elona_vector1<int> gdata);
ELONA_EXTERN(elona_vector1<int> genetemp);
ELONA_EXTERN(elona_vector1<int> giftvalue);
ELONA_EXTERN(elona_vector1<int> i);
ELONA_EXTERN(elona_vector1<int> ilight);
ELONA_EXTERN(elona_vector1<int> invcontainer);
ELONA_EXTERN(elona_vector1<int> invctrl);
ELONA_EXTERN(elona_vector1<int> invicon);
ELONA_EXTERN(elona_vector1<int> invmark);
ELONA_EXTERN(elona_vector1<int> iorgweight);
ELONA_EXTERN(elona_vector1<int> ipicref);
ELONA_EXTERN(elona_vector1<int> irandomname);
ELONA_EXTERN(elona_vector1<int> isetfruit);
ELONA_EXTERN(elona_vector1<int> mainskill);
ELONA_EXTERN(elona_vector1<int> mat);
ELONA_EXTERN(elona_vector1<int> mdata);
ELONA_EXTERN(elona_vector1<int> mdatatmp);
ELONA_EXTERN(elona_vector1<int> p);
ELONA_EXTERN(elona_vector1<int> recipememory);
ELONA_EXTERN(elona_vector1<int> reph);
ELONA_EXTERN(elona_vector1<int> repw);
ELONA_EXTERN(elona_vector1<int> rowactre);
ELONA_EXTERN(elona_vector1<int> rtval);
ELONA_EXTERN(elona_vector1<int> spact);
ELONA_EXTERN(elona_vector1<int> spell);
ELONA_EXTERN(elona_vector1<int> sx);
ELONA_EXTERN(elona_vector1<int> sy);
ELONA_EXTERN(elona_vector1<int> tc);
ELONA_EXTERN(elona_vector1<int> tile);
ELONA_EXTERN(elona_vector1<int> tile_default);
ELONA_EXTERN(elona_vector1<int> tile_fog);
ELONA_EXTERN(elona_vector1<int> tile_room);
ELONA_EXTERN(elona_vector1<int> tile_tunnel);
ELONA_EXTERN(elona_vector1<int> tile_wall);
ELONA_EXTERN(elona_vector1<int> trait);
ELONA_EXTERN(elona_vector1<int> traitref);
ELONA_EXTERN(elona_vector1<int> trate);
ELONA_EXTERN(elona_vector1<int> windowshadow);
ELONA_EXTERN(elona_vector1<int> x);
ELONA_EXTERN(elona_vector1<int> y);
ELONA_EXTERN(elona_vector1<std::string> ammoname);
ELONA_EXTERN(std::vector<std::string> artifactlocation);
ELONA_EXTERN(elona_vector1<std::string> booktitle);
ELONA_EXTERN(elona_vector1<std::string> buff);
ELONA_EXTERN(elona_vector1<std::string> buffboard);
ELONA_EXTERN(elona_vector1<std::string> description);
ELONA_EXTERN(elona_vector1<std::string> egominorn);
ELONA_EXTERN(elona_vector1<std::string> egoname);
ELONA_EXTERN(elona_vector1<std::string> filtern);
ELONA_EXTERN(elona_vector1<std::string> fltnrace);
ELONA_EXTERN(elona_vector1<std::string> ialphanameref);
ELONA_EXTERN(elona_vector1<std::string> iknownnameref);
ELONA_EXTERN(elona_vector1<std::string> inputlog);
ELONA_EXTERN(elona_vector1<std::string> invkey);
ELONA_EXTERN(elona_vector1<std::string> ioriginalnameref2);
ELONA_EXTERN(elona_vector1<std::string> ioriginalnameref);
ELONA_EXTERN(elona_vector1<std::string> key);
ELONA_EXTERN(std::string key_identify);
ELONA_EXTERN(std::string key_pageup);
ELONA_EXTERN(std::string key_pagedown);
ELONA_EXTERN(std::string key_cancel);
ELONA_EXTERN(std::string key_help);
ELONA_EXTERN(std::string key_msglog);
ELONA_EXTERN(std::string key_enter);
ELONA_EXTERN(std::string key_save);
ELONA_EXTERN(std::string key_skill);
ELONA_EXTERN(std::string key_close);
ELONA_EXTERN(std::string key_cast);
ELONA_EXTERN(std::string key_drink);
ELONA_EXTERN(std::string key_read);
ELONA_EXTERN(std::string key_zap);
ELONA_EXTERN(std::string key_fire);
ELONA_EXTERN(std::string key_search);
ELONA_EXTERN(std::string key_target);
ELONA_EXTERN(std::string key_dig);
ELONA_EXTERN(std::string key_wait);
ELONA_EXTERN(std::string key_inventory);
ELONA_EXTERN(std::string key_drop);
ELONA_EXTERN(std::string key_get);
ELONA_EXTERN(std::string key_charainfo);
ELONA_EXTERN(std::string key_eat);
ELONA_EXTERN(std::string key_wear);
ELONA_EXTERN(std::string key_godown);
ELONA_EXTERN(std::string key_goup);
ELONA_EXTERN(std::string key_interact);
ELONA_EXTERN(std::string key_use);
ELONA_EXTERN(std::string key_bash);
ELONA_EXTERN(std::string key_open);
ELONA_EXTERN(std::string key_dip);
ELONA_EXTERN(std::string key_pray);
ELONA_EXTERN(std::string key_offer);
ELONA_EXTERN(std::string key_journal);
ELONA_EXTERN(std::string key_material);
ELONA_EXTERN(std::string key_trait);
ELONA_EXTERN(std::string key_give);
ELONA_EXTERN(std::string key_prev);
ELONA_EXTERN(std::string key_next);
ELONA_EXTERN(std::string key_throw);
ELONA_EXTERN(std::string key_mode);
ELONA_EXTERN(std::string key_ammo);
ELONA_EXTERN(std::string key_mode2);
ELONA_EXTERN(elona_vector1<std::string> key_list);
ELONA_EXTERN(elona_vector1<std::string> key_select);
ELONA_EXTERN(elona_vector1<std::string> keylog);
ELONA_EXTERN(elona_vector1<std::string> mdatan);
ELONA_EXTERN(elona_vector1<std::string> newsbuff);
ELONA_EXTERN(elona_vector1<std::string> playerheader);
ELONA_EXTERN(elona_vector1<std::string> q);
ELONA_EXTERN(elona_vector1<std::string> qname);
ELONA_EXTERN(elona_vector1<std::string> s1);
ELONA_EXTERN(elona_vector1<std::string> s);
ELONA_EXTERN(elona_vector1<std::string> traitrefn2);
ELONA_EXTERN(elona_vector1<std::string> traitrefn);
ELONA_EXTERN(elona_vector2<int> adata);
ELONA_EXTERN(elona_vector2<int> breathlist);
ELONA_EXTERN(elona_vector2<int> c_col);
ELONA_EXTERN(elona_vector2<int> card);
ELONA_EXTERN(elona_vector2<int> cmapdata);
ELONA_EXTERN(elona_vector2<int> cycle);
ELONA_EXTERN(elona_vector2<int> dblist);
ELONA_EXTERN(elona_vector2<int> dirxy);
ELONA_EXTERN(elona_vector2<int> encprocref);
ELONA_EXTERN(elona_vector1<int> eqweapon1);
ELONA_EXTERN(elona_vector1<int> eqrange);
ELONA_EXTERN(elona_vector1<int> eqammo);
ELONA_EXTERN(elona_vector1<int> eqring1);
ELONA_EXTERN(elona_vector2<int> itemmemory);
ELONA_EXTERN(elona_vector2<int> list);
ELONA_EXTERN(elona_vector2<int> mapsync);
ELONA_EXTERN(elona_vector2<int> npcmemory);
ELONA_EXTERN(elona_vector2<int> pcc);
ELONA_EXTERN(elona_vector2<int> picfood);
ELONA_EXTERN(elona_vector2<int> qdata);
ELONA_EXTERN(elona_vector2<int> slight);
ELONA_EXTERN(elona_vector2<std::string> _melee);
ELONA_EXTERN(elona_vector2<std::string> cdatan);
ELONA_EXTERN(elona_vector2<std::string> listn);
ELONA_EXTERN(elona_vector2<std::string> mapnamerd);
ELONA_EXTERN(elona_vector3<int> bddata);
ELONA_EXTERN(elona_vector3<int> efmap);
ELONA_EXTERN(elona_vector3<int> map);
ELONA_EXTERN(int ammo);
ELONA_EXTERN(int ammoproc);
ELONA_EXTERN(int ammoprocbk);
ELONA_EXTERN(int animode);
ELONA_EXTERN(int area);
ELONA_EXTERN(int attacknum);
ELONA_EXTERN(int attackrange);
ELONA_EXTERN(int attackskill);
ELONA_EXTERN(int atxspot);
ELONA_EXTERN(int body);
ELONA_EXTERN(int bonus);
ELONA_EXTERN(int camera);
ELONA_EXTERN(int cc);
ELONA_EXTERN(int ccbk);
ELONA_EXTERN(int cellaccess);
ELONA_EXTERN(int chatesc);
ELONA_EXTERN(int chatteleport);
ELONA_EXTERN(int ci);
ELONA_EXTERN(int cidip);
ELONA_EXTERN(int client);
ELONA_EXTERN(int cm);
ELONA_EXTERN(int cmbg);
ELONA_EXTERN(int cmsex);
ELONA_EXTERN(int cmshade);
ELONA_EXTERN(int creaturepack);
ELONA_EXTERN(int critical);
ELONA_EXTERN(int crop);
ELONA_EXTERN(int cs);
ELONA_EXTERN(int cs_bk2);
ELONA_EXTERN(int cs_bk);
ELONA_EXTERN(int cspecialeq);
ELONA_EXTERN(int cw);
ELONA_EXTERN(int cxinit);
ELONA_EXTERN(int cyinit);
ELONA_EXTERN(int damage);
ELONA_EXTERN(int dbg_revealmap);
ELONA_EXTERN(int dbid);
ELONA_EXTERN(int dice1);
ELONA_EXTERN(int dice2);
ELONA_EXTERN(int distance);
ELONA_EXTERN(int dmg);
ELONA_EXTERN(int dmgfix);
ELONA_EXTERN(double dmgmulti);
ELONA_EXTERN(int dy);
ELONA_EXTERN(int efcancel);
ELONA_EXTERN(int efid);
ELONA_EXTERN(int efp);
ELONA_EXTERN(int efsource);
ELONA_EXTERN(CurseState efstatus);
ELONA_EXTERN(int egolv);
ELONA_EXTERN(int ele);
ELONA_EXTERN(int elep);
ELONA_EXTERN(int en);
ELONA_EXTERN(int encounter);
ELONA_EXTERN(int encounterlv);
ELONA_EXTERN(int encounterref);
ELONA_EXTERN(int enemyteam);
ELONA_EXTERN(int eqmultiweapon);
ELONA_EXTERN(int eqtwohand);
ELONA_EXTERN(int equip);
ELONA_EXTERN(int exp);
ELONA_EXTERN(int f2);
ELONA_EXTERN(int f);
ELONA_EXTERN(int filtermax);
ELONA_EXTERN(int firstturn);
ELONA_EXTERN(int fish);
ELONA_EXTERN(int fishx);
ELONA_EXTERN(int fishy);
ELONA_EXTERN(Quality fixlv);
ELONA_EXTERN(int fixmaterial);
ELONA_EXTERN(int fixtransfermap);
ELONA_EXTERN(int fltselect);
ELONA_EXTERN(int flttypemajor);
ELONA_EXTERN(int flttypeminor);
ELONA_EXTERN(int foot);
ELONA_EXTERN(int grown);
ELONA_EXTERN(int hire);
ELONA_EXTERN(int homemapmode);
ELONA_EXTERN(int ichargelevel);
ELONA_EXTERN(IdentifyState idtresult);
ELONA_EXTERN(int in);
ELONA_EXTERN(int inf_maxlog);
ELONA_EXTERN(size_t inf_maxmsglen);
ELONA_EXTERN(int inf_msgspace);
ELONA_EXTERN(int inf_msgx);
ELONA_EXTERN(int inf_msgy);
ELONA_EXTERN(int inf_screenh);
ELONA_EXTERN(int inf_screenw);
ELONA_EXTERN(int inf_screenx);
ELONA_EXTERN(int inf_screeny);
ELONA_EXTERN(int inf_tiles);
ELONA_EXTERN(int inf_verh);
ELONA_EXTERN(int inf_very);
ELONA_EXTERN(int initeco);
ELONA_EXTERN(int initlv);
ELONA_EXTERN(int invally);
ELONA_EXTERN(int invfile);
ELONA_EXTERN(int invhead);
ELONA_EXTERN(int invrange);
ELONA_EXTERN(int invsc);
ELONA_EXTERN(int invsubroutine);
ELONA_EXTERN(int jp);
ELONA_EXTERN(bool key_escape);
ELONA_EXTERN(int keybd_attacking);
ELONA_EXTERN(int keybd_wait);
ELONA_EXTERN(int keyrange);
ELONA_EXTERN(int keywait);
ELONA_EXTERN(int lastctrl);
ELONA_EXTERN(int len);
ELONA_EXTERN(int levelexitby);
ELONA_EXTERN(int listmax);
ELONA_EXTERN(int lomiaseaster);
ELONA_EXTERN(int mapstartx);
ELONA_EXTERN(int mapstarty);
ELONA_EXTERN(int mapsubroutine);
ELONA_EXTERN(int mapupdate);
ELONA_EXTERN(int marry);
ELONA_EXTERN(int maxbreath);
ELONA_EXTERN(int maxitemid);
ELONA_EXTERN(int menucycle);
ELONA_EXTERN(int minlevel);
ELONA_EXTERN(Mode mode);
ELONA_EXTERN(int msync);
ELONA_EXTERN(int mtilefilecur);
ELONA_EXTERN(int musicloop);
ELONA_EXTERN(int nostack);
ELONA_EXTERN(int novoidlv);
ELONA_EXTERN(int nowindowanime);
ELONA_EXTERN(int objfix);
ELONA_EXTERN(int objlv);
ELONA_EXTERN(int obvious);
ELONA_EXTERN(int oc);
ELONA_EXTERN(int orgdmg);
ELONA_EXTERN(int page);
ELONA_EXTERN(int page_bk);
ELONA_EXTERN(int pagemax);
ELONA_EXTERN(int pagesize);
ELONA_EXTERN(int pcattacker);
ELONA_EXTERN(int petarenawin);
ELONA_EXTERN(int potionspill);
ELONA_EXTERN(int potionthrow);
ELONA_EXTERN(int promptx);
ELONA_EXTERN(int prompty);
ELONA_EXTERN(int prot);
ELONA_EXTERN(int protdice1);
ELONA_EXTERN(int protdice2);
ELONA_EXTERN(int quickpage);
ELONA_EXTERN(int r2);
ELONA_EXTERN(int r);
ELONA_EXTERN(int range_);
ELONA_EXTERN(int rapidmagic);
ELONA_EXTERN(int rc);
ELONA_EXTERN(int reftype);
ELONA_EXTERN(int reftypeminor);
ELONA_EXTERN(int returnfromidentify);
ELONA_EXTERN(int rq);
ELONA_EXTERN(int running);
ELONA_EXTERN(int sc);
ELONA_EXTERN(int scene_cut);
ELONA_EXTERN(int sceneid);
ELONA_EXTERN(int scenemode);
ELONA_EXTERN(int screenupdate);
ELONA_EXTERN(int scroll);
ELONA_EXTERN(int scrollanime);
ELONA_EXTERN(int scrollp);
ELONA_EXTERN(int scrturn);
ELONA_EXTERN(int scx);
ELONA_EXTERN(int scxbk);
ELONA_EXTERN(int scy);
ELONA_EXTERN(int scybk);
ELONA_EXTERN(int shoptrade);
ELONA_EXTERN(int size);
ELONA_EXTERN(int sizefix);
ELONA_EXTERN(int sound);
ELONA_EXTERN(int strsize);
ELONA_EXTERN(int supply);
ELONA_EXTERN(int sxfix);
ELONA_EXTERN(int syfix);
ELONA_EXTERN(int t);
ELONA_EXTERN(int tail);
ELONA_EXTERN(int tcbk);
ELONA_EXTERN(int tg);
ELONA_EXTERN(int ti);
ELONA_EXTERN(int tile_doorclosed);
ELONA_EXTERN(int tile_downstairs);
ELONA_EXTERN(int tile_hidden);
ELONA_EXTERN(int tile_upstairs);
ELONA_EXTERN(int time_begin);
ELONA_EXTERN(int time_warn);
ELONA_EXTERN(int tlocx);
ELONA_EXTERN(int tlocy);
ELONA_EXTERN(int tx);
ELONA_EXTERN(int txt3rd);
ELONA_EXTERN(int ty);
ELONA_EXTERN(int vfix);
ELONA_EXTERN(int voidlv);
ELONA_EXTERN(int windowh);
ELONA_EXTERN(int windoww);
ELONA_EXTERN(int wh);
ELONA_EXTERN(int ww);
ELONA_EXTERN(int wx);
ELONA_EXTERN(int wy);
ELONA_EXTERN(int x1);
ELONA_EXTERN(int x2);
ELONA_EXTERN(int y1);
ELONA_EXTERN(int y2);
ELONA_EXTERN(std::string cmaka);
ELONA_EXTERN(std::string defload);
ELONA_EXTERN(std::string fmapfile);
ELONA_EXTERN(std::string geneuse);
ELONA_EXTERN(std::string mid);
ELONA_EXTERN(std::string playerid);
ELONA_EXTERN(std::string s2);
ELONA_EXTERN(std::string strhint1);
ELONA_EXTERN(std::string strhint2);
ELONA_EXTERN(std::string strhint3);
ELONA_EXTERN(std::string strhint3b);
ELONA_EXTERN(std::string strhint4);
ELONA_EXTERN(std::string strhint5);
ELONA_EXTERN(std::string strhint5b);
ELONA_EXTERN(std::string strhint7);

ELONA_EXTERN(optional<int> chatval_unique_chara_id);

//// Game formulae
int calcincome(int = 0);
int calcmagiccontrol(int = 0, int = 0);
int calcstartcard(int = 0);
int randskill();

//// Init
void initialize_pc_character();
int initialize_world_map();
void initialize_rankn();
void initialize_post_data();
void initialize_building_data();
void initialize_nefia_names();
void initialize_picfood();
void initialize_cloud_data();
void initialize_item_material_data();
void initialize_set_of_random_generation();
void initialize_economy();
void clear_existing_quest_list();


//// Character querying
int relationbetween(int, int);


//// Character manipulation
void refresh_burden_state();
int new_ally_joins();
void go_hostile();
void get_pregnant();
void wet(int = 0, int = 0);

// Character revival
void revive_character();
void do_chara_revival();
void chara_set_revived_status();
void chara_clear_status_effects_b();
void chara_clear_status_effects();
void revive_player();

// Trait
void clear_trait_data();
void gain_race_feat();


//// Items

// Item status querying
bool cargocheck(const Item& item);

// Item manipulation
int convertartifact(int = 0, int = 0);
int discsetmc();
void set_item_info();

// Item generation
int random_material(int = 0, int = 0);
int randattb();

// Equipment
int equip_item(int);
void unequip_item(int);

// Inventory
std::pair<int, int> inv_getheader(int);


// Math utility functions
int direction(int = 0, int = 0, int = 0, int = 0);
int dist(int = 0, int = 0, int = 0, int = 0);
int roll(int, int, int);
int roll_max(int, int, int);
int roundmargin(int = 0, int = 0);


// Player-owned building
int getworker(int = 0, int = 0);
void removeworker(int = 0);


//// flt
int fltsetdungeon();
std::string fltname(int = 0);
void flt(int = 0, Quality quality = Quality::none);
void fltn(const std::string&);


// Input translation
int key_direction(const std::string& action);


//// Actions

// Querying input
int ask_direction();
int target_position(bool target_chara = true);
int prompt_magic_location();
int prompt_really_attack();

// Action calculation
int find_enemy_target(bool silent = false);
int can_do_ranged_attack();

// Main action body
int try_to_reveal();
int can_evade_trap();
int try_to_disarm_trap();
int try_to_perceive_npc(int);

bool read_textbook(Item& textbook);
int decode_book();
int read_normal_book();

int try_to_cast_spell();
int do_cast_magic();
int do_cast_magic_attempt();

int drink_potion();
int drink_well();
int read_scroll();
int do_zap();
int do_magic_attempt();
int pick_up_item(bool play_sound = true);
int unlock_box(int);
void do_ranged_attack();

//// Command
TurnResult step_into_gate(Item& moon_gate);
optional<TurnResult> check_angband();
TurnResult do_bash();
TurnResult do_enter_strange_gate();
TurnResult do_gatcha(Item& gatcha_machine);
TurnResult do_use_magic();
TurnResult do_use_stairs_command(int);
TurnResult try_interact_with_npc();
TurnResult try_to_open_locked_door();

// Attacking
void build_target_list();
void equip_melee_weapon();
void get_inheritance();

void try_to_melee_attack();
void do_physical_attack();
void proc_weapon_enchantments();

// Planting
TurnResult do_plant();
void grow_plant(int);
void try_to_grow_plant(int = 0);
void harvest_plant(int);
void create_harvested_item();

// Searching
void disarm_trap(Character& chara, int x, int y);
void discover_trap();
void discover_hidden_path();

// Sleeping
void draw_sleep_background_frame();
void load_sleep_background();
void sleep_start();
void wake_up();
void do_rest();

// Opening
void open_box();
void open_new_year_gift();

// NPC interact
TurnResult call_npc();


//// Action effect
void dipcursed(int = 0, int = 0);
void start_stealing();
void hostileaction(int = 0, int = 0);
void turn_aggro(int = 0, int = 0, int = 0);
void ride_begin(int = 0);
void ride_end();
void make_sound(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);


//// pass_one_turn
void proc_pregnant();
void proc_negative_enchantments(Character& chara);
void damage_by_cursed_equipments();


//// proc_movement_event
TurnResult proc_movement_event();
void map_global_proc_travel_events();
void move_character();
void sense_map_feats_on_move();


//// Magic
int breath_list();
int efstatusfix(int = 0, int = 0, int = 0, int = 0);
int route_info(int&, int&, int = 0);
void try_to_return();
void heal_both_rider_and_mount();
void heal_completely();
void incognitobegin();
void incognitoend();
void lovemiracle(int = 0);


//// Blending
int blending_find_required_mat();
int blending_spend_materials();
void blending_start_attempt();
void blending_proc_on_success_events();

//// Map
int map_barrel(int = 0, int = 0);
int map_connectroom();
int map_createroom(int = 0);
int map_digcheck(int = 0, int = 0);
int map_placedownstairs(int = 0, int = 0);
int map_placeupstairs(int = 0, int = 0);
int map_trap(int = 0, int = 0, int = 0, int = 0);
int map_web(int = 0, int = 0, int = 0);
int mapitemfind(int = 0, int = 0, int = 0);

// Map drawing
void cell_draw();
void addefmap(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);

// Map animation
void animeblood(int = 0, int = 0, int = 0);
void animeload(int = 0, int = 0);
void spillblood(int = 0, int = 0, int = 0);
void spillfrag(int = 0, int = 0, int = 0);

// Mef
void delmef(int = 0);

// Map initialization
TurnResult initialize_map();
void initialize_map_from_map_type();
void map_global_proc_diastrophism();
void map_global_prepare();
void map_global_place_entrances();
void map_clear_material_spots_and_light();

// Map lifecycle
TurnResult exit_map();
void prepare_charas_for_map_unload();
void save_map_local_data();


//// Map generation
void initialize_cell_object_data();
void initialize_random_nefia_rdtype6();
void initialize_quest_map_town();
void initialize_random_nefia_rdtype8();
void initialize_random_nefia_rdtype9();
void mapgen_dig_maze();
void initialize_random_nefia_rdtype10();


//// weather_changes
void supply_income();


//// list/listn
void sort_list_by_column1();
void sort_list_and_listn_by_column1();


//// Special items

// Gene engineering
int gain_skills_by_geen_engineering();
int transplant_body_parts();

// objet of heart
void cnvbonus(int = 0, int = 0);


//// UI
void help_halt();
int winposy(int = 0, int = 0);
void txttargetnpc(int x, int y);

// character sheet
void append_accuracy_info(int);
void show_weapon_dice(int);

// Screen refresh
void auto_turn(int delay);
void house_board_update_screen();

// inventory
void savecycle();


//// Text parsing
int talk_conv(std::string&, int = 0);
void parse_quest_board_text(int);
void parse_talk_file();
void read_talk_file(const std::string&);
void get_npc_talk();
void text_replace_tags_in_quest_board();
void text_replace_tags_in_quest_text();


//// Text

// Text manipulation
std::string zentohan(const std::string&);
std::string cnven(const std::string&);
std::string fixtxt(const std::string&, int = 0);
std::string sncnv(const std::string&);
void cutname(std::string&, int = 0);
void lenfix(std::string&, int = 0);



// Text fragments
std::string cnvarticle(const std::string&);
std::string cnvdate(int, bool = true);
std::string cnveqweight(int = 0);
std::string cnvfix(int = 0);
std::string cnvitemname(int = 0);
std::string cnvplaytime(int = 0);
std::string cnvrank(int = 0);
std::string cnvrare(int = 0);
std::string cnvweight(int = 0);

// Whole message creation
std::string getnpctxt(const std::string&, const std::string&);
std::string txtbuilding(int x, int y);
std::string txtitemoncell(int = 0, int = 0);
std::string txtskillchange(int, int, bool);
std::string txttargetlevel(int, int);
std::string cheer_up_message(int);


// Name retrieval
std::string name(int = 0);
std::string itemname(int = 0, int = 0, int = 0);
std::string guildname();
std::string maplevel(int = 0);
std::string mapname(int, bool = false);
std::string ranktitle(int = 0);

// Job names
std::string snarmor(const std::string&);
std::string snbakery(const std::string&);
std::string snblack(const std::string&);
std::string snfish(const std::string&);
std::string snfood(const std::string&);
std::string sngeneral(const std::string&);
std::string sngoods(const std::string&);
std::string sninn(const std::string&);
std::string snmagic(const std::string&);
std::string sntrade(const std::string&);
std::string sntrainer(const std::string&);


//// Casino/ATX
void atxinit();

// Save manipulation
void begintempinv();
void exittempinv();
void migrate_save_data(const fs::path& filepath);
void load_gene_files();
void save_gene();
void dump_player_info();


//// dmgheal
void character_drops_item();
void check_kill(int = 0, int = 0);


//// Journal
void append_subquest_journal(int);
void append_quest_item_journal();


//// turn_begin
void auto_identify();
void monster_respawn();


//// weather
void weather_changes();


//// Religion
void god_fail_to_take_over_penalty();


//// ether disease
void lost_body_part(int);


//// Scene
void do_play_scene();
void scene_fade_to_black();


//// Scenario
void conquer_lesimas();
void play_the_last_scene_again();


//// Game lifecycle
void proc_turn_end(int);
TurnResult pc_died();
void show_game_score_ranking();
void finish_elona();


//// Status manipulation
void modrank(int = 0, int = 0, int = 0);


//// item_show_description
void page_load();
void page_save();

} // namespace elona
