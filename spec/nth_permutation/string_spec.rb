module NthPermutation
  RSpec.describe String, type: :class do
    describe 'NthPermutation::String' do
      context 'Check new method parameter validity' do
        it 'return a new object' do
          expect{ String.new 'abc' }.to_not raise_error
        end

        it 'return a TypeError Exception' do
          expect{ String.new 1 }.to raise_error(TypeError)
        end

        it 'return a Type Error Exception' do
          expect{ String.new 'abcdefghijklmnopqrstuv' }.to raise_error(RangeError)
        end
      end
    end
  end
end
