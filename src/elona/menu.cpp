#include "menu.hpp"

#include <iostream>
#include <stack>

#include "ability.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "command.hpp"
#include "config.hpp"
#include "config_menu.hpp"
#include "data/types/type_buff.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_portrait.hpp"
#include "defines.hpp"
#include "draw.hpp"
#include "enchantment.hpp"
#include "equipment.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "lua_env/interface.hpp"
#include "macro.hpp"
#include "magic.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "net.hpp"
#include "pic_loader/pic_loader.hpp"
#include "pic_loader/tinted_buffers.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "trait.hpp"
#include "ui.hpp"
#include "ui/ui_menu_adventurers.hpp"
#include "ui/ui_menu_alias.hpp"
#include "ui/ui_menu_book.hpp"
#include "ui/ui_menu_character_sheet.hpp"
#include "ui/ui_menu_composite_character.hpp"
#include "ui/ui_menu_composite_message.hpp"
#include "ui/ui_menu_composite_town.hpp"
#include "ui/ui_menu_ctrl_ally.hpp"
#include "ui/ui_menu_feats.hpp"
#include "ui/ui_menu_game_help.hpp"
#include "ui/ui_menu_god.hpp"
#include "ui/ui_menu_hire.hpp"
#include "ui/ui_menu_item_desc.hpp"
#include "ui/ui_menu_npc_tone.hpp"
#include "ui/ui_menu_quest_board.hpp"
#include "ui/ui_menu_scene.hpp"
#include "ui/ui_menu_skills.hpp"
#include "ui/ui_menu_spell_writer.hpp"
#include "ui/ui_menu_spells.hpp"
#include "ui/ui_menu_voting_box.hpp"
#include "variables.hpp"



namespace
{

std::string _set_pcc_info(Character& chara, int val0)
{
    std::string text;

    rtval = -2;
    if (page == 0)
    {
        if (val0 == 0)
        {
            rtval = -2;
        }
        if (val0 == 1)
        {
            rtval(0) = 100;
            rtval(1) = 0;
            rtval(2) = -2;
            text = chara.portrait;
        }
        if (val0 == 2)
        {
            rtval(0) = 1;
            rtval(1) = 0;
            rtval(2) = pcc(1, chara.index) % 1000;
            text = u8"hair"s;
        }
        if (val0 == 3)
        {
            rtval(0) = 10;
            rtval(1) = 0;
            rtval(2) = pcc(10, chara.index) % 1000;
            text = u8"subhair"s;
        }
        if (val0 == 4)
        {
            rtval(0) = 1;
            rtval(1) = 1;
            rtval(2) = pcc(1, chara.index) / 1000;
        }
        if (val0 == 5)
        {
            rtval(0) = 15;
            rtval(1) = 0;
            rtval(2) = pcc(15, chara.index) % 1000;
            text = u8"body"s;
        }
        if (val0 == 6)
        {
            rtval(0) = 9;
            rtval(1) = 0;
            rtval(2) = pcc(9, chara.index) % 1000;
            text = u8"cloth"s;
        }
        if (val0 == 7)
        {
            rtval(0) = 7;
            rtval(1) = 0;
            rtval(2) = pcc(7, chara.index) % 1000;
            text = u8"pants"s;
        }
        if (val0 == 8)
        {
            rtval = -1;
            text = "";
        }
        if (val0 == 9)
        {
            if (chara.index != 0)
            {
                rtval(0) = 101;
                rtval(1) = 0;
                rtval(2) = chara.has_own_sprite();
            }
            else
            {
                rtval(0) = 16;
                rtval(1) = 0;
                rtval(2) = pcc(16, chara.index) % 1000;
                text = u8"ride"s;
            }
        }
    }
    else
    {
        if (val0 == 0)
        {
            rtval(0) = 15;
            rtval(1) = 1;
            rtval(2) = pcc(15, chara.index) / 1000;
        }
        if (val0 == 1)
        {
            rtval(0) = 9;
            rtval(1) = 1;
            rtval(2) = pcc(9, chara.index) / 1000;
        }
        if (val0 == 2)
        {
            rtval(0) = 7;
            rtval(1) = 1;
            rtval(2) = pcc(7, chara.index) / 1000;
        }
        if (val0 == 3)
        {
            rtval(0) = 11;
            rtval(1) = 0;
            rtval(2) = pcc(11, chara.index) % 1000;
            text = u8"etc"s;
        }
        if (val0 == 4)
        {
            rtval(0) = 12;
            rtval(1) = 0;
            rtval(2) = pcc(12, chara.index) % 1000;
            text = u8"etc"s;
        }
        if (val0 == 5)
        {
            rtval(0) = 13;
            rtval(1) = 0;
            rtval(2) = pcc(13, chara.index) % 1000;
            text = u8"etc"s;
        }
        if (val0 == 6)
        {
            rtval(0) = 14;
            rtval(1) = 0;
            rtval(2) = pcc(14, chara.index) % 1000;
            text = u8"eye"s;
        }
        if (val0 == 7)
        {
            rtval = -1;
            text = "";
        }
    }

    return text;
}

} // namespace



