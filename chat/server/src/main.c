#include "router.h"
//#include "subscribs_manager.h"
#include "users_manager.h"





int main()
{
    // SubscribsManager* sm = create_subscribs_manager(200);
    // if(sm == NULL){printf("sm == null\n");}

    // SubscribsManager_return res = new_subscriber(sm, "yakov", "302");
    // printf("0: %d\n", res);

    // res = log_in_chack(sm, "yakov", "302");
    // printf("0: %d\n", res);

    // res = log_in_chack(sm, "yakov", "302 ");
    // printf("10: %d\n", res);

    // res = log_in_chack(sm, "yakav", "302");
    // printf("3: %d\n", res);


    // res = new_subscriber(sm, "hananel", "0545949422");
    // printf("0: %d\n", res);

    // res = log_in_chack(sm, "hananel", "0545949422");
    // printf("0: %d\n", res);

    // res = log_in_chack(sm, "hananel ", "0545949422");
    // printf("3: %d\n", res);

    // res = log_in_chack(sm, "hananel", "045949422");
    // printf("10: %d\n", res);


    // res = new_subscriber(sm, "yakov hananel", "1234");
    // printf("0: %d\n", res);

    // res = log_in_chack(sm, "yakov hananel", "1234");
    // printf("0: %d\n", res);

    // res = log_in_chack(sm, "yakov  hananel", "1234");
    // printf("3: %d\n", res);

    // res = log_in_chack(sm, "yakov hananel", "054594089422");
    // printf("10: %d\n", res);


    // destroy_subscribs_manager(sm);


    UserManager* um = create_users_manager(200);
    if(um == NULL){printf("um == null\n");}


    UserManager_return rese = user_log_in(um, "yakov hananel");
    printf("0: %d\n", rese);

     rese = user_log_in(um, "yakov hananel");
    printf("6: %d\n", rese);

        rese =  user_log_out(um, "yakov hananel");
    printf("0: %d\n", rese);

         rese = user_log_in(um, "yakov hananel");
    printf("0: %d\n", rese);

     rese = user_join_group(um, "yakov hananel", "yyy");
     printf("0: %d\n", rese);

    rese = user_join_group(um, "yakov hananel", "yyy");
     printf("5: %d\n", rese);

    rese = user_leave_group(um, "yakov hananel", "yyy");
    printf("0: %d\n", rese);


    rese = user_join_group(um, "yakov hananel", "yyy");
     printf("0: %d\n", rese);


    rese = user_join_group(um, "yakov  hananel", "875");
     printf("3: %d\n", rese);

    rese = user_join_group(um, "yakov hananel", "yyuuy");
     printf("0: %d\n", rese);


    rese = user_leave_group(um, "yakov hananel", "yyy");
    printf("0: %d\n", rese);

    rese = user_leave_group(um, "yakov aananel", "yyy");
    printf("3: %d\n", rese);

    rese = user_leave_group(um, "yakov hananel", "yyy");
    printf("4: %d\n", rese);

    rese = user_leave_group(um, "yakov hananel", "yy98y");
    printf("4: %d\n", rese);

    rese = user_leave_group(um, "yakov hananel", "yyuuy");
    printf("0: %d\n", rese);

    rese =  user_log_out(um, "yakov hananel");
    printf("0: %d\n", rese);

    rese =  user_log_out(um, "yakov hananel");
    printf("3: %d\n", rese);

    destroy_users_manager(um);

    // Router* router = router_create(); 
    // if(router == NULL)
    // {
    //     printf("router not initialized\n");
    //     return 0;
    // }

    // while(TRUE)
    // {
    //     char c = getchar();
    //     if(c == 'q' || c == 27)
    //     {
    //         stop_router(router);
    //         break;
    //     }
    // }

    // router_destroy(router);
}