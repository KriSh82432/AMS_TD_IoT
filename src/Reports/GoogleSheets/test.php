<?php

require 'DB/DB.php';
require 'Config/Domain.php';

$Sql = 'SELECT U.Name, U.Domain, E.EntryTime FROM EntryLogs E INNER JOIN Users U ON E.UID=U.UID WHERE EntryTime>=? AND EntryTime<=? ORDER BY EntryTime';
$result = \DB\DbConn::Get()->PrepareAndExecute($Sql, ['1677151800', '1677160800']);
$data = [];

foreach ($result as $value) {
    $value["Domain"] = \Config\Domain::ToLabel($value['Domain']);
    $value["EntryTime"] = date('g:i A \a\t F j', $value["EntryTime"]);
    $data[] = array_values($value);
}

var_dump($data);

