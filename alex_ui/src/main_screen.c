#include "Chat.h"
void *load_scc(){
    usleep(6000);
    GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "resource/styles/main_screen.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);
    usleep(3000);
    return NULL;
}
void main_screen(GtkWidget *widget, GdkEventButton *event, gpointer **activity_block) {

    if(main_data.login_box)gtk_widget_destroy(GTK_WIDGET(main_data.login_box));
    if(main_data.reg_box)gtk_widget_destroy(GTK_WIDGET(main_data.reg_box));
    if (widget) {}
    if(event->type != GDK_BUTTON_PRESS && event->button != 1){
        return;
    }
    //GtkCssProvider *styles = gtk_css_provider_new();
    //gtk_css_provider_load_from_path(styles, "resource/styles/main_screen.css", NULL);
    //gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);

    main_data.main_screen_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(main_data.main_screen_box), "main_screen");
    gtk_widget_set_size_request(GTK_WIDGET(main_data.main_screen_box), WINDOW_SIZE_X, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(activity_block), main_data.main_screen_box, 0, 0);
    
    write(2, "Braaah\n", 7);
    pthread_t display_thread = NULL;
    pthread_create(&display_thread, NULL, load_scc, NULL);
    write(2, "Braaah\n", 7);
    // Gtk fixed
    GtkWidget *main_fixed = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(main_fixed), 300, 100);
    gtk_container_add(GTK_CONTAINER(main_data.main_screen_box), main_fixed);
    
    // Chat bar
    GtkWidget *chat_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_bar), "chat_bar");
    gtk_fixed_put(GTK_FIXED(main_fixed), chat_bar, 0, 0);

    //Up box
    GtkWidget *up_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(up_box), "up_box");
    gtk_box_pack_start(GTK_BOX(chat_bar), up_box, FALSE, FALSE, 0);

        // User photo
        GtkWidget *user_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(user_avatar), 80, 80);
        char *path = strdup("resource/images/start.png");
        g_signal_connect(G_OBJECT(user_avatar), "draw", G_CALLBACK(draw_user_avatar), path);

        GtkWidget *user_photo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(user_photo), "user_photo");
        gtk_container_add(GTK_CONTAINER(user_photo), user_avatar);
        gtk_box_pack_start(GTK_BOX(up_box), user_photo, FALSE, FALSE, 0);

    //Chat list
    GtkWidget *chat_bar_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(chat_bar_scroll), 0, 0);
    gtk_box_pack_start(GTK_BOX(chat_bar), chat_bar_scroll, TRUE, TRUE, 0);   

    GtkWidget *chat_bar_for_scroll = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_bar_for_scroll), "chat_bar_for_scroll");
    gtk_container_add(GTK_CONTAINER(chat_bar_scroll), chat_bar_for_scroll);

    for(int i = 0; i < 15; i++) {
        GtkWidget *chat_button = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(chat_button), "chat_button");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(chat_button), TRUE);
        gtk_box_pack_start(GTK_BOX(chat_bar_for_scroll), chat_button, FALSE, FALSE, 0);

        GtkWidget *chat_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_box), "chat_small_box");
        gtk_widget_set_size_request(GTK_WIDGET(chat_box), 300, 70);
        gtk_container_add(GTK_CONTAINER(chat_button), chat_box);
        
        GtkWidget *left_chat_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(left_chat_avatar), 40, 40);
        char *path;
        if(i < 5) {
            path = strdup("resource/images/button.png");
        } else if(i < 10) {
            path = strdup("resource/images/start.png");
        } else {
            path = strdup("resource/images/font-emoji-svg-png-icon-free-download-389350-onlinewebfonts-play-button-image-11563230644rbzu7hlann.png");
        }
        g_signal_connect(G_OBJECT(left_chat_avatar), "draw", G_CALLBACK(draw_chat_avatar), path);

        GtkWidget* photo_chat = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(photo_chat), "left_chat_photo_box");
        gtk_container_add(GTK_CONTAINER(photo_chat), left_chat_avatar);
        //gtk_widget_set_size_request(GTK_WIDGET(photo_chat), 50, 30);
        gtk_box_pack_start(GTK_BOX(chat_box), photo_chat, FALSE, FALSE, 0);

        GtkWidget* name_chat = gtk_label_new("Lorem Ipsum");
        gtk_widget_set_name(GTK_WIDGET(name_chat), "chat_name");
        gtk_box_pack_start(GTK_BOX(chat_box), name_chat, FALSE, FALSE, 0);

        GtkWidget *key = gtk_label_new(int_to_str(i));
        gtk_box_pack_start(GTK_BOX(chat_box), key, FALSE, FALSE, 0);
        gtk_widget_set_name(GTK_WIDGET(key), "hidden");

        g_signal_connect(G_OBJECT(chat_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(chat_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

        g_signal_connect(G_OBJECT(chat_button), "button_press_event", G_CALLBACK(chat_click), NULL);
    }
    // Chat box
    chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(chat_box), "chat_box");
    gtk_widget_set_size_request(GTK_WIDGET(chat_box), WINDOW_SIZE_X - 310, WINDOW_SIZE_Y);
    gtk_fixed_put(GTK_FIXED(main_fixed), chat_box, 310, 0);

    /*GtkWidget *left_mid_box = gtk_label_new("Who you want to write?");
    gtk_widget_set_name(GTK_WIDGET(left_mid_box), "left_mid_box");
    gtk_widget_set_size_request(GTK_WIDGET(left_mid_box), 200, 30);
    gtk_box_pack_start(GTK_BOX(chat_box), left_mid_box, TRUE, FALSE, 0);*/

    // Top area
    GtkWidget *top_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(top_area), "top_area");
    gtk_widget_set_size_request(GTK_WIDGET(top_area), WINDOW_SIZE_X - 310, 60);
    gtk_box_pack_start(GTK_BOX(chat_box), top_area, FALSE, FALSE, 0);
        
        // Chat logo
        GtkWidget *top_chat_avatar = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(top_chat_avatar), 40, 40);
        char *path1 = strdup("resource/images/button.png");
        g_signal_connect(G_OBJECT(top_chat_avatar), "draw", G_CALLBACK(draw_chat_avatar), path1);

        GtkWidget* photo_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(photo_chat_box), "top_chat_photo_box");
        gtk_container_add(GTK_CONTAINER(photo_chat_box), top_chat_avatar);
        gtk_box_pack_start(GTK_BOX(top_area), photo_chat_box, FALSE, FALSE, 0);

        // Chat name
        GtkWidget* chat_name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_name_box), "top_chat_name_box");
        gtk_box_pack_start(GTK_BOX(top_area), chat_name_box, FALSE, FALSE, 0);

        GtkWidget* top_chat_name = gtk_label_new("Lorem Ipsum");
        gtk_widget_set_name(GTK_WIDGET(top_chat_name), "top_chat_name");
        gtk_container_add(GTK_CONTAINER(chat_name_box), top_chat_name);

        // Chat settings
        GtkWidget *chat_setting_button = gtk_event_box_new();
        gtk_box_pack_end(GTK_BOX(top_area), chat_setting_button, FALSE, FALSE, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_setting_button), "chat_setting_button");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(chat_setting_button), TRUE);

        g_signal_connect(G_OBJECT(chat_setting_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(chat_setting_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
        g_signal_connect(G_OBJECT(chat_setting_button), "button_press_event", G_CALLBACK(show_chat_settings), NULL);

        GtkWidget *chat_setting_button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(chat_setting_button_box), "chat_setting_button_box");
        gtk_widget_set_size_request(GTK_WIDGET(chat_setting_button_box), 18, 18);
        gtk_container_add(GTK_CONTAINER(chat_setting_button), chat_setting_button_box);

    // Settings button
    GtkWidget *settings_button_clickable = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(settings_button_clickable), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(settings_button_clickable), GTK_ALIGN_CENTER);
    gtk_fixed_put(GTK_FIXED(main_fixed), settings_button_clickable, 250, 10);

    GtkWidget *settings_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(GTK_WIDGET(settings_button), "settings_button");
    gtk_widget_set_size_request(GTK_WIDGET(settings_button), 20, 20);
    gtk_container_add(GTK_CONTAINER(settings_button_clickable), settings_button);

    g_signal_connect(G_OBJECT(settings_button_clickable), "button_press_event", G_CALLBACK(show_user_settings), (gpointer **)activity_block);

    // Exit button
    GtkWidget *exit_button_clickable = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(exit_button_clickable), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(exit_button_clickable), GTK_ALIGN_CENTER);
    gtk_fixed_put(GTK_FIXED(main_fixed), exit_button_clickable, 280, 10);

    GtkWidget *exit_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(exit_button), "exit_button");
    gtk_widget_set_size_request(GTK_WIDGET(exit_button), 19, 19);
    gtk_container_add(GTK_CONTAINER(exit_button_clickable), exit_button);

    g_signal_connect(G_OBJECT(exit_button_clickable), "button_press_event", G_CALLBACK(start_screen), activity_block);

    // Chat's messages area
    GtkWidget *messages_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(messages_area), "messages_area");
    gtk_box_pack_start(GTK_BOX(chat_box), messages_area, FALSE, FALSE, 0);
    //gtk_fixed_put(GTK_FIXED(main_fixed), messanges_area, 310, 73);
        
    messages_area_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_kinetic_scrolling(GTK_SCROLLED_WINDOW(messages_area_scroll), TRUE);
    gtk_widget_set_size_request(GTK_WIDGET(messages_area_scroll), 200, 760);
    gtk_box_pack_start(GTK_BOX(messages_area), messages_area_scroll, TRUE, TRUE, 0);   

    messanges_area_for_scroll = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(messages_area_scroll), messanges_area_for_scroll);

    // Bottom area
    GtkWidget *bottom_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_name(GTK_WIDGET(bottom_area), "bottom_area");
    gtk_widget_set_size_request(GTK_WIDGET(bottom_area), 100, 60);
    gtk_box_pack_end(GTK_BOX(chat_box), bottom_area, FALSE, FALSE, 0);

        // Clip button
        GtkWidget *clip_event_box = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(clip_event_box), "clip_event_box");
        gtk_widget_set_halign(GTK_WIDGET(clip_event_box), GTK_ALIGN_CENTER);
        gtk_widget_set_valign(GTK_WIDGET(clip_event_box), GTK_ALIGN_CENTER);
        gtk_box_pack_start(GTK_BOX(bottom_area), clip_event_box, FALSE, FALSE, 0);

        GtkWidget *clip_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(clip_box), "clip_box");
        gtk_widget_set_size_request(GTK_WIDGET(clip_box), 20, 20);
        gtk_container_add(GTK_CONTAINER(clip_event_box), clip_box);

        g_signal_connect(G_OBJECT(clip_event_box), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(clip_event_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

        // Message area
        GtkWidget *scrolled_message =  gtk_scrolled_window_new(NULL, NULL);
        gtk_widget_set_name(GTK_WIDGET(scrolled_message), "scrollable_msg");
        gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_message), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
        gtk_widget_set_size_request(scrolled_message, 700, 30); 
        gtk_box_pack_start(GTK_BOX(bottom_area), scrolled_message, TRUE, TRUE, 0);

        GtkWidget *msg_enter = gtk_text_view_new();
        gtk_widget_set_name(GTK_WIDGET(msg_enter), "msg_enter");
        gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(msg_enter), GTK_WRAP_WORD_CHAR);
        gtk_text_view_set_right_margin(GTK_TEXT_VIEW(msg_enter), 20);
        gtk_text_view_set_top_margin(GTK_TEXT_VIEW(msg_enter), 10);
        gtk_text_view_set_left_margin(GTK_TEXT_VIEW(msg_enter), 20);
        gtk_container_add(GTK_CONTAINER(scrolled_message), msg_enter);

        /*GtkWidget *important_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(important_box), "important_box");
        gtk_widget_set_size_request(GTK_WIDGET(important_box), 20, 60);
        gtk_fixed_put(GTK_FIXED(main_fixed), important_box, 1360, WINDOW_SIZE_Y - 60);*/

        g_signal_connect(G_OBJECT(clip_event_box), "button_press_event", G_CALLBACK(send_message_file), msg_enter);
    
        // Emotes
        GtkWidget *smile_button_clickable = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(smile_button_clickable), "smile_button_clickable");
        gtk_widget_set_halign(GTK_WIDGET(smile_button_clickable), GTK_ALIGN_CENTER);
        gtk_widget_set_valign(GTK_WIDGET(smile_button_clickable), GTK_ALIGN_CENTER);
        gtk_box_pack_start(GTK_BOX(bottom_area), smile_button_clickable, FALSE, FALSE, 0);

        g_signal_connect(G_OBJECT(smile_button_clickable), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(smile_button_clickable), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

        g_signal_connect(G_OBJECT(smile_button_clickable), "button_press_event", G_CALLBACK(show_emoji_box), NULL);

        GtkWidget *smile_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(GTK_WIDGET(smile_button), "smile_button");
        gtk_widget_set_size_request(GTK_WIDGET(smile_button), 20, 20);
        gtk_container_add(GTK_CONTAINER(smile_button_clickable), smile_button);

        // Send message
        GtkWidget *send_button_clickable = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(send_button_clickable), "send_button_clickable");
        gtk_widget_set_halign(GTK_WIDGET(send_button_clickable), GTK_ALIGN_CENTER);
        gtk_widget_set_valign(GTK_WIDGET(send_button_clickable), GTK_ALIGN_CENTER);
        gtk_box_pack_start(GTK_BOX(bottom_area), send_button_clickable, FALSE, FALSE, 0);

        g_signal_connect(G_OBJECT(send_button_clickable), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(send_button_clickable), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);

        GtkWidget *send_button = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_widget_set_name(GTK_WIDGET(send_button), "send_button");
        gtk_widget_set_size_request(GTK_WIDGET(send_button), 18, 18);
        gtk_container_add(GTK_CONTAINER(send_button_clickable), send_button);

        g_signal_connect(G_OBJECT(send_button_clickable), "button_press_event", G_CALLBACK(send_message), msg_enter);
    
    gtk_widget_show_all(main_data.main_screen_box);
}
