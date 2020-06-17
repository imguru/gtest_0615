
#include <gmock/gmock.h>

// 비가상함수에 대한 Mocking

struct Packet {};

class ConcreatPacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatPacketStream - AppendPacket\n");
	}
	const Packet* GetPacket(size_t packet_number) const {}
};


// C++에서는 의존성 주입을 2가지 모델로 구현 가능합니다.
// 1. 인터페이스 기반
//    : struct Interface {};  -> 명시적으로 함수가 약속됨.
// 2. 템플릿 기반 -> 암묵적으로 함수가 약속됨.
//    : 함수 호출에 대한 약속
//      함수에 대한 구현이 존재하는지 여부로 인터페이스를 만족하는지를 판단한다.
//      
template <typename PacketStream>
class PacketReader {
public:
	void ReadPackets(PacketStream* stream, size_t packet_num) { 
		printf("PacketReader - ReadPacket\n");
		stream->AppendPacket(nullptr);
	}
};

// 실제 제품 코드에서 사용하는 방식
TEST(PacketTest, Sample) {
	ConcreatPacketStream stream;
	PacketReader<ConcreatPacketStream> reader;

	reader.ReadPackets(&stream, 42);
}

// 1. ConcreatPacketStream에 대해서 Mocking
// 2. PacketReader를 통해 ReadPacket을 호출하였을 때, Stream에 대해서 AppendPacket이 제대로 호출되는지 여부를 검증하고 싶다.

class MockPacketStream {
public:
    // void AppendPacket(Packet* new_packet)
	// const Packet* GetPacket(size_t packet_number) const {}
	
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
};

TEST(PacketTest, Sample2) {
	MockPacketStream mock;
	PacketReader<MockPacketStream> reader; 

	EXPECT_CALL(mock, AppendPacket(nullptr));

	reader.ReadPackets(&mock, 42);
}















