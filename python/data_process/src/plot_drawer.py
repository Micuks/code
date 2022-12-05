from matplotlib import pyplot as plt
import numpy as np
import seaborn as sns


class plot_drawer:
    def __init__(self, data):
        self.data = data
        # Customize colors.
        self._customize_colors()
        # Curtomize plot.
        self._customize_plot()
        # Set default Chinese font.
        self._add_zh_cn_support()

    def _add_zh_cn_support(self):
        # Set default Chinese font.
        plt.rcParams["font.sans-serif"] = ["Songti SC"]
        plt.rcParams["axes.unicode_minus"] = False

    def _customize_colors(self):
        # Customize colors.
        CB91_Blue = "#2CBDFE"
        CB91_Green = "#47DBCD"
        CB91_Pink = "#F3A0F2"
        CB91_Purple = "#9D2EC5"
        CB91_Violet = "#661D98"
        CB91_Amber = "#F5B14C"
        color_list = [
            CB91_Blue,
            CB91_Pink,
            CB91_Green,
            CB91_Amber,
            CB91_Purple,
            CB91_Violet,
        ]
        plt.rcParams["axes.prop_cycle"] = plt.cycler(color=color_list)
        self.colors = color_list

    def _customize_plot(self):
        sns.set(
            font=["Songti SC", "Helvetica"],
            rc={
                "axes.axisbelow": True, # Let axis grid below figure.
                "axes.edgecolor": "lightgrey",
                "axes.facecolor": "white",
                "axes.grid": True,
                "axes.labelcolor": "dimgrey",
                "axes.spines.right": False,
                "axes.spines.top": False,
                "figure.facecolor": "white",
                "lines.solid_capstyle": "round",
                "patch.edgecolor": "w",
                "patch.force_edgecolor": True,
                "text.color": "dimgrey",
                "xtick.bottom": False,
                "xtick.color": "dimgrey",
                "xtick.direction": "out",
                "xtick.top": False,
                "ytick.color": "dimgrey",
                "ytick.direction": "out",
                "ytick.left": False,
                "ytick.right": False,
            },
        )
        sns.set_context(
            "notebook", rc={"font.size": 16, "axes.titlesize": 20,
                            "axes.labelsize": 15}
        )

    def draw_price_scatter_plot(self):
        # Create figure and axes
        fig = plt.figure()
        ax = plt.axes()
        
        avg_price = list()
        tot_price = list()
        resblock_type = list()
        # Get unqiue types in resblock_type.
        types = list()

        # Collect data.
        for d in self.data:
            avg_price.append(d["均价"])
            tot_price.append(d["总价"])
            resblock_type.append(d["类型"])

        def get_label(item: str):
            # If label[item] already exists, do not add new one.
            if item in types:
                return ""
            else:
                # Else add new one.
                types.append(item)
                return item

        def get_color(item: str):
            """
            If resblock_type item already exists, return the corresponding
            color.
            """

            def color(item: str):
                clrs = self.colors
                idx = types.index(item)
                return clrs[idx % len(clrs)]

            if item in types:
                return color(item)
            else:
                return self.colors[0]

        # Draw data on plot.
        for i in range(len(tot_price)):
            rtype = resblock_type[i]
            plt.scatter(
                tot_price[i],
                avg_price[i],
                label=get_label(rtype),
                s=35,
                c=get_color(rtype),
            )

        print(types)

        # Add axe labels and caption.
        plt.title("楼盘价格分布散点图")
        plt.xlabel("总价(万元)")
        plt.ylabel("均价(元)")
        plt.grid(True, linestyle="--", c="dimgrey", alpha=0.8)
        plt.legend(loc="lower right")

        plt.show()

    
    def draw_avg_of_avg_price_bar_figure(self):
        '''
        Draw the bar figure of all administrative district real estates.

        - One bar per administrative district. Height is average of average
          price of estates in each district;
        - width is the number of real estates in the administrative district.
        '''

        adm_districts, unique_adm_districts, num_districts, \
        num_estates_per_district, num_estates = self._get_real_estates_data()

        def get_avg_price_per_adm_district():
            sum = np.zeros(num_districts, dtype=np.float64)

            for item in self.data:
                avg_price = item["均价"]
                district = item["行政区"]

                sum[unique_adm_districts.index(district)] += avg_price

            return np.asarray([sum[i]/num_estates_per_district[i] for i in
                               range(num_districts)])


        avg_price_per_adm_district = get_avg_price_per_adm_district()

        # Draw bar plot. 
        # x axis is name of estates.
        # y axis of bar is average of average price of estates in the
        # same admistrative district; 
        # Width of bar is the number of estates in each admistrative district.
        for i in range(num_districts):
            plt.bar(unique_adm_districts[i], avg_price_per_adm_district[i], 
                    5*(num_estates_per_district[i] / num_estates))

        # Configure axes and figure.
        plt.rcParams["axes.grid"] = False
        plt.title("行政区楼盘平均均价")
        plt.xlabel("行政区")
        plt.ylabel("均价(元)")

        plt.show()

    def draw_avg_of_total_price_bar_figure(self):
        '''
        Draw another bar figure of all administrative district real estates.

        - One bar ber administrative districe. Height is total price;
        - width is the number of real estates in the administrative district.
        '''

        adm_districts, unique_adm_districts, num_districts, \
        num_estates_per_district, num_estates = self._get_real_estates_data()

        # Compute average of total price of real estates per administrative
        # district.
        def get_avg_price_per_adm_district():
            sum = np.zeros(num_districts, dtype=np.float64)
            for item in self.data:
                total_price = item["总价"]
                district = item["行政区"]

                sum[unique_adm_districts.index(district)] += total_price

            return np.asarray([sum[i]/num_estates_per_district[i] for i in
                               range(num_districts)])


        avg_price_per_adm_district = get_avg_price_per_adm_district()

        # Draw bar plot.
        for i in range(num_districts):
            plt.bar(unique_adm_districts[i], avg_price_per_adm_district[i],
                    5*(num_estates_per_district[i]/num_estates))

        plt.rcParams["axes.grid"] = False
        plt.title("行政区楼盘平均总价")
        plt.xlabel("行政区")
        plt.ylabel("平均总价(万元)")

        plt.show()


    def draw_estate_distribution_pie_figure(self):
        '''
        Draw a pie plot showing the proportion of read estates in each
        administrative region.
        '''
        adm_districts, unique_adm_districts, num_districts, \
        num_estates_per_district, num_estates = self._get_real_estates_data()

        # Draw pie plot.
        '''
        Inputs:
        - num_estates_per_district: Number of real estates per administrative
          district.
        - labels=unqiue_adm_districts: Labels of all administrative districts.
        - labeldistance: Distance between label text and the center of pie.
          1.1 means 1.1*radius.
        - autopct="%1.1f%%": Text format inside pie plot. Auto compute
          percentage of each district.
        - shadow=False: Config whether shadow is enables.
        - startangle: Start angle. Default to begin from 0, counterclockwise.
        - pctdistance: Set distence between text inside pie and center of pie.

        Returns:
        - patches: An array containing slices of the pie part.
        - texts: An array containing label instances. Labels are text outside
          the pie.
        - autotexts: An array containing data label instances. Data label
          instances mean the text inside pie plot. Better display effect can be
          get by setting the autotexts return value.
        '''

        patches, texts, autotexts = plt.pie(num_estates_per_district,
                                            labels=unique_adm_districts,
                                            labeldistance=1.1,
                                            autopct="%1.1f%%",
                                            shadow=False,startangle=180,pctdistance=0.7)

        # Modify parameters of the pie plot.
        # plt.rcParams["axes.grid"] = False
        plt.title("各行政区楼盘占比")
        plt.rcParams["axes.edgecolor"]="b"
        plt.rcParams["axes.labelcolor"] = "b"
        plt.rcParams["xtick.color"]="b"

        plt.show()


    # TODO: draw compare average and total price bar plot.
    def draw_compare_avg_and_total_price_bar_plot(self):
        '''
        Draw a bar figure comparing average and total price of real estates per
        district in bar plot.
        '''
        # Get administrative districts.
        pass

        adm_districts = [x["行政区"] for x in self.data]
        unique_adm_districts = list(set(adm_districts))

        print(adm_districts, len(adm_districts))
        print(unique_adm_districts, len(unique_adm_districts))

        # Compute the average price and number of real estates in each
        # admistrative district.
        num_districts = len(unique_adm_districts)

        def get_num_of_real_estates_per_district():
            tmp = np.zeros(num_districts, dtype=np.int32)
            for item in adm_districts:
                tmp[unique_adm_districts.index(item)] += 1;

            return tmp


        num_estates_per_district = get_num_of_real_estates_per_district()

        num_estates = len(adm_districts)


        def get_avg_price_per_adm_district():
            sum = np.zeros(num_districts, dtype=np.float64)

            for item in self.data:
                avg_price = item["均价"]
                district = item["行政区"]

                sum[unique_adm_districts.index(district)] += avg_price

            return np.asarray([sum[i]/num_estates_per_district[i] for i in
                               range(num_districts)])


        avg_price_per_adm_district = get_avg_price_per_adm_district()

        # Draw bar plot. 
        # x axis is name of estates.
        # y axis of bar is average of average price of estates in the
        # same admistrative district; 
        # Width of bar is the number of estates in each admistrative district.
        for i in range(num_districts):
            plt.bar(unique_adm_districts[i], avg_price_per_adm_district[i], 
                    5*(num_estates_per_district[i] / num_estates))

        # Configure axes and figure.
        plt.rcParams["axes.grid"] = False
        plt.title("行政区楼盘平均均价")
        plt.xlabel("行政区")
        plt.ylabel("均价(元)")

        plt.show()

    
    def _get_real_estates_data(self):
        '''
        Compute statistics data about real estates in different administrative
        districts.

        Returns:
        - adm_districts: all administrative districts in self.data.
        - unique_adm_districts: Removed duplicate elements from adm_districts.
        - num_districts: The number of administrative districts.
        - num_estates_per_district: The number of real estates in each
          administrative district.
        - num_estates: The total number of real estates.
        '''
        adm_districts = [x["行政区"] for x in self.data]
        unique_adm_districts = list(set(adm_districts))

        num_districts = len(unique_adm_districts)

        def get_num_of_real_estates_per_district():
            tmp = np.zeros(num_districts, dtype=np.int32)
            for item in adm_districts:
                tmp[unique_adm_districts.index(item)] += 1

            return tmp


        num_estates_per_district = get_num_of_real_estates_per_district()

        num_estates = len(adm_districts)

        return adm_districts, unique_adm_districts, num_districts, \
    num_estates_per_district, num_estates


    def draw_compare_avg_and_total_price_plot(self):
        '''
        Compare average and total price of administrative distincts in subplot.
        '''

        adm_districts, unique_adm_districts, num_districts, \
        num_estates_per_district, num_estates = self._get_real_estates_data()

        # Compute average of average price of real estates per administrative
        # district.
        def get_avg_of_avg_price_per_adm_district():
            sum = np.zeros(num_districts, dtype=np.float64)

            for item in self.data:
                avg_price = item["均价"]
                district = item["行政区"]

                sum[unique_adm_districts.index(district)] += avg_price

            return np.asarray([sum[i]/num_estates_per_district[i] for i in
                               range(num_districts)])


        avg_of_avg_price_per_adm_district = get_avg_of_avg_price_per_adm_district()

        # Compute average of total price of real estates per administrative
        # district.
        def get_avg_of_total_price_per_adm_district():
            sum = np.zeros(num_districts, dtype=np.float64)
            for item in self.data:
                total_price = item["总价"]
                district = item["行政区"]

                sum[unique_adm_districts.index(district)] += total_price

            return np.asarray([sum[i]/num_estates_per_district[i] for i in
                               range(num_districts)])


        plt.figure(figsize=(15,6))
        # Set subplot distribution as (1,2)
        # First draw the first one
        plt.subplot(1,2,1)
        # Draw bar plot. 
        # x axis is name of estates.
        # y axis of bar is average of average price of estates in the
        # same admistrative district; 
        # Width of bar is the number of estates in each admistrative district.
        for i in range(num_districts):
            plt.bar(unique_adm_districts[i], avg_of_avg_price_per_adm_district[i], 
                    5*(num_estates_per_district[i] / num_estates))

        # Configure axes and figure.
        plt.rcParams["axes.grid"] = False
        plt.title("行政区楼盘平均均价")
        plt.xlabel("行政区")
        plt.ylabel("均价(元)")

        avg_of_total_price_per_adm_district = get_avg_of_total_price_per_adm_district()

        # Then draw the second one
        plt.subplot(1,2,2)

        for i in range(num_districts):
            plt.bar(unique_adm_districts[i], avg_of_total_price_per_adm_district[i],
                    5*(num_estates_per_district[i]/num_estates))

        plt.rcParams["axes.grid"] = False
        plt.title("行政区楼盘平均总价")
        plt.xlabel("行政区")
        plt.ylabel("平均总价(万元)")

        plt.show()
