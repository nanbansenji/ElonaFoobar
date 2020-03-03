#include "blending.hpp"

#include "ability.hpp"
#include "activity.hpp"
#include "audio.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "config.hpp"
#include "data/types/type_item.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "enums.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "map_cell.hpp"
#include "message.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

int step;
elona_vector2<int> rpdata;
elona_vector2<std::string> rfnameorg;
elona_vector1<std::string> rpdatan;
elona_vector1<int> rpref;
int rpid = 0;
int rpmode = 0;
elona_vector1<int> rppage;
int rpresult = 0;



void window_recipe(optional_ref<Item> item, int x, int y, int width, int height)
{
    elona_vector1<std::string> s_;
    int xfix2_ = 0;
    int dx_ = 0;
    int dy_ = 0;
    int i_ = 0;

    if (windowshadow == 1)
    {
        window(x + 4, y + 4, width, height - height % 8, true);
        boxf(x + width - 522, 0, 486, 69, {30, 30, 30});
        windowshadow = 0;
    }
    window(x, y, width, height - height % 8);
    window_recipe2();
    gmode(2);
    line(
        x + 50 + 0,
        y + height - 48 - height % 8,
        x + width - 40,
        y + height - 48 - height % 8,
        {194, 170, 146});
    line(
        x + 50 + 0,
        y + height - 49 - height % 8,
        x + width - 40,
        y + height - 49 - height % 8,
        {234, 220, 188});
    s_(0) = u8"Page."s + (rppage + 1) + u8"/"s + (rppage(1) + 1);
    s_(1) = ""s + key_prev + u8","s + key_next + ""s +
        i18n::s.get("core.blending.recipe.hint");
    if (step == -1)
    {
        s_(1) += strhint3;
    }
    else
    {
        s_(1) += strhint3b;
    }
    font(12 + sizefix - en * 2);
    mes(x + 25 + 0, y + height - 43 - height % 8, s_(1));
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    mes(x + width - strlen_u(s_) * 7 - 40 - xfix2_,
        y + height - 65 - height % 8,
        s_);
    dx_ = x + 35;
    dy_ = y + 48;
    font(12 - en * 2, snail::Font::Style::bold);
    mes(dx_ - 10, dy_, i18n::s.get("core.blending.window.procedure"));
    dy_ = dy_ + 18;
    font(13 - en * 2);
    i_ = 1;
    if (step == i_ - 2)
    {
        boxf(dx_ - 10, dy_ - 2, width - 60, 17, {60, 20, 10, 32});
    }
    else if (step > i_ - 2)
    {
        boxf(dx_ - 10, dy_ - 2, width - 60, 17, {20, 20, 20, 32});
    }
    if (step == -1)
    {
        mes(dx_,
            dy_,
            ""s + i_ + u8"."s +
                i18n::s.get("core.blending.window.choose_a_recipe"));
    }
    else
    {
        mes(dx_,
            dy_,
            ""s + i_ + u8"."s +
                i18n::s.get(
                    "core.blending.window.chose_the_recipe_of", rpname(rpid)));
    }
    dy_ += 17;
    ++i_;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (rpdata(20 + cnt, rpid) == 0)
        {
            break;
        }
        if (step == i_ - 2)
        {
            boxf(dx_ - 10, dy_ - 2, width - 60, 17, {60, 20, 10, 32});
        }
        else if (step > i_ - 2)
        {
            boxf(dx_ - 10, dy_ - 2, width - 60, 17, {20, 20, 20, 32});
        }
        if (step <= cnt)
        {
            int stat = blendmatnum(rpdata(20 + cnt, rpid), cnt);
            s_ = i18n::s.get("core.blending.window.add", rpmatname(cnt), stat);
        }
        else
        {
            s_ = i18n::s.get(
                "core.blending.window.selected", inv[rpref(10 + cnt * 2)]);
            s_ = strmid(s_, 0, 44);
        }
        mes(dx_, dy_, ""s + i_ + u8"."s + s_);
        dy_ += 17;
        ++i_;
    }
    draw("deco_blend_b", wx + ww + 243, wy - 4);
    if (step == i_ - 2)
    {
        boxf(dx_ - 10, dy_ - 2, width - 60, 17, {60, 20, 10, 32});
    }
    else if (step > i_ - 2)
    {
        boxf(dx_ - 10, dy_ - 2, width - 60, 17, {20, 20, 20, 32});
    }
    mes(dx_,
        dy_,
        ""s + i_ + u8"."s + i18n::s.get("core.blending.window.start"));
    dy_ += 30;
    if (rppage == 0)
    {
        font(12 - en * 2, snail::Font::Style::bold);
        mes(dx_ - 10,
            dy_,
            i18n::s.get("core.blending.window.the_recipe_of", rpname(rpid)));
        dy_ += 20;
        mes(dx_ - 10, dy_, i18n::s.get("core.blending.window.required_skills"));
        dy_ = dy_ + 18;
        font(13 - en * 2);
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            if (rpdata(10 + cnt * 2, rpid) == 0)
            {
                break;
            }
            const auto text_color = (rpdata(11 + cnt * 2, rpid) >
                                     sdata(rpdata(10 + cnt * 2, rpid), 0))
                ? snail::Color{150, 0, 0}
                : snail::Color{0, 120, 0};
            mes(dx_ + cnt % 2 * 140,
                dy_ + cnt / 2 * 17,
                i18n::s.get_m(
                    "ability",
                    the_ability_db
                        .get_id_from_legacy(rpdata(10 + cnt * 2, rpid))
                        ->get(),
                    "name") +
                    u8"  "s + rpdata((11 + cnt * 2), rpid) + u8"("s +
                    sdata(rpdata((10 + cnt * 2), rpid), 0) + u8")"s,
                text_color);
        }
        dy_ += 50;
        font(12 - en * 2, snail::Font::Style::bold);
        mes(dx_ - 10,
            dy_,
            i18n::s.get("core.blending.window.required_equipment"));
        return;
    }

    if (!item)
        return;

    font(12 - en * 2, snail::Font::Style::bold);
    mes(dx_ - 10, dy_, itemname(item->index));
    dy_ += 20;
    font(13 - en * 2);
    if (item->identify_state <= IdentifyState::partly)
    {
        mes(dx_, dy_, i18n::s.get("core.blending.window.havent_identified"));
        dy_ += 16;
        return;
    }

    const auto inheritance = item_get_inheritance(*item);
    if (inheritance.empty())
    {
        mes(dx_, dy_, i18n::s.get("core.blending.window.no_inherited_effects"));
    }
    else
    {
        for (const auto& inh : inheritance)
        {
            if (item->enchantments[inh].id == 0)
                break;

            get_enchantment_description(
                item->enchantments[inh].id,
                item->enchantments[inh].power,
                the_item_db[itemid2int(item->id)]->category);
            const auto text_color = item->enchantments[inh].power < 0
                ? snail::Color{180, 0, 0}
                : snail::Color{0, 0, 100};
            mes(dx_, dy_, cnven(s), text_color);
            dy_ += 16;
        }
    }
}



