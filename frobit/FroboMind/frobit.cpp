#include <stdio.h>
#include <string.h>
#include <sstream>
#include "ros/ros.h"
#include "fmMsgs/adc.h"
#include "fmMsgs/encoder.h"
#include "fmMsgs/nmea.h"
#include "boost/lexical_cast.hpp"

ros::Publisher adc_pub;
ros::Publisher encoder_pub;
fmMsgs::encoder frobit_encoder;
fmMsgs::adc frobit_adc;

/* Parses from nmea message to frobit message */
void frobit_callback(const fmMsgs::nmea& msg) {

	if (msg.id == "RC") {
		if(msg.type == "POS") {
			//build first message
			frobit_encoder.header.stamp = msg.header.stamp;
			frobit_encoder.header.frame_id = "left";
			frobit_encoder.encoderticks = boost::lexical_cast<int>(msg.data[0]);

			//publish first message
			encoder_pub.publish(frobit_encoder);

			//build second message
			frobit_encoder.header.frame_id = "right";
			frobit_encoder.encoderticks = boost::lexical_cast<int>(msg.data[1]);

			//publish second message
			encoder_pub.publish(frobit_encoder);
		}

		if(msg.type == "ADC") {
			//build first message
			frobit_adc.header.stamp = msg.header.stamp;
			frobit_adc.header.frame_id = "left";
			frobit_adc.value = boost::lexical_cast<int>(msg.data[0]);

			//publish first message
			adc_pub.publish(frobit_adc);

			//build second message
			frobit_adc.header.frame_id = "right";
			frobit_adc.value = boost::lexical_cast<int>(msg.data[1]);

			//publish second message
			adc_pub.publish(frobit_adc);
		}
	}
}

/* sets up frobit parser node */
int main(int argc, char **argv) {
	ros::init(argc, argv, "frobit_parser");
	ros::NodeHandle nh;
	ros::NodeHandle n("~");

	std::string subscribe_topic_id;
	std::string adc_topic_id;
	std::string encoder_topic_id;

	n.param<std::string>("subscribe_topic_id", subscribe_topic_id,
			"/fmSensors/nmea");

	n.param<std::string>("adc_topic_id", adc_topic_id,
			"/fmExtractors/adc");
	n.param<std::string>("encoder_topic_id", encoder_topic_id,
			"/fmExtractors/encoder");

	ros::Subscriber sub = nh.subscribe(subscribe_topic_id, 10, frobit_callback);
	encoder_pub = nh.advertise<fmMsgs::encoder>(encoder_topic_id, 1);
	adc_pub = nh.advertise<fmMsgs::adc>(adc_topic_id, 1);

	ros::spin();
	return 0;
}

