#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "../ProjetTutCppGraphs/Cgraphe.h"
#include "../ProjetTutCppGraphs/Csommet.h"
#include "../ProjetTutCppGraphs/Carc.h"
#include "../ProjetTutCppGraphs/GraphTextFileParser.h"
#include "../ProjetTutCppGraphs/Cexception.h"

#include "../ProjetTutCppGraphs/Cgraphe.cpp"
#include "../ProjetTutCppGraphs/Csommet.cpp"
#include "../ProjetTutCppGraphs/Carc.cpp"
#include "../ProjetTutCppGraphs/GraphTextFileParser.cpp"
#include "../ProjetTutCppGraphs/Cexception.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestGraphProject
{
	TEST_CLASS(UnitTestGraphProjectArc)
	{
	public:
		
		TEST_METHOD(TestClassInit)
		{
			int iDest = 1;
			Carc ARCtest(1);

			Assert::AreEqual(iDest,ARCtest.ARCgetDest());
		}

		TEST_METHOD(TestModificationDest)
		{
			int iDest = 2;
			Carc ARCtest(1);
			ARCtest.ARCModifDest(2);
			Assert::AreEqual(iDest, ARCtest.ARCgetDest());
		}
	};

	TEST_CLASS(UnitTestGraphProjectSommet)
	{
	public:

		TEST_METHOD(TestClassInit)
		{
			int iNum = 1;
			Csommet SOMtest(1);

			Assert::AreEqual(iNum, SOMtest.SOMGetSomNum());

		}


		TEST_METHOD(TestDeleteArrivant)
		{
			Csommet SOMtest(1);
			SOMtest.SOMAddArcArrivant(2);

			SOMtest.SOMDeleteArcArrivant(2);

			Assert::AreEqual(0, SOMtest.SOMGetNbArcArrivant());

		}



		TEST_METHOD(TestDeleteSortant)
		{
			Csommet SOMtest(1);
			SOMtest.SOMAddArcSortant(2);

			SOMtest.SOMDeleteArcSortant(2);

			Assert::AreEqual(0, SOMtest.SOMGetNbArcSortant());

		}


		TEST_METHOD(TestNbArcArrivant)
		{
			Csommet SOMtest(1);
			SOMtest.SOMAddArcArrivant(2);
			SOMtest.SOMAddArcArrivant(3);
			SOMtest.SOMAddArcArrivant(4);

			//SOMtest.SOMDeleteArcArrivant(2);

			Assert::AreEqual(3, SOMtest.SOMGetNbArcArrivant());

		}
		

		TEST_METHOD(TestNbArcSortant)
		{
			Csommet SOMtest(1);
			SOMtest.SOMAddArcSortant(2);
			SOMtest.SOMAddArcSortant(3);
			SOMtest.SOMAddArcSortant(4);

			//SOMtest.SOMDeleteArcSortant(2);

			Assert::AreEqual(3, SOMtest.SOMGetNbArcSortant());

		}

		TEST_METHOD(TestModificationArcArrivantDest)
		{
			Csommet SOMtest(1);
			SOMtest.SOMAddArcArrivant(2);

			Assert::AreEqual(2, SOMtest.SOMgetDestArrivant(0));
			
		}

		TEST_METHOD(TestModificationArcSortantDest)
		{
			Csommet SOMtest(1);
			SOMtest.SOMAddArcSortant(2);

			Assert::AreEqual(2, SOMtest.SOMgetDestSortant(0));

		}


		TEST_METHOD(TestInversionArcSommet)
		{
			Csommet SOMtest(1);
			SOMtest.SOMAddArcSortant(2);


			SOMtest.SOMInverserArcSom();

			Assert::AreEqual(0, SOMtest.SOMGetNbArcSortant());

			Assert::AreEqual(1, SOMtest.SOMGetNbArcArrivant());

		}



	};



	TEST_CLASS(UnitTestGraphProjectGraph)
	{
	public:

		TEST_METHOD(TestClassInit)
		{
			Cgraphe GRAtest;

			Assert::AreEqual(0, GRAtest.GRAGetNbSommets());
			

		}

		TEST_METHOD(TestClassAddSommet)
		{
			Cgraphe GRAtest;

			GRAtest.GRAAddSommet(1);
			GRAtest.GRAAddSommet(2);

			Assert::AreEqual(2, GRAtest.GRAGetNbSommets());


		}

		TEST_METHOD(TestClassDeleteSommet)
		{
			Cgraphe GRAtest;

			GRAtest.GRAAddSommet(1);
			GRAtest.GRADeleteSommet(1);

			Assert::AreEqual(0, GRAtest.GRAGetNbSommets());


		}

		TEST_METHOD(TestClassAddArc)
		{
			Cgraphe GRAtest;

			try {
				GRAtest.GRAAddSommet(1);
				GRAtest.GRAAddSommet(2);
				GRAtest.GRAAddArc(1, 2);

				
			}
			catch (Cexception e) {
				Assert::Fail();
			}
			

		}

	};
}
