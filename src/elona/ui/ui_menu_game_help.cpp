#include "ui_menu_game_help.hpp"

#include "../../util/fileutil.hpp"
#include "../../util/strutil.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"



namespace elona
{
namespace ui
{

bool UIMenuGameHelp::init()
{
    // pre - notesel init
    snd("core.pop2");
    listmax = 0;
    page = 0;
    pagesize = 18;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    page_bk = 0;
    cs_bk2 = 0;
    if (mode != Mode::new_game)
    {
        load_background_variants(4);
        gsel(0);
    }
    else
    {
        cs = 3;
        cs_bk2 = cs;
    }

    list(0, 0) = 0 /* dummy */;
    listn(0, 0) = i18n::s.get("core.ui.manual.keys.list");
    ++listmax;

    _help.load(
        lua::resolve_path_for_mod("<core>/locale/<LANGUAGE>/lazy/manual.txt"));

    for (const auto& section : _help.section_headings())
    {
        list(0, listmax) = listmax - 1;
        listn(0, listmax) = section;
        ++listmax;
    }

    windowshadow = 1;

    update();

    return true;
}



void UIMenuGameHelp::_draw_key_list()
{
    const auto x = wx + 188;
    const auto y = wy + 6;
    const auto desc_font_size = 13 - en * 2;
    const auto key_font_size = 15 - en * 2;

    struct KeyDescPair
    {
        std::string key;
        std::string desc;
    };

    {
        // Section "Item"
        display_topic(
            i18n::s.get("core.ui.manual.keys.item.title"), x + 18, y + 30);

        std::vector<KeyDescPair> keys{
            {key_get, i18n::s.get("core.ui.manual.keys.item.get")},
            {key_read, i18n::s.get("core.ui.manual.keys.item.read")},
            {key_drop, i18n::s.get("core.ui.manual.keys.item.drop")},
            {key_zap, i18n::s.get("core.ui.manual.keys.item.zap")},
            {key_inventory, i18n::s.get("core.ui.manual.keys.item.examine")},
            {key_use, i18n::s.get("core.ui.manual.keys.item.tool")},
            {key_wear, i18n::s.get("core.ui.manual.keys.item.wear_wield")},
            {key_dip, i18n::s.get("core.ui.manual.keys.item.blend")},
            {key_eat, i18n::s.get("core.ui.manual.keys.item.eat")},
            {key_throw, i18n::s.get("core.ui.manual.keys.item.throw")},
            {key_drink, i18n::s.get("core.ui.manual.keys.item.quaff")},
            {key_ammo, i18n::s.get("core.ui.manual.keys.item.ammo")},
        };

        int index = 0;
        for (const auto& pair : keys)
        {
            font(desc_font_size);
            mes(x + 38 + index % 2 * 290, y + 58 + index / 2 * 14, pair.desc);
            font(key_font_size);
            mes(x + 248 + index % 2 * 290, y + 57 + index / 2 * 14, pair.key);
            ++index;
        }
    }

    // Section "Action"
    {
        display_topic(
            i18n::s.get("core.ui.manual.keys.action.title"), x + 18, y + 142);

        std::vector<KeyDescPair> keys{
            {key_search, i18n::s.get("core.ui.manual.keys.action.search")},
            {key_target, i18n::s.get("core.ui.manual.keys.action.target")},
            {key_cast, i18n::s.get("core.ui.manual.keys.action.cast")},
            {key_fire, i18n::s.get("core.ui.manual.keys.action.fire")},
            {key_interact, i18n::s.get("core.ui.manual.keys.action.interact")},
            {key_skill, i18n::s.get("core.ui.manual.keys.action.apply")},
            {key_godown, i18n::s.get("core.ui.manual.keys.action.go_down")},
            {key_bash, i18n::s.get("core.ui.manual.keys.action.bash")},
            {key_goup, i18n::s.get("core.ui.manual.keys.action.go_up")},
            {key_dig, i18n::s.get("core.ui.manual.keys.action.dig")},
            {key_wait, i18n::s.get("core.ui.manual.keys.action.wait")},
            {key_open, i18n::s.get("core.ui.manual.keys.action.open")},
        };

        int index = 0;
        for (const auto& pair : keys)
        {
            font(desc_font_size);
            mes(x + 38 + index % 2 * 290, y + 170 + index / 2 * 14, pair.desc);
            font(key_font_size);
            mes(x + 248 + index % 2 * 290, y + 169 + index / 2 * 14, pair.key);
            ++index;
        }
    }

    // Section "Info"
    {
        display_topic(
            i18n::s.get("core.ui.manual.keys.info.title"), x + 18, y + 256);

        std::vector<KeyDescPair> keys{
            {key_charainfo, i18n::s.get("core.ui.manual.keys.info.chara")},
            {key_msglog, i18n::s.get("core.ui.manual.keys.info.log")},
            {key_journal, i18n::s.get("core.ui.manual.keys.info.journal")},
            {key_material, i18n::s.get("core.ui.manual.keys.info.material")},
            {key_help, i18n::s.get("core.ui.manual.keys.info.help")},
            {key_trait, i18n::s.get("core.ui.manual.keys.info.feat")},
        };

        int index = 0;
        for (const auto& pair : keys)
        {
            font(desc_font_size);
            mes(x + 38 + index % 2 * 290, y + 284 + index / 2 * 14, pair.desc);
            font(key_font_size);
            mes(x + 248 + index % 2 * 290, y + 283 + index / 2 * 14, pair.key);
            ++index;
        }
    }

    // Section "Other"
    {
        display_topic(
            i18n::s.get("core.ui.manual.keys.other.title"), x + 18, y + 328);

        std::vector<KeyDescPair> keys{
            {key_save, i18n::s.get("core.ui.manual.keys.other.save")},
            {key_close, i18n::s.get("core.ui.manual.keys.other.close")},
            {key_pray, i18n::s.get("core.ui.manual.keys.other.pray")},
            {key_give, i18n::s.get("core.ui.manual.keys.other.give")},
            {key_offer, i18n::s.get("core.ui.manual.keys.other.offer")},
        };

        int index = 0;
        for (const auto& pair : keys)
        {
            font(desc_font_size);
            mes(x + 38 + index % 2 * 290, y + 356 + index / 2 * 14, pair.desc);
            font(key_font_size);
            mes(x + 248 + index % 2 * 290, y + 355 + index / 2 * 14, pair.key);
            ++index;
        }
    }

    // Misc.
    // TODO: support key bindings!
    const auto misc_keys = u8"F9 "s +
        i18n::s.get("core.ui.manual.keys.other.hide_interface") + u8"  F11 " +
        i18n::s.get("core.ui.manual.keys.other.export_chara_sheet") +
        u8"  F12 " + i18n::s.get("core.ui.manual.keys.other.console");
    font(desc_font_size);
    mes(x + 38, y + 408, misc_keys);
}



void UIMenuGameHelp::_draw_regular_pages()
{
    const auto& topic = listn(0, pagesize * page_bk + cs_bk2);
    display_topic(topic, wx + 206, wy + 36);

    font(14 - en * 2);
    const auto section_index = list(0, pagesize * page_bk + cs_bk2);
    int y = wy + 60;
    for (const auto& line : _help.get_section(section_index))
    {
        const auto ny = gmes(line, wx + 216, y, 510, {30, 30, 30}, false).y;
        y = ny;
    }
}



void UIMenuGameHelp::_draw_navigation_menu()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        const auto& section = listn(0, p);
        cs_list(cs == cnt, section, wx + 66, wy + 66 + cnt * 19 - 1);
    }

    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}



