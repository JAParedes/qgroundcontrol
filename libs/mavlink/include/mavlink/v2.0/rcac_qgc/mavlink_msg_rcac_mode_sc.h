#pragma once
// MESSAGE RCAC_MODE_SC PACKING

#define MAVLINK_MSG_ID_RCAC_MODE_SC 10003


typedef struct __mavlink_rcac_mode_sc_t {
 uint64_t timestamp; /*<  Time since system start*/
 float RCAC_switch; /*<  RCAC mode*/
 float PID_scale_f; /*<  PID scaling*/
} mavlink_rcac_mode_sc_t;

#define MAVLINK_MSG_ID_RCAC_MODE_SC_LEN 16
#define MAVLINK_MSG_ID_RCAC_MODE_SC_MIN_LEN 16
#define MAVLINK_MSG_ID_10003_LEN 16
#define MAVLINK_MSG_ID_10003_MIN_LEN 16

#define MAVLINK_MSG_ID_RCAC_MODE_SC_CRC 199
#define MAVLINK_MSG_ID_10003_CRC 199



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_RCAC_MODE_SC { \
    10003, \
    "RCAC_MODE_SC", \
    3, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_rcac_mode_sc_t, timestamp) }, \
         { "RCAC_switch", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_rcac_mode_sc_t, RCAC_switch) }, \
         { "PID_scale_f", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_rcac_mode_sc_t, PID_scale_f) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_RCAC_MODE_SC { \
    "RCAC_MODE_SC", \
    3, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_rcac_mode_sc_t, timestamp) }, \
         { "RCAC_switch", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_rcac_mode_sc_t, RCAC_switch) }, \
         { "PID_scale_f", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_rcac_mode_sc_t, PID_scale_f) }, \
         } \
}
#endif

