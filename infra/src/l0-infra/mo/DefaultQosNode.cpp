

extern char * getEnbQosNode()
{
        return R"({
  "result": {
    "ENBFunction.QoSPBRMapping": [
      {
        "qCI": 5,
        "arpSegID": 1,
        "lchDirection": "Downlink",
        "pbrValue": 1
      },
      {
        "qCI": 5,
        "arpSegID": 2,
        "lchDirection": "Downlink",
        "pbrValue": 1
      },
      {
        "qCI": 5,
        "arpSegID": 3,
        "lchDirection": "Downlink",
        "pbrValue": 1
      },
      {
        "qCI": 6,
        "arpSegID": 1,
        "lchDirection": "Downlink",
        "pbrValue": 48
      },
      {
        "qCI": 6,
        "arpSegID": 2,
        "lchDirection": "Downlink",
        "pbrValue": 32
      },
      {
        "qCI": 6,
        "arpSegID": 3,
        "lchDirection": "Downlink",
        "pbrValue": 32
      },
      {
        "qCI": 6,
        "arpSegID": 3,
        "lchDirection": "Downlink",
        "pbrValue": 32
      },
      {
        "qCI": 7,
        "arpSegID": 1,
        "lchDirection": "Downlink",
        "pbrValue": 64
      },
      {
        "qCI": 7,
        "arpSegID": 2,
        "lchDirection": "Downlink",
        "pbrValue": 32
      },
      {
        "qCI": 7,
        "arpSegID": 3,
        "lchDirection": "Downlink",
        "pbrValue": 16
      },
      {
        "qCI": 8,
        "arpSegID": 1,
        "lchDirection": "Downlink",
        "pbrValue": 8
      },
      {
        "qCI": 8,
        "arpSegID": 2,
        "lchDirection": "Downlink",
        "pbrValue": 8
      },
      {
        "qCI": 8,
        "arpSegID": 3,
        "lchDirection": "Downlink",
        "pbrValue": 8
      },
      {
        "qCI": 9,
        "arpSegID": 1,
        "lchDirection": "Downlink",
        "pbrValue": 8
      },
      {
        "qCI": 9,
        "arpSegID": 2,
        "lchDirection": "Downlink",
        "pbrValue": 8
      },
      {
        "qCI": 9,
        "arpSegID": 3,
        "lchDirection": "Downlink",
        "pbrValue": 8
      },
      {
        "qCI": 5,
        "arpSegID": 1,
        "lchDirection": "Uplink",
        "pbrValue": 1
      },
      {
        "qCI": 5,
        "arpSegID": 2,
        "lchDirection": "Uplink",
        "pbrValue": 1
      },
      {
        "qCI": 5,
        "arpSegID": 3,
        "lchDirection": "Uplink",
        "pbrValue": 1
      },
      {
        "qCI": 6,
        "arpSegID": 1,
        "lchDirection": "Uplink",
        "pbrValue": 48
      },
      {
        "qCI": 6,
        "arpSegID": 2,
        "lchDirection": "Uplink",
        "pbrValue": 32
      },
      {
        "qCI": 6,
        "arpSegID": 3,
        "lchDirection": "Uplink",
        "pbrValue": 32
      },
      {
        "qCI": 7,
        "arpSegID": 1,
        "lchDirection": "Uplink",
        "pbrValue": 64
      },
      {
        "qCI": 7,
        "arpSegID": 2,
        "lchDirection": "Uplink",
        "pbrValue": 32
      },
      {
        "qCI": 7,
        "arpSegID": 3,
        "lchDirection": "Uplink",
        "pbrValue": 16
      },
      {
        "qCI": 8,
        "arpSegID": 1,
        "lchDirection": "Uplink",
        "pbrValue": 8
      },
      {
        "qCI": 8,
        "arpSegID": 2,
        "lchDirection": "Uplink",
        "pbrValue": 8
      },
      {
        "qCI": 8,
        "arpSegID": 3,
        "lchDirection": "Uplink",
        "pbrValue": 8
      },
      {
        "qCI": 9,
        "arpSegID": 1,
        "lchDirection": "Uplink",
        "pbrValue": 8
      },
      {
        "qCI": 9,
        "arpSegID": 2,
        "lchDirection": "Uplink",
        "pbrValue": 8
      },
      {
        "qCI": 9,
        "arpSegID": 3,
        "lchDirection": "Uplink",
        "pbrValue": 8
      }
    ],
    "ENBFunction.QoSServiceClass": [
      {
        "qCI": 1,
        "srvPacketDelay": 100,
        "srvPacketLoss": 0.01,
        "srvClassName": "CVoIP",
        "srvPrior": 2,
        "srvBearerType": "GBR",
        "prdPhrTimer": "sf1000",
        "phtPhrTimer": "sf10",
        "dlPathlossChgTh": "dB3",
        "rlcMode": "Unacknowledged Mode",
        "factorForQCI": 64,
        "meaGRP": "80",
        "discardTimer": "100"
      },
      {
        "qCI": 2,
        "srvPacketDelay": 150,
        "srvPacketLoss": 0.001,
        "srvClassName": "CLSoIP",
        "srvPrior": 4,
        "srvBearerType": "GBR",
        "prdPhrTimer": "sf1000",
        "phtPhrTimer": "sf10",
        "dlPathlossChgTh": "dB3",
        "rlcMode": "Unacknowledged Mode",
        "factorForQCI": 16,
        "meaGRP": "80",
        "discardTimer": "150"
      },
      {
        "qCI": 3,
        "srvPacketDelay": 50,
        "srvPacketLoss": 0.001,
        "srvClassName": "RealGaming",
        "srvPrior": 3,
        "srvBearerType": "GBR",
        "prdPhrTimer": "sf1000",
        "phtPhrTimer": "sf10",
        "dlPathlossChgTh": "dB3",
        "rlcMode": "Acknowledged Mode",
        "factorForQCI": 32,
        "meaGRP": "80",
        "discardTimer": "300"
      },
      {
        "qCI": 4,
        "srvPacketDelay": 300,
        "srvPacketLoss": 0.000001,
        "srvClassName": "BSoIP",
        "srvPrior": 5,
        "srvBearerType": "GBR",
        "prdPhrTimer": "sf1000",
        "phtPhrTimer": "sf10",
        "dlPathlossChgTh": "dB3",
        "rlcMode": "Acknowledged Mode",
        "factorForQCI": 8,
        "meaGRP": "80",
        "discardTimer": "300"
      },
      {
        "qCI": 5,
        "srvPacketDelay": 100,
        "srvPacketLoss": 0.000001,
        "srvClassName": "IMS Signaling",
        "srvPrior": 1,
        "srvBearerType": "Non-GBR",
        "prdPhrTimer": "sf1000",
        "phtPhrTimer": "sf10",
        "dlPathlossChgTh": "dB3",
        "rlcMode": "Acknowledged Mode",
        "factorForQCI": 1,
        "meaGRP": "80",
        "discardTimer": "infinity"
      },
      {
        "qCI": 6,
        "srvPacketDelay": 300,
        "srvPacketLoss": 0.000001,
        "srvClassName": "Prior IP Service",
        "srvPrior": 6,
        "srvBearerType": "Non-GBR",
        "prdPhrTimer": "sf1000",
        "phtPhrTimer": "sf10",
        "dlPathlossChgTh": "dB3",
        "rlcMode": "Acknowledged Mode",
        "factorForQCI": 72,
        "meaGRP": "80",
        "discardTimer": "300"
      },
      {
        "qCI": 7,
        "srvPacketDelay": 100,
        "srvPacketLoss": 0.001,
        "srvClassName": "LSoIP",
        "srvPrior": 7,
        "srvBearerType": "Non-GBR",
        "prdPhrTimer": "sf1000",
        "phtPhrTimer": "sf10",
        "dlPathlossChgTh": "dB3",
        "rlcMode": "Acknowledged Mode",
        "factorForQCI": 4,
        "meaGRP": "80",
        "discardTimer": "300"
      },
      {
        "qCI": 8,
        "srvPacketDelay": 300,
        "srvPacketLoss": 0.000001,
        "srvClassName": "VIP Default Bearer",
        "srvPrior": 8,
        "srvBearerType": "Non-GBR",
        "prdPhrTimer": "sf1000",
        "phtPhrTimer": "sf0",
        "dlPathlossChgTh": "dB3",
        "rlcMode": "Acknowledged Mode",
        "factorForQCI": 2,
        "meaGRP": "80",
        "discardTimer": "300"
      },
      {
        "qCI": 9,
        "srvPacketDelay": 300,
        "srvPacketLoss": 0.000001,
        "srvClassName": "NVIP Default Bearer",
        "srvPrior": 9,
        "srvBearerType": "Non-GBR",
        "prdPhrTimer": "sf1000",
        "phtPhrTimer": "sf10",
        "dlPathlossChgTh": "dB3",
        "rlcMode": "Acknowledged Mode",
        "factorForQCI": 1,
        "meaGRP": "80",
        "discardTimer": "300"
      },
      {
        "qCI": 256,
        "srvPacketDelay": 0,
        "srvPacketLoss": 0,
        "srvClassName": 256,
        "srvPrior": 1,
        "srvBearerType": "GBR",
        "prdPhrTimer": "sf1000",
        "phtPhrTimer": "sf0",
        "dlPathlossChgTh": "dB6",
        "rlcMode": "Acknowledged Mode",
        "factorForQCI": 1,
        "meaGRP": "80",
        "discardTimer": "300"
      }
    ]
  }
})";

}


