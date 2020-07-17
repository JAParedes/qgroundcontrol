/** @file
 *	@brief MAVLink comm testsuite protocol generated from rcac.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "rcac.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(rcac, RCAC_ATT_RATE_VARIABLES)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::rcac::msg::RCAC_ATT_RATE_VARIABLES packet_in{};
    packet_in.timestamp = 93372036854775807ULL;
    packet_in.ii_att = 93372036854776311ULL;
    packet_in.switch_att = 145;
    packet_in.rcac_att_z = {{ 185.0, 186.0, 187.0 }};
    packet_in.rcac_att_u = {{ 269.0, 270.0, 271.0 }};
    packet_in.rcac_att_theta = {{ 353.0, 354.0, 355.0 }};
    packet_in.ii_rate = 93372036854776815ULL;
    packet_in.switch_rate = 212;
    packet_in.rcac_rate_z = {{ 437.0, 438.0, 439.0 }};
    packet_in.rcac_rate_u = {{ 521.0, 522.0, 523.0 }};
    packet_in.rcac_rate_theta = {{ 605.0, 606.0, 607.0, 608.0, 609.0, 610.0, 611.0, 612.0, 613.0, 614.0, 615.0, 616.0 }};

    mavlink::rcac::msg::RCAC_ATT_RATE_VARIABLES packet1{};
    mavlink::rcac::msg::RCAC_ATT_RATE_VARIABLES packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.timestamp, packet2.timestamp);
    EXPECT_EQ(packet1.ii_att, packet2.ii_att);
    EXPECT_EQ(packet1.switch_att, packet2.switch_att);
    EXPECT_EQ(packet1.rcac_att_z, packet2.rcac_att_z);
    EXPECT_EQ(packet1.rcac_att_u, packet2.rcac_att_u);
    EXPECT_EQ(packet1.rcac_att_theta, packet2.rcac_att_theta);
    EXPECT_EQ(packet1.ii_rate, packet2.ii_rate);
    EXPECT_EQ(packet1.switch_rate, packet2.switch_rate);
    EXPECT_EQ(packet1.rcac_rate_z, packet2.rcac_rate_z);
    EXPECT_EQ(packet1.rcac_rate_u, packet2.rcac_rate_u);
    EXPECT_EQ(packet1.rcac_rate_theta, packet2.rcac_rate_theta);
}

#ifdef TEST_INTEROP
TEST(rcac_interop, RCAC_ATT_RATE_VARIABLES)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_rcac_att_rate_variables_t packet_c {
         93372036854775807ULL, 93372036854776311ULL, 93372036854776815ULL, { 185.0, 186.0, 187.0 }, { 269.0, 270.0, 271.0 }, { 353.0, 354.0, 355.0 }, { 437.0, 438.0, 439.0 }, { 521.0, 522.0, 523.0 }, { 605.0, 606.0, 607.0, 608.0, 609.0, 610.0, 611.0, 612.0, 613.0, 614.0, 615.0, 616.0 }, 145, 212
    };

    mavlink::rcac::msg::RCAC_ATT_RATE_VARIABLES packet_in{};
    packet_in.timestamp = 93372036854775807ULL;
    packet_in.ii_att = 93372036854776311ULL;
    packet_in.switch_att = 145;
    packet_in.rcac_att_z = {{ 185.0, 186.0, 187.0 }};
    packet_in.rcac_att_u = {{ 269.0, 270.0, 271.0 }};
    packet_in.rcac_att_theta = {{ 353.0, 354.0, 355.0 }};
    packet_in.ii_rate = 93372036854776815ULL;
    packet_in.switch_rate = 212;
    packet_in.rcac_rate_z = {{ 437.0, 438.0, 439.0 }};
    packet_in.rcac_rate_u = {{ 521.0, 522.0, 523.0 }};
    packet_in.rcac_rate_theta = {{ 605.0, 606.0, 607.0, 608.0, 609.0, 610.0, 611.0, 612.0, 613.0, 614.0, 615.0, 616.0 }};

    mavlink::rcac::msg::RCAC_ATT_RATE_VARIABLES packet2{};

    mavlink_msg_rcac_att_rate_variables_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.timestamp, packet2.timestamp);
    EXPECT_EQ(packet_in.ii_att, packet2.ii_att);
    EXPECT_EQ(packet_in.switch_att, packet2.switch_att);
    EXPECT_EQ(packet_in.rcac_att_z, packet2.rcac_att_z);
    EXPECT_EQ(packet_in.rcac_att_u, packet2.rcac_att_u);
    EXPECT_EQ(packet_in.rcac_att_theta, packet2.rcac_att_theta);
    EXPECT_EQ(packet_in.ii_rate, packet2.ii_rate);
    EXPECT_EQ(packet_in.switch_rate, packet2.switch_rate);
    EXPECT_EQ(packet_in.rcac_rate_z, packet2.rcac_rate_z);
    EXPECT_EQ(packet_in.rcac_rate_u, packet2.rcac_rate_u);
    EXPECT_EQ(packet_in.rcac_rate_theta, packet2.rcac_rate_theta);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(rcac, RCAC_POS_VEL_VARIABLES)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::rcac::msg::RCAC_POS_VEL_VARIABLES packet_in{};
    packet_in.timestamp = 93372036854775807ULL;
    packet_in.rcac_alpha = {{ 297.0, 298.0 }};
    packet_in.ii_pos = 93372036854776311ULL;
    packet_in.switch_pos = 249;
    packet_in.rcac_pos_z = {{ 353.0, 354.0, 355.0 }};
    packet_in.rcac_pos_u = {{ 437.0, 438.0, 439.0 }};
    packet_in.rcac_pos_theta = {{ 521.0, 522.0, 523.0 }};
    packet_in.ii_vel = 93372036854776815ULL;
    packet_in.switch_vel = 60;
    packet_in.rcac_vel_z = {{ 605.0, 606.0, 607.0 }};
    packet_in.rcac_vel_u = {{ 689.0, 690.0, 691.0 }};
    packet_in.rcac_vel_theta = {{ 773.0, 774.0, 775.0, 776.0, 777.0, 778.0, 779.0, 780.0, 781.0 }};
    packet_in.ii_att = 93372036854777319ULL;
    packet_in.rcac_att_z = {{ 1025.0, 1026.0, 1027.0 }};
    packet_in.rcac_att_u = {{ 1109.0, 1110.0, 1111.0 }};
    packet_in.rcac_att_theta = {{ 1193.0, 1194.0, 1195.0 }};
    packet_in.ii_rate = 93372036854777823ULL;
    packet_in.rcac_rate_z = {{ 1277.0, 1278.0, 1279.0 }};
    packet_in.rcac_rate_u = {{ 1361.0, 1362.0, 1363.0 }};
    packet_in.rcac_rate_theta = {{ 1445.0, 1446.0, 1447.0, 1448.0, 1449.0, 1450.0, 1451.0, 1452.0, 1453.0, 1454.0, 1455.0, 1456.0 }};

    mavlink::rcac::msg::RCAC_POS_VEL_VARIABLES packet1{};
    mavlink::rcac::msg::RCAC_POS_VEL_VARIABLES packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.timestamp, packet2.timestamp);
    EXPECT_EQ(packet1.rcac_alpha, packet2.rcac_alpha);
    EXPECT_EQ(packet1.ii_pos, packet2.ii_pos);
    EXPECT_EQ(packet1.switch_pos, packet2.switch_pos);
    EXPECT_EQ(packet1.rcac_pos_z, packet2.rcac_pos_z);
    EXPECT_EQ(packet1.rcac_pos_u, packet2.rcac_pos_u);
    EXPECT_EQ(packet1.rcac_pos_theta, packet2.rcac_pos_theta);
    EXPECT_EQ(packet1.ii_vel, packet2.ii_vel);
    EXPECT_EQ(packet1.switch_vel, packet2.switch_vel);
    EXPECT_EQ(packet1.rcac_vel_z, packet2.rcac_vel_z);
    EXPECT_EQ(packet1.rcac_vel_u, packet2.rcac_vel_u);
    EXPECT_EQ(packet1.rcac_vel_theta, packet2.rcac_vel_theta);
    EXPECT_EQ(packet1.ii_att, packet2.ii_att);
    EXPECT_EQ(packet1.rcac_att_z, packet2.rcac_att_z);
    EXPECT_EQ(packet1.rcac_att_u, packet2.rcac_att_u);
    EXPECT_EQ(packet1.rcac_att_theta, packet2.rcac_att_theta);
    EXPECT_EQ(packet1.ii_rate, packet2.ii_rate);
    EXPECT_EQ(packet1.rcac_rate_z, packet2.rcac_rate_z);
    EXPECT_EQ(packet1.rcac_rate_u, packet2.rcac_rate_u);
    EXPECT_EQ(packet1.rcac_rate_theta, packet2.rcac_rate_theta);
}

#ifdef TEST_INTEROP
TEST(rcac_interop, RCAC_POS_VEL_VARIABLES)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_rcac_pos_vel_variables_t packet_c {
         93372036854775807ULL, 93372036854776311ULL, 93372036854776815ULL, 93372036854777319ULL, 93372036854777823ULL, { 297.0, 298.0 }, { 353.0, 354.0, 355.0 }, { 437.0, 438.0, 439.0 }, { 521.0, 522.0, 523.0 }, { 605.0, 606.0, 607.0 }, { 689.0, 690.0, 691.0 }, { 773.0, 774.0, 775.0, 776.0, 777.0, 778.0, 779.0, 780.0, 781.0 }, { 1025.0, 1026.0, 1027.0 }, { 1109.0, 1110.0, 1111.0 }, { 1193.0, 1194.0, 1195.0 }, { 1277.0, 1278.0, 1279.0 }, { 1361.0, 1362.0, 1363.0 }, { 1445.0, 1446.0, 1447.0, 1448.0, 1449.0, 1450.0, 1451.0, 1452.0, 1453.0, 1454.0, 1455.0, 1456.0 }, 249, 60
    };

    mavlink::rcac::msg::RCAC_POS_VEL_VARIABLES packet_in{};
    packet_in.timestamp = 93372036854775807ULL;
    packet_in.rcac_alpha = {{ 297.0, 298.0 }};
    packet_in.ii_pos = 93372036854776311ULL;
    packet_in.switch_pos = 249;
    packet_in.rcac_pos_z = {{ 353.0, 354.0, 355.0 }};
    packet_in.rcac_pos_u = {{ 437.0, 438.0, 439.0 }};
    packet_in.rcac_pos_theta = {{ 521.0, 522.0, 523.0 }};
    packet_in.ii_vel = 93372036854776815ULL;
    packet_in.switch_vel = 60;
    packet_in.rcac_vel_z = {{ 605.0, 606.0, 607.0 }};
    packet_in.rcac_vel_u = {{ 689.0, 690.0, 691.0 }};
    packet_in.rcac_vel_theta = {{ 773.0, 774.0, 775.0, 776.0, 777.0, 778.0, 779.0, 780.0, 781.0 }};
    packet_in.ii_att = 93372036854777319ULL;
    packet_in.rcac_att_z = {{ 1025.0, 1026.0, 1027.0 }};
    packet_in.rcac_att_u = {{ 1109.0, 1110.0, 1111.0 }};
    packet_in.rcac_att_theta = {{ 1193.0, 1194.0, 1195.0 }};
    packet_in.ii_rate = 93372036854777823ULL;
    packet_in.rcac_rate_z = {{ 1277.0, 1278.0, 1279.0 }};
    packet_in.rcac_rate_u = {{ 1361.0, 1362.0, 1363.0 }};
    packet_in.rcac_rate_theta = {{ 1445.0, 1446.0, 1447.0, 1448.0, 1449.0, 1450.0, 1451.0, 1452.0, 1453.0, 1454.0, 1455.0, 1456.0 }};

    mavlink::rcac::msg::RCAC_POS_VEL_VARIABLES packet2{};

    mavlink_msg_rcac_pos_vel_variables_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.timestamp, packet2.timestamp);
    EXPECT_EQ(packet_in.rcac_alpha, packet2.rcac_alpha);
    EXPECT_EQ(packet_in.ii_pos, packet2.ii_pos);
    EXPECT_EQ(packet_in.switch_pos, packet2.switch_pos);
    EXPECT_EQ(packet_in.rcac_pos_z, packet2.rcac_pos_z);
    EXPECT_EQ(packet_in.rcac_pos_u, packet2.rcac_pos_u);
    EXPECT_EQ(packet_in.rcac_pos_theta, packet2.rcac_pos_theta);
    EXPECT_EQ(packet_in.ii_vel, packet2.ii_vel);
    EXPECT_EQ(packet_in.switch_vel, packet2.switch_vel);
    EXPECT_EQ(packet_in.rcac_vel_z, packet2.rcac_vel_z);
    EXPECT_EQ(packet_in.rcac_vel_u, packet2.rcac_vel_u);
    EXPECT_EQ(packet_in.rcac_vel_theta, packet2.rcac_vel_theta);
    EXPECT_EQ(packet_in.ii_att, packet2.ii_att);
    EXPECT_EQ(packet_in.rcac_att_z, packet2.rcac_att_z);
    EXPECT_EQ(packet_in.rcac_att_u, packet2.rcac_att_u);
    EXPECT_EQ(packet_in.rcac_att_theta, packet2.rcac_att_theta);
    EXPECT_EQ(packet_in.ii_rate, packet2.ii_rate);
    EXPECT_EQ(packet_in.rcac_rate_z, packet2.rcac_rate_z);
    EXPECT_EQ(packet_in.rcac_rate_u, packet2.rcac_rate_u);
    EXPECT_EQ(packet_in.rcac_rate_theta, packet2.rcac_rate_theta);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(rcac, RCAC_MODE_SC)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::rcac::msg::RCAC_MODE_SC packet_in{};
    packet_in.timestamp = 93372036854775807ULL;
    packet_in.RCAC_switch = 73.0;
    packet_in.PID_scale_f = 101.0;

    mavlink::rcac::msg::RCAC_MODE_SC packet1{};
    mavlink::rcac::msg::RCAC_MODE_SC packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.timestamp, packet2.timestamp);
    EXPECT_EQ(packet1.RCAC_switch, packet2.RCAC_switch);
    EXPECT_EQ(packet1.PID_scale_f, packet2.PID_scale_f);
}

#ifdef TEST_INTEROP
TEST(rcac_interop, RCAC_MODE_SC)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_rcac_mode_sc_t packet_c {
         93372036854775807ULL, 73.0, 101.0
    };

    mavlink::rcac::msg::RCAC_MODE_SC packet_in{};
    packet_in.timestamp = 93372036854775807ULL;
    packet_in.RCAC_switch = 73.0;
    packet_in.PID_scale_f = 101.0;

    mavlink::rcac::msg::RCAC_MODE_SC packet2{};

    mavlink_msg_rcac_mode_sc_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.timestamp, packet2.timestamp);
    EXPECT_EQ(packet_in.RCAC_switch, packet2.RCAC_switch);
    EXPECT_EQ(packet_in.PID_scale_f, packet2.PID_scale_f);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
