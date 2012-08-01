#include <stdio.h>
#include <string.h>
#include <sstream>
#include "ros/ros.h"
#include "fmMsgs/nmea.h"
#include "fmMsgs/serial.h"
#include "boost/tokenizer.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"

#define ASCII_OFFSET '0'

ros::Publisher nmea_pub;
fmMsgs::nmea nmea_msg;
bool use_checksum;


typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

/* Parses from a string into two hex characters */
int atox(const char *s) {
	int ret = 0;
	int cnt = 8;
	while (cnt) {
		if ((*s >= '0') && (*s <= '9')) {
			ret <<= 4;
			ret += (*s - '0');
			cnt--;
			s++;
			continue;
		}
		if ((*s >= 'a') && (*s <= 'f')) {
			ret <<= 4;
			ret += (*s - 'a' + 10);
			cnt--;
			s++;
			continue;
		}
		if ((*s >= 'A') && (*s <= 'F')) {
			ret <<= 4;
			ret += (*s - 'A' + 10);
			cnt--;
			s++;
			continue;
		}
		break;
	}
	return ret;
}

/* Calculates expected checksum and compares to contained checksum */
bool verify_checksum(std::vector<std::string> tokens) {
	//Setup proper string
	std::string temp_str = "0x";
	temp_str.append(tokens.at(tokens.size() - 1).c_str());

	unsigned char expected_checksum = atox(
			tokens.at(tokens.size() - 1).c_str());
	unsigned char checksum = 0;
	unsigned char *string_breakdown;

	//Calculate check sum
	for (unsigned int i = 0; i < tokens.size() - 1; i++) {
		string_breakdown = (unsigned char*) tokens.at(i).c_str();

		for (unsigned int j = 0; j < tokens.at(i).length(); j++)
			if (string_breakdown[j] != '$')
				checksum ^= string_breakdown[j];

		//Remember the ','
		if (i < (tokens.size() - 2))
			checksum ^= ',';
	}

	return (checksum == expected_checksum);
}

/* Parses from serial_string message to nmea message */
void nmea_callback(const fmMsgs::serial::ConstPtr& msg) {
	std::string nmeastr(msg->data);
	boost::char_separator<char> sep("$,*\r");
	tokenizer tokens(nmeastr, sep);
	std::vector<std::string> nmea;

	nmea.assign(tokens.begin(), tokens.end());
	try {

		//build message
		nmea_msg.header.stamp = ros::Time::now();
		nmea_msg.id =  nmea.at(0).substr(0,2);
		nmea_msg.type = nmea.at(0).substr(2,3);
		nmea_msg.data.clear();
		for (int i = 1 ; i < nmea.size() ; i++ )
			nmea_msg.data.push_back( nmea.at(i).c_str() );

		if(use_checksum)
		{
			if (!verify_checksum(nmea))
			{
				ROS_WARN("NMEA string discarded due to faulty checksum");
			}
			else
				//publish message
				nmea_pub.publish(nmea_msg);
		}
		else
			//publish message
			nmea_pub.publish(nmea_msg);

	} catch (boost::bad_lexical_cast &) {
		ROS_WARN("nmea_parser: bad lexical cast");
	}
	}

/* sets up nmea parser node */
int main(int argc, char **argv) {
	ros::init(argc, argv, "nmea_parser");
	ros::NodeHandle nh;
	ros::NodeHandle n("~");

	std::string subscribe_topic_id;
	std::string publish_topic_id;

	n.param<std::string>("nmea_parser_sub", subscribe_topic_id,
			"/fmCSP/S0_rx_msg");
	n.param<std::string>("nmea_parser_pub", publish_topic_id,
			"/nmea");
	n.param<bool>("use_nmea_checksum" , use_checksum , false);

	ros::Subscriber sub = nh.subscribe(subscribe_topic_id, 10, nmea_callback);
	nmea_pub = nh.advertise<fmMsgs::nmea>(publish_topic_id, 1);

	ros::spin();
	return 0;
}

