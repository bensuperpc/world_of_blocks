# Based on work: https://int-i.github.io/python/2021-11-07/matplotlib-google-benchmark-visualization/
# Modified by: Bensuperpc

from argparse import ArgumentParser
from itertools import groupby
import json
import operator
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
import pandas as pd

# Extract the benchmark name from the benchmark name string
def extract_label_from_benchmark(benchmark):
    bench_full_name = benchmark['name']
    bench_name = bench_full_name.split('/')[0]  # Remove all after /
    if (bench_name.startswith('BM_')):  # Remove if string start with BM_
        return bench_name[3:]  # Remove BM_
    else:
        return bench_name

# Extract the benchmark size from the benchmark
def extract_size_from_benchmark(benchmark):
    bench_name = benchmark['name']
    return bench_name.split('/')[1]  # Remove all before /

if __name__ == "__main__":
    # ./prog_name --benchmark_format=json --benchmark_out=result.json
    parser = ArgumentParser()
    parser.add_argument('path', help='benchmark result json file')
    args = parser.parse_args()

    with open(args.path) as file:
        benchmark_result = json.load(file)
        benchmarks = benchmark_result['benchmarks']
        elapsed_times = groupby(benchmarks, extract_label_from_benchmark)

        data1 = None
        data2 = None

        for key, group in elapsed_times:
            benchmark = list(group)
            x = list(map(extract_size_from_benchmark, benchmark))
            y1 = list(map(operator.itemgetter('bytes_per_second'), benchmark))
            y2 = list(map(operator.itemgetter('items_per_second'), benchmark))

            if data1 is None:
                data1 = pd.DataFrame({'size': x, key: y1})
            else:
                data1[key] = y1
            
            if data2 is None:
                data2 = pd.DataFrame({'size': x, key: y2})
            else:
                data2[key] = y2

        df1 = pd.melt(data1, id_vars=['size'], var_name='Benchmark', value_name='bytes_per_second')
        df1_max_indices = df1.groupby(['size', 'Benchmark'])['bytes_per_second'].transform(max) == df1['bytes_per_second']
        df1 = df1.loc[df1_max_indices]
        df1.reset_index(drop=True, inplace=True)


        df2 = pd.melt(data2, id_vars=['size'], var_name='Benchmark', value_name='items_per_second')
        df2_max_indices = df2.groupby(['size', 'Benchmark'])['items_per_second'].transform(max) == df2['items_per_second']
        df2 = df2.loc[df2_max_indices]
        df2.reset_index(drop=True, inplace=True)
        
        sns.set_theme()

        fig, ax = plt.subplots(2, 1)

        fig.set_size_inches(16, 9)
        fig.set_dpi(96)

        sns.lineplot(data=df1, x='size', y='bytes_per_second', hue='Benchmark', ax=ax[0])
        sns.lineplot(data=df2, x='size', y='items_per_second', hue='Benchmark', ax=ax[1])

        ax[0].set_title('Bytes per second')
        ax[1].set_title('Items per second')

        ax[0].set_xlabel('Array size')
        ax[1].set_xlabel('Array size')

        ax[0].set_ylabel('byte per second')
        ax[1].set_ylabel('items per second')

        fig.tight_layout()

        plt.savefig('benchmark.png', bbox_inches='tight', dpi=300)

        plt.show()