int calc_max_number_of_products_you_can_blend(int recipe_id)
{
    int ret = 10;
    for (int i = 0; i < 10; ++i)
    {
        const auto item_index = rpref(10 + i * 2);
        if (item_index == -1)
        {
            break;
        }
        if (rpdata(2, recipe_id) == 2 && i == 0)
        {
            continue;
        }
        if (inv[item_index].number() < ret)
        {
            ret = inv[item_index].number();
        }
    }
    return ret;
}



bool all_ingredient_are_added(int step, int recipe_id)
{
    return step != -1 && rpdata(20 + step, recipe_id) == 0;
}



optional<TurnResult> blending_menu_1()
{
    elona_vector1<int> blendchecklist;

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
            DIM2(blendchecklist, pagesize);
            for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
            {
                p = pagesize * page + cnt;
                if (p >= listmax)
                {
                    break;
                }
                blendchecklist(cnt) = blendcheckmat(list(0, p));
            }
        }

        windowshadow = windowshadow(1);
        ui_display_window(
            i18n::s.get("core.blending.recipe.title"),
            strhint2,
            (windoww - 780) / 2 + inf_screenx,
            winposy(445),
            380,
            432,
            74);
        display_topic(
            i18n::s.get("core.blending.recipe.name"), wx + 28, wy + 30);
        s = i18n::s.get("core.blending.recipe.counter", listmax);
        font(12 + sizefix - en * 2, snail::Font::Style::bold);
        mes(wx + 130, wy + wh - 65 - wh % 8, s);
        keyrange = 0;
        gmode(2);
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * page + cnt;
            if (p >= listmax)
            {
                break;
            }
            key_list(cnt) = key_select(cnt);
            ++keyrange;
            if (cnt % 2 == 0)
            {
                boxf(
                    wx + 70,
                    wy + 60 + cnt * 19,
                    ww - 100,
                    18,
                    {12, 14, 16, 16});
            }

            draw_item_material(
                550, wx + 37, wy + 70 + cnt * 19); // Recipe image

            if (blendchecklist(cnt) == 1)
            {
                draw("blend_ingredient", wx + 330, wy + 53 + cnt * 19);
            }
            rpid = list(0, p);

            int difficulty = (4 - rpdiff(rpid, -1, -1) / 25);
            draw_indexed(
                "recipe_difficulty", wx + 317, wy + 60 + cnt * 19, difficulty);
        }
        font(14 - en * 2);
        cs_listbk();
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * page + cnt;
            if (p >= listmax)
            {
                break;
            }
            p = list(0, p);
            rpid = p;
            s = i18n::s.get("core.blending.recipe.of", cnven(rpname(rpid)));
            display_key(wx + 58, wy + 60 + cnt * 19 - 2, cnt);
            cs_list(cs == cnt, s, wx + 84, wy + 60 + cnt * 19 - 1);
        }
        if (cs_bk != cs)
        {
            rpid = list(0, pagesize * page + cs);
            windowshadow = windowshadow(1);
            window_recipe(none, wx + ww, wy, 400, wh);
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        windowshadow(1) = 0;
        draw("deco_blend_c", wx + 10, wy + wh - 100);
        redraw();

        const auto action = get_selected_item(p(0));
        if (p != -1)
        {
            rpid = p;
            step = 0;
            rppage(0) = 1;
            rppage(1) = 1;
            rpref(0) = rpid;
            return none;
        }
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
            screenupdate = 0;
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
    }
}