namespace elona
{

void text_set()
{
    strhint1 = i18n::s.get("core.ui.hint.cursor");
    strhint2 = ""s + key_pageup + u8","s + key_pagedown +
        i18n::s.get("core.ui.hint.page");
    strhint3 = i18n::s.get("core.ui.hint.close");
    strhint3b = i18n::s.get("core.ui.hint.back");
    strhint4 = i18n::s.get("core.ui.hint.enter");
    strhint5 = ""s + key_identify + i18n::s.get("core.ui.hint.known_info");
    strhint5b = ""s + key_mode + i18n::s.get("core.ui.hint.mode");
    strhint7 = i18n::s.get("core.ui.hint.shortcut");

    SDIM4(_melee, 20, 3, 8);
    if (jp)
    {
        _melee(0, 0) = u8"殴って"s;
        _melee(1, 0) = u8"殴られた。"s;
        _melee(2, 0) = u8"手"s;
    }
    else
    {
        _melee(0, 0) = u8"punch"s;
        _melee(1, 0) = u8"punch"s;
        _melee(2, 0) = u8"hand"s;
    }
    if (jp)
    {
        _melee(0, 3) = u8"噛み付いて"s;
        _melee(1, 3) = u8"噛み付かれた。"s;
        _melee(2, 3) = u8"牙"s;
    }
    else
    {
        _melee(0, 3) = u8"bite"s;
        _melee(1, 3) = u8"bite"s;
        _melee(2, 3) = u8"fang"s;
    }
    if (jp)
    {
        _melee(0, 4) = u8"睨んで"s;
        _melee(1, 4) = u8"睨まれた。"s;
        _melee(2, 4) = u8"眼"s;
    }
    else
    {
        _melee(0, 4) = u8"gaze"s;
        _melee(1, 4) = u8"gaze"s;
        _melee(2, 4) = u8"eye"s;
    }
    if (jp)
    {
        _melee(0, 1) = u8"引っ掻き"s;
        _melee(1, 1) = u8"引っ掻かれた。"s;
        _melee(2, 1) = u8"爪"s;
    }
    else
    {
        _melee(0, 1) = u8"claw"s;
        _melee(1, 1) = u8"claw"s;
        _melee(2, 1) = u8"claw"s;
    }
    if (jp)
    {
        _melee(0, 5) = u8"刺し"s;
        _melee(1, 5) = u8"刺された。"s;
        _melee(2, 5) = u8"針"s;
    }
    else
    {
        _melee(0, 5) = u8"sting"s;
        _melee(1, 5) = u8"sting"s;
        _melee(2, 5) = u8"needle"s;
    }
    if (jp)
    {
        _melee(0, 6) = u8"触って"s;
        _melee(1, 6) = u8"触られた。"s;
        _melee(2, 6) = u8"手"s;
    }
    else
    {
        _melee(0, 6) = u8"touch"s;
        _melee(1, 6) = u8"touch"s;
        _melee(2, 6) = u8"hand"s;
    }
    if (jp)
    {
        _melee(0, 7) = u8"胞子を撒き散らし"s;
        _melee(1, 7) = u8"胞子を飛ばされた。"s;
        _melee(2, 7) = u8"胞子"s;
    }
    else
    {
        _melee(0, 7) = u8"attack"s;
        _melee(1, 7) = u8"attack"s;
        _melee(2, 7) = u8"spore"s;
    }
}



bool maybe_show_ex_help(int id, bool should_update_screen)
{
    if (g_config.extra_help())
    {
        if (game_data.exhelp_flags.at(id) == 0)
        {
            if (mode == Mode::zero_default)
            {
                if (cdata.player().activity.turn == 0)
                {
                    game_data.exhelp_flags.at(id) = 1;
                    show_ex_help(id);

                    if (should_update_screen)
                    {
                        screenupdate = -1;
                        update_screen();
                    }

                    return true;
                }
            }
        }
    }

    return false;
}



void show_ex_help(int id)
{
    asset_load("deco_help");
    gsel(0);
    page = 0;
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{lua::resolve_path_for_mod(
                             "<core>/locale/<LANGUAGE>/lazy/exhelp.txt")
                             .native(),
                         std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    p = instr(buff, 0, u8"%"s + id + u8","s + i18n::s.get("core.meta.tag"));
    if (p == -1)
    {
        dialog(
            u8"help index not found %"s + id + u8","s +
            i18n::s.get("core.meta.tag"));
        return;
    }
    buff = strmid(buff, p, instr(buff, p, u8"%END"s));
    notedel(0);
    if (noteinfo() == 0)
    {
        return;
    }
    snd("core.chime");
    while (1)
    {
        gmode(2);
        dx = 480;
        dy = 175;
        window2((windoww - dx) / 2 + inf_screenx, winposy(dy), dx, dy, 4, 0);
        wx = (windoww - dx) / 2 + inf_screenx;
        wy = winposy(dy);
        window2(
            (windoww - 325) / 2 + inf_screenx, winposy(dy) + 6, 325, 32, 0, 1);
        draw("deco_help_a", wx + 5, wy + 4);
        draw("deco_help_a", wx + dx - 55, wy + 4);
        draw("deco_help_b", wx + 10, wy + 42);
        font(16 - en * 2, snail::Font::Style::bold);
        bmes(
            i18n::s.get("core.ui.exhelp.title"),
            wx + 142,
            wy + 13,
            {255, 245, 235},
            {80, 60, 50});
        tx = wx + 120;
        ty = wy + 55;
        font(15 - en * 2);
        {
            int y = ty;
            int cnt = 0;
            for (int cnt_end = cnt + (10); cnt < cnt_end; ++cnt)
            {
                noteget(s, page);
                ++page;
                if (page > noteinfo() || s == ""s)
                {
                    break;
                }
                const auto ny = gmes(s, tx, y, 330, {30, 30, 30}, true).y;
                y = ny;
            }
        }
        gmode(2);
        redraw();
        help_halt();
        if (page >= noteinfo())
        {
            break;
        }
    }
}

void show_game_help()
{
    ui::UIMenuGameHelp().show();
}

TurnResult show_journal()
{
    ui::UIMenuCompositeMessage(
        static_cast<size_t>(ui::UIMenuCompositeMessage::Index::journal))
        .show();
    return TurnResult::pc_turn_user_error;
}

TurnResult show_message_log()
{
    ui::UIMenuCompositeMessage(
        static_cast<size_t>(ui::UIMenuCompositeMessage::Index::message_log))
        .show();
    return TurnResult::pc_turn_user_error;
}

TurnResult show_chat_history()
{
    ui::UIMenuCompositeMessage(
        static_cast<size_t>(ui::UIMenuCompositeMessage::Index::chat_history))
        .show();
    return TurnResult::pc_turn_user_error;
}



TurnResult play_scene()
{
    auto result = ui::UIMenuScene().show();

    if (result.canceled)
    {
        return TurnResult::pc_turn_user_error;
    }
    else
    {
        return TurnResult::play_scene;
    }
}


static TurnResult _show_skill_spell_menu(size_t menu_index)
{
    auto result = ui::UIMenuCompositeSkills(menu_index).show();

    if (result.canceled || !result.value)
    {
        return TurnResult::pc_turn_user_error;
    }

    if (std::holds_alternative<ui::UIMenuSkillsResult>(*result.value))
    {
        efid = std::get<ui::UIMenuSkillsResult>(*result.value).effect_id;
        return do_use_magic();
    }
    else
    {
        efid = std::get<ui::UIMenuSpellsResult>(*result.value).effect_id;
        return do_cast_command();
    }
}

TurnResult show_spell_list()
{
    return _show_skill_spell_menu(
        static_cast<size_t>(ui::UIMenuCompositeSkills::Index::spells));
}

TurnResult show_skill_list()
{
    return _show_skill_spell_menu(
        static_cast<size_t>(ui::UIMenuCompositeSkills::Index::skills));
}

static std::string _make_buff_power_string(int skill_id)
{
    const auto buff_id = the_ability_db[skill_id]->ability_type % 1000;
    const auto duration = buff_calc_duration(
        *the_buff_db.get_id_from_legacy(buff_id), calcspellpower(skill_id, cc));
    const auto description = buff_get_description(
        *the_buff_db.get_id_from_legacy(buff_id), calcspellpower(skill_id, cc));
    return std::to_string(duration) +
        i18n::s.get("core.ui.spell.turn_counter") + " " + description;
}

std::string make_spell_description(int skill_id)
{
    std::string result = "";
    if (the_ability_db[skill_id]->ability_type / 1000 == 1)
    {
        return _make_buff_power_string(skill_id);
    }
    const auto damage =
        calc_skill_damage(skill_id, cc, calcspellpower(skill_id, cc));
    if (damage)
    {
        dice1 = damage->dice_x;
        dice2 = damage->dice_y;
        bonus = damage->damage_bonus;
        ele = damage->element;
        elep = damage->element_power;
        if (cc == 0)
        {
            if (trait(165) != 0)
            {
                if (ele == 50 || ele == 51 || ele == 52)
                {
                    dice2 = dice2 * 125 / 100;
                }
            }
        }
        if (dice1 != 0)
        {
            result += ""s + dice1 + u8"d"s + dice2;
            if (bonus != 0)
            {
                if (bonus > 0)
                {
                    result += u8"+"s + bonus;
                }
                else
                {
                    result += bonus;
                }
            }
        }
        else if (skill_id == 461)
        {
            result += ""s + clamp(bonus, 1, 100) + u8"%"s;
        }
        else
        {
            result += i18n::s.get("core.ui.spell.power") + bonus;
        }
        result += u8" "s;
    }
    result += i18n::s
                  .get_m_optional(
                      "ability",
                      the_ability_db.get_id_from_legacy(skill_id)->get(),
                      "description")
                  .value_or("");

    return result;
}

MenuResult _show_character_sheet_menu(size_t menu_index)
{
    ui::UIMenuCompositeCharacter(menu_index).show();

    update_screen();
    return {false, false, TurnResult::pc_turn_user_error};
}

MenuResult menu_character_sheet_normal()
{
    return _show_character_sheet_menu(static_cast<size_t>(
        ui::UIMenuCompositeCharacter::Index::character_sheet));
}

MenuResult menu_feats()
{
    return _show_character_sheet_menu(
        static_cast<size_t>(ui::UIMenuCompositeCharacter::Index::feats));
}

MenuResult menu_equipment()
{
    return _show_character_sheet_menu(
        static_cast<size_t>(ui::UIMenuCompositeCharacter::Index::equipment));
}

MenuResult menu_materials()
{
    return _show_character_sheet_menu(
        static_cast<size_t>(ui::UIMenuCompositeCharacter::Index::materials));
}

// Returns false if canceled, true if confirmed
bool menu_character_sheet_character_making()
{
    auto result =
        ui::UIMenuCharacterSheet(CharacterSheetOperation::character_making)
            .show();

    if (result.canceled)
    {
        return false;
    }

    return true;
}

// Returns skill ID if skill selected, none if canceled
optional<int> menu_character_sheet_trainer(bool is_training)
{
    CharacterSheetOperation op;
    if (is_training)
    {
        op = CharacterSheetOperation::train_skill;
    }
    else
    {
        op = CharacterSheetOperation::learn_skill;
    }

    auto result = ui::UIMenuCharacterSheet(op).show();

    if (result.canceled || !result.value)
    {
        return none;
    }

    auto sheet_result = std::get<ui::CharacterSheetResult>(*result.value);
    return sheet_result.trainer_skill_id;
}

void menu_character_sheet_investigate()
{
    ui::UIMenuCharacterSheet(CharacterSheetOperation::investigate_ally).show();
}

MenuResult menu_feats_character_making()
{
    MenuResult m_result = {false, false, TurnResult::none};

    auto result =
        ui::UIMenuFeats(ui::UIMenuFeats::Operation::character_making).show();

    if (result.canceled)
    {
        m_result.succeeded = false;
    }
    else if (result.value)
    {
        auto FeatsResult = std::get<ui::FeatsResult>(*result.value);

        if (FeatsResult == ui::FeatsResult::pressed_f1)
        {
            m_result.pressed_f1 = true;
        }
        else
        {
            m_result.succeeded = true;
        }
    }

    return m_result;
}



ChangeAppearanceResult menu_change_appearance(Character& chara)
{
    create_pcpic(chara, false);
    page = 0;
    pagesize = 19;
    cs = 0;
    cs_bk = -1;
    ww = 380;
    wh = 340;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
    snd("core.port");
    window_animation(wx, wy, ww, wh, 9, 7);
    asset_load("deco_mirror");
    gsel(0);
    windowshadow = 1;

    bool init = true;
    int tick = 0;
    while (true)
    {
        ++tick;
        if (init)
        {
            init = false;
            listmax = 0;
            if (page == 0)
            {
                s(0) = i18n::s.get("core.ui.appearance.basic.done");
                s(1) = i18n::s.get("core.ui.appearance.basic.portrait");
                s(2) = i18n::s.get("core.ui.appearance.basic.hair");
                s(3) = i18n::s.get("core.ui.appearance.basic.sub_hair");
                s(4) = i18n::s.get("core.ui.appearance.basic.hair_color");
                s(5) = i18n::s.get("core.ui.appearance.basic.body");
                s(6) = i18n::s.get("core.ui.appearance.basic.cloth");
                s(7) = i18n::s.get("core.ui.appearance.basic.pants");
                s(8) = i18n::s.get("core.ui.appearance.basic.set_detail");
                if (chara.index != 0)
                {
                    s(9) = i18n::s.get("core.ui.appearance.basic.custom");
                }
                else
                {
                    s(9) = i18n::s.get("core.ui.appearance.basic.riding");
                }
                p = 9 + (chara.index != 0) +
                    (chara.index == 0) * (game_data.mount != 0);
            }
            else
            {
                s(0) = i18n::s.get("core.ui.appearance.detail.body_color");
                s(1) = i18n::s.get("core.ui.appearance.detail.cloth_color");
                s(2) = i18n::s.get("core.ui.appearance.detail.pants_color");
                s(3) = i18n::s.get("core.ui.appearance.detail.etc_1");
                s(4) = i18n::s.get("core.ui.appearance.detail.etc_2");
                s(5) = i18n::s.get("core.ui.appearance.detail.etc_3");
                s(6) = i18n::s.get("core.ui.appearance.detail.eyes");
                s(7) = i18n::s.get("core.ui.appearance.detail.set_basic");
                p = 8;
            }
            for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
            {
                list(0, cnt) = cnt;
                listn(0, cnt) = s(cnt);
                ++listmax;
            }
            keyrange = 0;
            for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
            {
                p = cnt;
                if (p >= listmax)
                {
                    break;
                }
                key_list(cnt) = key_enter;
                ++keyrange;
            }
        }

        pagesize = 0;
        ui_display_window(
            i18n::s.get("core.ui.appearance.basic.title"),
            i18n::s.get("core.ui.appearance.hint"),
            (windoww - 380) / 2 + inf_screenx,
            winposy(340) - 12,
            380,
            340);
        pagesize = listmax;
        display_topic(
            i18n::s.get("core.ui.appearance.basic.category"), wx + 34, wy + 36);
        draw("deco_mirror_a", wx + ww - 40, wy);
        window2(wx + 234, wy + 71, 88, 120, 1, 1);
        if (cs == 1 && page == 0)
        {
            if (chara.portrait != "")
            {
                if (const auto rect = draw_get_rect_portrait(chara.portrait))
                {
                    gcopy(
                        rect->buffer,
                        rect->x,
                        rect->y,
                        rect->width,
                        rect->height,
                        wx + 238,
                        wy + 75);
                }
            }
        }
        else if (chara.has_own_sprite())
        {
            gmode(2);
            const auto is_fullscale =
                g_config.pcc_graphic_scale() == "fullscale";
            const auto width = is_fullscale ? 32 : 24;
            const auto height = is_fullscale ? 48 : 40;
            for (int i = 0; i < 4; ++i)
            {
                gcopy_c(
                    chara.index + 10 + PicLoader::max_buffers +
                        TintedBuffers::max_buffers,
                    tick / 5 % 4 * 32,
                    i % 4 * 48,
                    32,
                    48,
                    wx + 238 + i % 2 * (32 + 8) + (32 + 8) / 2,
                    wy + 75 + i / 2 * (48 + 8) + (48 + 8) / 2,
                    width,
                    height);
            }
        }
        else
        {
            draw_chara(chara, wx + 280, wy + 130);
        }
        gmode(2);
        font(14 - en * 2);
        cs_listbk();
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = cnt;
            if (p >= listmax)
            {
                break;
            }
            const auto text = _set_pcc_info(chara, cnt);
            s = listn(0, p);
            if (rtval >= 0)
            {
                if (rtval(2) >= 0)
                {
                    s += u8" "s + rtval(2);
                }
                else if (rtval(2) == -1)
                {
                    s += u8" N/A"s;
                }
                else
                {
                    s += " " + text;
                }
            }
            cs_list(cs == cnt, s, wx + 60, wy + 66 + cnt * 21 - 1);
            if (rtval != -2)
            {
                draw("arrow_left", wx + 30, wy + 66 + cnt * 21 - 5);
                draw("arrow_right", wx + 175, wy + 66 + cnt * 21 - 5);
            }
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        redraw();
        auto action = cursor_check_ex();
        const auto text = _set_pcc_info(chara, cs);
        bool changed = false;
        if (rtval == -2)
        {
            if (action == "enter")
            {
                create_pcpic(chara);
                return ChangeAppearanceResult::proceed;
            }
            if (action == "next_page" || action == "previous_page")
            {
                action = ""s;
            }
        }
        else if (action == "enter")
        {
            action = "next_page";
        }
        if (rtval == -1)
        {
            if (action == "next_page" || action == "previous_page")
            {
                snd("core.cursor1");
                if (page == 0)
                {
                    page = 1;
                }
                else
                {
                    page = 0;
                    cs = 8;
                }
                init = true;
                continue;
            }
        }
        if (action == "next_page")
        {
            snd("core.cursor1");
            if (rtval == 100)
            {
                chara.portrait =
                    the_portrait_db.get_next_portrait(chara.portrait);
                continue;
            }
            if (rtval == 101)
            {
                chara.has_own_sprite() = true;
                continue;
            }
            if (rtval(1) == 0)
            {
                if (fs::exists(
                        filesystem::dirs::graphic() /
                        (u8"pcc_"s + text + u8"_" +
                         (pcc(rtval, chara.index) % 1000 + 1) + u8".bmp")))
                {
                    ++pcc(rtval, chara.index);
                    changed = true;
                }
            }
            else if (pcc(rtval, chara.index) / 1000 < 21)
            {
                pcc(rtval, chara.index) += 1000;
                changed = true;
            }
        }
        if (action == "previous_page")
        {
            snd("core.cursor1");
            if (rtval == 100)
            {
                chara.portrait =
                    the_portrait_db.get_previous_portrait(chara.portrait);
                continue;
            }
            if (rtval == 101)
            {
                chara.has_own_sprite() = false;
                continue;
            }
            if (rtval(1) == 0)
            {
                if ((pcc(rtval, chara.index) % 1000 == 1 && rtval != 15) ||
                    fs::exists(
                        filesystem::dirs::graphic() /
                        (u8"pcc_"s + text + u8"_"s +
                         (pcc(rtval, chara.index) % 1000 - 1) + u8".bmp"s)))
                {
                    --pcc(rtval, chara.index);
                    changed = true;
                }
            }
            else if (pcc(rtval, chara.index) / 1000 > 0)
            {
                pcc(rtval, chara.index) -= 1000;
                changed = true;
            }
        }
        if (changed)
        {
            create_pcpic(chara, false);
        }
        if (action == "cancel")
        {
            if (page == 0)
            {
                create_pcpic(chara);
                return ChangeAppearanceResult::canceled;
            }
            else
            {
                page = 0;
                cs = 8;
                init = true;
                continue;
            }
        }
        if (mode == Mode::new_game)
        {
            if (getkey(snail::Key::f1))
            {
                return ChangeAppearanceResult::show_help;
            }
        }
    }
}



void change_appearance_equipment(Character& chara)
{
    create_pcpic(chara);
    snd("core.pop2");
    page = 0;
    pagesize = 18;
    cs = 0;
    cs_bk = -1;
    windowshadow = 1;
    listmax = 0;
    s(0) = i18n::s.get("core.ui.appearance.equipment.done");
    s(1) = i18n::s.get("core.ui.appearance.equipment.chest");
    s(2) = i18n::s.get("core.ui.appearance.equipment.leg");
    s(3) = i18n::s.get("core.ui.appearance.equipment.belt");
    s(4) = i18n::s.get("core.ui.appearance.equipment.glove");
    s(5) = i18n::s.get("core.ui.appearance.equipment.mantle");
    p = 6;
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        list(0, cnt) = cnt;
        listn(0, cnt) = s(cnt);
        ++listmax;
    }
    keyrange = 0;
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_enter;
        ++keyrange;
    }

