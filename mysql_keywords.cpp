#include <QList>
#include <QString>

static QList<QString> keywords = {
    "<>",
    "ACTION",
    "ADD",
    "AES_DECRYPT",
    "AES_ENCRYPT",
    "AFTER",
    "AGAINST",
    "AGGREGATE",
    "ALL",
    "ALTER",
    "ANALYSE",
    "ANALYZE",
    "AND",
    "ARCHIVE",
    "AS",
    "ASC",
    "AT",
    "AUTHORS",
    "AUTOCOMMIT",
    "AUTOEXTEND_SIZE",
    "AVG_ROW_LENGTH",
    "BEFORE",
    "BEGIN",
    "BETWEEN",
    "BIGINT",
    "BINARY",
    "BINLOG",
    "BOOL",
    "BOOLEAN",
    "BOTH",
    "BTREE",
    "BY",
    "BYTE",
    "CACHE",
    "CALL",
    "CASCADE",
    "CASE",
    "CATALOG_NAME",
    "CEIL",
    "CEILING",
    "CHAIN",
    "CHANGE",
    "CHAR",
    "CHARACTER",
    "CHECK",
    "CHECKSUM",
    "CIPHER",
    "CLASS_ORIGIN",
    "CLIENT",
    "CLOSE",
    "COALESCE",
    "CODE",
    "COLLATE",
    "COLLATION",
    "COLUMN",
    "COLUMNS",
    "COLUMN_NAME",
    "COMMENT",
    "COMMIT",
    "COMMITTED",
    "COMPACT",
    "COMPLETION",
    "COMPRESSED",
    "CONCURRENT",
    "CONDITION",
    "CONNECTION",
    "CONSISTENT",
    "CONSTRAINT",
    "CONSTRAINT_CATALOG",
    "CONSTRAINT_NAME",
    "CONSTRAINT_SCHEMA",
    "CONTINUE",
    "CONTRIBUTORS",
    "CONVERT",
    "COUNT",
    "CREATE",
    "CROSS",
    "CSV",
    "CURRENT_USER",
    "CURSOR",
    "CURSOR_NAME",
    "DATA",
    "DATABASE",
    "DATABASES",
    "DATAFILE",
    "DATE",
    "DATETIME",
    "DATE_ADD",
    "DATE_SUB",
    "DAY",
    "DAY_HOUR",
    "DAY_MINUTE",
    "DAY_SECOND",
    "DEALLOCATE",
    "DEC",
    "DECIMAL",
    "DECLARE",
    "DEFAULT",
    "DEFINER",
    "DELAYED",
    "DELAY_KEY_WRITE",
    "DELETE",
    "DESC",
    "DESCRIBE",
    "DES_KEY_FILE",
    "DIRECTORY",
    "DISABLE",
    "DISCARD",
    "DISTINCT",
    "DISTINCTROW",
    "DO",
    "DROP",
    "DUAL",
    "DUMPFILE",
    "DUPLICATE",
    "DYNAMIC",
    "ELSE",
    "ELSEIF",
    "ENABLE",
    "ENCLOSED",
    "END",
    "ENDS",
    "ENGINE",
    "ENGINES",
    "ERRORS",
    "ESCAPE",
    "ESCAPED",
    "EVENT",
    "EVENTS",
    "EVERY",
    "EXECUTE",
    "EXISTS",
    "EXIT",
    "EXPANSION",
    "EXPLAIN",
    "EXTENDED",
    "EXTENT_SIZE",
    "FALSE",
    "FAST",
    "FEDERATED",
    "FETCH",
    "FIELDS",
    "FILE",
    "FIRST",
    "FIXED",
    "FLOAT4",
    "FLOAT8",
    "FLOOR",
    "FLUSH",
    "FOR",
    "FORCE",
    "FOREIGN",
    "FROM",
    "FULL",
    "FULLTEXT",
    "FUNCTION",
    "GEOMETRYCOLLECTIONFROMTEXT",
    "GEOMETRYCOLLECTIONFROMWKB",
    "GEOMETRYFROMTEXT",
    "GEOMETRYFROMWKB",
    "GLOBAL",
    "GRANT",
    "GRANTS",
    "GROUP",
    "HANDLER",
    "HAVING",
    "HEAP",
    "HELP",
    "HELP_DATE",
    "HELP_VERSION",
    "HIGH_PRIORITY",
    "HOST",
    "HOSTS",
    "HOUR",
    "HOUR_MINUTE",
    "HOUR_SECOND",
    "IDENTIFIED",
    "IF",
    "IGNORE",
    "IGNORE_SERVER_IDS",
    "IMPORT",
    "IN",
    "INDEX",
    "INDEXES",
    "INFILE",
    "INITIAL_SIZE",
    "INNER",
    "INNODB",
    "INSERT",
    "INSERT_METHOD",
    "INSTALL",
    "INT1",
    "INT2",
    "INT3",
    "INT4",
    "INT8",
    "INTEGER",
    "INTERVAL",
    "INTO",
    "IO_THREAD",
    "IS",
    "ISOLATION",
    "ISSUER",
    "ITERATE",
    "JOIN",
    "KEY",
    "KEYS",
    "KEY_BLOCK_SIZE",
    "KILL",
    "LAST",
    "LEADING",
    "LEAVE",
    "LEFT",
    "LEVEL",
    "LIKE",
    "LIMIT",
    "LINES",
    "LINESTRINGFROMTEXT",
    "LINESTRINGFROMWKB",
    "LOAD",
    "LOCAL",
    "LOCK",
    "LOGFILE",
    "LOGS",
    "LONG",
    "LONGBINARY",
    "LOOP",
    "LOW_PRIORITY",
    "MASTER",
    "MASTER_BIND",
    "MASTER_CONNECT_RETRY",
    "MASTER_HEARTBEAT_PERIOD",
    "MASTER_HOST",
    "MASTER_LOG_FILE",
    "MASTER_LOG_POS",
    "MASTER_PASSWORD",
    "MASTER_PORT",
    "MASTER_SSL",
    "MASTER_SSL_CA",
    "MASTER_SSL_CERT",
    "MASTER_SSL_CIPHER",
    "MASTER_SSL_KEY",
    "MASTER_SSL_VERIFY_SERVER_CERT",
    "MASTER_USER",
    "MATCH",
    "MAX_CONNECTIONS_PER_HOUR",
    "MAX_QUERIES_PER_HOUR",
    "MAX_ROWS",
    "MAX_SIZE",
    "MAX_UPDATES_PER_HOUR",
    "MAX_USER_CONNECTIONS",
    "MEDIUM",
    "MEMORY",
    "MERGE",
    "MESSAGE_TEXT",
    "MIDDLEINT",
    "MINUTE",
    "MINUTE_SECOND",
    "MIN_ROWS",
    "MOD",
    "MODE",
    "MODIFY",
    "MONTH",
    "MRG_MYISAM",
    "MULTILINESTRINGFROMTEXT",
    "MULTILINESTRINGFROMWKB",
    "MULTIPOINTFROMTEXT",
    "MULTIPOINTFROMWKB",
    "MULTIPOLYGONFROMTEXT",
    "MULTIPOLYGONFROMWKB",
    "MUTEX",
    "MYISAM",
    "MYSQL_ERRNO",
    "NAME",
    "NATIONAL",
    "NATURAL",
    "NCHAR",
    "NDB",
    "NDBCLUSTER",
    "NEXT",
    "NO",
    "NODEGROUP",
    "NONE",
    "NOT",
    "NO_WRITE_TO_BINLOG",
    "NULL",
    "NUMERIC",
    "NVARCHAR",
    "OFFLINE",
    "OFFSET",
    "ON",
    "ONLINE",
    "OPEN",
    "OPTIMIZE",
    "OPTION",
    "OPTIONALLY",
    "OPTIONS",
    "OR",
    "ORDER",
    "OUTER",
    "OUTFILE",
    "OWNER",
    "PACK_KEYS",
    "PARSER",
    "PARTIAL",
    "PARTITION",
    "PARTITIONS",
    "PASSWORD",
    "PLUGIN",
    "PLUGINS",
    "POLYGONFROMTEXT",
    "POLYGONFROMWKB",
    "PORT",
    "POW",
    "POWER",
    "PRECISION",
    "PREPARE",
    "PRESERVE",
    "PREV",
    "PRIMARY",
    "PRIVILEGES",
    "PROCEDURE",
    "PROCESS",
    "PROCESSLIST",
    "PROFILE",
    "PROFILES",
    "PURGE",
    "QUERY",
    "QUICK",
    "READ",
    "REAL",
    "REBUILD",
    "REDUNDANT",
    "REFERENCES",
    "RELAYLOG",
    "RELAY_LOG_FILE",
    "RELAY_LOG_POS",
    "RELEASE",
    "RELOAD",
    "REMOVE",
    "RENAME",
    "REORGANIZE",
    "REPAIR",
    "REPEAT",
    "REPEATABLE",
    "REPLACE",
    "REPLICATION",
    "REQUIRE",
    "RESET",
    "RESIGNAL",
    "RESTRICT",
    "RETURN",
    "RETURNS",
    "REVOKE",
    "RIGHT",
    "RLIKE",
    "ROLLBACK",
    "ROWS",
    "ROW_FORMAT",
    "SAVEPOINT",
    "SCHEDULE",
    "SCHEMA",
    "SCHEMAS",
    "SCHEMA_NAME",
    "SECOND",
    "SECURITY",
    "SELECT",
    "SEPARATOR",
    "SERIAL",
    "SERIALIZABLE",
    "SERVER",
    "SESSION",
    "SET",
    "SHA",
    "SHA1",
    "SHA2",
    "SHARE",
    "SHOW",
    "SHUTDOWN",
    "SIGNAL",
    "SIGNED",
    "SLAVE",
    "SNAPSHOT",
    "SOCKET",
    "SONAME",
    "SOUNDS",
    "SPATIAL",
    "SQLSTATE",
    "SQL_BIG_RESULT",
    "SQL_BUFFER_RESULT",
    "SQL_CACHE",
    "SQL_CALC_FOUND_ROWS",
    "SQL_LOG_BIN",
    "SQL_NO_CACHE",
    "SQL_SLAVE_SKIP_COUNTER",
    "SQL_SMALL_RESULT",
    "SQL_THREAD",
    "SSL",
    "START",
    "STARTING",
    "STARTS",
    "STATUS",
    "STD",
    "STDDEV",
    "STOP",
    "STORAGE",
    "STRAIGHT_JOIN",
    "STRING",
    "SUBCLASS_ORIGIN",
    "SUBJECT",
    "SUPER",
    "TABLE",
    "TABLES",
    "TABLESPACE",
    "TABLE_NAME",
    "TEMPORARY",
    "TERMINATED",
    "THEN",
    "TIME",
    "TIMESTAMP",
    "TO",
    "TRAILING",
    "TRANSACTION",
    "TRIGGER",
    "TRIGGERS",
    "TRUE",
    "TRUNCATE",
    "TYPE",
    "UNCOMMITTED",
    "UNDO",
    "UNINSTALL",
    "UNION",
    "UNIQUE",
    "UNLOCK",
    "UNSIGNED",
    "UNTIL",
    "UPDATE",
    "UPGRADE",
    "USAGE",
    "USE",
    "USER",
    "USER_RESOURCES",
    "USE_FRM",
    "USING",
    "VALUE",
    "VALUES",
    "VARCHARACTER",
    "VARIABLE",
    "VARIABLES",
    "VARYING",
    "VIEW",
    "WAIT",
    "WARNINGS",
    "WHEN",
    "WHERE",
    "WHILE",
    "WITH",
    "WORK",
    "WRAPPER",
    "WRITE",
    "X509",
    "YEAR",
    "YEAR_MONTH",
    "ZEROFILL",
};
