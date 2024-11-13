#pragma once
#include <string>
#include <stdexcept>
#include <cstdint>
#include <vector>

class TiXmlElement;

namespace config {

    // XML 파싱중에 발생할 수 있는 에러를 처리하기 위한 사용자 정의 예외 구조체
    struct ParseError : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    // 특정 경로와 관련된 정보 저장. 네트워크 전송과 관련된 설정 보관
    struct Route {

        void Load(TiXmlElement* sub);

        //Path 정보
        std::string path;

        // QAM 시스템의 목적지 정보
        std::string qam_destination;

        // QAM 시스템 이름
        std::string qam_name;

        // 전송 목적지
        std::string destination;

        // 목적지 포트 번호
        std::string destination_port;

        // 멀티캐스트 주소
        std::string multicast_address;
    };

    struct SDV {
        void Load(TiXmlElement* sub);
        std::vector<Route> routes;
        std::string qam_ip = "127.0.0.1";
        uint16_t qam_port = 554;
    };

    SDV Load(const std::string& file_path);
}



