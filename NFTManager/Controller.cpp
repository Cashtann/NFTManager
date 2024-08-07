#include "Controller.h"
#include <QDebug>
#include <QTimer>
#include "NFTables.h"
#include "Utilities.h"
#include <QStringList>
#include <fstream>

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    //setListening(false);
    //Utilities::resetNFTablesConfigFileToDefault();
    //std::ifstream inputFile("isBlockedAllInPackets.shitloadofdata", std::ios::in);
    //setBlockedAllInPackets()
}

Controller::~Controller()
{
    NFTables::cleanupTcpUdpNFTables();
}

void Controller::debug()
{
    qDebug() << "[DEBUG] Whatever this is, I guess it is working!";
    updateTcpUdpCount();
}

void Controller::updateTcpUdpCount()
{
    if (!m_listening)
    {
        setListening(true);
        NFTables counter;

        NFTables::setupTcpUdpNFTables();
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&Controller::getTcpUdpCount));
        timer->setSingleShot(true);
        timer->start(10000);
    }
}

void Controller::getTcpUdpCount()
{
    setListening(false);
    TcpUdpCount output = NFTables::getTcpUdpCounters();
    setInTcpCount(output.tcpCount);
    setInUdpCount(output.udpCount);
    qDebug() << "Tcp count: " << m_inTcpCount;
    qDebug() << "Udp count: " << m_inUdpCount;
}

void Controller::toogleBlockAllPackets()
{
    QStringList nftBlockAllContent = {
        //"table inet block_all {;   chain input {;       type filter hook input priority 0; policy drop; }; }" // original one, withour accepting kernel's packets
        "table inet block_all {;   chain input {;       type filter hook input priority -10; policy drop;       iif lo accept; }; }"
        /// NFTables has strange syntax and to make it one-line it has to look ugly af (I guess ';' = '\n')
    };

    if (!m_blockedAllInPackets)
    {
        for (const auto& cmd : nftBlockAllContent)
        {
            Utilities::addLineToFile(NFTables::NFTConfigPath, cmd.toStdString());
        }
    }
    else
    {
        for (const auto& cmd : nftBlockAllContent)
        {
            Utilities::removeLineContainingFromFile(NFTables::NFTConfigPath, cmd.toStdString());
        }
    }

    NFTables::reloadNFT();
    setBlockedAllInPackets(!m_blockedAllInPackets);
}

void Controller::resetNFT(const bool& hard)
{
    Utilities::resetNFTablesConfigFileToDefault();
    if (hard)
        system("sudo nft flush ruleset");
    NFTables::reloadNFT();
}

int Controller::inUdpCount() const
{
    return m_inUdpCount;
}

void Controller::setInUdpCount(int newInUdpCount)
{
    if (m_inUdpCount == newInUdpCount)
        return;
    m_inUdpCount = newInUdpCount;
    emit inUdpCountChanged();
}

int Controller::inTcpCount() const
{
    return m_inTcpCount;
}

void Controller::setInTcpCount(int newInTcpCount)
{
    if (m_inTcpCount == newInTcpCount)
        return;
    m_inTcpCount = newInTcpCount;
    emit inTcpCountChanged();
}

bool Controller::listening() const
{
    return m_listening;
}

void Controller::setListening(bool newListening)
{
    if (m_listening == newListening)
        return;
    m_listening = newListening;
    emit listeningChanged();
}

bool Controller::blockedAllInPackets() const
{
    return m_blockedAllInPackets;
}

void Controller::setBlockedAllInPackets(bool newBlockedAllInPackets)
{
    if (m_blockedAllInPackets == newBlockedAllInPackets)
        return;
    m_blockedAllInPackets = newBlockedAllInPackets;

    std::ofstream outputFile("isBlockedAllInPackets.shitloadofdata", std::ios::trunc);
    outputFile << m_blockedAllInPackets;
    outputFile.close();

    emit blockedAllInPacketsChanged();
}
