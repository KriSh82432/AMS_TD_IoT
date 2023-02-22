<?php

namespace GoogleSheets\GSheetsBase;
require 'vendor/autoload.php';
require 'Config.php';

class AMS
{
    private $client;
    private string $sheetId;
    private string $credentials;
    private $service;
    private $spreadSheet;
    private $clear;

    public function __construct(string $path, string $sheetId)
    {
        $this->credentials = $path;
        $this->sheetId = $sheetId;
        $this->client = new \Google\Client();
        $this->client->setApplicationName('Google Sheets API');
        $this->client->setAuthConfig($this->credentials);
        $this->client->setAccessType('offline');
        $this->client->setScopes(['https://www.googleapis.com/auth/spreadsheets']);
        //$this->client->setPrompt('select_account consent');
        $this->service = new \Google\Service\Sheets($this->client);
        $this->spreadSheet = $this->service->spreadsheets->get($this->sheetId);
    }

    public function GetAllRows(string $sheetName) 
    {
        $response = $this->service->spreadsheets_values->get($this->sheetId, $sheetName);
        $values = $response->getValues();
        return $values;
    }

    public function GetSpecificRows(string $sheetName, string $range)
    {
        $response = $this->service->spreadsheets_values->get($this->sheetId, $sheetName . '!' . $range);
        $values = $response->getValues();
        return $values;
    }

    public function GetSpecificColumns(string $sheetName, string $range)
    {
        $response = $this->service->spreadsheets_values->get($this->sheetId, $sheetName . '!' . $range);
        $values = $response->getValues();
        return $values;
    }

    public function DeleteAllRows(string $sheetName)
    {
        $range = 'Sheet1!A2:ZZ';
        $values = $this->GetSpecificRows($this->sheetId, $range);
        $delete_range = 'Sheet1!A2:' . end($values) . count($values);
        $this->clear = new \Google\Service\Sheets\ClearValuesRequest();
        $request = $this->service->spreadsheets_values->clear($this->sheetId, $delete_range, $this->clear);
        return $request->getClearedRange();
    }

    public function DeleteRows(string $sheetName, string $range)
    {
        $this->clear = new \Google\Service\Sheets\ClearValuesRequest();
        $request = $this->service->spreadsheets_values->clear($this->sheetId, $sheetName . '!' . $range, $this->clear);
        return $request->getClearedRange();
    }

    public function GetMultiDimArray(array $values)
    {
        $headers = array_shift($values);
        $formatted_array = [];
        foreach ($values as $val) {
            $formatted_array[] = array_combine($headers, $val);
        }
        return $formatted_array;
    }

    public function GetAsJSON(array $values)
    {
        return json_encode($this->GetMultiDimArray($values), JSON_PRETTY_PRINT);
    }
}
