<?php

require 'GoogleSheets/GSheetsBase.php';
require 'Logs/Logs.php';

$Log = new \GoogleSheets\GSheetsBase\AMS(\GoogleSheets\Config\Credentials::credentialsPath, \GoogleSheets\Config\Credentials::entryLogSheetId);
$data = $Log->GetMultiDimArray($Log->GetAllRows('Sheet1'));
$filterArray = [];
$duplicateArray = [];

foreach ($data as $val) {
    if (!in_array($val, $filterArray)) {
        $filterArray[] = $val;
    } else {
        $duplicateArray[] = $val;
    }
}
var_dump($duplicateArray);

foreach ($filterArray as $val) {
    var_dump($val);
    \Logs\Logs::AddEntryLog($val['UID'], $val['Time Stamp']);
}