void blending_menu_2()
{
    while (true)
    {
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
        windowshadow = windowshadow(1);
        ui_display_window(
            i18n::s.get(
                "core.blending.steps.add_ingredient_prompt", rpmatname(step)),
            strhint2,
            (windoww - 780) / 2 + inf_screenx,
            winposy(445),
            380,
            432,
            74);
        display_topic(
            i18n::s.get("core.blending.steps.item_name"), wx + 28, wy + 30);
        s = i18n::s.get("core.blending.steps.item_counter", listmax);
        font(12 + sizefix - en * 2, snail::Font::Style::bold);
        mes(wx + 130, wy + wh - 65 - wh % 8, s);
        keyrange = 0;
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * page + cnt;
            if (p >= listmax)
            {
                break;
            }
            key_list(cnt) = key_select(cnt);
            ++keyrange;
            if (cnt % 2 == 0)
            {
                boxf(
                    wx + 70,
                    wy + 60 + cnt * 19,
                    ww - 100,
                    18,
                    {12, 14, 16, 16});
            }
        }
        font(14 - en * 2);
        cs_listbk();
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * page + cnt;
            if (p >= listmax)
            {
                break;
            }
            p = list(0, p);
            s = itemname(p, inv[p].number());
            s = strmid(s, 0, 28);
            if (p >= ELONA_ITEM_ON_GROUND_INDEX)
            {
                s += i18n::s.get("core.blending.steps.ground");
            }
            display_key(wx + 58, wy + 60 + cnt * 19 - 2, cnt);

            draw_item_with_portrait_scale_height(
                inv[p], wx + 37, wy + 69 + cnt * 19);

            if (inv[p].body_part != 0)
            {
                draw("equipped", wx + 46, wy + 72 + cnt * 18 - 3);
            }
            cs_list(
                cs == cnt,
                s,
                wx + 84,
                wy + 60 + cnt * 19 - 1,
                0,
                cs_list_get_item_color(inv[p]));
        }
        p = list(0, pagesize * page + cs);
        if (listmax == 0)
        {
            p = -1;
        }
        if (cs_bk != cs)
        {
            windowshadow = windowshadow(1);
            window_recipe(
                p == -1 ? none : optional_ref<Item>(inv[p]),
                wx + ww,
                wy,
                400,
                wh);
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        windowshadow(1) = 0;
        draw("deco_blend_c", wx + 10, wy + wh - 100);
        redraw();

        const auto action = get_selected_item(p(0));
        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                continue;
            }
        }
        if (p != -1)
        {
            ci = p;
            if (inv[ci].is_marked_as_no_drop())
            {
                snd("core.fail1");
                txt(i18n::s.get("core.ui.inv.common.set_as_no_drop"));
                continue;
            }
            rpref(10 + step * 2 + 0) = ci;
            rpref(10 + step * 2 + 1) = itemid2int(inv[ci].id);
            snd("core.drink1");
            txt(i18n::s.get("core.blending.steps.you_add", inv[ci]));
            ++step;
            p = rpdiff(rpid, step, step - 1);
            return;
        }
        if (action == "previous_menu")
        {
            snd("core.pop1");
            --rppage;
            cs_bk = -1;
            if (rppage < 0)
            {
                rppage = rppage(1);
            }
        }
        if (action == "next_menu")
        {
            snd("core.pop1");
            ++rppage;
            cs_bk = -1;
            if (rppage > rppage(1))
            {
                rppage = 0;
            }
        }
        if (action == "cancel")
        {
            --step;
            return;
        }
    }
}

} // namespace