    int tick = 0;
    while (true)
    {
        ++tick;
        pagesize = 0;
        ui_display_window(
            i18n::s.get("core.ui.appearance.equipment.title"),
            i18n::s.get("core.ui.appearance.hint"),
            (windoww - 360) / 2 + inf_screenx,
            winposy(289) - 12,
            360,
            289);
        s = i18n::s.get("core.ui.appearance.equipment.part");
        pagesize = listmax;
        display_topic(s, wx + 34, wy + 36);
        window2(wx + 234, wy + 60, 88, 120, 1, 1);
        gmode(2);
        const auto is_fullscale = g_config.pcc_graphic_scale() == "fullscale";
        const auto width = is_fullscale ? 32 : 24;
        const auto height = is_fullscale ? 48 : 40;
        for (int i = 0; i < 4; ++i)
        {
            gcopy_c(
                chara.index + 10 + PicLoader::max_buffers +
                    TintedBuffers::max_buffers,
                tick / 5 % 4 * 32,
                i % 4 * 48,
                32,
                48,
                wx + 238 + i % 2 * (32 + 8) + (32 + 8) / 2,
                wy + 64 + i / 2 * (48 + 8) + (48 + 8) / 2,
                width,
                height);
        }
        gmode(2);
        font(14 - en * 2);
        cs_listbk();
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = cnt;
            if (p >= listmax)
            {
                break;
            }
            s = listn(0, p);
            if (cnt != 0)
            {
                if (pcc(20 + cnt - 1, chara.index) == 0)
                {
                    s += u8"On"s;
                }
                else
                {
                    s += u8"Off"s;
                }
                draw("arrow_left", wx + 30, wy + 66 + cnt * 21 - 5);
                draw("arrow_right", wx + 175, wy + 66 + cnt * 21 - 5);
            }
            cs_list(cs == cnt, s, wx + 60, wy + 66 + cnt * 21 - 1);
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        redraw();
        auto action = cursor_check_ex();
        if (cs != 0)
        {
            if (action == "enter")
            {
                action = "next_page";
            }
            if (action == "next_page" || action == "previous_page")
            {
                if (pcc(20 + cs - 1, chara.index) == 0)
                {
                    pcc(20 + cs - 1, chara.index) = 1;
                }
                else
                {
                    pcc(20 + cs - 1, chara.index) = 0;
                }
                create_pcpic(chara);
                snd("core.cursor1");
            }
        }
        if ((cs == 0 && action == "enter") || action == "cancel")
        {
            snd("core.ok1");
            create_pcpic(chara);
            return;
        }
    }
}



