<?php

namespace Logs;

require __DIR__ . '/DB/DB.php';
require __DIR__ . '/../Logs/Config/Domain.php';

class Logs
{
    public static function AddUser(string $name, string $regNo, string $uid, string $domain)
    {
        $Sql = 'INSERT INTO Users(`Name`, `RegisterNo`, `UID`, `Domain`) VALUES(?, ?, ?, ?)';
        \DB\DbConn::Get()->PrepareAndExecute($Sql, [$name, $regNo, $uid, \Config\Domain::ToValue($domain)]);
    }

    public static function AddEntryLog(string $uid, string $entryTime)
    {
        $Sql = 'INSERT INTO EntryLogs(`EntryTime`, `UID`) VALUES(?, ?)';
        \DB\DbConn::Get()->PrepareAndExecute($Sql, [self::ToUnixTimeStamp($entryTime), $uid]);
    }

    public static function AddExitLog(string $uid, string $exitTime)
    {
        $Sql = 'UPDATE EntryLogs SET ExitTime=? WHERE UID=?';
        \DB\DbConn::Get()->PrepareAndExecute($Sql, [self::ToUnixTimeStamp($exitTime), $uid]);
    }

    public static function ToUnixTimeStamp(string $time)
    {
        return strtotime(str_replace('at', '', $time));
    }
}