void activity_blending()
{
    while (true)
    {
        rpid = rpref(0);
        if (rpid == 0)
        {
            cdata[cc].activity.finish();
            return;
        }
        if (!cdata[cc].activity)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.blending.started", cdata[cc], rpname(rpid)));
            cdata[cc].activity.type = Activity::Type::blend;
            cdata[cc].activity.turn = rpref(2) % 10000;
            return;
        }
        if (cdata[cc].activity.turn > 0)
        {
            if (rnd(30) == 0)
            {
                txt(i18n::s.get("core.blending.sounds"),
                    Message::color{ColorIndex::blue});
            }
            return;
        }
        if (rpref(2) >= 10000)
        {
            cdata[cc].activity.turn = rpref(2) / 10000;
            for (int cnt = 0;; ++cnt)
            {
                mode = Mode::blending;
                ++game_data.date.hour;
                weather_changes();
                render_hud();
                if (cnt % 5 == 0)
                {
                    txt(i18n::s.get("core.blending.sounds"),
                        Message::color{ColorIndex::blue});
                }
                redraw();
                await(g_config.animation_wait() * 5);
                game_data.date.minute = 0;
                cc = 0;
                --cdata[cc].activity.turn;
                if (cdata[cc].activity.turn <= 0)
                {
                    int stat = blending_find_required_mat();
                    if (stat == 0)
                    {
                        txt(i18n::s.get(
                            "core.blending.required_material_not_found"));
                        break;
                    }
                    blending_start_attempt();
                    if (rpref(1) > 0)
                    {
                        cdata[cc].activity.turn = rpref(2) / 10000;
                        cnt = 0 - 1;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            cdata[cc].activity.finish();
            mode = Mode::zero_default;
            return;
        }
        int stat = blending_find_required_mat();
        if (stat == 0)
        {
            txt(i18n::s.get("core.blending.required_material_not_found"));
            cdata[cc].activity.finish();
            return;
        }
        blending_start_attempt();
        if (rpref(1) > 0)
        {
            cdata[cc].activity.type = Activity::Type::none;
        }
        else
        {
            break;
        }
    }

    cdata[cc].activity.finish();
}



void initialize_recipememory()
{
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        recipememory(200 + cnt) = 1;
    }
}

void initialize_recipe()
{
    DIM3(rpdata, 100, 1200);
    SDIM4(rfnameorg, 20, 2, 6);
    SDIM3(rpdatan, 40, 1200);
    DIM2(rpref, 100);
    rpsourcelist(0) = 0;
    rpsourcelist(1) = 898;
    rpsourcelist(2) = 1156;
    rpsourcelist(3) = 1187;
    rpsourcelist(4) = 209;
    rpsourcelist(5) = 210;
    rpid = 200;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10000;
    rpdata(1, rpid) = 10;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 8;
    rpdata(12, rpid) = 178;
    rpdata(13, rpid) = 3;
    rpdata(20, rpid) = 57000;
    rpdata(21, rpid) = 620;
    rpid = 201;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10001;
    rpdata(1, rpid) = 4;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 6;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 519;
    rpid = 202;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10002;
    rpdata(1, rpid) = 7;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 3;
    rpdata(20, rpid) = 57000;
    rpdata(21, rpid) = 262;
    rpid = 203;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10003;
    rpdata(1, rpid) = 15;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 18;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 736;
    rpid = 204;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10004;
    rpdata(1, rpid) = 15;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 10;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 566;
    rpid = 205;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10005;
    rpdata(1, rpid) = 10;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 185;
    rpdata(11, rpid) = 2;
    rpdata(12, rpid) = 12;
    rpdata(13, rpid) = 10;
    rpdata(20, rpid) = 342;
    rpdata(21, rpid) = 617;
    rpid = 206;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10006;
    rpdata(1, rpid) = 5;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 5;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 516;
    rpid = 207;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10007;
    rpdata(1, rpid) = 3;
    rpdata(2, rpid) = 2;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 3;
    rpdata(20, rpid) = 60001;
    rpdata(21, rpid) = 52000;
    rpid = 208;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10008;
    rpdata(1, rpid) = 16;
    rpdata(2, rpid) = 2;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 24;
    rpdata(20, rpid) = 60001;
    rpdata(21, rpid) = 601;
    rpid = 209;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10009;
    rpdata(1, rpid) = 16;
    rpdata(2, rpid) = 2;
    rpdata(10, rpid) = 178;
    rpdata(11, rpid) = 999;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 9004;
    rpid = 210;
    rpdatan(rpid) = i18n::s.get_enum("core.blending.recipe", rpid);
    rpdata(0, rpid) = 10009;
    rpdata(1, rpid) = 16;
    rpdata(2, rpid) = 2;
    rpdata(10, rpid) = 178;
    rpdata(11, rpid) = 999;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 9004;
    rpdata(22, rpid) = 9004;
    rpid = 898;
    rpdata(0, rpid) = 498;
    rpdata(1, rpid) = 150060;
    rpdata(10, rpid) = 175;
    rpdata(11, rpid) = 4;
    rpdata(12, rpid) = 457;
    rpdata(13, rpid) = 20;
    rpdata(14, rpid) = 12;
    rpdata(15, rpid) = 8;
    rpdata(30, rpid) = 0;
    rpdata(20, rpid) = 260;
    rpdata(21, rpid) = 9001;
    rpid = 1156;
    rpdata(0, rpid) = 756;
    rpdata(1, rpid) = 20020;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 4;
    rpdata(12, rpid) = 179;
    rpdata(13, rpid) = 20;
    rpdata(14, rpid) = 157;
    rpdata(15, rpid) = 8;
    rpdata(30, rpid) = 0;
    rpdata(20, rpid) = 260;
    ++rpid;
    rpid = 1187;
    rpdata(0, rpid) = 787;
    rpdata(1, rpid) = 30;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 10;
    rpdata(12, rpid) = 178;
    rpdata(13, rpid) = 5;
    rpdata(30, rpid) = 0;
    rpdata(20, rpid) = 9004;
    rpid = 1191;
    rpdata(0, rpid) = 791;
    rpdata(1, rpid) = 160045;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 10;
    rpdata(12, rpid) = 178;
    rpdata(13, rpid) = 65;
    rpdata(14, rpid) = 10;
    rpdata(15, rpid) = 105;
    rpdata(30, rpid) = 0;
    rpdata(20, rpid) = 10000;
    rpdata(21, rpid) = 748;
    rpdata(22, rpid) = 716;
    rpid = 1192;
    rpdata(0, rpid) = 792;
    rpdata(1, rpid) = 10024;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 20;
    rpdata(12, rpid) = 0;
    rpdata(13, rpid) = 10;
    rpdata(14, rpid) = 151;
    rpdata(15, rpid) = 5;
    rpdata(30, rpid) = 0;
    rpdata(20, rpid) = 204;
    rpdata(21, rpid) = 9005;
    rpdata(40, rpid) = 10003;
    rpdata(50, rpid) = 10017;
    rpdata(51, rpid) = 500;
    rpdata(52, rpid) = 60017;
    rpdata(53, rpid) = 500;
    rpdata(54, rpid) = 10010;
    rpdata(55, rpid) = 100;
    rpdata(56, rpid) = 60010;
    rpdata(57, rpid) = 100;
    rpdata(58, rpid) = 10016;
    rpdata(59, rpid) = 300;
    rpdata(60, rpid) = 60016;
    rpdata(61, rpid) = 300;
    rpdata(62, rpid) = 10011;
    rpdata(63, rpid) = 200;
    rpdata(64, rpid) = 60011;
    rpdata(65, rpid) = 200;
    rfnameorg(0, 1) = u8"flavor"s;
    rfnameorg(1, 1) = i18n::s.get_enum("core.blending.ingredient", 1);
    rfnameorg(0, 2) = u8"ore"s;
    rfnameorg(1, 2) = i18n::s.get_enum("core.blending.ingredient", 2);
    rfnameorg(0, 3) = u8"wood"s;
    rfnameorg(1, 3) = i18n::s.get_enum("core.blending.ingredient", 3);
    rfnameorg(0, 5) = u8"fish"s;
    rfnameorg(1, 5) = i18n::s.get_enum("core.blending.ingredient", 4);
    rfnameorg(0, 4) = "";
    rfnameorg(1, 4) = i18n::s.get_enum("core.blending.ingredient", 5);
}

void window_recipe2(int val0)
{
    int x_at_m183 = 0;
    int w_at_m183 = 0;
    int dx_at_m183 = 0;
    int dy_at_m183 = 0;
    std::string s_at_m183;
    int p_at_m183 = 0;
    x_at_m183 = wx + ww;
    w_at_m183 = 400;
    gmode(2);
    draw("deco_blend_a", x_at_m183 + w_at_m183 - 520, 0);
    dx_at_m183 = x_at_m183 + w_at_m183 - 500;
    dy_at_m183 = 10;
    font(15 - en * 2, snail::Font::Style::bold);
    s_at_m183 = ""s + rpsuccessrate(rpdiff(rpid, step, -1));
    bmes(
        i18n::s.get("core.blending.rate_panel.success_rate", s_at_m183),
        dx_at_m183 + 140,
        dy_at_m183,
        {235, 235, 235},
        {30, 30, 30});
    p_at_m183 = rpdata(1, rpid);
    if (rpmode)
    {
        if (p_at_m183 < 10000)
        {
            p_at_m183 = p_at_m183 * val0;
        }
        else
        {
            p_at_m183 = p_at_m183 % 10000;
        }
        p_at_m183 += rpdata(1, rpid) / 10000 * val0 * 10000;
    }
    s_at_m183 =
        i18n::s.get("core.blending.rate_panel.turns", p_at_m183 % 10000);
    if (p_at_m183 >= 10000)
    {
        s_at_m183 += i18n::s.get(
            "core.blending.rate_panel.and_hours", p_at_m183 / 10000);
    }
    bmes(
        i18n::s.get("core.blending.rate_panel.required_time", s_at_m183),
        dx_at_m183 + 140,
        dy_at_m183 + 20,
        {235, 235, 235},
        {40, 40, 40});
}



TurnResult blending_menu()
{
    std::string action;
    step = -1;
    rpid = 0;
    asset_load("deco_blend");
    gsel(0);
    clear_rprefmat();

    while (true)
    {
        if (all_ingredient_are_added(step, rpid))
        {
            rppage = 0;
            window_recipe(none, wx + ww, wy, 400, wh);
            Message::instance().linebreak();
            txt(i18n::s.get("core.blending.prompt.how_many"));

            p = calc_max_number_of_products_you_can_blend(rpid);

            rpmode = 1;
            PromptWithNumber prompt(p(0), "core.blending.prompt");
            prompt.append("start", snail::Key::key_a);
            prompt.append("go_back", snail::Key::key_b);
            prompt.append("from_the_start", snail::Key::key_c);
            const auto result = prompt.query(promptx, prompty, 220);
            rtval = result.index;
            rpmode = 0;

            if (rtval == 0) // start
            {
                rpref(1) = result.number;
                rpref(2) = rpdata(1, rpid);
                rpref(3) = rpdiff(rpid, step, -1);
                activity_blending();
                return TurnResult::turn_end;
            }
            else if (rtval == 2) // from the start
            {
                step = -1;
                continue;
            }
            else
            {
                --step; // go back
                continue;
            }
        }

        page = 0;
        pagesize = 16;
        listmax = 0;
        cs = 0;
        cs_bk = -1;
        cc = 0;
        screenupdate = -1;
        update_screen();

        if (step == -1)
        {
            rppage(0) = 0;
            rppage(1) = 0;
            listmax = 0;
            for (int cnt = 0; cnt < 1200; ++cnt)
            {
                if (rpdata(0, cnt) == 0)
                {
                    continue;
                }
                if (recipememory(cnt) > 0)
                {
                    list(0, listmax) = cnt;
                    list(1, listmax) = cnt;
                    ++listmax;
                }
            }
            sort_list_by_column1();
            windowshadow(1) = 1;
            Message::instance().linebreak();
            txt(i18n::s.get("core.blending.recipe.warning"));
            Message::instance().linebreak();
            txt(i18n::s.get("core.blending.recipe.which"));
            if (const auto result = blending_menu_1())
            {
                return *result;
            }
            else
            {
                continue;
            }
        }
        else
        {
            rppage = 1;
            listmax = blendlist(list, step);
            sort_list_by_column1();

            windowshadow(1) = 1;
            Message::instance().linebreak();
            txt(i18n::s.get(
                "core.blending.steps.add_ingredient", rpmatname(step)));
            blending_menu_2();
        }
    }
}



std::string rpmatname(int step)
{
    std::string s_at_m177;
    int p_at_m177 = 0;
    s_at_m177 = u8"?????"s;
    if (rpdata(20 + step, rpid) < 9000)
    {
        s_at_m177 = ioriginalnameref(rpdata(20 + step, rpid));
    }
    else if (rpdata(20 + step, rpid) < 10000)
    {
        s_at_m177 = rfnameorg(1, rpdata(20 + step, rpid) - 9000);
    }
    else
    {
        s_at_m177 = fltname(rpdata(20 + step, rpid));
    }
    if (rpdata(40 + step, rpid) == 0)
    {
        return s_at_m177;
    }
    if (rpdata(40 + step, rpid) >= 10000)
    {
        p_at_m177 = rpdata((40 + step), rpid) % 10000;
        if (p_at_m177 < 0 || p_at_m177 >= 800)
        {
            s_at_m177 += u8"/bugged/"s;
            return s_at_m177;
        }
        s_at_m177 = i18n::s.get(
            "core.blending.ingredient.corpse",
            chara_db_get_name(int2charaid(p_at_m177)));
        return s_at_m177;
    }
    return s_at_m177;
}



std::string rpsuccessrate(int success_rate)
{
    if (success_rate == 100)
    {
        return i18n::s.get("core.blending.success_rate.perfect");
    }
    if (success_rate >= 90)
    {
        return i18n::s.get("core.blending.success_rate.piece_of_cake");
    }
    if (success_rate >= 80)
    {
        return i18n::s.get("core.blending.success_rate.very_likely");
    }
    if (success_rate >= 70)
    {
        return i18n::s.get("core.blending.success_rate.no_problem");
    }
    if (success_rate >= 60)
    {
        return i18n::s.get("core.blending.success_rate.probably_ok");
    }
    if (success_rate >= 50)
    {
        return i18n::s.get("core.blending.success_rate.maybe");
    }
    if (success_rate >= 40)
    {
        return i18n::s.get("core.blending.success_rate.bad");
    }
    if (success_rate >= 30)
    {
        return i18n::s.get("core.blending.success_rate.very_bad");
    }
    if (success_rate >= 20)
    {
        return i18n::s.get("core.blending.success_rate.almost_impossible");
    }
    return i18n::s.get("core.blending.success_rate.impossible");
}



std::string rpname(int recipe_id)
{
    std::string s_at_m62;
    s_at_m62 = u8"?????"s;
    if (rpdatan(recipe_id) != ""s)
    {
        return rpdatan(recipe_id);
    }
    if (recipe_id >= 400)
    {
        return ioriginalnameref(recipe_id - 400);
    }
    return s_at_m62;
}



int rpdiff(int, int number_of_ingredients, int current_step)
{
    int p1_at_m180 = 0;
    int f_at_m180 = 0;
    int f2_at_m180 = 0;
    int i_at_m180 = 0;
    int d_at_m180 = 0;
    int p_at_m180 = 0;
    p1_at_m180 = 80;
    f_at_m180 = 100;
    if (number_of_ingredients > 0)
    {
        for (int cnt = 0, cnt_end = (number_of_ingredients); cnt < cnt_end;
             ++cnt)
        {
            f2_at_m180 = 0;
            if (rpref(10 + cnt * 2) == -1)
            {
                break;
            }
            i_at_m180 = rpref(10 + cnt * 2);
            if (inv[i_at_m180].curse_state == CurseState::blessed)
            {
                f2_at_m180 -= 10;
            }
            if (is_cursed(inv[i_at_m180].curse_state))
            {
                f2_at_m180 += 20;
            }
            f_at_m180 += f2_at_m180;
            if (current_step == cnt)
            {
                while (1)
                {
                    if (f2_at_m180 < 0)
                    {
                        txt(i18n::s.get("core.blending.success_rate.goes_up"),
                            Message::color{ColorIndex::green});
                        break;
                    }
                    if (f2_at_m180 > 0)
                    {
                        txt(i18n::s.get("core.blending.success_rate.goes_down"),
                            Message::color{ColorIndex::red});
                        break;
                    }
                    break;
                }
            }
        }
    }
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        if (rpdata(10 + cnt * 2, rpid) == 0)
        {
            break;
        }
        if (sdata(rpdata(10 + cnt * 2, rpid), 0) <= 0)
        {
            p1_at_m180 -= 125;
            continue;
        }
        d_at_m180 = rpdata(11 + cnt * 2, rpid);
        if (number_of_ingredients > 0)
        {
            d_at_m180 = d_at_m180 * f_at_m180 / 100;
            if (d_at_m180 < 1)
            {
                d_at_m180 = 1;
            }
        }
        p_at_m180 =
            (d_at_m180 * 200 / sdata(rpdata((10 + cnt * 2), rpid), 0) - 200) *
            -1;
        if (p_at_m180 > 0)
        {
            p_at_m180 /= 5;
        }
        if (p_at_m180 < -125)
        {
            p_at_m180 = -125;
        }
        p1_at_m180 += p_at_m180;
    }
    if (p1_at_m180 < 25)
    {
        p1_at_m180 = 0;
    }
    if (p1_at_m180 > 100)
    {
        p1_at_m180 = 100;
    }
    return p1_at_m180;
}



