#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N, K; cin >> N >> K;
    i64 node_cnt = K;

    i64 time = 0;

    // groups with at least 1 free
    set<i64> free_groups;
    set<i64> never_added;
    map<i64, i64> group_capacity;

    i64 bessie_group = -1;

    vector<vector<i64> > graph(node_cnt + 1, vector<i64>());

    vector<i64> duration(N + 1);
    for (i64 i = 1; i <= N; i++) {
        cin >> duration[i];
    }

    // the groups whose interviews ended at a particular time
    map<i64, vector<i64> > interview_ends;

    for (i64 i = 1; i <= K; i++) {
        // farmer i's interview will end at duration[i] + time
        interview_ends[duration[i] + time].push_back(i);
        group_capacity[i] = 0;
        never_added.insert(i);
    }

    i64 curr_farmers_free = 0;
    i64 curr_cow = K + 1;

    while (!interview_ends.empty()) {
        // printf("\n\n");
        time = interview_ends.begin()->first;

        printf("time is %lld\n", time);

        // happens at the same time
        vector<i64>& earliest = interview_ends.begin()->second;

        i64 new_group = ++node_cnt;
        graph.push_back(vector<i64>());

        printf("freed up:\n");
        for (i64 x: earliest) {
            printf("%lld\n", x);
            // never been in the set before, it's safe to add
            if (never_added.count(x)) {
                printf("move %lld into group %lld\n", x, new_group);
                free_groups.insert(x);
                never_added.erase(x);
            }
            curr_farmers_free++;
        }
        printf("\n");

        for (i64 x: free_groups) {
            printf("connected %lld to %lld\n", new_group, x);
            graph[new_group].push_back(x);
        }
        free_groups.clear();

        while (curr_farmers_free > 0) {
            // is bessie
            if (curr_cow == N + 1) {
                bessie_group = new_group;
                goto done;
            }

            interview_ends[time + duration[curr_cow]].push_back(new_group);

            curr_farmers_free--;
            curr_cow++;
        }

        if (curr_farmers_free > 0) {
            free_groups.insert(new_group);
        } else {
            never_added.insert(new_group);
        }

        interview_ends.erase(interview_ends.begin());
    }

    printf("\n\n");

    done: (void) 0;
    printf("%lld\n", time);

    set<i64> seen_all;
    vector<bool> seen_farmers(K + 1);

    function<void(i64)> dfs = [&] (i64 now) {

        if (now <= K) seen_farmers[now] = true;
        seen_all.insert(now);

        for (i64 x: graph[now]) {
            // printf("conn: %lld\n", x);
            if (!seen_all.count(x)) {
                dfs(x);
            }
        }
    };

    dfs(bessie_group);

    for (i64 f = 1; f <= K; f++) {
        if (seen_farmers[f]) printf("1");
        else printf("0");
    }
    printf("\n");
}