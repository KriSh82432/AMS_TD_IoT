<?php

require 'GoogleSheets/GSheetsBase.php';
require 'Logs/Logs.php';

$Log = new \GoogleSheets\GSheetsBase\AMS(\GoogleSheets\Config\Credentials::credentialsPath, \GoogleSheets\Config\Credentials::sheetId);
$data = $Log->GetMultiDimArray($Log->GetAllRows('Sheet1'));

foreach ($data as $val) {
    \Logs\Logs::AddEntryLog($val['UID'], $val['Time Stamp']);
}