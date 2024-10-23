#include "User.h"

User::User(string RegisterID, string RegisterPassword, string fullName, string address, string phone)
{
	this->RegisterID = RegisterID;
	this->RegisterPassword = RegisterPassword;
	this->fullName = fullName;
	this->address = address;
	this->phone = phone;
}

void User::Display()
{
	cout << "\n\nAccount ID : " << RegisterID
		<< " \n\nAccount Password : " << RegisterPassword
		<< " \n\nFull Name : " << fullName
		<< " \n\nAddress : " << address
		<< " \n\nPhone : " << phone << endl;
}


json User::ConvertToJson()
{
	return json({
			{"id",RegisterID},{"password",RegisterPassword}, {"name",fullName} , {"address",address} , {"phone",phone}
		});
}

void User::FromJson(json j)
{
	this->RegisterID = j["id"];
	this->RegisterPassword = j["password"];
	this->fullName = j["name"];
	this->address = j["address"];
	this->phone = j["phone"];
}