void append_accuracy_info(int val0)
{
    p(1) = 0;
    p(2) = 0;
    attackskill = 106;
    ammo = -1;
    attacknum = 0;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata[cc].body_parts[cnt] % 10000 == 0)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 10)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 11)
        {
            continue;
        }
        cw = cdata[cc].body_parts[cnt] % 10000 - 1;
        if (inv[cw].dice_x > 0)
        {
            attackskill = inv[cw].skill;
            ++p(1);
            s(1) = i18n::s.get("core.ui.chara_sheet.damage.melee") + p(1);
            ++attacknum;
            show_weapon_dice(val0);
        }
    }
    if (attackskill == 106)
    {
        s(1) = i18n::s.get("core.ui.chara_sheet.damage.unarmed");
        show_weapon_dice(val0);
    }
    attacknum = 0;
    int stat = can_do_ranged_attack();
    if (stat == 1)
    {
        s(1) = i18n::s.get("core.ui.chara_sheet.damage.dist");
        show_weapon_dice(val0);
    }
}



void show_weapon_dice(int val0)
{
    tc = cc;
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    if (val0 == 0)
    {
        mes(wx + 590,
            wy + 281 + p(2) * 16,
            i18n::s.get("core.ui.chara_sheet.damage.hit"),
            {20, 10, 0});
        mes(wx + 417, wy + 281 + p(2) * 16, s(1), {20, 10, 0});
    }
    attackrange = 0;
    if (the_item_db[itemid2int(inv[cw].id)]->category == 24000) // TODO coupling
    {
        attackrange = 1;
    }
    int tohit = calc_accuracy(false);
    dmg = calcattackdmg(AttackDamageCalculationMode::raw_damage);
    font(14 - en * 2);
    s(2) = ""s + dmgmulti;
    s = ""s + tohit + u8"%"s;
    if (val0 == 0)
    {
        mes(wx + 625 - en * 8, wy + 279 + p(2) * 16, s);
    }
    else
    {
        s(3) = s;
    }
    s = ""s + dice1 + u8"d"s + dice2 + cnvfix(dmgfix) + u8" x"s +
        strmid(
            s(2),
            0,
            3 + (elona::stoi(s(2)) >= 10) + (elona::stoi(s(2)) >= 100));
    if (val0 == 0)
    {
        mes(wx + 460 + en * 8, wy + 279 + p(2) * 16, s);
    }
    else
    {
        noteadd(s(1) + "   : " + fixtxt(s(3), 12) + " " + fixtxt(s, 20));
    }
    ++p(2);
}