int blendcheckext(int item_index, int step)
{
    int p_at_m178 = 0;
    if (rpdata(40 + step, rpid) >= 10000)
    {
        p_at_m178 = rpdata((40 + step), rpid) % 10000;
        if (p_at_m178 < 0 || p_at_m178 >= 800)
        {
            return 0;
        }
        if (inv[item_index].subname == p_at_m178)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}



int blendcheckmat(int recipe_id)
{
    int f_at_m181 = 0;
    int step_at_m181 = 0;
    int id_at_m181 = 0;
    int rp_at_m181 = 0;
    int o_at_m181 = 0;
    rpid = recipe_id;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (rpdata(20 + cnt, rpid) == 0)
        {
            break;
        }
        f_at_m181 = 0;
        step_at_m181 = cnt;
        id_at_m181 = rpdata(20 + cnt, rpid);
        rp_at_m181 = cnt;
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            if (cnt == 0)
            {
                o_at_m181 = -1;
            }
            if (cnt == 1)
            {
                o_at_m181 = 0;
            }
            for (const auto& item : o_at_m181 == -1 ? inv.ground() : inv.pc())
            {
                if (item.number() <= 0)
                {
                    continue;
                }
                if ((rpdata(2, rpid) <= 0 || step_at_m181 != 0) &&
                    item.own_state > 0)
                {
                    continue;
                }
                if (o_at_m181 == -1)
                {
                    if (dist(
                            item.position.x,
                            item.position.y,
                            cdata.player().position.x,
                            cdata.player().position.y) > 4)
                    {
                        continue;
                    }
                }
                if (rpdata(40 + rp_at_m181, rpid))
                {
                    int stat = blendcheckext(item.index, rp_at_m181);
                    if (stat == 0)
                    {
                        continue;
                    }
                }
                if (id_at_m181 < 9000)
                {
                    if (item.id == int2itemid(id_at_m181))
                    {
                        f_at_m181 = 1;
                        break;
                    }
                    continue;
                }
                if (id_at_m181 < 10000)
                {
                    if (instr(
                            the_item_db[itemid2int(item.id)]->rffilter,
                            0,
                            u8"/"s + rfnameorg(0, (id_at_m181 - 9000)) +
                                u8"/"s) != -1 ||
                        id_at_m181 == 9004)
                    {
                        f_at_m181 = 1;
                        break;
                    }
                    continue;
                }
                if (the_item_db[itemid2int(item.id)]->category == id_at_m181)
                {
                    f_at_m181 = 1;
                    break;
                }
            }
            if (f_at_m181 == 1)
            {
                break;
            }
        }
        if (f_at_m181 == 0)
        {
            break;
        }
    }
    return f_at_m181;
}



