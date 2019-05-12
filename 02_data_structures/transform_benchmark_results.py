import pandas
import json
import matplotlib.pyplot as plt

fname = "/tmp/result"


def extractMethodName(name):
    return name.split("_")[2]


def extractType(name):
    type_name = name[name.find("<")+1:name.rfind(">")]

    splitted = name.split("/")
    if len(splitted) == 3:
        type_parameter = splitted[2]
    else:
        type_parameter = ""
    return "{0}({1})".format(type_name, type_parameter)


def extractIterations(name):
    return int(name.split("/")[1])


def buildDataFrame():
    with open(fname) as fd:
        data = json.load(fd)["benchmarks"]
    df = pandas.DataFrame(data)[["name", "cpu_time"]]
    df["method"] = df["name"].apply(extractMethodName)
    df["type"] = df["name"].apply(extractType)
    df["iterations"] = df["name"].apply(extractIterations)
    df = df.drop(columns="name")
    df = df[["method", "type", "iterations", "cpu_time"]]
    print(df)
    return df


def renderDataFrame(df, method_name):
    pivot = df[df["method"] == method_name].pivot(
        index="iterations", columns="type", values="cpu_time")
    print(pivot)
    axes = pivot.plot(kind="line", title="DynamicArray.{}".format(
        method_name), logx=True, logy=True)
    axes.set_ylabel("nanoseconds")
    lgd = axes.legend(loc='center right', bbox_to_anchor=(1.5, 0.5))
    axes.figure.savefig("/tmp/" + method_name + ".png",
                        bbox_extra_artists=(lgd,), bbox_inches='tight')


def main():
    df = buildDataFrame()
    df.to_csv("/tmp/benchmark.csv")
    for method_name in df["method"].unique().tolist():
        renderDataFrame(df, method_name)


if __name__ == "__main__":
    main()
