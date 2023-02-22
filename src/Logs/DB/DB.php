<?php

namespace Db {

    require_once __DIR__ . '/../Config/SqlConfig.php';
    
    class DbConn extends \mysqli
    {

        private static $instance;

        public static function Get(): self
        {
            if (self::$instance === null) {
                self::$instance = new self( \Config\SqlConfig::Host , \Config\SqlConfig::User, \Config\SqlConfig::Password, \Config\SqlConfig::Database);
                if (self::$instance->connect_error) {
                    throw new \Exception("DB connection failed: " . self::$instance->connect_error);
                }
            }
            return self::$instance;
        }

        public function PrepareAndExecute(string $Query, array $Args = null, bool $AsArrayObjects = false, string $TableClassName = null)
        {
            $stmt = $this->prepare($Query);
            if (!$stmt) {
                if(true) {
                }
                throw new \Exception("Unable to prepare sql statement");
            }
            if ($Args !== null) {
                $params = [];
                $types = array_reduce($Args, function ($string, $arg) use (&$params) {
                    $params[] = &$arg;
                    if (is_float($arg)) {
                        $string .= 'd';
                    } elseif (is_integer($arg)) {
                        $string .= 'i';
                    } elseif (is_string($arg)) {
                        $string .= 's';
                    } else {
                        $string .= 'b';
                    }
                    return $string;
                });
                array_unshift($params, $types);
                if (!call_user_func_array([$stmt, 'bind_param'], $params)) {
                    throw new \Exception("Unable to bind params");
                }
            }

            $StmtResult = $stmt->execute();
            if (!$StmtResult) {
                throw new \Exception($stmt->error, $stmt->errno);
            }

            $result = $stmt->get_result();
            if (!($result instanceof \mysqli_result)) {
                if ($StmtResult) {
                    if ($stmt->insert_id > 0) {
                        return $stmt->insert_id;
                    } else if ($stmt->affected_rows > 0) {
                        return $stmt->affected_rows;
                    } else {
                        return $StmtResult;
                    }
                }
                return false;
            }

            if ($result->num_rows > 0) {
                $Table = [];
                if ($AsArrayObjects) {
                    while ($Row = $result->fetch_object($TableClassName)) {
                        $Table[] = $Row;
                    }
                } else {
                    while ($Table[] = $result->fetch_assoc()) ;
                    \array_pop($Table);
                }
                return $Table;
            } else if ($StmtResult) {
                return [];
            } else {
                return null;
            }
        }
    }
}