int blendmatnum(int matcher, int step)
{
    int m_at_m182 = 0;
    int o_at_m182 = 0;
    m_at_m182 = 0;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        if (cnt == 0)
        {
            o_at_m182 = -1;
        }
        if (cnt == 1)
        {
            o_at_m182 = 0;
        }
        for (const auto& item : o_at_m182 == -1 ? inv.ground() : inv.pc())
        {
            if (item.number() <= 0)
            {
                continue;
            }
            if ((rpdata(2, rpid) <= 0 || step != 0) && item.own_state > 0)
            {
                continue;
            }
            if (o_at_m182 == -1)
            {
                if (dist(
                        item.position.x,
                        item.position.y,
                        cdata.player().position.x,
                        cdata.player().position.y) > 4)
                {
                    continue;
                }
            }
            if (rpdata(40 + step, rpid))
            {
                int stat = blendcheckext(item.index, step);
                if (stat == 0)
                {
                    continue;
                }
            }
            if (matcher < 9000)
            {
                if (item.id == int2itemid(matcher))
                {
                    m_at_m182 += item.number();
                }
                continue;
            }
            if (matcher < 10000)
            {
                if (instr(
                        the_item_db[itemid2int(item.id)]->rffilter,
                        0,
                        u8"/"s + rfnameorg(0, (matcher - 9000)) + u8"/"s) !=
                        -1 ||
                    matcher == 9004)
                {
                    m_at_m182 += item.number();
                }
                continue;
            }
            if (the_item_db[itemid2int(item.id)]->category == matcher)
            {
                m_at_m182 += item.number();
                continue;
            }
        }
    }
    return m_at_m182;
}