void UIMenuGameHelp::_draw_background_vignette(int id, int type)
{
    cmbg = id;
    x = ww / 5 * 2;
    y = wh - 80;
    gmode(2, 50);
    gcopy_c(
        type,
        cmbg % 4 * 180,
        cmbg / 4 % 2 * 300,
        180,
        300,
        wx + ww / 4,
        wy + wh / 2,
        x,
        y);
    gmode(2);
}



void UIMenuGameHelp::update()
{
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
        page = pagemax;
    else if (page > pagemax)
        page = 0;

    _redraw = true;
}


void UIMenuGameHelp::_draw_window()
{
    int y;
    if (mode == Mode::new_game)
    {
        y = winposy(496, 1);
    }
    else
    {
        y = winposy(496) - 24;
    }
    ui_display_window(
        u8"Elona In-Game Help",
        strhint2 + strhint3b,
        (windoww - 780) / 2 + inf_screenx,
        y,
        780,
        496);
    display_topic(i18n::s.get("core.ui.manual.topic"), wx + 34, wy + 36);

    _draw_background_vignette(page % 5, mode == Mode::new_game ? 2 : 4);
    keyrange = 0;

    // Moves and refresh cursor
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
            break;
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
    }

    // Draws the first page, key lists, in a specific way
    if (cs_bk2 == 0 && page_bk == 0)
        _draw_key_list();
    else
        _draw_regular_pages();
}



void UIMenuGameHelp::draw()
{
    if (_redraw)
    {
        _draw_window();
        _draw_navigation_menu();
        _redraw = false;
    }
}



optional<UIMenuGameHelp::ResultType> UIMenuGameHelp::on_key(
    const std::string& action)
{
    // Key selection
    if (auto selected = get_selected_index_this_page())
    {
        cs = *selected;
        snd("core.ok1");
        page_bk = page;
        cs_bk2 = cs;
        set_reupdate();
    }

    if (cs != cs_bk)
    {
        set_reupdate();
    }

    // Page changes
    if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            ++page;
            set_reupdate();
        }
    }
    if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            --page;
            set_reupdate();
        }
    }

    // Closing menu
    if (action == "cancel")
    {
        return UIMenuGameHelp::ResultType::finish();
    }
    return none;
}



void UIMenuGameHelp::GameHelp::load(const fs::path& filepath)
{
    constexpr const char* section_marker = u8"{}";

    for (const auto& line : fileutil::read_by_line(filepath))
    {
        const auto section_marker_pos = line.find(section_marker);
        if (section_marker_pos != std::string::npos)
        {
            _section_headings.emplace_back(line, section_marker_pos + 3);
            _sections.emplace_back();
        }
        else
        {
            if (_sections.empty())
            {
                continue; // Skip this line.
            }
            _sections.back().push_back(line);
        }
    }
}

} // namespace ui
} // namespace elona
