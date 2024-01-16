//
// Created by Sulsenti, Tyler on 1/15/24.
//

#include "HLSPlaylistSorter.h"
#include "StreamINF.h"

/**
 * Uses quicksort to sort the HLSPlaylist's StreamINF list (#EXT-X-STREAM-INF tag) by resolution
 * from least to greatest (ascending).
 *
 * @param playlist the reference to the HLSPlaylist object
 */
void HLSPlaylistSorter::sort(HLSPlaylist &playlist){
    //quicksort is chosen because it is usually the most efficient sorting algorithm on large datasets.
    //our dataset is above 20 in size, and while it is not necessarily large, using quicksort would be probably
    //more efficient than insertion sort here. (>20) Even, so it is future proofing in case a larger dataset is used.
    //O(nlogn) - average case

    //In the future with more time, a hybrid sort between both insertion & quicksort could be used depending on dataset size.
    //using last element as pivot for simplicity, in the future with more time, a pivot at the middle could provide a better chance
    // at not having worst case time complexity.
    quickSort(playlist.getStreamInfList().getV(), 0, playlist.getStreamInfList().getV().size() - 1);

}

/**
 * quicksort function to partition the vector by index, and recursively sort
 * @param vector the reference to the vector to sort
 * @param left the index of the left position
 * @param right the index of the right position
 */
void HLSPlaylistSorter::quickSort(std::vector<StreamINF> &vector, int left, int right) {
    //partition when the left is less than right
    if(left < right){
        //partition the vector
        int partitionIndex = quicksortPartition(vector, left, right);

        //recursively call quicksort.
        quickSort(vector, left, partitionIndex - 1);
        quickSort(vector, partitionIndex + 1, right);
    }
}

/**
 * quicksort helper function to swap values within the partition index
 * @param vector the reference to the vector to sort
 * @param left the index of the left position
 * @param right the index of the right position
 * @return the new partition index after the swap.
 */
int HLSPlaylistSorter::quicksortPartition(std::vector<StreamINF> &vector, int left, int right){

    //quicksort pivot
    //first we need the resolution at the right
    int pivot = calculateResolution(vector[right].getResolution());

    //index of the smaller element on the right position
    int index = left - 1;

    //let's look through this partition
    for(int j = left; j <= right; j++){
        //is the current resolution smaller than the pivot resolution?
        if(calculateResolution(vector[j].getResolution()) < pivot){
            //if so, then increment the index and swap
            index++;
            std::swap(vector[index], vector[j]);
        }
    }
    //swap the next element from the index with the right
    std::swap(vector[index + 1], vector[right]);
    return index + 1; //return the next index;

}

/**
 * Helper function to calculate the total resolution of a HxV notation.
 * @param resolution the resolution ini HxV notation
 * @return the total number of pixels, or the area of the resolution.
 */
int HLSPlaylistSorter::calculateResolution(const std::string& resolution){

    //Get the horizontal and vertical pixel counts as integers.
    int horizontal = stoi(resolution.substr(0, resolution.find('x')));
    int vertical = stoi(resolution.substr(resolution.find('x') + 1));

    return horizontal * vertical;
}