int blendlist(elona_vector2<int>& result_array, int step)
{
    int id_at_m183 = 0;
    int m_at_m183 = 0;
    int o_at_m183 = 0;
    int reftype_at_m183 = 0;
    id_at_m183 = rpdata(20 + step, rpid);
    m_at_m183 = 0;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        if (cnt == 0)
        {
            o_at_m183 = -1;
        }
        if (cnt == 1)
        {
            o_at_m183 = 0;
        }
        for (const auto& item : o_at_m183 == -1 ? inv.ground() : inv.pc())
        {
            if (m_at_m183 >= 500)
            {
                break;
            }
            if (item.number() <= 0)
            {
                continue;
            }
            if ((rpdata(2, rpid) <= 0 || step != 0) && item.own_state > 0)
            {
                continue;
            }
            if (o_at_m183 == -1)
            {
                if (dist(
                        item.position.x,
                        item.position.y,
                        cdata.player().position.x,
                        cdata.player().position.y) > 4)
                {
                    continue;
                }
            }
            reftype_at_m183 = the_item_db[itemid2int(item.id)]->category;
            if (rpdata(40 + step, rpid))
            {
                int stat = blendcheckext(item.index, step);
                if (stat == 0)
                {
                    continue;
                }
            }
            if (id_at_m183 < 9000)
            {
                if (item.id != int2itemid(id_at_m183))
                {
                    continue;
                }
            }
            else if (id_at_m183 < 10000)
            {
                if (instr(
                        the_item_db[itemid2int(item.id)]->rffilter,
                        0,
                        u8"/"s + rfnameorg(0, (id_at_m183 - 9000)) + u8"/"s) ==
                        -1 &&
                    id_at_m183 != 9004)
                {
                    continue;
                }
            }
            else if (reftype_at_m183 != id_at_m183)
            {
                continue;
            }
            if (step > 0)
            {
                bool has_already_used = false;
                for (int i = 0; i < step; ++i)
                {
                    if (rpref(10 + i * 2) == item.index)
                    {
                        has_already_used = true;
                        break;
                    }
                }
                if (has_already_used)
                {
                    continue;
                }
            }
            result_array(0, m_at_m183) = item.index;
            result_array(1, m_at_m183) =
                reftype_at_m183 * 1000 + itemid2int(item.id);
            ++m_at_m183;
        }
    }
    return m_at_m183;
}



void clear_rprefmat()
{
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        rpref(10 + cnt * 2) = -1;
    }
}


int blending_find_required_mat()
{
    f = 1;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (rpref(10 + cnt * 2) == -1)
        {
            break;
        }
        if (rpref(10 + cnt * 2) == -2)
        {
            f = 0;
            break;
        }
        if (inv[rpref(10 + cnt * 2)].number() <= 0 ||
            inv[rpref(10 + cnt * 2)].id != int2itemid(rpref(11 + cnt * 2)))
        {
            f = 0;
            break;
        }
    }
    return f;
}

int blending_spend_materials()
{
    p = 0;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (rpref(10 + cnt * 2) == -1)
        {
            break;
        }
        if (rpref(10 + cnt * 2) == -2)
        {
            continue;
        }
        if ((rpdata(2, rpid) <= 0 || cnt != 0) && rpresult)
        {
            inv[rpref(10 + cnt * 2)].modify_number(-1);
        }
        else if (rnd(3) == 0)
        {

            txt(i18n::s.get(
                "core.blending.you_lose", inv[rpref(10 + cnt * 2)]));
            inv[rpref(10 + cnt * 2)].modify_number(-1);
        }
        if (chara_unequip(inv[rpref(10 + cnt * 2)]))
        {
            chara_refresh(0);
        }
        cell_refresh(
            inv[rpref(10 + cnt * 2)].position.x,
            inv[rpref(10 + cnt * 2)].position.y);
    }
    refresh_burden_state();
    return 1;
}

void blending_start_attempt()
{
    rpresult = 1;
    if (rpdiff(rpid, -1, -1) < rnd(100))
    {
        rpresult = 0;
        txt(i18n::s.get("core.blending.failed"),
            Message::color{ColorIndex::red});
    }
    else
    {
        if (rpdata(0, rpid) >= 10000)
        {
            blending_proc_on_success_events();
        }
        else
        {
            flt();
            nostack = 1;
            if (const auto item = itemcreate_extra_inv(
                    rpdata(0, rpid), cdata.player().position, 0))
            {
                for (int cnt = 0;; ++cnt)
                {
                    if (rpdata(50 + cnt * 2, rpid) == 0)
                    {
                        break;
                    }
                    enchantment_add(
                        *item,
                        rpdata(50 + cnt * 2, rpid),
                        rpdata(51 + cnt * 2, rpid),
                        0,
                        1);
                }
                txt(i18n::s.get("core.blending.succeeded", *item),
                    Message::color{ColorIndex::green});
                snd("core.drink1");
            }
        }
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            if (rpdata(10 + cnt * 2, rpid) == 0)
            {
                break;
            }
            chara_gain_skill_exp(
                cdata.player(),
                rpdata(10 + cnt * 2, rpid),
                50 + rpdata((11 + cnt * 2), rpid) + rpref(2) / 10000 * 25,
                2,
                50);
        }
    }
    --rpref(1);
    blending_spend_materials();
}