static TurnResult _visit_quest_giver(int quest_index)
{
    // TODO move the below somewhere else to decouple quest_teleport
    tc = quest_data[quest_index].client_chara_index;
    rq = quest_index;
    client = tc;
    efid = 619;
    magic();
    tc = client;
    if (cdata.player().state() == Character::State::alive)
    {
        quest_teleport = true;
        talk_to_npc();
    }
    if (chatteleport == 1)
    {
        chatteleport = 0;
        return TurnResult::exit_map;
    }
    return TurnResult::turn_end;
}

TurnResult show_quest_board()
{
    maybe_show_ex_help(4, true);

    auto result = ui::UIMenuQuestBoard().show();

    if (result.canceled)
    {
        return TurnResult::turn_end;
    }

    int quest_index = *result.value;
    return _visit_quest_giver(quest_index);
}

int show_hire_menu(HireOperation operation)
{
    auto result = ui::UIMenuHire(operation).show();

    if (result.canceled)
    {
        return -1;
    }
    else
    {
        return *result.value;
    }
}

int show_spell_writer_menu()
{
    ui::UIMenuSpellWriter().show();

    return -1;
}

void list_adventurers()
{
    ui::UIMenuAdventurers().show();
}

int select_alias(int val0)
{
    auto result = ui::UIMenuAlias(val0).show();

    if (result.canceled)
    {
        return 0;
    }

    if (val0 == 3)
    {
        return result.value->seed;
    }
    else
    {
        cmaka = result.value->alias;
        return 1;
    }
}

