// MESSAGE RCAC_MODE_SC support class

#pragma once

namespace mavlink {
namespace rcac {
namespace msg {

/**
 * @brief RCAC_MODE_SC message
 *
 * RCAC mode and scale
 */
struct RCAC_MODE_SC : mavlink::Message {
    static constexpr msgid_t MSG_ID = 10003;
    static constexpr size_t LENGTH = 16;
    static constexpr size_t MIN_LENGTH = 16;
    static constexpr uint8_t CRC_EXTRA = 199;
    static constexpr auto NAME = "RCAC_MODE_SC";


    uint64_t timestamp; /*<  Time since system start */
    float RCAC_switch; /*<  RCAC mode */
    float PID_scale_f; /*<  PID scaling */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  timestamp: " << timestamp << std::endl;
        ss << "  RCAC_switch: " << RCAC_switch << std::endl;
        ss << "  PID_scale_f: " << PID_scale_f << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << timestamp;                     // offset: 0
        map << RCAC_switch;                   // offset: 8
        map << PID_scale_f;                   // offset: 12
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> timestamp;                     // offset: 0
        map >> RCAC_switch;                   // offset: 8
        map >> PID_scale_f;                   // offset: 12
    }
};

} // namespace msg
} // namespace rcac
} // namespace mavlink
