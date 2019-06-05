#!/usr/bin/python3

import pandas
import json
import sys
import matplotlib.pyplot as plt

pandas.set_option('display.max_rows', 500)
pandas.set_option('display.max_columns', 500)
pandas.set_option('display.width', 1000)


def extractFunc(name: str, bench_prefix: str) -> str:
    return name.split("/")[0].split(bench_prefix)[1]


def extractN(name):
    return int(name.split("/")[1])


def buildDataFrame(fname: str, bench_prefix: str):
    with open(fname) as fd:
        data = json.load(fd)["benchmarks"]
    src = pandas.DataFrame(data)

    # данные графиков
    df = src[pandas.notnull(src["cpu_time"])][["name", "cpu_time"]]
    df["func"] = df["name"].apply(
        lambda x: extractFunc(x, bench_prefix))
    df["n"] = df["name"].apply(extractN)

    df = df[["func", "n", "cpu_time"]]

    return df


def buildComplexity(fname: str, bench_prefix: str):
    with open(fname) as fd:
        data = json.load(fd)["benchmarks"]
    src = pandas.DataFrame(data)

    # вычислительная сложность
    df = src[pandas.notnull(src["big_o"])][["name", "big_o"]]
    df["method"] = df["name"].apply(
        lambda x: extractFunc(x, bench_prefix))
    df = df[["method", "big_o"]]

    return df

def renderDataFrame(df, title: str):
    print("\n\n")
    pivot = df.pivot(
        index="n", columns="func", values="cpu_time")
    print(pivot)
    axes = pivot.plot(kind="line", title=title, logx=True, logy=True)
    axes.set_ylabel("nanoseconds")
    lgd = axes.legend(loc='center right', bbox_to_anchor=(1.5, 0.5))
    axes.figure.savefig("/tmp/" + title + ".png",
                        bbox_extra_artists=(lgd,), bbox_inches='tight')


def make_title(prefix: str, method_name: str) -> str:
    return "{}.{}".format(prefix, method_name)


def main():
    fname = sys.argv[1]
    title_prefix = sys.argv[2]
    bench_prefix = sys.argv[3] + "_"

    cf = buildComplexity(fname, bench_prefix)
    print(cf)

    df = buildDataFrame(fname, bench_prefix)
    print(df)
    renderDataFrame(df, title_prefix)


if __name__ == "__main__":
    main()