void show_city_chart()
{
    ui::UIMenuCompositeTown(
        static_cast<size_t>(ui::UIMenuCompositeTown::Index::chart))
        .show();
}



void begin_to_believe_god(int god_id)
{
    bool already_believing = cdata.player().god_id != core_god::eyth;

    auto result = ui::UIMenuGod(god_id, already_believing).show();

    if (!result.canceled && result.value)
    {
        rtval = *result.value;
        god_proc_switching_penalty(core_god::int2godid(god_id));
    }
}



void house_board_update_screen()
{
    screenupdate = -1;
    update_screen();
}



int ctrl_ally(ControlAllyOperation operation)
{
    auto result = ui::UIMenuCtrlAlly(operation).show();

    if (!result.canceled && result.value)
    {
        return *result.value;
    }
    else
    {
        return -1;
    }
}



void screen_analyze_self()
{
    // TODO: untranslated
    if (rc < 0)
    {
        rc = tc;
        if (rc < 0)
        {
            rc = 0;
        }
    }
    listmax = 0;
    page = 0;
    pagesize = 14;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    snd("core.pop2");
    buff = "";
    notesel(buff);
    chara_delete(56);
    cdata.tmp().piety_point = cdata.player().piety_point;
    cdata.tmp().god_id = cdata.player().god_id;
    for (int cnt = 0; cnt < 600; ++cnt)
    {
        sdata(cnt, rc) = 1;
    }
    apply_god_blessing(56);
    if (cdata.player().god_id != core_god::eyth)
    {
        buff += u8"<title1>◆ "s + god_name(cdata.player().god_id) +
            u8"による能力の恩恵<def>\n"s;
        for (int cnt = 0; cnt < 600; ++cnt)
        {
            p = sdata(cnt, rc) - 1;
            cnvbonus(cnt, p);
        }
    }
    refreshmode = 1;
    chara_refresh(0);
    refreshmode = 0;
    buff += u8"\n"s;
    buff += u8"<title1>◆ 特徴と特殊状態による能力の恩恵<def>\n"s;
    listmax = noteinfo();

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;

            cs_bk = -1;
            pagemax = (listmax - 1) / pagesize;
            if (page < 0)
            {
                page = pagemax;
            }
            else if (page > pagemax)
            {
                page = 0;
            }
            ui_display_window(
                i18n::s.get("core.ui.analysis.title"),
                strhint2 + strhint3b,
                (windoww - 400) / 2 + inf_screenx,
                winposy(448),
                400,
                448);
            s = i18n::s.get("core.ui.analysis.result");
            display_topic(s, wx + 28, wy + 36);
            font(14 - en * 2);
            for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
            {
                p = pagesize * page + cnt;
                if (p >= listmax)
                {
                    break;
                }
                noteget(s, p);
                gmes(s, wx, wy + 66 + cnt * 19 + 2, 600, {30, 30, 30}, false);
            }
            redraw();
        }

        redraw();
        auto action = get_selected_item(p(0));
        p = -1;
        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                init = true;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                init = true;
                continue;
            }
        }
        if (action == "cancel")
        {
            return;
        }
    }
}



