<?php

namespace Config {
    class Domain {
        public const Admin = "1";
        public const Web = "2";
        public const IOT = "3";
        public const ML = "4";
        public const App = "5";
        public const Event = "6";
        public const Content = "7";
        public const Graphic = "8";
        public const Organizer = "9";

        public static function ToValue(string $domain)
        {
            return match ($domain) {
                "IOT" => self::IOT,
                "Web" => self::Web,
                "App" => self::App,
                "ML" => self::ML,
                "Event" => self::Event,
                "Content" => self::Content,
                "Graphic" => self::Graphic,
                "Admin" => self::Admin,
                "Organizer" => self::Organizer
            };
        }

        public static function ToLabel(string $val)
        {
            return match ($val) {
                self::IOT => "IOT",
                self::Web => "Web",
                self::App => "App",
                self::ML => "ML",
                self::Event => "Event",
                self::Content => "Content",
                self::Graphic => "Graphic",
                self::Admin => "Admin",
                self::Organizer => "Organizer"
            };
        }
    }
}