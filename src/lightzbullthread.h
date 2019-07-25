//
// Copyright (c) 2015-2018 The bulldog developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
//

#ifndef bulldog_LIGHTzbullTHREAD_H
#define bulldog_LIGHTzbullTHREAD_H

#include <atomic>
#include "genwit.h"
#include "zbull/accumulators.h"
#include "concurrentqueue.h"
#include "chainparams.h"
#include <boost/function.hpp>
#include <boost/thread.hpp>

extern CChain chainActive;
// Max amount of computation for a single request
const int COMP_MAX_AMOUNT = 60 * 24 * 60;


/****** Thread ********/

class CLightWorker{

private:

    concurrentqueue<CGenWit> requestsQueue;
    std::atomic<bool> isWorkerRunning;
    boost::thread threadIns;

public:

    CLightWorker() {
        isWorkerRunning = false;
    }

    enum ERROR_CODES {
        NOT_ENOUGH_MINTS = 0,
        NON_DETERMINED = 1
    };

    bool addWitWork(CGenWit wit) {
        if (!isWorkerRunning) {
            LogPrintf("%s not running trying to add wit work \n", "bulldog-light-thread");
            return false;
        }
        requestsQueue.push(wit);
        return true;
    }

    void StartLightzbullThread(boost::thread_group& threadGroup) {
        LogPrintf("%s thread start\n", "bulldog-light-thread");
        threadIns = boost::thread(boost::bind(&CLightWorker::ThreadLightzbullSimplified, this));
    }

    void StopLightzbullThread() {
        threadIns.interrupt();
        LogPrintf("%s thread interrupted\n", "bulldog-light-thread");
    }

private:

    void ThreadLightzbullSimplified();

    void rejectWork(CGenWit& wit, int blockHeight, uint32_t errorNumber);

};

#endif //bulldog_LIGHTzbullTHREAD_H