int change_npc_tone()
{
    auto result = ui::UIMenuNPCTone().show();

    if (result.canceled)
    {
        return -1;
    }

    snd("core.ok1");
    txt(i18n::s.get(
        "core.action.interact.change_tone.is_somewhat_different", cdata[tc]));

    if (result.value)
    {
        cdata[tc].has_custom_talk() = true;
        cdatan(4, tc) = *result.value;
    }
    else
    {
        cdata[tc].has_custom_talk() = false;
        cdatan(4, tc) = "";
    }

    return 1;
}



void show_book_window(const Item& book)
{
    ui::UIMenuBook(book.param1).show();
}



void item_show_description(const Item& item)
{
    ui::UIMenuItemDesc(item).show();

    returnfromidentify = 1;
}



void menu_chat_dialog()
{
    if (!net_can_send_chat_now())
    {
        txt(i18n::s.get("core.net.chat.wait_more"));
        return;
    }

    inputlog = "";
    input_text_dialog(80, windowh - inf_verh - 70, 38);
    if (inputlog(0).empty())
    {
        return;
    }

    const auto message = i18n::s.get("core.net.chat.message", inputlog(0));
    txt(message);
    net_send_chat(message);
}



void menu_voting_box()
{
    ui::UIMenuVotingBox().show();
}



void show_option_menu()
{
    struct ConfigMenuHistory
    {
        int cs;
        int submenu;
    };


    int submenu = 0;
    cs = 0;
    std::stack<ConfigMenuHistory> history;

    const auto config_menu = config_build_menu();

    while (true)
    {
        auto& menu_def = config_menu.at(submenu);
        const auto result = menu_def->query();

        if (result)
        {
            if (result->go_back)
            {
                {
                    const auto& prev = history.top();
                    cs = prev.cs;
                    submenu = prev.submenu;
                }
                history.pop();
            }
            // Don't push history if the submenu index returned is the same
            // (user viewed and exited the help text of an option)
            else if (result->submenu != submenu)
            {
                history.push({cs, submenu});
                cs = 0;
                submenu = result->submenu;
            }
        }
        else
        {
            break;
        }
    }
}

} // namespace elona
