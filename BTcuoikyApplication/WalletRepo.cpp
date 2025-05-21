#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Database.h"
#include "WalletEntity.cpp"
#include <cppconn/resultset.h>

class WalletRepo {
private:
	Database db;
	sql::Connection* con = db.getConnection();

public:
	void createWallet(int& accountId, double& amount, std::string& numWallet) {
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO wallet(num_wallet,account_id, amount, is_active) VALUES (?,?, ?, ?)");
			pstmt->setString(1, numWallet);
			pstmt->setInt(2, accountId);
			pstmt->setDouble(3, amount);
			pstmt->setBoolean(4, true);
			pstmt->execute();
			delete pstmt;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
			return;
		}
	}
	void updateAmountWallet(std::string& numWallet, double& amount) {
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE wallet SET amount = ? WHERE num_wallet = ? and is_active = true");
			pstmt->setDouble(1, amount);
			pstmt->setString(2, numWallet);
			pstmt->execute();
			delete pstmt;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
			return;
		}
	}
	bool lockWallet(int& id, bool& isActive) {
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE wallet SET is_active = ? WHERE id = ?");
			pstmt->setBoolean(1, isActive);
			pstmt->setInt(2, id);
			pstmt->execute();
			delete pstmt;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
			return false;
		}

		return true;
	}

	std::vector<WalletEntity> findAllWallets(const int& accountId) {
		std::vector<WalletEntity> wallets;
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM wallet WHERE account_id = ?");
			pstmt->setInt(1, accountId);

			sql::ResultSet* res = pstmt->executeQuery();
			while (res->next()) {
				WalletEntity walletResp = WalletEntity();
				walletResp.setId(res->getInt("id"));
				walletResp.setNumWallet(res->getString("num_wallet"));
				walletResp.setAccountId(res->getInt("account_id"));
				walletResp.setIsActive(res->getBoolean("is_active") == 1 ? "Hoat dong" : "Da Khoa");
				walletResp.setAmount(res->getDouble("amount"));
				wallets.push_back(walletResp);
			}
			delete res;
			delete pstmt;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
		}
		return wallets;
	}

	WalletEntity getWalletById(const int& id) {
		WalletEntity walletResp = WalletEntity();
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM wallet WHERE id = ? and is_active = true");
			pstmt->setInt(1, id);
			sql::ResultSet* res = pstmt->executeQuery();
			if (res->next()) {
				walletResp.setId(res->getInt("id"));
				walletResp.setNumWallet(res->getString("num_wallet"));
				walletResp.setAccountId(res->getInt("account_id"));
				walletResp.setIsActive(res->getBoolean("is_active") == 1 ? "Hoat dong" : "Da Khoa");
				walletResp.setAmount(std::stod(res->getString("amount")));
			}
			delete res;
			delete pstmt;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
		}
		return walletResp;
	}

	WalletEntity getDetailWalletByNumWall(const std::string& numWall) {
		WalletEntity walletResp = WalletEntity();
		try {
			sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM wallet WHERE num_wallet = ?");
			pstmt->setString(1, numWall);
			sql::ResultSet* res = pstmt->executeQuery();
			if (res->next()) {
				walletResp.setId(res->getInt("id"));
				walletResp.setNumWallet(res->getString("num_wallet"));
				walletResp.setAccountId(res->getInt("account_id"));
				walletResp.setIsActive(res->getBoolean("is_active") == 1 ? "Hoat dong" : "Da Khoa");
				walletResp.setAmount(res->getDouble("amount"));
			}
			delete res;
			delete pstmt;
		}
		catch (const sql::SQLException& e) {
			std::cerr << "SQL Error: " << e.what() << std::endl;
		}
		return walletResp;
	}
};