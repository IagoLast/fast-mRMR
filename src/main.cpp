/*
 * mrmr.cpp
 *
 *  Created on: 28/11/2013
 *      Author: iago
 */

#include "../plib/JointProb.h"
#include "../plib/MutualInfo.h"
#include "../plib/utils.h"

#include <vector>
#include <algorithm>
#include <limits>
#include <boost/bind.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;

/**
 * @brief Calculates the index of the most relevant feature (excluding the class).
 * @param classRelevances: Array with the relevances for each class.
 * @param classIndex: Index of the class feature, (this feature will be ignored).
 */
uint getMaxRelevance(vector<double> classRelevances, uint classIndex) {
	uint i = 0;
	uint newFeature = -1;
	double relevance = 0;
	for (i = 0; i < classRelevances.size(); ++i) {
		if (classRelevances[i] > relevance && i != classIndex) {
			relevance = classRelevances[i];
			newFeature = i;
		}
	}
	return newFeature;
}

/**
 * @brief Parse command line options
 * 	-c Class index
 * 	-f Number of features to select.
 * 	-h print help
 */
options parseOptions(int argc, char*argv[]) {
	options opts;
	opts.classIndex = 0;
	opts.selectedFeatures = 10;

	if (argc > 1) {
		for (int i = 0; i < argc; ++i) {
			if (strcmp(argv[i], "-c") == 0) {
				opts.classIndex = atoi(argv[i + 1]) - 1;
			}
			if (strcmp(argv[i], "-f") == 0) {
				opts.selectedFeatures = atoi(argv[i + 1]);
			}
			if (strcmp(argv[i], "-h") == 0) {
				printf(
						"Mrmr by Iago lastra:\nOptions:\n-c <index of class feature>\t\tUsed to select index of class feature. (from 1 to features Size)\n-f <number of mrmr features required>\t Indicates the number of features to select.\n-h Prints this message");
				exit(0);
			}
		}
	}
	return opts;
}

/**
 * @brief Main mRMR function.
 */
int main(int argc, char* argv[]) {
	options opts;
	uint i = 0;
	uint j = 0;
	uint newFeatureIndex = 0;
	uint lastFeatureIndex = 0;
	double mrmr = 0;
	double acum = 0;
	vector<double> relevances;
	vector<double> redundances;
	vector<int> selectedFeatures;

	Timer tm;
	RawData rawData = RawData();
	tm.start();
	ProbTable prob = ProbTable(rawData);
	MutualInfo mutualInfo = MutualInfo(rawData, prob);
	opts = parseOptions(argc, argv);

	//Get relevances between all features and class.
	for (i = 0; i < rawData.getFeaturesSize(); ++i) {
		relevances.push_back(mutualInfo.get(opts.classIndex, i));
		cout << "Index: " << i << " " <<mutualInfo.get(opts.classIndex, i) << "\n";
		redundances.push_back(0);
	}

	// Max relevance feature is added because no redundancy is possible.
	newFeatureIndex = getMaxRelevance(relevances, opts.classIndex);
	selectedFeatures.push_back(newFeatureIndex);

	lastFeatureIndex = newFeatureIndex;

	cout << newFeatureIndex << ",";
	//MRMR
	while (selectedFeatures.size() < rawData.getFeaturesSize() - 1 //-1 porque la class feature se descarta
	and selectedFeatures.size() < opts.selectedFeatures) {
		acum = -std::numeric_limits<double>::infinity();
		for (j = 0; j < rawData.getFeaturesSize(); ++j) {
			//If feature not in selected selectedFeatures
			if (find(selectedFeatures.begin(), selectedFeatures.end(), j)
					== selectedFeatures.end() && j != opts.classIndex) {
				redundances[j] += mutualInfo.get(lastFeatureIndex, j);
				mrmr = relevances[j]
						- (redundances[j] / selectedFeatures.size());
				if (mrmr > acum) {
					acum = mrmr;
					newFeatureIndex = j;
				}
			}
		}
		//Last feature doesn't prints comma.
		if ( (selectedFeatures.size() == (opts.selectedFeatures - 1)) or (selectedFeatures.size() == (rawData.getFeaturesSize() -2)) ){
			cout << newFeatureIndex;
		}else{
			cout << newFeatureIndex << ",";
		}
		selectedFeatures.push_back(newFeatureIndex);
		lastFeatureIndex = newFeatureIndex;
	}

	rawData.destroy();
	prob.destroy();
	printf("\n");
	return (0);
}
