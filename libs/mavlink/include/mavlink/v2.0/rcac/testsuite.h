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
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,{ 185.0, 186.0, 187.0 },{ 269.0, 270.0, 271.0 },{ 353.0, 354.0, 355.0 },{ 437.0, 438.0, 439.0 },{ 521.0, 522.0, 523.0 },{ 605.0, 606.0, 607.0, 608.0, 609.0, 610.0, 611.0, 612.0, 613.0, 614.0, 615.0, 616.0 },145,212
    };
    mavlink_rcac_att_rate_variables_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp = packet_in.timestamp;
        packet1.ii_att = packet_in.ii_att;
        packet1.ii_rate = packet_in.ii_rate;
        packet1.switch_att = packet_in.switch_att;
        packet1.switch_rate = packet_in.switch_rate;
        
        mav_array_memcpy(packet1.rcac_att_z, packet_in.rcac_att_z, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_att_u, packet_in.rcac_att_u, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_att_theta, packet_in.rcac_att_theta, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_rate_z, packet_in.rcac_rate_z, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_rate_u, packet_in.rcac_rate_u, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_rate_theta, packet_in.rcac_rate_theta, sizeof(float)*12);
        
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
    mavlink_msg_rcac_att_rate_variables_pack(system_id, component_id, &msg , packet1.timestamp , packet1.ii_att , packet1.switch_att , packet1.rcac_att_z , packet1.rcac_att_u , packet1.rcac_att_theta , packet1.ii_rate , packet1.switch_rate , packet1.rcac_rate_z , packet1.rcac_rate_u , packet1.rcac_rate_theta );
    mavlink_msg_rcac_att_rate_variables_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_att_rate_variables_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp , packet1.ii_att , packet1.switch_att , packet1.rcac_att_z , packet1.rcac_att_u , packet1.rcac_att_theta , packet1.ii_rate , packet1.switch_rate , packet1.rcac_rate_z , packet1.rcac_rate_u , packet1.rcac_rate_theta );
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
    mavlink_msg_rcac_att_rate_variables_send(MAVLINK_COMM_1 , packet1.timestamp , packet1.ii_att , packet1.switch_att , packet1.rcac_att_z , packet1.rcac_att_u , packet1.rcac_att_theta , packet1.ii_rate , packet1.switch_rate , packet1.rcac_rate_z , packet1.rcac_rate_u , packet1.rcac_rate_theta );
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
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,93372036854777319ULL,93372036854777823ULL,{ 297.0, 298.0 },{ 353.0, 354.0, 355.0 },{ 437.0, 438.0, 439.0 },{ 521.0, 522.0, 523.0 },{ 605.0, 606.0, 607.0 },{ 689.0, 690.0, 691.0 },{ 773.0, 774.0, 775.0, 776.0, 777.0, 778.0, 779.0, 780.0, 781.0 },{ 1025.0, 1026.0, 1027.0 },{ 1109.0, 1110.0, 1111.0 },{ 1193.0, 1194.0, 1195.0 },{ 1277.0, 1278.0, 1279.0 },{ 1361.0, 1362.0, 1363.0 },{ 1445.0, 1446.0, 1447.0, 1448.0, 1449.0, 1450.0, 1451.0, 1452.0, 1453.0, 1454.0, 1455.0, 1456.0 },249,60
    };
    mavlink_rcac_pos_vel_variables_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp = packet_in.timestamp;
        packet1.ii_pos = packet_in.ii_pos;
        packet1.ii_vel = packet_in.ii_vel;
        packet1.ii_att = packet_in.ii_att;
        packet1.ii_rate = packet_in.ii_rate;
        packet1.switch_pos = packet_in.switch_pos;
        packet1.switch_vel = packet_in.switch_vel;
        
        mav_array_memcpy(packet1.rcac_alpha, packet_in.rcac_alpha, sizeof(float)*2);
        mav_array_memcpy(packet1.rcac_pos_z, packet_in.rcac_pos_z, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_pos_u, packet_in.rcac_pos_u, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_pos_theta, packet_in.rcac_pos_theta, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_vel_z, packet_in.rcac_vel_z, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_vel_u, packet_in.rcac_vel_u, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_vel_theta, packet_in.rcac_vel_theta, sizeof(float)*9);
        mav_array_memcpy(packet1.rcac_att_z, packet_in.rcac_att_z, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_att_u, packet_in.rcac_att_u, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_att_theta, packet_in.rcac_att_theta, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_rate_z, packet_in.rcac_rate_z, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_rate_u, packet_in.rcac_rate_u, sizeof(float)*3);
        mav_array_memcpy(packet1.rcac_rate_theta, packet_in.rcac_rate_theta, sizeof(float)*12);
        
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
    mavlink_msg_rcac_pos_vel_variables_pack(system_id, component_id, &msg , packet1.timestamp , packet1.rcac_alpha , packet1.ii_pos , packet1.switch_pos , packet1.rcac_pos_z , packet1.rcac_pos_u , packet1.rcac_pos_theta , packet1.ii_vel , packet1.switch_vel , packet1.rcac_vel_z , packet1.rcac_vel_u , packet1.rcac_vel_theta , packet1.ii_att , packet1.rcac_att_z , packet1.rcac_att_u , packet1.rcac_att_theta , packet1.ii_rate , packet1.rcac_rate_z , packet1.rcac_rate_u , packet1.rcac_rate_theta );
    mavlink_msg_rcac_pos_vel_variables_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_pos_vel_variables_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp , packet1.rcac_alpha , packet1.ii_pos , packet1.switch_pos , packet1.rcac_pos_z , packet1.rcac_pos_u , packet1.rcac_pos_theta , packet1.ii_vel , packet1.switch_vel , packet1.rcac_vel_z , packet1.rcac_vel_u , packet1.rcac_vel_theta , packet1.ii_att , packet1.rcac_att_z , packet1.rcac_att_u , packet1.rcac_att_theta , packet1.ii_rate , packet1.rcac_rate_z , packet1.rcac_rate_u , packet1.rcac_rate_theta );
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
    mavlink_msg_rcac_pos_vel_variables_send(MAVLINK_COMM_1 , packet1.timestamp , packet1.rcac_alpha , packet1.ii_pos , packet1.switch_pos , packet1.rcac_pos_z , packet1.rcac_pos_u , packet1.rcac_pos_theta , packet1.ii_vel , packet1.switch_vel , packet1.rcac_vel_z , packet1.rcac_vel_u , packet1.rcac_vel_theta , packet1.ii_att , packet1.rcac_att_z , packet1.rcac_att_u , packet1.rcac_att_theta , packet1.ii_rate , packet1.rcac_rate_z , packet1.rcac_rate_u , packet1.rcac_rate_theta );
    mavlink_msg_rcac_pos_vel_variables_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_rcac_mode_sc(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RCAC_MODE_SC >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_rcac_mode_sc_t packet_in = {
        93372036854775807ULL,73.0,101.0
    };
    mavlink_rcac_mode_sc_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp = packet_in.timestamp;
        packet1.RCAC_switch = packet_in.RCAC_switch;
        packet1.PID_scale_f = packet_in.PID_scale_f;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RCAC_MODE_SC_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RCAC_MODE_SC_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_mode_sc_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_rcac_mode_sc_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_mode_sc_pack(system_id, component_id, &msg , packet1.timestamp , packet1.RCAC_switch , packet1.PID_scale_f );
    mavlink_msg_rcac_mode_sc_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_mode_sc_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp , packet1.RCAC_switch , packet1.PID_scale_f );
    mavlink_msg_rcac_mode_sc_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_rcac_mode_sc_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rcac_mode_sc_send(MAVLINK_COMM_1 , packet1.timestamp , packet1.RCAC_switch , packet1.PID_scale_f );
    mavlink_msg_rcac_mode_sc_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_rcac(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_rcac_att_rate_variables(system_id, component_id, last_msg);
    mavlink_test_rcac_pos_vel_variables(system_id, component_id, last_msg);
    mavlink_test_rcac_mode_sc(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // RCAC_TESTSUITE_H
