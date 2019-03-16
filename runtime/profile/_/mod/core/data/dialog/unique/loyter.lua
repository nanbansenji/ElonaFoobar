local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")

return {
   name = "loyter",
   root = "core.locale.talk.unique.loyter",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("nightmare")
         if Chara.player().fame < 20000 then
            return "fame_too_low"
         end
         if flag == 1000 then
            return "quest_completed"
         end
         if flag == 0 then
            return "quest_ask"
         end
         if flag == 1 or flag == 2 then
            return "quest_begin"
         end
         if flag == 3 then
            return "quest_finish"
         end
         return "__END__"
      end,
      fame_too_low = {
         text = {
            {"fame_too_low"}
         }
      },
      quest_completed = {
         text = {
            {"complete"}
         }
      },
      quest_ask = {
         text = {
            {"quest.dialog._0", args = function() return {Chara.player().title} end},
            {"quest.dialog._1"},
         },
         choices = {
            {"quest_yes", "quest.choices.yes"},
            {"quest_no", "quest.choices.no"}
         }
      },
      quest_yes = {
         text = {
             GUI.show_journal_update_message,
            {"quest.yes"},
         },
         on_finish = function()
            Internal.set_quest_flag("nightmare", 1)
         end
      },
      quest_no = {
         text = {
            {"quest.no"},
         }
      },
      quest_begin = {
         text = {
            {"quest.begin.dialog"},
         },
         choices = {
            {"quest_begin_yes", "quest.begin.choices.yes"},
            {"quest_begin_no", "quest.begin.choices.no"}
         }
      },
      quest_begin_yes = {
         text = {
            GUI.show_journal_update_message,
            {"quest.begin.yes"},
         },
         on_finish = function()
            Internal.set_quest_flag("nightmare", 2)
            Internal.go_to_quest_map("core.vernis", 5)
         end
      },
      quest_begin_no = {
         text = {
            {"quest.begin.no"},
         }
      },
      quest_finish = {
         text = {
            function()
               local item = Item.create(Chara.player().position, {id = "core.material_kit", nostack = true})
               item:change_material("core.rubynus")
               Item.create(Chara.player().position, "core.gold_piece", 100000)
               Item.create(Chara.player().position, "core.platinum_coin", 5)

               GUI.txt(I18N.get("core.locale.quest.completed"))
               GUI.play_sound("core.complete1")
               GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"))
               GUI.show_journal_update_message()
            end,
            {"quest.end"}
         },
         on_finish = function()
            Internal.set_quest_flag("nightmare", 1000)
         end
      }
   }
}