// TODO: Much duplication with do_dip_command()
void blending_proc_on_success_events()
{
    int cibk = ci;
    ci = rpref(10);
    ti = rpref(12);
    if (rpdata(2, rpid) == 2)
    {
        item_separate(ci);
    }
    else if (inv[ci].number() <= 1)
    {
        rpref(10) = -2;
    }
    else
    {
        int stat = item_separate(ci);
        if (rpref(10) == stat)
        {
            rpref(10) = -2;
        }
        else
        {
            rpref(10) = stat;
        }
    }
    switch (rpdata(0, rpid))
    {
    case 10000:
        inv[ci].is_aphrodisiac() = true;
        txt(i18n::s.get("core.blending.succeeded", inv[ci]),
            Message::color{ColorIndex::green});
        txt(i18n::s.get("core.action.dip.result.love_food.guilty"));
        snd("core.offer1");
        break;
    case 10001:
        inv[ci].color = inv[ti].color;
        txt(i18n::s.get("core.action.dip.result.dyeing", inv[ci]),
            Message::color{ColorIndex::green});
        snd("core.drink1");
        break;
    case 10002:
        inv[ci].is_poisoned() = true;
        txt(i18n::s.get("core.blending.succeeded", inv[ci]),
            Message::color{ColorIndex::green});
        txt(i18n::s.get("core.action.dip.result.poisoned_food"));
        snd("core.offer1");
        break;
    case 10003:
        txt(i18n::s.get("core.action.dip.result.put_on", inv[ci], inv[ti]),
            Message::color{ColorIndex::green});
        if (inv[ci].id == ItemId::fireproof_blanket)
        {
            txt(i18n::s.get("core.action.dip.result.good_idea_but"));
        }
        else
        {
            inv[ci].is_fireproof() = true;
            txt(i18n::s.get("core.action.dip.result.gains_fireproof", inv[ci]));
        }
        snd("core.drink1");
        break;
    case 10004:
        txt(i18n::s.get("core.action.dip.result.put_on", inv[ci], inv[ti]),
            Message::color{ColorIndex::green});
        inv[ci].is_acidproof() = true;
        txt(i18n::s.get("core.action.dip.result.gains_acidproof", inv[ci]));
        snd("core.drink1");
        break;
    case 10005:
        txt(i18n::s.get(
                "core.action.dip.result.bait_attachment", inv[ci], inv[ti]),
            Message::color{ColorIndex::green});
        if (inv[ci].param4 == inv[ti].param1)
        {
            inv[ci].count += rnd(10) + 15;
        }
        else
        {
            inv[ci].count = rnd(10) + 15;
            inv[ci].param4 = inv[ti].param1;
        }
        snd("core.equip1");
        break;
    case 10006:
        txt(i18n::s.get(
                "core.action.dip.result.blessed_item", inv[ci], inv[ti]),
            Message::color{ColorIndex::green});
        if (inv[ti].curse_state == CurseState::blessed)
        {
            txt(i18n::s.get("core.action.dip.result.becomes_blessed", inv[ci]),
                Message::color{ColorIndex::orange});
            inv[ci].curse_state = CurseState::blessed;
        }
        if (is_cursed(inv[ti].curse_state))
        {
            txt(i18n::s.get("core.action.dip.result.becomes_cursed", inv[ci]),
                Message::color{ColorIndex::purple});
            inv[ci].curse_state = CurseState::cursed;
        }
        snd("core.drink1");
        break;
    case 10007:
        txt(i18n::s.get(
            "core.action.dip.result.well_refill", inv[ci], inv[ti]));
        if (inv[ti].id == ItemId::empty_bottle)
        {
            txt(i18n::s.get("core.action.dip.result.empty_bottle_shatters"));
            break;
        }
        snd("core.drink1");
        if (inv[ci].id == ItemId::holy_well)
        {
            txt(i18n::s.get("core.action.dip.result.holy_well_polluted"));
            break;
        }
        if (inv[ci].param3 >= 20)
        {
            txt(i18n::s.get("core.action.dip.result.well_dry", inv[ci]));
            break;
        }
        txt(i18n::s.get("core.action.dip.result.well_refilled", inv[ci]),
            Message::color{ColorIndex::green});
        if (inv[ti].id == ItemId::handful_of_snow)
        {
            txt(i18n::s.get("core.action.dip.result.snow_melts.blending"));
        }
        else
        {
            inv[ci].param1 += rnd(3);
        }
        break;
    case 10008:
        if (inv[ci].param1 < -5 || inv[ci].param3 >= 20 ||
            (inv[ci].id == ItemId::holy_well && game_data.holy_well_count <= 0))
        {
            txt(i18n::s.get(
                "core.action.dip.result.natural_potion_dry", inv[ci]));
            txt(i18n::s.get("core.action.dip.result.natural_potion_drop"));
            break;
        }
        if (inv_getfreeid(0) == -1)
        {
            txt(i18n::s.get("core.ui.inv.common.inventory_is_full"));
            break;
        }
        cibk = ci;
        if (inv[ci].id == ItemId::holy_well)
        {
            --game_data.holy_well_count;
            flt();
            if (const auto item = itemcreate_player_inv(516, 0))
            {
                item->curse_state = CurseState::blessed;
            }
        }
        else
        {
            inv[ci].param1 -= 3;
            flt(20);
            flttypemajor = 52000;
            itemcreate_player_inv(0, 0);
        }
        txt(i18n::s.get("core.action.dip.result.natural_potion"));
        txt(i18n::s.get("core.action.dip.you_get", inv[ci]),
            Message::color{ColorIndex::green});
        item_stack(0, inv[ci], true);
        item_stack(0, inv[ci]);
        ci = cibk;
        snd("core.drink1");
        break;
    }

    item_stack(0, inv[ci]);
    if (inv[ci].body_part != 0)
    {
        create_pcpic(cdata.player());
    }
    if (inv_getowner(ci) == -1)
    {
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
    }
    chara_refresh(0);
}

} // namespace elona
