/** @file
 *    @brief MAVLink comm protocol testsuite generated from rcac.xml
 *    @see http://qgroundcontrol.org/mavlink/
 */
#pragma once
#ifndef RCAC_TESTSUITE_H
#define RCAC_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_rcac(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common(system_id, component_id, last_msg);
    mavlink_test_rcac(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_rcac_att_rate_variables(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_rcac_att_rate_variables_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,409.0,437.0,465.0,493.0,521.0,549.0,577.0,605.0,633.0,661.0,689.0,717.0,745.0,773.0,801.0,829.0,857.0,885.0,913.0,941.0,969.0,997.0,1025.0,1053.0,1081.0,1109.0,1137.0,1165.0,1193.0,1221.0,1249.0,1277.0,1305.0,1333.0,1361.0,1389.0,1417.0,1445.0,117,184
    };
    mavlink_rcac_att_rate_variables_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp = packet_in.timestamp;
        packet1.ii_att = packet_in.ii_att;
        packet1.ii_rate = packet_in.ii_rate;
        packet1.alpha_pid_att = packet_in.alpha_pid_att;
        packet1.rcac_att_z_0 = packet_in.rcac_att_z_0;
        packet1.rcac_att_z_1 = packet_in.rcac_att_z_1;
        packet1.rcac_att_z_2 = packet_in.rcac_att_z_2;
        packet1.rcac_att_u_0 = packet_in.rcac_att_u_0;
        packet1.rcac_att_u_1 = packet_in.rcac_att_u_1;
        packet1.rcac_att_u_2 = packet_in.rcac_att_u_2;
        packet1.rcac_att_theta_0 = packet_in.rcac_att_theta_0;
        packet1.rcac_att_theta_1 = packet_in.rcac_att_theta_1;
        packet1.rcac_att_theta_2 = packet_in.rcac_att_theta_2;
        packet1.alpha_pid_rate = packet_in.alpha_pid_rate;
        packet1.rcac_rate_z_0 = packet_in.rcac_rate_z_0;
        packet1.rcac_rate_z_1 = packet_in.rcac_rate_z_1;
        packet1.rcac_rate_z_2 = packet_in.rcac_rate_z_2;
        packet1.rcac_rate_u_0 = packet_in.rcac_rate_u_0;
        packet1.rcac_rate_u_1 = packet_in.rcac_rate_u_1;
        packet1.rcac_rate_u_2 = packet_in.rcac_rate_u_2;
        packet1.rcac_rate_theta_0 = packet_in.rcac_rate_theta_0;
        packet1.rcac_rate_theta_1 = packet_in.rcac_rate_theta_1;
        packet1.rcac_rate_theta_2 = packet_in.rcac_rate_theta_2;
        packet1.rcac_rate_theta_3 = packet_in.rcac_rate_theta_3;
        packet1.rcac_rate_theta_4 = packet_in.rcac_rate_theta_4;
        packet1.rcac_rate_theta_5 = packet_in.rcac_rate_theta_5;
        packet1.rcac_rate_theta_6 = packet_in.rcac_rate_theta_6;
        packet1.rcac_rate_theta_7 = packet_in.rcac_rate_theta_7;
        packet1.rcac_rate_theta_8 = packet_in.rcac_rate_theta_8;
        packet1.rcac_rate_theta_9 = packet_in.rcac_rate_theta_9;
        packet1.rcac_rate_theta_10 = packet_in.rcac_rate_theta_10;
        packet1.rcac_rate_theta_11 = packet_in.rcac_rate_theta_11;
        packet1.px4_att_theta_0 = packet_in.px4_att_theta_0;
        packet1.px4_att_theta_1 = packet_in.px4_att_theta_1;
        packet1.px4_att_theta_2 = packet_in.px4_att_theta_2;
        packet1.px4_rate_theta_0 = packet_in.px4_rate_theta_0;
        packet1.px4_rate_theta_1 = packet_in.px4_rate_theta_1;
        packet1.px4_rate_theta_2 = packet_in.px4_rate_theta_2;
        packet1.px4_rate_theta_3 = packet_in.px4_rate_theta_3;
        packet1.px4_rate_theta_4 = packet_in.px4_rate_theta_4;
        packet1.px4_rate_theta_5 = packet_in.px4_rate_theta_5;
        packet1.px4_rate_theta_6 = packet_in.px4_rate_theta_6;
        packet1.px4_rate_theta_7 = packet_in.px4_rate_theta_7;
        packet1.px4_rate_theta_8 = packet_in.px4_rate_theta_8;
        packet1.px4_rate_theta_9 = packet_in.px4_rate_theta_9;
        packet1.px4_rate_theta_10 = packet_in.px4_rate_theta_10;
        packet1.px4_rate_theta_11 = packet_in.px4_rate_theta_11;
        packet1.p11_att = packet_in.p11_att;
        packet1.p11_ratex = packet_in.p11_ratex;
        packet1.switch_att = packet_in.switch_att;
        packet1.switch_rate = packet_in.switch_rate;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_att_rate_variables_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_rcac_att_rate_variables_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_att_rate_variables_pack(system_id, component_id, &msg , packet1.timestamp , packet1.ii_att , packet1.switch_att , packet1.alpha_pid_att , packet1.rcac_att_z_0 , packet1.rcac_att_z_1 , packet1.rcac_att_z_2 , packet1.rcac_att_u_0 , packet1.rcac_att_u_1 , packet1.rcac_att_u_2 , packet1.rcac_att_theta_0 , packet1.rcac_att_theta_1 , packet1.rcac_att_theta_2 , packet1.ii_rate , packet1.switch_rate , packet1.alpha_pid_rate , packet1.rcac_rate_z_0 , packet1.rcac_rate_z_1 , packet1.rcac_rate_z_2 , packet1.rcac_rate_u_0 , packet1.rcac_rate_u_1 , packet1.rcac_rate_u_2 , packet1.rcac_rate_theta_0 , packet1.rcac_rate_theta_1 , packet1.rcac_rate_theta_2 , packet1.rcac_rate_theta_3 , packet1.rcac_rate_theta_4 , packet1.rcac_rate_theta_5 , packet1.rcac_rate_theta_6 , packet1.rcac_rate_theta_7 , packet1.rcac_rate_theta_8 , packet1.rcac_rate_theta_9 , packet1.rcac_rate_theta_10 , packet1.rcac_rate_theta_11 , packet1.px4_att_theta_0 , packet1.px4_att_theta_1 , packet1.px4_att_theta_2 , packet1.px4_rate_theta_0 , packet1.px4_rate_theta_1 , packet1.px4_rate_theta_2 , packet1.px4_rate_theta_3 , packet1.px4_rate_theta_4 , packet1.px4_rate_theta_5 , packet1.px4_rate_theta_6 , packet1.px4_rate_theta_7 , packet1.px4_rate_theta_8 , packet1.px4_rate_theta_9 , packet1.px4_rate_theta_10 , packet1.px4_rate_theta_11 , packet1.p11_att , packet1.p11_ratex );
    mavlink_msg_rcac_att_rate_variables_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_att_rate_variables_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp , packet1.ii_att , packet1.switch_att , packet1.alpha_pid_att , packet1.rcac_att_z_0 , packet1.rcac_att_z_1 , packet1.rcac_att_z_2 , packet1.rcac_att_u_0 , packet1.rcac_att_u_1 , packet1.rcac_att_u_2 , packet1.rcac_att_theta_0 , packet1.rcac_att_theta_1 , packet1.rcac_att_theta_2 , packet1.ii_rate , packet1.switch_rate , packet1.alpha_pid_rate , packet1.rcac_rate_z_0 , packet1.rcac_rate_z_1 , packet1.rcac_rate_z_2 , packet1.rcac_rate_u_0 , packet1.rcac_rate_u_1 , packet1.rcac_rate_u_2 , packet1.rcac_rate_theta_0 , packet1.rcac_rate_theta_1 , packet1.rcac_rate_theta_2 , packet1.rcac_rate_theta_3 , packet1.rcac_rate_theta_4 , packet1.rcac_rate_theta_5 , packet1.rcac_rate_theta_6 , packet1.rcac_rate_theta_7 , packet1.rcac_rate_theta_8 , packet1.rcac_rate_theta_9 , packet1.rcac_rate_theta_10 , packet1.rcac_rate_theta_11 , packet1.px4_att_theta_0 , packet1.px4_att_theta_1 , packet1.px4_att_theta_2 , packet1.px4_rate_theta_0 , packet1.px4_rate_theta_1 , packet1.px4_rate_theta_2 , packet1.px4_rate_theta_3 , packet1.px4_rate_theta_4 , packet1.px4_rate_theta_5 , packet1.px4_rate_theta_6 , packet1.px4_rate_theta_7 , packet1.px4_rate_theta_8 , packet1.px4_rate_theta_9 , packet1.px4_rate_theta_10 , packet1.px4_rate_theta_11 , packet1.p11_att , packet1.p11_ratex );
    mavlink_msg_rcac_att_rate_variables_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_rcac_att_rate_variables_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_att_rate_variables_send(MAVLINK_COMM_1 , packet1.timestamp , packet1.ii_att , packet1.switch_att , packet1.alpha_pid_att , packet1.rcac_att_z_0 , packet1.rcac_att_z_1 , packet1.rcac_att_z_2 , packet1.rcac_att_u_0 , packet1.rcac_att_u_1 , packet1.rcac_att_u_2 , packet1.rcac_att_theta_0 , packet1.rcac_att_theta_1 , packet1.rcac_att_theta_2 , packet1.ii_rate , packet1.switch_rate , packet1.alpha_pid_rate , packet1.rcac_rate_z_0 , packet1.rcac_rate_z_1 , packet1.rcac_rate_z_2 , packet1.rcac_rate_u_0 , packet1.rcac_rate_u_1 , packet1.rcac_rate_u_2 , packet1.rcac_rate_theta_0 , packet1.rcac_rate_theta_1 , packet1.rcac_rate_theta_2 , packet1.rcac_rate_theta_3 , packet1.rcac_rate_theta_4 , packet1.rcac_rate_theta_5 , packet1.rcac_rate_theta_6 , packet1.rcac_rate_theta_7 , packet1.rcac_rate_theta_8 , packet1.rcac_rate_theta_9 , packet1.rcac_rate_theta_10 , packet1.rcac_rate_theta_11 , packet1.px4_att_theta_0 , packet1.px4_att_theta_1 , packet1.px4_att_theta_2 , packet1.px4_rate_theta_0 , packet1.px4_rate_theta_1 , packet1.px4_rate_theta_2 , packet1.px4_rate_theta_3 , packet1.px4_rate_theta_4 , packet1.px4_rate_theta_5 , packet1.px4_rate_theta_6 , packet1.px4_rate_theta_7 , packet1.px4_rate_theta_8 , packet1.px4_rate_theta_9 , packet1.px4_rate_theta_10 , packet1.px4_rate_theta_11 , packet1.p11_att , packet1.p11_ratex );
    mavlink_msg_rcac_att_rate_variables_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_rcac_pos_vel_variables(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_rcac_pos_vel_variables_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,409.0,437.0,465.0,493.0,521.0,549.0,577.0,605.0,633.0,661.0,689.0,717.0,745.0,773.0,801.0,829.0,857.0,885.0,913.0,941.0,969.0,997.0,1025.0,1053.0,1081.0,1109.0,1137.0,1165.0,1193.0,1221.0,1249.0,33,100
    };
    mavlink_rcac_pos_vel_variables_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp = packet_in.timestamp;
        packet1.ii_pos = packet_in.ii_pos;
        packet1.ii_vel = packet_in.ii_vel;
        packet1.pid_factor = packet_in.pid_factor;
        packet1.rcac_master_sw = packet_in.rcac_master_sw;
        packet1.alpha_pid_pos = packet_in.alpha_pid_pos;
        packet1.rcac_pos_z_0 = packet_in.rcac_pos_z_0;
        packet1.rcac_pos_z_1 = packet_in.rcac_pos_z_1;
        packet1.rcac_pos_z_2 = packet_in.rcac_pos_z_2;
        packet1.rcac_pos_u_0 = packet_in.rcac_pos_u_0;
        packet1.rcac_pos_u_1 = packet_in.rcac_pos_u_1;
        packet1.rcac_pos_u_2 = packet_in.rcac_pos_u_2;
        packet1.rcac_pos_theta_0 = packet_in.rcac_pos_theta_0;
        packet1.rcac_pos_theta_1 = packet_in.rcac_pos_theta_1;
        packet1.rcac_pos_theta_2 = packet_in.rcac_pos_theta_2;
        packet1.alpha_pid_vel = packet_in.alpha_pid_vel;
        packet1.rcac_vel_z_0 = packet_in.rcac_vel_z_0;
        packet1.rcac_vel_z_1 = packet_in.rcac_vel_z_1;
        packet1.rcac_vel_z_2 = packet_in.rcac_vel_z_2;
        packet1.rcac_vel_u_0 = packet_in.rcac_vel_u_0;
        packet1.rcac_vel_u_1 = packet_in.rcac_vel_u_1;
        packet1.rcac_vel_u_2 = packet_in.rcac_vel_u_2;
        packet1.rcac_vel_theta_0 = packet_in.rcac_vel_theta_0;
        packet1.rcac_vel_theta_1 = packet_in.rcac_vel_theta_1;
        packet1.rcac_vel_theta_2 = packet_in.rcac_vel_theta_2;
        packet1.rcac_vel_theta_3 = packet_in.rcac_vel_theta_3;
        packet1.rcac_vel_theta_4 = packet_in.rcac_vel_theta_4;
        packet1.rcac_vel_theta_5 = packet_in.rcac_vel_theta_5;
        packet1.rcac_vel_theta_6 = packet_in.rcac_vel_theta_6;
        packet1.rcac_vel_theta_7 = packet_in.rcac_vel_theta_7;
        packet1.rcac_vel_theta_8 = packet_in.rcac_vel_theta_8;
        packet1.px4_ol_theta_0 = packet_in.px4_ol_theta_0;
        packet1.px4_ol_theta_1 = packet_in.px4_ol_theta_1;
        packet1.px4_ol_theta_2 = packet_in.px4_ol_theta_2;
        packet1.px4_ol_theta_3 = packet_in.px4_ol_theta_3;
        packet1.px4_ol_theta_4 = packet_in.px4_ol_theta_4;
        packet1.px4_ol_theta_5 = packet_in.px4_ol_theta_5;
        packet1.px4_ol_theta_6 = packet_in.px4_ol_theta_6;
        packet1.px4_ol_theta_7 = packet_in.px4_ol_theta_7;
        packet1.px4_ol_theta_8 = packet_in.px4_ol_theta_8;
        packet1.p11_pos = packet_in.p11_pos;
        packet1.p11_velx = packet_in.p11_velx;
        packet1.switch_pos = packet_in.switch_pos;
        packet1.switch_vel = packet_in.switch_vel;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_pos_vel_variables_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_rcac_pos_vel_variables_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_pos_vel_variables_pack(system_id, component_id, &msg , packet1.timestamp , packet1.pid_factor , packet1.rcac_master_sw , packet1.ii_pos , packet1.switch_pos , packet1.alpha_pid_pos , packet1.rcac_pos_z_0 , packet1.rcac_pos_z_1 , packet1.rcac_pos_z_2 , packet1.rcac_pos_u_0 , packet1.rcac_pos_u_1 , packet1.rcac_pos_u_2 , packet1.rcac_pos_theta_0 , packet1.rcac_pos_theta_1 , packet1.rcac_pos_theta_2 , packet1.ii_vel , packet1.switch_vel , packet1.alpha_pid_vel , packet1.rcac_vel_z_0 , packet1.rcac_vel_z_1 , packet1.rcac_vel_z_2 , packet1.rcac_vel_u_0 , packet1.rcac_vel_u_1 , packet1.rcac_vel_u_2 , packet1.rcac_vel_theta_0 , packet1.rcac_vel_theta_1 , packet1.rcac_vel_theta_2 , packet1.rcac_vel_theta_3 , packet1.rcac_vel_theta_4 , packet1.rcac_vel_theta_5 , packet1.rcac_vel_theta_6 , packet1.rcac_vel_theta_7 , packet1.rcac_vel_theta_8 , packet1.px4_ol_theta_0 , packet1.px4_ol_theta_1 , packet1.px4_ol_theta_2 , packet1.px4_ol_theta_3 , packet1.px4_ol_theta_4 , packet1.px4_ol_theta_5 , packet1.px4_ol_theta_6 , packet1.px4_ol_theta_7 , packet1.px4_ol_theta_8 , packet1.p11_pos , packet1.p11_velx );
    mavlink_msg_rcac_pos_vel_variables_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_pos_vel_variables_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp , packet1.pid_factor , packet1.rcac_master_sw , packet1.ii_pos , packet1.switch_pos , packet1.alpha_pid_pos , packet1.rcac_pos_z_0 , packet1.rcac_pos_z_1 , packet1.rcac_pos_z_2 , packet1.rcac_pos_u_0 , packet1.rcac_pos_u_1 , packet1.rcac_pos_u_2 , packet1.rcac_pos_theta_0 , packet1.rcac_pos_theta_1 , packet1.rcac_pos_theta_2 , packet1.ii_vel , packet1.switch_vel , packet1.alpha_pid_vel , packet1.rcac_vel_z_0 , packet1.rcac_vel_z_1 , packet1.rcac_vel_z_2 , packet1.rcac_vel_u_0 , packet1.rcac_vel_u_1 , packet1.rcac_vel_u_2 , packet1.rcac_vel_theta_0 , packet1.rcac_vel_theta_1 , packet1.rcac_vel_theta_2 , packet1.rcac_vel_theta_3 , packet1.rcac_vel_theta_4 , packet1.rcac_vel_theta_5 , packet1.rcac_vel_theta_6 , packet1.rcac_vel_theta_7 , packet1.rcac_vel_theta_8 , packet1.px4_ol_theta_0 , packet1.px4_ol_theta_1 , packet1.px4_ol_theta_2 , packet1.px4_ol_theta_3 , packet1.px4_ol_theta_4 , packet1.px4_ol_theta_5 , packet1.px4_ol_theta_6 , packet1.px4_ol_theta_7 , packet1.px4_ol_theta_8 , packet1.p11_pos , packet1.p11_velx );
    mavlink_msg_rcac_pos_vel_variables_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_rcac_pos_vel_variables_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_pos_vel_variables_send(MAVLINK_COMM_1 , packet1.timestamp , packet1.pid_factor , packet1.rcac_master_sw , packet1.ii_pos , packet1.switch_pos , packet1.alpha_pid_pos , packet1.rcac_pos_z_0 , packet1.rcac_pos_z_1 , packet1.rcac_pos_z_2 , packet1.rcac_pos_u_0 , packet1.rcac_pos_u_1 , packet1.rcac_pos_u_2 , packet1.rcac_pos_theta_0 , packet1.rcac_pos_theta_1 , packet1.rcac_pos_theta_2 , packet1.ii_vel , packet1.switch_vel , packet1.alpha_pid_vel , packet1.rcac_vel_z_0 , packet1.rcac_vel_z_1 , packet1.rcac_vel_z_2 , packet1.rcac_vel_u_0 , packet1.rcac_vel_u_1 , packet1.rcac_vel_u_2 , packet1.rcac_vel_theta_0 , packet1.rcac_vel_theta_1 , packet1.rcac_vel_theta_2 , packet1.rcac_vel_theta_3 , packet1.rcac_vel_theta_4 , packet1.rcac_vel_theta_5 , packet1.rcac_vel_theta_6 , packet1.rcac_vel_theta_7 , packet1.rcac_vel_theta_8 , packet1.px4_ol_theta_0 , packet1.px4_ol_theta_1 , packet1.px4_ol_theta_2 , packet1.px4_ol_theta_3 , packet1.px4_ol_theta_4 , packet1.px4_ol_theta_5 , packet1.px4_ol_theta_6 , packet1.px4_ol_theta_7 , packet1.px4_ol_theta_8 , packet1.p11_pos , packet1.p11_velx );
    mavlink_msg_rcac_pos_vel_variables_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_rcac(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_rcac_att_rate_variables(system_id, component_id, last_msg);
    mavlink_test_rcac_pos_vel_variables(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // RCAC_TESTSUITE_H
