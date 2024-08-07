#pragma once
#include "grey.h"
#include <string>
#include <memory>
#include <map>
#include "../browser.h"
#include "../setup.h"
#include "url.h"
#include "../../globals.h"

namespace bt::ui {

    struct rule_match_status {
        std::string id;
        bool matched;
        size_t version;
    };

    class config_app {
    public:
        config_app();
        ~config_app();
        void run();

    private:

        const std::string RuleMatchesIcon = ICON_MD_CRUELTY_FREE;
        const std::string RuleDoesNotMatchIcon = ICON_MD_CRUELTY_FREE;

        std::unique_ptr<grey::app> app;
        std::string title;
        grey::widgets::window wnd_config;
        grey::widgets::popup pop_dash{"pop_dash"};
        grey::widgets::window wnd_about;
        bool is_open{true};
        std::map<std::string, rule_match_status> id_to_rule_match_status;
#if _DEBUG
        bool show_demo{false};
#endif
        // UI elements
        size_t selected_browser_idx{0};
        size_t selected_profile_idx{0};
        grey::widgets::container w_left_panel;
        grey::widgets::container w_right_panel;

        // "About" window
        bool show_about{false};
        float about_frame_time{60.0f};
        std::string about_fps;
        std::string about_fps_tooltip;
        std::string about_mem;
        std::string about_cpu;

        // "Health Dashboard" popup
        std::vector<system_check> health_checks;
        float health_frame_time{60.0f};
        size_t health_succeeded{0};
        size_t health_failed{0};
        void check_health();

        // "Substitutions" window
        bool show_subs{false};
        grey::widgets::window wnd_subs{"Substitutions"};
        std::vector<std::string> replacer_kinds{"string", "regex"};
        url_payload url_subs_up;

        // URL Tester
        bool show_url_tester{false};
        size_t url_tester_payload_version{0};
        url_payload url_tester_up;

        std::vector<std::string> rule_locations { "URL", "Title", "Process" };
        std::vector<std::pair<std::string, std::string>> url_scopes{
            { ICON_MD_LANGUAGE, "Match anywhere" },
            { ICON_MD_GITE, "Match only in host name" },
            { ICON_MD_ROUNDABOUT_LEFT, "Match only in path" }
        };

        bool run_frame();
        void render_menu_bar();

        bool startup_health_warned{false};
        bool startup_health_opened{false};
        void startup_health_warning();
        void render_about_window();
        void render_subs_window();
        void render_dashboard();
        void render_url_tester_input();

        void render_status_bar();
        void render_no_browsers();
        void render_browsers();
        void render_card(std::shared_ptr<bt::browser> b, bool is_selected);
        void render_detail(std::shared_ptr<bt::browser> b);

        /**
         * @brief If "path_override" is not empty, it will be used as the icon path. Otherwise, "path1" if not empty, then "path2".
         * @param path1 
         * @param path2 
         * @param path_override 
         */
        void render_icon(const std::string& path_default, bool is_incognito, std::string& path_override);
        void render_rules(std::shared_ptr<browser_instance> bi);

        void rediscover_browsers();
        void add_custom_browser_by_asking();
        void test_url();

        void recalculate_test_url_matches();

        std::shared_ptr<bt::browser_instance> get_selected_browser_instance();
    };
}