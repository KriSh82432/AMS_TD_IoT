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

foreach ($filterArray as $val) {
    \Logs\Logs::AddEntryLog($val['UID'], $val['Time Stamp']);
}