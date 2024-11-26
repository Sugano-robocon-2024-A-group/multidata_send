#include <Arduino.h>
#include <CAN.h>

// setupReceiver関数: 受信の初期設定
void setupReceiver() {
  // 受信側の初期化が行われる際にメッセージをシリアルに表示
  Serial.println("CAN Receiver Initialized");
}

// setupSender関数: 送信の初期設定
void setupSender() {
  // 送信側の初期化が行われる際にメッセージをシリアルに表示
  Serial.println("CAN Sender Initialized");
}

// sendPacket関数: CANメッセージを送信する
void sendPacket(int PS4_Circle) {
  // 通常パケットの送信
  Serial.print("Sending packet ... ");
  
  // CANパケットを送信。ID: 0x12
  CAN.beginPacket(0x12);
  Serial.print("Sending 1 ");
  CAN.write(static_cast<uint8_t>(PS4_Circle));
  CAN.endPacket();  // 送信終了
  
  Serial.println("done");

}


// receivePacket関数: CANメッセージを受信し、内容を表示する
void receivePacket() {
  int packetSize = CAN.parsePacket();  // 受信したパケットのサイズを取得

  if (packetSize) {  // パケットが受信された場合
    Serial.print("Received ");

    // 拡張パケットの場合
    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    // RTRパケットの場合
    if (CAN.packetRtr()) {
      Serial.print("RTR ");
    }

    // パケットIDを表示
    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    // RTRパケットの場合、要求された長さを表示
    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      // 通常パケットの場合、受信データの長さを表示
      Serial.print(" and length ");
      Serial.println(packetSize);

      // データをシリアルに表示
      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }
    Serial.println();
  }
}
