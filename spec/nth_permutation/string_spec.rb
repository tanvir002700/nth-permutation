module NthPermutation
  RSpec.describe String, type: :class do
    describe 'NthPermutation::String' do
      context 'Check new method parameter validity' do
        it 'return a new object' do
          expect{ described_class.new 'abc' }.to_not raise_error
        end

        it 'return a TypeError Exception' do
          expect{ described_class.new 1 }.to raise_error(TypeError)
        end

        it 'return a Type Error Exception' do
          expect{ described_class.new 'abcdefghijklmnopqrstuv' }.to raise_error(RangeError)
        end

        it 'return a Range Error Exception' do
          expect{ (described_class.new 'abc').permutation -1 }.to raise_error(RangeError)
        end
      end
    end

    describe 'attribue accessors' do
      context '.str attribue' do
        it 'return main string' do
          expect((described_class.new 'abc').str).to eq('abc')
        end
      end

      context '.length attribue' do
        it 'return length of main string' do
          expect((described_class.new 'abcdef').length).to eq(6)
        end
      end

      context '.possible_permutation attribue' do
        it 'return number of total possible permutation' do
          expect((described_class.new 'abcabcdef').possible_permutation).to eq(45360)
        end
      end
    end

    describe '.permutation' do
      it 'return first permutation' do
        expect((described_class.new 'abc').permutation 1).to eq('abc')
      end

      it 'return 2nd permutation' do
        expect((described_class.new 'abc').permutation 2).to eq('acb')
      end

      it 'return 3rd permutation' do
        expect((described_class.new 'abc').permutation 3).to eq('bac')
      end

      it 'return 4th permutation' do
        expect((described_class.new 'abc').permutation 4).to eq('bca')
      end

      it 'return 5th permutation' do
        expect((described_class.new 'abc').permutation 5).to eq('cab')
      end

      it 'return last permutation' do
        expect((described_class.new 'abc').permutation 6).to eq('cba')
      end

      subject{ described_class.new 'abcdefghijklmnopqrst' }
      it 'return total number of permutation' do
        expect(subject.possible_permutation).to eq(2432902008176640000)
      end

      it 'return the last permutation' do
        expect(subject.permutation 2432902008176640000).to eq('tsrqponmlkjihgfedcba')
      end
    end
  end
end