/**
 * @brief Pack a rcac_mode_sc message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp  Time since system start
 * @param RCAC_switch  RCAC mode
 * @param PID_scale_f  PID scaling
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rcac_mode_sc_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t timestamp, float RCAC_switch, float PID_scale_f)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RCAC_MODE_SC_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, RCAC_switch);
    _mav_put_float(buf, 12, PID_scale_f);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN);
#else
    mavlink_rcac_mode_sc_t packet;
    packet.timestamp = timestamp;
    packet.RCAC_switch = RCAC_switch;
    packet.PID_scale_f = PID_scale_f;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RCAC_MODE_SC;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RCAC_MODE_SC_MIN_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_CRC);
}

/**
 * @brief Pack a rcac_mode_sc message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp  Time since system start
 * @param RCAC_switch  RCAC mode
 * @param PID_scale_f  PID scaling
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rcac_mode_sc_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t timestamp,float RCAC_switch,float PID_scale_f)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RCAC_MODE_SC_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, RCAC_switch);
    _mav_put_float(buf, 12, PID_scale_f);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN);
#else
    mavlink_rcac_mode_sc_t packet;
    packet.timestamp = timestamp;
    packet.RCAC_switch = RCAC_switch;
    packet.PID_scale_f = PID_scale_f;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RCAC_MODE_SC;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RCAC_MODE_SC_MIN_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_CRC);
}

/**
 * @brief Encode a rcac_mode_sc struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param rcac_mode_sc C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rcac_mode_sc_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_rcac_mode_sc_t* rcac_mode_sc)
{
    return mavlink_msg_rcac_mode_sc_pack(system_id, component_id, msg, rcac_mode_sc->timestamp, rcac_mode_sc->RCAC_switch, rcac_mode_sc->PID_scale_f);
}

/**
 * @brief Encode a rcac_mode_sc struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rcac_mode_sc C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rcac_mode_sc_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_rcac_mode_sc_t* rcac_mode_sc)
{
    return mavlink_msg_rcac_mode_sc_pack_chan(system_id, component_id, chan, msg, rcac_mode_sc->timestamp, rcac_mode_sc->RCAC_switch, rcac_mode_sc->PID_scale_f);
}

/**
 * @brief Send a rcac_mode_sc message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp  Time since system start
 * @param RCAC_switch  RCAC mode
 * @param PID_scale_f  PID scaling
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_rcac_mode_sc_send(mavlink_channel_t chan, uint64_t timestamp, float RCAC_switch, float PID_scale_f)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RCAC_MODE_SC_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, RCAC_switch);
    _mav_put_float(buf, 12, PID_scale_f);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_MODE_SC, buf, MAVLINK_MSG_ID_RCAC_MODE_SC_MIN_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_CRC);
#else
    mavlink_rcac_mode_sc_t packet;
    packet.timestamp = timestamp;
    packet.RCAC_switch = RCAC_switch;
    packet.PID_scale_f = PID_scale_f;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_MODE_SC, (const char *)&packet, MAVLINK_MSG_ID_RCAC_MODE_SC_MIN_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_CRC);
#endif
}

/**
 * @brief Send a rcac_mode_sc message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_rcac_mode_sc_send_struct(mavlink_channel_t chan, const mavlink_rcac_mode_sc_t* rcac_mode_sc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_rcac_mode_sc_send(chan, rcac_mode_sc->timestamp, rcac_mode_sc->RCAC_switch, rcac_mode_sc->PID_scale_f);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_MODE_SC, (const char *)rcac_mode_sc, MAVLINK_MSG_ID_RCAC_MODE_SC_MIN_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_CRC);
#endif
}

#if MAVLINK_MSG_ID_RCAC_MODE_SC_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_rcac_mode_sc_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t timestamp, float RCAC_switch, float PID_scale_f)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, RCAC_switch);
    _mav_put_float(buf, 12, PID_scale_f);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_MODE_SC, buf, MAVLINK_MSG_ID_RCAC_MODE_SC_MIN_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_CRC);
#else
    mavlink_rcac_mode_sc_t *packet = (mavlink_rcac_mode_sc_t *)msgbuf;
    packet->timestamp = timestamp;
    packet->RCAC_switch = RCAC_switch;
    packet->PID_scale_f = PID_scale_f;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_MODE_SC, (const char *)packet, MAVLINK_MSG_ID_RCAC_MODE_SC_MIN_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN, MAVLINK_MSG_ID_RCAC_MODE_SC_CRC);
#endif
}
#endif

#endif

// MESSAGE RCAC_MODE_SC UNPACKING


/**
 * @brief Get field timestamp from rcac_mode_sc message
 *
 * @return  Time since system start
 */
static inline uint64_t mavlink_msg_rcac_mode_sc_get_timestamp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field RCAC_switch from rcac_mode_sc message
 *
 * @return  RCAC mode
 */
static inline float mavlink_msg_rcac_mode_sc_get_RCAC_switch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field PID_scale_f from rcac_mode_sc message
 *
 * @return  PID scaling
 */
static inline float mavlink_msg_rcac_mode_sc_get_PID_scale_f(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a rcac_mode_sc message into a struct
 *
 * @param msg The message to decode
 * @param rcac_mode_sc C-struct to decode the message contents into
 */
static inline void mavlink_msg_rcac_mode_sc_decode(const mavlink_message_t* msg, mavlink_rcac_mode_sc_t* rcac_mode_sc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    rcac_mode_sc->timestamp = mavlink_msg_rcac_mode_sc_get_timestamp(msg);
    rcac_mode_sc->RCAC_switch = mavlink_msg_rcac_mode_sc_get_RCAC_switch(msg);
    rcac_mode_sc->PID_scale_f = mavlink_msg_rcac_mode_sc_get_PID_scale_f(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_RCAC_MODE_SC_LEN? msg->len : MAVLINK_MSG_ID_RCAC_MODE_SC_LEN;
        memset(rcac_mode_sc, 0, MAVLINK_MSG_ID_RCAC_MODE_SC_LEN);
    memcpy(rcac_mode_sc, _MAV_PAYLOAD(msg), len);
#endif
}
