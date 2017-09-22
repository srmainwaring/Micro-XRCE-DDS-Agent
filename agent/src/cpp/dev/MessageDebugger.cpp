#include "MessageDebugger.h"

#include <agent/MessageHeader.h>
#include <agent/ObjectVariant.h>
#include <agent/Payloads.h>
#include <agent/SubMessageHeader.h>

#include <iomanip>

#define YELLOW "\e[1;33m"
#define RESTORE_COLOR "\e[0m"


namespace eprosima{
namespace micrortps{
namespace debug{

const std::string separator = " | ";
    
std::ostream& operator<<(std::ostream& stream, const MessageHeader& header)
{
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "<Header>" << std::endl;
    stream << "  - client_key: " <<  std::setw(10) << header.client_key() << std::endl;
    stream << "  - session_id: " << std::setw(4) << +header.session_id() << std::endl;
    stream << "  - stream_id: " << std::setw(4) << +header.stream_id() << std::endl;
    stream << "  - sequence_nr: " << std::setw(6) << header.sequence_nr();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const SubmessageHeader& submessage_header)
{
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    switch(submessage_header.submessage_id())
    {
        case CREATE:
            stream << "<Submessage> [CREATE]" << std::endl;
        break;
        case DELETE:
            stream << "<Submessage> [DELETE]" << std::endl;
        break;
        case WRITE_DATA:
            stream << "<Submessage> [WRITE_DATA]" << std::endl;
        break;
        case READ_DATA:
            stream << "<Submessage> [READ_DATA]" << std::endl;
        break;
        case DATA:
            stream << "<Submessage> [DATA]" << std::endl;
            break;
        case STATUS:
            stream << "<Submessage> [STATUS]" << std::endl;
        break;
    }
    stream << "  <Submessage header> " << std::endl;
    stream << "  - id: " << std::setw(4) << +submessage_header.submessage_id() << std::endl;
    stream << "  - flags: " << std::setw(4) << +submessage_header.flags() << std::endl;
    stream << "  - length: " << std::setw(6) << submessage_header.submessage_length();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Status& status)
{
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  <Payload>" << std::endl;
    stream << "  - result : " << status.result() << std::endl;
    stream << "  - object_id: " << status.object_id();
    return stream;
}

std::ostream& short_print(std::ostream& stream, const Status& status)
{
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "[Status" << separator;
    stream << "id: " << status.object_id() << separator;
    short_print(stream, status.result()) << "]";
}

std::ostream& operator<<(std::ostream& stream, const ResultStatus& status)
{
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  <ResultStatus>" << std::endl;
    stream << "  - request_id : " << status.request_id() << std::endl;
    stream << "  - status: " << std::setw(4) << +status.status() << std::endl;
    stream << "  - implementation_status: " << std::setw(4) << +status.implementation_status();
    return stream;
}

std::ostream& short_print(std::ostream& stream, const ResultStatus& status)
{    
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;

    stream << "#" << status.request_id() << separator;
    stream << std::setw(4) << +status.status() << " ";
    switch(status.status())
    {
        case STATUS_OK:
            stream << "OK";
        break;
        case STATUS_OK_MATCHED:
            stream << "OK_MATCHED";
        break;
        case STATUS_ERR_DDS_ERROR:
            stream << "ERR_DDS_ERROR";
        break;
        case STATUS_ERR_MISMATCH:
            stream << "ERR_MISMATCH";
        break;
        case STATUS_ERR_ALREADY_EXISTS:
            stream << "ERR_ALREADY_EXISTS";
        break;
        case STATUS_ERR_DENIED:
            stream << "ERR_DENIED";
        break;
        case STATUS_ERR_UNKNOWN_REFERENCE:
            stream << "ERR_UNKNOWN_REFERENCE";
        break;
        case STATUS_ERR_INVALID_DATA:
            stream << "ERR_INVALID_DATA";
        break;
        case STATUS_ERR_INCOMPATIBLE:
            stream << "ERR_INCOMPATIBLE";
        break;
        case STATUS_ERR_RESOURCES:
            stream << "ERR_RESOURCES";
        break;
        default:
            stream << "UNKNOWN";
    }
    stream << separator;
    stream << std::setw(4) << +status.implementation_status() << " ";
    switch(status.implementation_status())
    {
        case STATUS_LAST_OP_NONE:
            stream << "NONE";
        break;
        case STATUS_LAST_OP_CREATE:
            stream << "CREATE";
        break;
        case STATUS_LAST_OP_UPDATE:
            stream << "UPDATE";
        break;
        case STATUS_LAST_OP_DELETE:
            stream << "DELETE";
        break;
        case STATUS_LAST_OP_LOOKUP:
            stream << "LOOKUP";
        break;
        case STATUS_LAST_OP_READ:
            stream << "READ";
        break;
        case STATUS_LAST_OP_WRITE:
            stream << "WRITE";
        break;
        default:
            stream << "UNKNOWN";
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const CREATE_PAYLOAD& create_payload)
{ 
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  <Payload>" << std::endl;
    stream << "  - request_id : " << create_payload.request_id() << std::endl;
    stream << "  - object_id: " << create_payload.object_id() << std::endl;
    stream << "  - object_representation: " << create_payload.object_representation();
    return stream;   
}

std::ostream& operator<<(std::ostream& stream, const OBJK_PUBLISHER_Representation& data)
{
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  <Publisher>" << std::endl;
    stream << "  - string_size: " << std::setw(8) << data.as_string().size() << std::endl;
    stream << "  - string: " << data.as_string() << std::endl;
    stream << "  - participan_id: " << data.participant_id();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const OBJK_SUBSCRIBER_Representation& data)
{
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  <Subscriber>" << std::endl;
    stream << "  - string_size: " << std::setw(8) << data.as_string().size() << std::endl;
    stream << "  - string: " << data.as_string() << std::endl;
    stream << "  - participan_id: " << data.participant_id();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const OBJK_DATAWRITER_Representation& data)
{
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  <Data writer>" << std::endl;
    stream << "  - string_size: " << std::setw(8) << data.as_string().size() << std::endl;
    stream << "  - string: " << data.as_string() << std::endl;
    stream << "  - participan_id: " << data.participant_id() << std::endl;
    stream << "  - publisher_id: " << data.publisher_id();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const OBJK_DATAREADER_Representation& data)
{
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  <Data Reader>" << std::endl;
    stream << "  - string_size: " << std::setw(8) << data.as_string().size() << std::endl;
    stream << "  - string: " << data.as_string() << std::endl;
    stream << "  - participan_id: " << data.participant_id() << std::endl;
    stream << "  - subscriber_id: " << data.subscriber_id();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const ObjectVariant& object_representation)
{ 
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  - Kind " << std::setw(4) << +object_representation.discriminator() << std::endl;
    switch(object_representation.discriminator())
    {
        case OBJK_DATAWRITER:
            stream << object_representation.data_writer();
        break;

        case OBJK_DATAREADER:
            stream << object_representation.data_reader();
        break;

        case OBJK_SUBSCRIBER:
            stream << object_representation.subscriber();
        break;

        case OBJK_PUBLISHER:
            stream << object_representation.publisher();
        break;
        default:
            stream << "No string representation for this kind of object";
        break;
    }
    
    return stream;   
}

std::ostream& operator<<(std::ostream& stream, const DELETE_PAYLOAD& delete_data)
{
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  <PayLoad>" << std::endl;
    stream << "  - request_id : " << delete_data.request_id() << std::endl;
    stream << "  - object_id: " << delete_data.object_id();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const SampleData& data)
{
    StreamScopedFlags flags_backup{stream};
    stream << data.serialized_data() << std::endl;
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const RT_Data& data)
{
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  - read_mode: " << std::setw(4) << +data._d() << std::endl;
    switch(data._d())
    {
        case READM_DATA:
        {
            stream << "    <Data>" << std::endl;
            stream << "    - serialized_data_size: " << data.data().serialized_data().size() << std::endl;
            stream << "    - serialized_data: " << data.data().serialized_data() << std::endl;
            break;
        }
        default:
        break;
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const WRITE_DATA_PAYLOAD& write_data)
{
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "  <Payload>" << std::endl;
    stream << "  - request_id : " << write_data.request_id() << std::endl;
    stream << "  - object_id: " << write_data.object_id();
    stream << "  - data: " << write_data.data_writer();
    return stream;
}

std::ostream& short_print(std::ostream& stream, const CREATE_PAYLOAD& create_payload)
{
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "[Create" << separator;
    stream << "#" << create_payload.request_id() << separator;
    stream << "id: " << create_payload.object_id() << separator;
    switch(create_payload.object_representation().discriminator())
    {
        case OBJK_PARTICIPANT:
            stream << "PARTICIPANT";
            break; 
        case OBJK_PUBLISHER:
            stream << "PUBLISHER" << separator;;
            stream << "id: " << create_payload.object_representation().publisher().participant_id() << separator;
            stream << "topic: " << create_payload.object_representation().publisher().as_string();
        break;
        case OBJK_SUBSCRIBER:
            stream << "SUBSCRIBER" << separator;;
            stream << "id: " << create_payload.object_representation().subscriber().participant_id() << separator;
            stream << "topic: " << create_payload.object_representation().subscriber().as_string();
        break;
        default:
            stream << "UNKNOWN";
        break;
    }
    stream << "]";
    return stream;
}

std::ostream& short_print(std::ostream& stream, const DELETE_PAYLOAD& delete_data)
{
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "[Delete" << separator;
    stream << "#" << delete_data.request_id() << separator;
    stream << "id: " << delete_data.object_id() << separator;
    stream << "]";
    return stream;
}

std::ostream& short_print(std::ostream& stream, const WRITE_DATA_PAYLOAD& write_data)
{
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "[Write data" << separator;
    stream << "#" << write_data.request_id() << separator;
    stream << "id: " << write_data.object_id() << separator;
    switch(write_data.data_writer()._d())
    {
        case READM_DATA:
        {
            stream << "DATA" << separator << "data size: " << write_data.data_writer().data().serialized_data().size();
            break;
        }
        default:
        break;
    }
    stream << "]";
    return stream;
}


std::ostream& short_print(std::ostream& stream, const READ_DATA_PAYLOAD& read_data)
{
    StreamScopedFlags flags_backup{stream};
    stream << std::showbase << std::internal << std::setfill('0') << std::hex;
    stream << "[Read data" << separator;
    stream << "#" << read_data.request_id() << separator;
    stream << "id: " << read_data.object_id() << separator;
    stream << "max messages: " << read_data.max_messages();
    stream << "]";
    return stream;
}

// void printl_data_submessage(const DataPayloadSpec* payload)
// {
//     char content[64];
//     const SampleKindSpec* kind = &payload->data_reader.sample_kind;
//     switch(payload->data_reader.read_mode)
//     {
//         case READ_MODE_DATA:
//             sprintf(content, "DATA | data size: %u",
//                     kind->data.serialized_data_size);
//         break;

//         case READ_MODE_SAMPLE:
//             sprintf(content, "DATA | sq_nr: %u | session time: %u | data size: %u",
//                     kind->sample.info.sequence_number,
//                     kind->sample.info.session_time_offset,
//                     kind->sample.data.serialized_data_size);
//         break;
//     }

//     printf("%s[Data | #%08X | id: %u | %s]%s\n", YELLOW,
//             payload->request_id,
//             payload->object_id,
//             content,
//             RESTORE_COLOR);
// }

// void print_read_data_submessage(const ReadDataPayloadSpec* payload)
// {
//     printf("  <Payload>\n");
//     printf("  - request_id: 0x%08X\n", payload->request_id);
//     printf("  - object_id: 0x%06X\n", payload->object_id);
//     printf("  - max_messages: %hu\n", payload->max_messages);
//     printf("  - read_mode: 0x%02X\n", payload->read_mode);
//     printf("  - max_elapsed_time: %u\n", payload->max_elapsed_time);
//     printf("  - max_rate: %u\n", payload->max_rate);
//     printf("  - expression_size: %u\n", payload->expression_size);
//     printf("  - content_filter_expression: %s\n", payload->content_filter_expression);
//     printf("  - max_samples: %hu\n", payload->max_samples);
//     printf("  - include_sample_info: 0x%02X\n", payload->include_sample_info);
//     printf("\n\n");
// }

// void print_data_submessage(const DataPayloadSpec* payload)
// {
//     printf("  <Payload>\n");
//     printf("  - request_id: 0x%08X\n", payload->request_id);
//     printf("  - object_id: 0x%06X\n", payload->object_id);
//     printf("  - read_mode: 0x%02X\n", payload->data_reader.read_mode);

//     const SampleKindSpec* kind = &payload->data_reader.sample_kind;
//     switch(payload->data_reader.read_mode)
//     {
//         case READ_MODE_DATA:
//             printf("    <Data>\n");
//             printf("    - serialized_data_size: 0x%08X\n", kind->data.serialized_data_size);
//             printf("    - serialized_data: %s\n", data_to_string(kind->data.serialized_data,
//                 kind->data.serialized_data_size));
//         break;

//         case READ_MODE_SAMPLE:
//             printf("    - state: 0x%02X\n", kind->sample.info.state);
//             printf("    - sequence_number: 0x%08X\n", kind->sample.info.sequence_number);
//             printf("    - session_time_offset: 0x%08X\n", kind->sample.info.session_time_offset);
//             printf("    - serialized_data_size: 0x%08X\n", kind->sample.data.serialized_data_size);
//             printf("    - serialized_data: %s\n", data_to_string(kind->sample.data.serialized_data,
//                 kind->sample.data.serialized_data_size));

//         break;
//     }
//     printf("\n\n");
// }



// const char* data_to_string(const uint8_t* data, uint32_t size)
// {
//     static char buffer[1024];
//     for(uint32_t i = 0; i < size; i++)
//         sprintf(buffer + 3 * i, "%02X ", data[i]);
//     sprintf(buffer + 5 * size, "\n");
//     return buffer;
// }
} // namespace debug
} // namespace micrortps
} // namespace eprosima