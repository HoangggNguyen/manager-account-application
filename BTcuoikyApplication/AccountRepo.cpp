#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Database.h"
#include "AccountEntity.cpp"
#include "PersonalUser.cpp"
#include "AccountDTO.cpp"
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

class AccountRepo
{
private:
	Database db;
	sql::Connection* con = db.getConnection();

public:
	std::string timeToDateString(time_t t) {
		std::tm tm_struct;
		localtime_s(&tm_struct, &t);
		std::ostringstream oss;
		oss << std::put_time(&tm_struct, "%Y-%m-%d");
		return oss.str();
	}

	void createAccount(const std::string& userName, const std::string& password, bool isActive, const std::string& maker) {
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO account(user_name, password, is_active, maker) VALUES (?, ?, ?, ?)");
			pstmt->setString(1, userName);
			pstmt->setString(2, password);
			pstmt->setBoolean(3, isActive);
			pstmt->setString(4, maker);
			pstmt->execute();
			delete pstmt;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
			return;
		}
	}

	void createPersonalUser(std::string& fullName, time_t& dateOfBirth, bool& gender, std::string& address, std::string& phoneNumber, int& accountId, std::string& email) {
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO account_personal (fullname, date_of_birth, address, phonenumber, email, gender, account_id) VALUES(?, ?, ?, ?, ?, ?, ?)");
			pstmt->setString(1, fullName);

			std::string dob = timeToDateString(dateOfBirth);
			pstmt->setDateTime(2, dob);

			pstmt->setString(3, address);
			pstmt->setString(4, phoneNumber);
			pstmt->setString(5, email);
			pstmt->setBoolean(6, gender);
			pstmt->setInt(7, accountId);

			pstmt->execute();
			delete pstmt;

		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
			return;
		}
	}

	void deleteAccount(const std::string& userName) {
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE account SET `is_active` = '0' WHERE (`user_name` = ?);");
			pstmt->setString(1, userName);
			pstmt->execute();
			delete pstmt;
			std::cout << "Deleted account of user: " << userName << std::endl;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
			return;
		}
	}

	void deleteAccountPersonal(const int& accountId) {
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE account_personal SET `is_active` = '0' WHERE (`account_id` = ?);");
			pstmt->setInt(1, accountId);
			pstmt->execute();
			delete pstmt;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
			return;
		}
	}

	void updatePass(const std::string& userName, const std::string& newPassword) {
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE account SET password = ? WHERE user_name = ?");
			pstmt->setString(1, newPassword);
			pstmt->setString(2, userName);
			pstmt->execute();
			delete pstmt;
			std::cout << "Updated account: " << userName << std::endl;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
			return;
		}
	}

	AccountEntity getAccount(const std::string& userName) {
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM account WHERE user_name = ?");
			pstmt->setString(1, userName);
			sql::ResultSet* res = pstmt->executeQuery();
			AccountEntity accountResp = AccountEntity();

			if (res->next()) {
				accountResp.setId(res->getInt("id"));
				accountResp.setUserName(res->getString("user_name"));
				accountResp.setPassword(res->getString("password"));
				accountResp.setIsActive(res->getBoolean("is_active") == 1 ? true : false);
				accountResp.setMaker(res->getString("maker"));

				//std::cout << "Username: " << res->getString("user_name") << std::endl;
				//std::cout << "Username: " << res->getString("user_name") << std::endl;
				//std::cout << "Password: " << res->getString("password") << std::endl;
			}

			delete res;
			delete pstmt;

			return accountResp;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
			return AccountEntity();
		}
	}

	bool checkAccountLogin(const std::string& userName, const std::string& password) {
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM account WHERE user_name = ? and password = ? and is_active = true");
			pstmt->setString(1, userName);
			pstmt->setString(2, password);
			sql::ResultSet* res = pstmt->executeQuery();
			bool isExist = false;

			if (res->next()) {
				isExist = true;
			}

			delete res;
			delete pstmt;

			return isExist;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
			return false;
		}
	}

	PersonalUser getPersonalUserByAccountId(int& accountId) {
		PersonalUser personaUser = PersonalUser();
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("select * from account_personal where account_id = ? and is_active = true and exists(select 1 from account where id = ? and is_active = true)");
			pstmt->setInt(1, accountId);
			pstmt->setInt(2, accountId);

			sql::ResultSet* res = pstmt->executeQuery();
			if (res->next()) {
				personaUser.setId(res->getInt("id"));
				personaUser.setAccountId(res->getInt("account_id"));
				personaUser.setIsActive(res->getBoolean("is_active") == 1 ? true : false);
				personaUser.setAddress(res->getString("address"));
				personaUser.setDateOfBirth(res->getString("date_of_birth"));
				personaUser.setEmail(res->getString("email"));
				personaUser.setFullName(res->getString("fullname"));
				personaUser.setGender(res->getBoolean("gender") == 1 ? "Nam" : "Nu");
				personaUser.setPhoneNumber(res->getString("phonenumber"));
			}

			delete res;
			delete pstmt;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
		}
		return personaUser;
	}
	std::vector<AccountDTO> findAllActiveAccounts() {
		std::vector<AccountDTO> accounts;
		try {
			std::string query =
				"SELECT a.user_name, a.created_date, a.maker, a.is_admin, "
				"b.fullname, b.date_of_birth, b.address, b.phonenumber, b.email, b.gender "
				"FROM account a "
				"LEFT JOIN account_personal b ON a.id = b.account_id "
				"WHERE a.is_active = true AND b.is_active = true";

			std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(query));
			std::unique_ptr<sql::ResultSet> rs(pstmt->executeQuery());

			while (rs->next()) {
				AccountDTO dto = AccountDTO();
				dto.setAddres(rs->getString("address"));
				dto.setDateOfBirth(rs->getString("date_of_birth"));
				dto.setEmail(rs->getString("email"));
				dto.setFullName(rs->getString("fullname"));
				dto.setAddres(rs->getString("address"));
				dto.setPhoneNumber(rs->getString("phonenumber"));
				dto.setGender(rs->getBoolean("gender") == 1 ? "Nam" : "Nu");
				dto.setUserName(rs->getString("user_name"));
				dto.setCreatedDate(rs->getString("created_date"));
				dto.setMaker(rs->getString("maker"));
				dto.setIsAdmin(rs->getBoolean("is_admin") == 1 ? "Admin" : "User");

				accounts.push_back(dto);
			}
		}
		catch (sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
		}

		return accounts;
	}

};