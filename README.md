<div align="center">

[![Arma Reforger Workshop](https://img.shields.io/badge/Workshop-647C62912FCE9459-blue?style=flat-square)](https://reforger.armaplatform.com/workshop/647C62912FCE9459)
[![License MIT](https://img.shields.io/badge/License-MIT-green?style=flat-square)](https://opensource.org/licenses/MIT)

</div>

# ArmaStats.com - Reforger Synchronisation Addon

> **Warning**
> This addon is still in **ALPHA** and for internal testing only. Until version 1.0.0 there is no backward compatibility guarantee! Expect some bugs/performance issues and function signature updates until then. Feedback via [issue](https://github.com/armastats-com/addon-reforger-synchronisation-module/issues) or [discussion](https://github.com/armastats-com/addon-reforger-synchronisation-module/discussions) is welcome.

**A statistics addon to connect your Arma Reforger Server to the API of https://armastats.com/.**

> **Note**
> With this addon alone you will not be able to have any statistics on your server! This addon gathers all the data and sends it to https://armastats.com/. 
> All gathered statistics will be visible on this website!

## 🚀 Features
- ✅ Gather and send kill statistics
- 🚧 Basic online / playtime statistics
- 🚧 Basic player movement statistics
- 🚧 Basic server statistics
- 🚧 Basic round / session statistics

## 📖 How to test this addon
* Open a [discussion](https://github.com/armastats-com/addon-reforger-synchronisation-module/discussions) and request an API key for this addon
* We will send you all required data (ServerId, API Key, URLs)
* Update your server configuration and start the server with the following CLI params  
  * `-armastats-api <your api server here>`
  * `-armastats-api-key <your api key here>`
  * `-armastats-server-id <your server id here>`
* Your game server will now send all the relevant data to the API of ArmaStats.com
* The statistics should now be visible on our website

## ⚡ Quick start on developing

> **Note**
> Feel free to create pull requests which add new features, improve performance or maintainability of this project.
> In case of bigger wishes, do not hesitate to open a [discussion](https://github.com/armastats-com/addon-reforger-synchronisation-module/discussions).

- Install Arma Reforger
- Install Arma Workbench Tools
- Clone this repository
- Start editing the scripts and test it locally
- Create a pull request

## 📕 License

MIT License

Copyright (c) 2025 Sebastian Foth - Software Solutions

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.