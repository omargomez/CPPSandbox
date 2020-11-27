#include <cstdio>

struct Logger {
  virtual ~Logger() = default;
  virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger {
	ConsoleLogger(const char *aPrefix) :
		prefix{ aPrefix } {

	}
  void log_transfer(long from, long to, double amount) override {
    printf("[%s] %ld -> %ld: %f\n", prefix, from, to, amount);
  }
private:
	const char *prefix;
};

struct AccountDatabase {
	virtual ~AccountDatabase() = default;
	virtual void retrieveAmmount(long id, double amount) = 0;
	virtual void setAmount(long id, double amount) = 0;
};

struct InMemoryAccountDatabase : AccountDatabase {
	virtual void retrieveAmmount(long id, double amount) override {

	}

	virtual void setAmount(long id, double amount) override {

	}

};

struct FileLogger : Logger {
  void log_transfer(long from, long to, double amount) override {
    printf("[file] %ld,%ld,%f\n", from, to, amount);
  }
};

struct Bank {
  Bank(Logger& logger, AccountDatabase &aDatabase)
      : logger{ logger }, database { aDatabase } {}
  void make_transfer(long from, long to, double amount) {
    //
	  database.retrieveAmmount(from, amount);
	  database.setAmount(to, amount);
    logger.log_transfer(from, to, amount);
  }

  private:
  Logger& logger;
  AccountDatabase& database;
};

int main() {
	ConsoleLogger logger{ "##>" };
  InMemoryAccountDatabase theDatabase;
  Bank bank{ logger, theDatabase };
  bank.make_transfer(1000, 2000, 49.95);
  bank.make_transfer(2000, 4000, 20.00);
}
