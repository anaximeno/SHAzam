#include "../include/shazam/checker.hh"
#include "../include/shazam/hash.hh"
#include "../include/shazam/files.hh"

#include <list>
#include <string>
#include <memory>
#include <algorithm>

void shazam::Checker::displayValidHashes()
{
    if (!validFilesHashes.empty()) {
        for (auto& hash : validFilesHashes) {
            std::cout << hash->get().hashSum << " ";
            std::cout << hash->getFilePath() << "\n";
        }
    }
}

void shazam::Checker::displayInvalidFiles()
{
    if (!invalidFilesList.empty() && showInvalidFiles) {
        std::cout << std::endl << "Invalid Files:\n";

        for (auto& file : invalidFilesList) {
            std::cout << " " << file->path() << " -> ";
            std::cout << file->explainStatus() << "\n";
        }

        std::cout << std::endl;
    }
}

void shazam::Checker::add(std::shared_ptr<shazam::File> file, std::string hashtype)
{
    if (file->isValid()) {
        auto hash = hashFactory.hashFile(hashtype, file);
        hash->setObserver(progress);
        validFilesHashes.push_front(hash);
    } else
        invalidFilesList.push_front(file);
}

void shazam::Checker::calculateHashSums()
{
    if (showProgressBar) {
        // add observer for the init operation
        progress->increaseObervableCounter();
        // initialize the progress bar
        progress->init();
        // after calling init, update the progress bar
        progress->update();
    }

    std::for_each(
        validFilesHashes.begin(),
        validFilesHashes.end(),
        [](std::shared_ptr<HashCalculator>& hash) {
            hash->calculate();
            hash->notifyObserver();
        }
    );
}

void shazam::Checker::setShowProgressBar(bool value)
{
    showProgressBar = value;
}

void shazam::Checker::setShowInvalidFiles(bool value)
{
    showInvalidFiles = value;
}

void shazam::Checker::displayResults()
{
    if (showProgressBar)
        progress->done();

    displayValidHashes();
    displayInvalidFiles();
}

std::list<std::shared_ptr<shazam::HashCalculator>> shazam::Checker::getValidHashesList()
{
    return validFilesHashes;
}

std::list<std::shared_ptr<shazam::File>> shazam::Checker::getInvalidFilesList()
{
    return invalidFilesList;
}
