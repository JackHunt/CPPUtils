/*
BSD 3-Clause License

Copyright (c) 2023 Jack Miles Hunt
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CPP_UTILS_TESTS_LINEAR_ALGEBRA_MATRIX_EXAMPLES_H
#define CPP_UTILS_TESTS_LINEAR_ALGEBRA_MATRIX_EXAMPLES_H

#include <array>
#include <tuple>
#include <utility>

#include <gtest/gtest.h>

#include <CPPUtils/LinearAlgebra/Matrix.hpp>

using CPPUtils::LinearAlgebra::Matrix;
using CPPUtils::LinearAlgebra::Util::DeviceType;

namespace TestUtils::LinearAlgebra {
    namespace TestMatrices {
        template<typename T, size_t M, size_t N>
        struct MatrixSpec {
            const std::array<T, M * N> elems;

            static constexpr size_t Rows = M;
            static constexpr size_t Cols = N;

            explicit MatrixSpec(const std::array<T, M * N>& elems) :
                elems(elems) {}

            const std::array<T, M * N>& operator()() const {
                return elems;
            }

            template<DeviceType D = DeviceType::CPU>
            const Matrix<T, D> asMatrix() const {
                Matrix<T, D> mat(Rows, Cols);
                mat.setContents(elems);
                return mat;
            }
        };

        // 4x4 matrices.
        template<typename T>
        struct A final : public MatrixSpec<T, 4, 4> {
            A() : MatrixSpec<T, 4, 4>(
                {
                    0.55766378, 0.68445097, 0.4145077, 0.21463164,
                    0.15868892, 0.992214, 0.09069661, 0.52513248,
                    0.65802801, 0.93370618, 0.24956661, 0.11259711,
                    0.12831182, 0.38880986, 0.93238085, 0.66215145
                }) {}
        };

        template<typename T>
        struct B final : public MatrixSpec<T, 4, 4> {
            B() : MatrixSpec<T, 4, 4>(
                {
                    0.50585029, 0.01381094, 0.64199972, 0.69423779,
                    0.62090961, 0.84185181, 0.8455993 , 0.37761089,
                    0.2444823, 0.64341411, 0.89884036, 0.68741319,
                    0.53513187, 0.34634159, 0.30644915, 0.23464744
                }) {}
        };

        template<typename T>
        struct C final : public MatrixSpec<T, 4, 4> {
            C() : MatrixSpec<T, 4, 4>(
                {
                    0.54600224, 0.5454627, 0.52769453, 0.8392025,
                    0.5349935, 0.20034535, 0.36027647, 0.90043104,
                    0.02055378, 0.24479729, 0.21207014, 0.0366292,
                    0.23777526, 0.67004896, 0.8520715, 0.86000042
                }) {}
        };

        // 4x3 matrices
        template<typename T>
        struct D final : public MatrixSpec<T, 4, 3> {
            D() : MatrixSpec<T, 4, 3>(
                {
                    0.62496158, 0.71334813, 0.79737023,
                    0.03571888, 0.82973627, 0.8374377,
                    0.22455511, 0.9883449, 0.91083474,
                    0.91578061, 0.75367366, 0.02413316
                }) {}
        };

        template<typename T>
        struct E final : public MatrixSpec<T, 4, 3> {
            E() : MatrixSpec<T, 4, 3>(
                {
                    0.98107297, 0.82445986, 0.07442518,
                    0.76373333, 0.23546057, 0.99451245,
                    0.67850332, 0.69923818, 0.9557316,
                    0.51032609, 0.79149574, 0.89951436
                }) {}
        };

        template<typename T>
        struct F final : public MatrixSpec<T, 4, 3> {
            F() : MatrixSpec<T, 4, 3>(
                {
                    0.39444037, 0.41925121, 0.45069636,
                    0.39273509, 0.90533605, 0.53546554,
                    0.11903078, 0.67915281, 0.8994787,
                    0.90941683, 0.2634679, 0.32816192
                }) {}
        };

        // 3x4 matrices
        template<typename T>
        struct G final : public MatrixSpec<T, 3, 4> {
            G() : MatrixSpec<T, 3, 4>(
                {
                    0.72216128, 0.57212529, 0.62311077, 0.74030086,
                    0.35207834, 0.91643651, 0.31510376, 0.42333465,
                    0.14249265, 0.20283275, 0.031765, 0.99738141
                }) {}
        };

        template<typename T>
        struct H final : public MatrixSpec<T, 3, 4> {
            H() : MatrixSpec<T, 3, 4>(
                {
                    0.91278903, 0.24038452, 0.37398921, 0.27359872,
                    0.88707916, 0.27711698, 0.17547097, 0.71198952,
                    0.35722917, 0.82494037, 0.86909136, 0.30934892
                }) {}
        };

        template<typename T>
        struct I final : public MatrixSpec<T, 3, 4> {
            I() : MatrixSpec<T, 3, 4>(
                {
                    0.72786695, 0.60472051, 0.3273219, 0.52569234,
                    0.16448384, 0.43525911, 0.8964277, 0.2395171, 
                    0.05847619, 0.58404601, 0.27119968, 0.94203044
                }) {}
        };

        // Matmul solutions.
        //AxA
        template<typename T>
        struct AxA final : public MatrixSpec<T, 4, 4> {
            AxA() : MatrixSpec<T, 4, 4>(
                {
                    0.71990113, 1.53129464, 0.59679903, 0.66791075,
                    0.37301005, 1.38196407, 0.66802654, 0.91303287,
                    0.69379657, 1.65362499, 0.52470854, 0.73420989,
                    0.83174924, 1.6016265, 0.93851843, 0.77514439
                }) {}
        };

        //AxB
        template<typename T>
        struct AxB final : public MatrixSpec<T, 4, 4> {
            AxB() : MatrixSpec<T, 4, 4>(
                {
                    0.9232726, 0.92494411, 1.37514119, 0.98090824,
                    0.99953688, 1.07771949, 1.18334188, 0.67040569,
                    1.03387972, 0.99470196, 1.47082092, 1.00738153,
                    0.88861131, 1.15832997, 1.45213078, 1.03220079
                }) {}
        };

        //AxC
        template<typename T>
        struct AxC final : public MatrixSpec<T, 4, 4> {
            AxC() : MatrixSpec<T, 4, 4>(
                {
                    0.73021628, 0.68659544, 0.81165392, 1.28406012,
                    0.74420021, 0.65941111, 0.90789509, 1.48152871,
                    0.89071384, 0.68253224, 0.83249656, 1.49893176,
                    0.45467647, 0.81980376, 0.96971901, 1.06137895
                }) {}
        };

        //BxA
        template<typename T>
        struct BxA final : public MatrixSpec<T, 4, 4> {
            BxA() : MatrixSpec<T, 4, 4>(
                {
                    0.79581875, 1.22929874, 1.01844716, 0.64780193,
                    1.08473132, 2.19663946, 0.89683543, 0.92059821,
                    0.91810699, 1.91226646, 1.02494671, 0.94672976,
                    0.5851444, 1.0872832, 0.54848854, 0.48660888
                }) {}
        };

        //BxB
        template<typename T>
        struct BxB final : public MatrixSpec<T, 4, 4> {
            BxB() : MatrixSpec<T, 4, 4>(
                {
                    0.79292621, 0.67212814, 1.12623811, 0.96061576,
                    1.24560687, 1.39214269, 1.98627041, 1.41883287,
                    1.11078072, 1.36144222, 1.71959928, 1.1918635,
                    0.68623215, 0.57740084, 0.98377709, 0.76800773
                }) {}
        };

        //BxC
        template<typename T>
        struct BxC final : public MatrixSpec<T, 4, 4> {
            BxC() : MatrixSpec<T, 4, 4>(
                {
                    0.46185225, 0.90102253, 0.9995994, 1.05750736,
                    0.89657007, 0.96736233, 1.13202784, 1.63481754,
                    0.65963467, 0.94289519, 1.13716133, 1.40861963,
                    0.53956574, 0.5935256, 0.67209, 0.97396261
                }) {}
        };

        //CxA
        template<typename T>
        struct CxA final : public MatrixSpec<T, 4, 4> {
            CxA() : MatrixSpec<T, 4, 4>(
                {
                    0.84596194, 1.73392934, 1.18994502, 1.01872557,
                    0.68274704, 1.25145111, 1.1693872, 0.85682219,
                    0.19455677, 0.46921235, 0.11779997, 0.18109506,
                    0.90996313, 1.95753852, 1.17382735, 1.06828987
                }) {}
        };

        //CxB
        template<typename T>
        struct CxB final : public MatrixSpec<T, 4, 4> {
            CxB() : MatrixSpec<T, 4, 4>(
                {
                    1.19297441, 1.09691641, 1.5432622, 1.14468895,
                    0.96495354, 0.71971355, 1.11264492, 0.90600793,
                    0.23384298, 0.35550205, 0.42203813, 0.2610821,
                    1.20484856, 1.41345457, 1.74866723, 1.20561244
                }) {}
        };

        //CxC
        template<typename T>
        struct CxC final : public MatrixSpec<T, 4, 4> {
            CxC() : MatrixSpec<T, 4, 4>(
                {
                    0.80032515, 1.09858973, 1.31160856, 1.69040152,
                    0.62079637, 1.02348484, 1.19812837, 1.41693276,
                    0.15525573, 0.13671287, 0.17522526, 0.27694095,
                    0.71029777, 1.04876591, 1.28035634, 1.57368588
                }) {}
        };

        //AxD
        template<typename T>
        struct AxD final : public MatrixSpec<T, 4, 3> {
            AxD() : MatrixSpec<T, 4, 3>(
                {
                    0.66260158, 1.537161, 1.4005773,
                    0.63588778, 1.42189444, 1.05273396,
                    0.60374887, 1.57565229, 1.53664396,
                    0.90983415, 1.8347006, 1.29314073
                }) {}
        };

        //AxE
        template<typename T>
        struct AxE final : public MatrixSpec<T, 4, 3> {
            AxE() : MatrixSpec<T, 4, 3>(
                {
                    1.46062385, 1.08065226, 1.31142159,
                    1.24299907, 0.84351857, 1.55762545,
                    1.58546903, 1.0259953, 1.31735768,
                    1.39336697, 1.37338367, 1.88294645
                }) {}
        };

        //AxF
        template<typename T>
        struct AxF final : public MatrixSpec<T, 4, 3> {
            AxF() : MatrixSpec<T, 4, 3>(
                {
                    0.73330182, 1.19152197, 1.06111172,
                    0.94063057, 1.16477004, 0.85672507,
                    0.75835581, 1.32035649, 1.05796824,
                    0.91646433, 1.2134832, 1.32197355
                }) {}
        };

        //BxD
        template<typename T>
        struct BxD final : public MatrixSpec<T, 4, 3> {
            BxD() : MatrixSpec<T, 4, 3>(
                {
                    1.09656414, 1.53005269, 1.01642557,
                    0.95380702, 2.26177882, 1.97940744,
                    1.00713295, 2.11471452, 1.56904662,
                    0.63050809, 1.14883255, 1.00152504
                }) {}
        };

        //BxE
        template<typename T>
        struct BxE final : public MatrixSpec<T, 4, 3> {
            BxE() : MatrixSpec<T, 4, 3>(
                {
                    1.29671053, 1.41870217, 1.28943944,
                    2.01855454, 1.60029068, 2.0312758,
                    1.69192284, 1.52565261, 2.13546716,
                    1.11718951, 0.92274793, 0.88822019
                }) {}
        };

        //BxF
        template<typename T>
        struct BxF final : public MatrixSpec<T, 4, 3> {
            BxF() : MatrixSpec<T, 4, 3>(
                {
                    0.91272108, 0.84350719, 1.04066765,
                    1.0195946, 1.69625539, 1.6151404,
                    1.08125979, 1.47656676, 1.48878396,
                    0.59696732, 0.80785808, 0.77928281
                }) {}
        };

        //CxD
        template<typename T>
        struct CxD final : public MatrixSpec<T, 4, 3> {
            CxD() : MatrixSpec<T, 4, 3>(
                {
                    1.24773562, 1.99610889, 1.39305208,
                    1.2470057, 1.58257899, 0.94424721,
                    0.10275495, 0.4549841, 0.41543629,
                    1.15144251, 2.21588064, 1.54757002
                }) {}
        };

        //CxE
        template<typename T>
        struct CxE final : public MatrixSpec<T, 4, 3> {
            CxE() : MatrixSpec<T, 4, 3>(
                {
                    1.73856551, 1.61180126, 1.84231481,
                    1.38184031, 1.45286049, 1.39334119,
                    0.36970774, 0.25186527, 0.4806143,
                    1.76202759, 1.63029386, 2.27200288
                }) {}
        };

        //CxF
        template<typename T>
        struct CxF final : public MatrixSpec<T, 4, 3> {
            CxF() : MatrixSpec<T, 4, 3>(
                {
                    1.25558444, 1.3022273, 1.28820199,
                    1.15145681, 0.887594, 0.96794584,
                    0.16280181, 0.38391966, 0.34311691,
                    1.24046149, 1.5115763, 1.51459212
                }) {}
        };
        
        //GxA
        template<typename T>
        struct GxA final : public MatrixSpec<T, 3, 4> {
            GxA() : MatrixSpec<T, 3, 4>(
                {
                    0.99852682, 1.93159335, 1.19698122, 1.01579199,
                    0.6034356, 1.60909251, 0.70240536, 0.87260915,
                    0.26052839, 0.71623363, 1.01532735, 0.80109169
                }) {}
        };

        //GxB
        template<typename T>
        struct GxB final : public MatrixSpec<T, 3, 4> {
            GxB() : MatrixSpec<T, 3, 4>(
                {
                    1.26904172, 1.14893368, 1.73435776, 1.31943666,
                    1.05070032, 1.12572687, 1.41393079, 0.90642337,
                    0.73951731, 0.53859579, 0.59719382, 0.43138431
                }) {}
        };

        //GxC
        template<typename T>
        struct GxC final : public MatrixSpec<T, 3, 4> {
            GxC() : MatrixSpec<T, 3, 4>(
                {
                    0.88921749, 1.15710834, 1.35013629, 1.78068201,
                    0.78965822, 0.73644089, 0.94349581, 1.49626288,
                    0.42412102, 0.79443139, 1.00484514, 1.16112905
                }) {}
        };

        //HxA
        template<typename T>
        struct HxA final : public MatrixSpec<T, 3, 4> {
            HxA() : MatrixSpec<T, 3, 4>(
                {
                    0.82837706, 1.31884613, 0.74859357, 0.54542102,
                    0.7454888, 1.3227884, 1.1004718, 0.8271208,
                    0.94170224, 1.9947771, 0.72822072, 0.81256867
                }) {}
        };

        //HxB
        template<typename T>
        struct HxB final : public MatrixSpec<T, 3, 4> {
            HxB() : MatrixSpec<T, 3, 4>(
                {
                    0.8488368, 0.55036318, 1.20927998, 1.04574881,
                    1.04470168, 0.60503491, 1.17974347, 1.00817384,
                    1.0709378, 1.36573725, 1.80288413, 1.22952125
                }) {}
        };

        //HxC
        template<typename T>
        struct HxC final : public MatrixSpec<T, 3, 4> {
            HxC() : MatrixSpec<T, 3, 4>(
                {
                    0.69973091, 0.82092838, 0.88071628, 1.23145846,
                    0.80550307, 1.05941035, 1.21182368, 1.61270242,
                    0.72780429, 0.78015829, 0.9336102, 1.34046384
                }) {}
        };

        //IxA
        template<typename T>
        struct IxA final : public MatrixSpec<T, 3, 4> {
            IxA() : MatrixSpec<T, 3, 4>(
                {
                    0.784707, 1.60821824, 0.92838664, 0.8587251,
                    0.78140489, 1.474578, 0.55469592, 0.5234039,
                    0.42462232, 1.23901426, 1.02322335, 0.97355549
                }) {}
        };

        //IxB
        template<typename T>
        struct IxB final : public MatrixSpec<T, 3, 4> {
            IxB() : MatrixSpec<T, 3, 4>(
                {
                    1.10500762, 0.91181024, 1.43394973, 1.08201955,
                    0.70079471, 1.02842432, 1.35279859, 0.95096778,
                    0.96263402, 0.99324583, 1.06386025, 0.66860979
                }) {}
        };

        //IxC
        template<typename T>
        struct IxC final : public MatrixSpec<T, 3, 4> {
            IxC() : MatrixSpec<T, 3, 4>(
                {
                    0.85266286, 0.95054434, 1.11930064, 1.61942205,
                    0.39804556, 0.5568532, 0.63780208, 0.7687763,
                    0.57395466, 0.84650295, 1.10146625, 1.39504692
                }) {}
        };
        
        //DxG
        template<typename T>
        struct DxG final : public MatrixSpec<T, 4, 4> {
            DxG() : MatrixSpec<T, 4, 4>(
                {
                    0.81609687, 1.17302739, 0.63952744, 1.55992682,
                    0.43725568, 0.95069608, 0.31031105, 1.21294363,
                    0.63992709, 1.21897612, 0.48028657, 1.49308862,
                    0.93013227, 1.21953031, 0.80888476, 1.02107931
                }) {}
        };

        //DxH
        template<typename T>
        struct DxH final : public MatrixSpec<T, 4, 4> {
            DxH() : MatrixSpec<T, 4, 4>(
                {
                    1.48809823, 1.00569486, 1.05188835, 0.9255507,
                    1.06780273, 0.92935644, 0.88676297, 0.85959662,
                    1.40708833, 1.07925107, 1.04900562, 1.04689494,
                    1.51310376, 0.44890367, 0.49571383, 0.79462972
                }) {}
        };

        //DxI
        template<typename T>
        struct DxI final : public MatrixSpec<T, 4, 4> {
            DxI() : MatrixSpec<T, 4, 4>(
                {
                    0.61885029, 1.15411926, 1.06027519, 1.25054362,
                    0.21144697, 0.87185237, 0.98260299, 1.00640497,
                    0.37927515, 1.09794861, 1.20649964, 1.21280645,
                    0.79194479, 0.89592953, 0.98191391, 0.68467075
                }) {}
        };

        //ExG
        template<typename T>
        struct ExG final : public MatrixSpec<T, 4, 4> {
            ExG() : MatrixSpec<T, 4, 4>(
                {
                    1.00937241, 1.33195764, 0.87347165, 1.14954188,
                    0.77614992, 0.8544555, 0.58167567, 1.65697929,
                    0.87236017, 1.22284997, 0.67347413, 1.75153727,
                    0.77538043, 1.19977703, 0.59596605, 1.61002132
                }) {}
        };

        //ExH
        template<typename T>
        struct ExH final : public MatrixSpec<T, 4, 4> {
            ExH() : MatrixSpec<T, 4, 4>(
                {
                    1.65346064, 0.52570292, 0.57626176, 0.87845044,
                    1.26126842, 1.06925326, 1.19126669, 0.68425327,
                    1.58102521, 1.14529405, 1.20706699, 0.97914243,
                    1.4892722, 1.08405711, 1.11150113, 0.98142503
                }) {}
        };

        //ExI
        template<typename T>
        struct ExI final : public MatrixSpec<T, 4, 4> {
            ExI() : MatrixSpec<T, 4, 4>(
                {
                    0.85405301, 0.99559635, 1.08037941, 0.78332557,
                    0.65278101, 1.1451726, 0.73077148, 1.39474659,
                    0.66476107, 1.2728459, 1.10809958, 1.42449176,
                    0.55423793, 1.17846817, 1.12050763, 1.30522119
                }) {}
        };

        //FxG
        template<typename T>
        struct FxG final : public MatrixSpec<T, 4, 4> {
            FxG() : MatrixSpec<T, 4, 4>(
                {
                    0.49667975, 0.70130241, 0.39220405, 0.91900428,
                    0.67866719, 1.16298664, 0.54700132, 1.20806562,
                    0.45324352, 0.87294469, 0.31674491, 1.27275084,
                    0.79626762, 0.82831395, 0.66011121, 1.11207975
                }) {}
        };

        //FxH
        template<typename T>
        struct FxH final : public MatrixSpec<T, 4, 4> {
            FxH() : MatrixSpec<T, 4, 4>(
                {
                    0.89295174, 0.58279661, 0.61277917, 0.54584328,
                    1.35287293, 0.78701857, 0.77110735, 0.91768729,
                    1.03243232, 0.95883422, 0.94541699, 0.79436912,
                    1.18105159, 0.56233517, 0.67154573, 0.5379182
                }) {}
        };

        //FxI
        template<typename T>
        struct FxI final : public MatrixSpec<T, 4, 4> {
            FxI() : MatrixSpec<T, 4, 4>(
                {
                    0.38241516, 0.68423651, 0.62716608, 0.7323418,
                    0.46608403, 0.94428725, 1.0853372, 0.92772613,
                    0.25094632, 0.89292476, 0.89171112, 1.07257859,
                    0.72446032, 0.85628148, 0.62284938, 0.85031704
                }) {}
        };
    }

    template<typename T, size_t M, size_t N>
    inline constexpr std::array<T, M * N> eye() {
        std::array<T, M * N> I;
        for (size_t m = 0; m < M; m++) {
            for (size_t n = 0; n < N; n++) {
                constexpr size_t idx = m * N + n;
                I[idx] = m == n ? 1 : 0;
            }
        }
        return I;
    }

    using namespace TestMatrices;

    template<typename T, typename U, typename V>
    struct MatmulCase {
        using A = T;
        using B = U;
        using C = V;
    };

    template<typename T>
    using MatmulCases = ::testing::Types<
        MatmulCase<A<T>, A<T>, AxA<T>>,
        MatmulCase<A<T>, B<T>, AxB<T>>,
        MatmulCase<A<T>, C<T>, AxC<T>>,
        MatmulCase<B<T>, A<T>, BxA<T>>,
        MatmulCase<B<T>, B<T>, BxB<T>>,
        MatmulCase<B<T>, C<T>, BxC<T>>,
        MatmulCase<C<T>, A<T>, CxA<T>>,
        MatmulCase<C<T>, B<T>, CxB<T>>,
        MatmulCase<C<T>, C<T>, CxC<T>>,
        MatmulCase<A<T>, D<T>, AxD<T>>,
        MatmulCase<A<T>, E<T>, AxE<T>>,
        MatmulCase<A<T>, F<T>, AxF<T>>,
        MatmulCase<B<T>, D<T>, BxD<T>>,
        MatmulCase<B<T>, E<T>, BxE<T>>,
        MatmulCase<B<T>, F<T>, BxF<T>>,
        MatmulCase<C<T>, D<T>, CxD<T>>,
        MatmulCase<C<T>, E<T>, CxE<T>>,
        MatmulCase<C<T>, F<T>, CxF<T>>,
        MatmulCase<G<T>, A<T>, GxA<T>>,
        MatmulCase<G<T>, B<T>, GxB<T>>,
        MatmulCase<G<T>, C<T>, GxC<T>>,
        MatmulCase<H<T>, A<T>, HxA<T>>,
        MatmulCase<H<T>, B<T>, HxB<T>>,
        MatmulCase<H<T>, C<T>, HxC<T>>,
        MatmulCase<I<T>, A<T>, IxA<T>>,
        MatmulCase<I<T>, B<T>, IxB<T>>,
        MatmulCase<I<T>, C<T>, IxC<T>>,
        MatmulCase<D<T>, G<T>, DxG<T>>,
        MatmulCase<D<T>, H<T>, DxH<T>>,
        MatmulCase<D<T>, I<T>, DxI<T>>,
        MatmulCase<E<T>, G<T>, ExG<T>>,
        MatmulCase<E<T>, H<T>, ExH<T>>,
        MatmulCase<E<T>, I<T>, ExI<T>>,
        MatmulCase<F<T>, G<T>, FxG<T>>,
        MatmulCase<F<T>, H<T>, FxH<T>>,
        MatmulCase<F<T>, I<T>, FxI<T>>
    >;

}

#endif
